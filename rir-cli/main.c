#include <rir.h>
#include <stc/coption.h>

char man_main_txt[] = {
#embed  "templates/man_main.txt"
,0
};

char man_target_txt[] = {
#embed  "templates/man_target.txt"
,0
};

char common_exemples_txt[] = {
#embed "templates/common_exemples.txt"
,0
};


char cli_usage_txt[] = {
#embed "templates/cli_usage.txt"
,0
};

char cli_target_txt[] = {
#embed "templates/cli_target.txt"
,0
};

////////////////////////

static void usage() {
    cstr result = cstr_init();
    for (c_each(e, Targets, targets))
        cstr_append_fmt(&result, cli_target_txt, e.ref->second->name, e.ref->second->descr);
    fmt_printd(stdout, cli_usage_txt, cstr_toraw(&result), common_exemples_txt);
    cstr_drop(&result);
}

void parse_color_flags(int ac, char **av) {
    int i = 1;
    while (i < ac) {
        if (!strcmp(av[i], "-fcolor-diagnostics"))
            colors_enabled = true;
        else if (!strcmp(av[i], "-fno-color-diagnostics"))
            colors_enabled = false;
        i += 1;
    }
}

static void parse_feature_flag(const char *flag) {
    if (!strcmp(flag, "color-diagnostics"))
       ;// SKIP: shall be done first using parse_color_flags
    else if (!strcmp(flag, "no-color-diagnostics"))
       ;// SKIP: shall be done first using parse_color_flags
    else 
        fmt_error("unknown argument: '-f{}'", flag);
}

typedef struct {
    char *name;
    char *value;
} define;

static define parse_define(const char *arg) {
    size_t pos = strchr(arg, '=') - arg;
    return (define) { 
        .name = strndup(arg, pos),
        .value = strdup(arg + pos + 1)
    };
}

// TODO: parse if debug flag and pass it to libdiag
int main(int argc, char **argv) {
    static coption_long  longopts[] = {
        { "target", coption_required_argument, 't' },
        { "help",   coption_no_argument,       'h' },
        { 0 }
    };
    const char *shortopts = "f:D:t:h";
    coption opt = coption_init();
    int c;

    define defines[argc];
    int defines_count = 0;
    char *target = strdup("print");

    colors_enabled = !getenv("NO_COLOR");
    setup();
    parse_color_flags(argc, argv);
    while ((c = coption_get(&opt, argc, argv, shortopts, longopts)) != -1) {
        switch (c) {
            case 'f':
                parse_feature_flag(opt.arg);
                break;
            case 'D':
                defines[defines_count++] = parse_define(opt.arg);
                break;
            case 't':
                free(target);
                target = strdup(opt.arg);
                break;
            case 'h':
                usage();
                return 0;
            case '?':
                fmt_error("unknown argument: '{}'", opt.arg);
            default:
        }
    }

    // check target
    auto result = Targets_find(&targets, target);
    if (!result.ref)
        fmt_error("unknown target: '{}'", target);

    // get files
    int files_count = argc - opt.ind;
    char **files = argv + opt.ind;
    if (files_count <= 0)
        error("no input files");

    // continue if no error
    if (errors)
        exit(1);
    fmt_debug("choosen target: {}", target);
    for(int i = 0; i < defines_count; i += 1)
        fmt_debug("#define {}={}", defines[i].name, defines[i].value);
    for(int i = 0; i < files_count; i += 1)
        fmt_debug("file {}", files[i]);

    // todo: parse and use target result to produce output
    
    return 0;
}