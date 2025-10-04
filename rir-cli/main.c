#include "diagnostic.h"
#include <rir.h>
#include <stc/coption.h>
#include <stc/cstr.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char *value;
} Define;

#define T DefineVec, Define
#include <stc/vec.h>

#define T StrVec, char*
#include <stc/vec.h>

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
    c_defer(cstr_drop(&result))
    {
        for (c_each(e, Targets, targets))
            cstr_append_fmt(&result, cli_target_txt, e.ref->second->name, e.ref->second->descr);
        fmt_printd(stdout, cli_usage_txt, cstr_toraw(&result), common_exemples_txt);
    }
}

static void parse_feature_flag(const char *flag) {
    if (!strcmp(flag, "color-diagnostics"))
       ;// SKIP: shall be done first using bellow
    else if (!strcmp(flag, "no-color-diagnostics"))
       ;// SKIP: shall be done first using bellow
    else 
        fmt_error("unknown argument: '-f{}'", flag);
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


static void add_define(DefineVec* defs, const char *arg) {
    size_t pos = strchr(arg, '=') - arg;

    char *key = strndup(arg, pos);
    char *value = strdup(arg + pos + 1);

    Define d = { 
        key,
        value
     };
    DefineVec_push(defs, d);
}

int main(int argc, char **argv) {
    static coption_long  longopts[] = {
        { "target", coption_required_argument, 't' },
        { "help",   coption_no_argument,       'h' },
        { 0 }
    };
    const char *shortopts = "f:D:t:h";
    const char *prog = (argc > 0) ? argv[0] : "rir";
    DefineVec defines = DefineVec_init();
    StrVec paths = StrVec_init();
    colors_enabled = !getenv("NO_COLOR");
    setup_targets();
    char *target = strdup("print"); // TODO: use host as default target
    coption opt = coption_init();
    parse_color_flags(argc, argv);
    int c;
    while ((c = coption_get(&opt, argc, argv, shortopts, longopts)) != -1) {
        switch (c) {
            case 'f':
                parse_feature_flag(opt.arg);
                break;
            case 'D':
                add_define(&defines, opt.arg);
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

    // pupulate StrVec paths 
    int file_count = argc - opt.ind;
    char **files = argv + opt.ind;
    if (file_count <= 0)
        error("no input files");
    for (int i = 0; i < file_count; i += 1) 
        StrVec_push(&paths, files[i]);

    // continue if no error
    if (errors)
        exit(1);
    fmt_debug("choosen target: {}", target);
    for(c_each(i, DefineVec, defines))
        fmt_debug("#define {}={}", i.ref->name, i.ref->value);
    for(c_each(i, StrVec, paths))
        fmt_debug("file {}", i.ref[0]);
    // todo: parse and use target result
    return 0;
}