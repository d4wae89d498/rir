#include <rir.h>
#include <stc/coption.h>
#include <stc/cstr.h>

typedef struct {
    char *name;
    char *value;
} Define;

#define T DefineVec, Define
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

static void usage(FILE *out, const char *progname) {
    cstr result = cstr_init();
    c_defer(cstr_drop(&result))
    {
        for (c_each(e, Targets, targets))
            cstr_append_fmt(&result, cli_target_txt, e.ref->second->name, e.ref->second->descr);
        fprintf(out, cli_usage_txt, cstr_toraw(&result), common_exemples_txt);
    }
}

static void version(FILE *out) {
    fprintf(out, "rir 0.1 — Reflective IR experimental compiler pipelines\n");
    fprintf(out, "Manual: August 2025\n");
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
    const char *shortopts = "D:t:h";
    const char *prog = (argc > 0) ? argv[0] : "rir";
    char *target = NULL;
    DefineVec defines = DefineVec_init();
    setup_targets();
    coption opt = coption_init();
    int c;
    while ((c = coption_get(&opt, argc, argv, shortopts, longopts)) != -1) {
        switch (c) {
            case 'D':
                add_define(&defines, opt.arg);
                break;
            case 't':
                free(target);
                target = strdup(opt.arg);
                break;
            case 'h':
                usage(stdout, prog);
                return 0;
            case '?':
            default:
                //usage(stderr, prog);
                return 2;
        }
    }

    int file_count = argc - opt.ind;
    char **files = argv + opt.ind;

    if (!target) {
        fprintf(stderr, "%s: option required -- 't'\n", prog);
        return 2;
    }

    if (file_count <= 0) {
        fprintf(stderr, "%s: missing one ore multiple files\n", prog);
        return 2;
    }

    printf("choosen target: %s\n", target);

    auto result = Targets_find(&targets, target);

    if (!result.ref) {
        printf("Target \"%s\" don't exist. Type: rir -h to list em.\n", target);
    }

    for(c_each(i, DefineVec, defines)) {
        fmt_println("#define {}={}", i.ref->name, i.ref->value);
    }

    return 0;
}