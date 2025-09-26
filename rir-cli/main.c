/* rir_main.c
 * A simple CLI "main" implementing the behaviour described in the provided man page.
 *
 *
 * This is currently a CLI front-end stub — the actual compilation/interpretation
 * backends are left as TODOs for now.
 */

#include <rir.h>

////////////////////////

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

typedef struct {
    char *name;
    char *value; /* may be NULL */
} Define;


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

static void add_define(Define **defs, size_t *count, const char *arg) {
    char *eq = strchr(arg, '=');
    Define d;
    if (eq) {
        size_t nlen = (size_t)(eq - arg);
        d.name = malloc(nlen + 1);
        if (!d.name) { perror("malloc"); exit(2); }
        memcpy(d.name, arg, nlen);
        d.name[nlen] = '\0';
        d.value = strdup(eq + 1);
    } else {
        d.name = strdup(arg);
        d.value = NULL;
    }

    Define *tmp = realloc(*defs, (*count + 1) * sizeof(Define));
    if (!tmp) { perror("realloc"); exit(2); }
    *defs = tmp;
    (*defs)[*count] = d;
    (*count)++;
}

int main(int argc, char **argv) {
    setup_targets();
    const char *prog = (argc > 0) ? argv[0] : "rir";

    static struct option longopts[] = {
        { "target", required_argument, NULL, 't' },
        { "help",   no_argument,       NULL, 'h' },
        { NULL, 0, NULL, 0 }
    };

    const char *shortopts = "D:t:h";

    char *target = NULL;
    Define *defines = NULL;
    size_t defines_count = 0;

    int opt;
    while ((opt = getopt_long(argc, argv, shortopts, longopts, NULL)) != -1) {
        switch (opt) {
            case 'D':
                add_define(&defines, &defines_count, optarg);
                break;
            case 't':
                free(target);
                target = strdup(optarg);
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

    int file_count = argc - optind;
    char **files = argv + optind;

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
        printf("Target don't exist. Type: rir -h to list em.\n");
    }

    return 0;
    /*

    TODO: replace bellow using automatically built targets

    // Validate supported targets and extract optional data
    bool target_ok = false;
    char *elf_out = NULL;

    if (strcmp(target, "print") == 0) {
        target_ok = true;
    } else if (strcmp(target, "interpret-ffi") == 0) {
        target_ok = true;
    } else if (strcmp(target, "linux-x86_32-jit") == 0) {
        target_ok = true;
    } else if (strncmp(target, "linux-x86_32-elf", 17) == 0) {
        char *col = strchr(target, ':');
        if (col && *(col + 1) != '\0') {
            elf_out = strdup(col + 1);
            target_ok = true;
        } else {
            fprintf(stderr, "error: linux-x86_32-elf requires an output filename (e.g. --target=linux-x86_32-elf:out.o)\n");
            target_ok = false;
        }
    } else {
        target_ok = false;
    }

    if (!target_ok) {
        fprintf(stderr, "error: unrecognized or invalid target: %s\n", target);
        return 2;
    }

    // For now we only stub the behaviour described in the man page.
    printf("rir: files to process (%d):\n", file_count);
    for (int i = 0; i < file_count; ++i) printf("  %s\n", files[i]);

    printf("rir: selected target: %s\n", target);
    if (elf_out) printf("rir: elf output file: %s\n", elf_out);

    if (defines_count) {
        printf("rir: %zu defines:\n", defines_count);
        for (size_t i = 0; i < defines_count; ++i) {
            printf("  %s", defines[i].name);
            if (defines[i].value) printf("=%s", defines[i].value);
            printf("\n");
        }
    }

    // Simulate actions
    if (strcmp(target, "print") == 0) {
        printf("[stub] would dump the internal IR after processing these files.\n");
    } else if (strcmp(target, "interpret-ffi") == 0) {
        printf("[stub] would interpret the IR with FFI support.\n");
    } else if (strcmp(target, "linux-x86_32-jit") == 0) {
        printf("[stub] would JIT-compile and execute the code on 32-bit Linux (host must support it).\n");
    } else if (elf_out) {
        printf("[stub] would generate 32-bit Linux ELF object: %s\n", elf_out);
    }

    // cleanup 
    free(target);
    free(elf_out);
    for (size_t i = 0; i < defines_count; ++i) {
        free(defines[i].name);
        free(defines[i].value);
    }
    free(defines);
    */
    return 0;
}