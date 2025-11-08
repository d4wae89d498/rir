#ifndef RIR_DIAGNOSTIC_H
# define RIR_DIAGNOSTIC_H
# include <stdio.h>
# include <stdbool.h>
# include <sugar.h>
# if __STDC_VERSION__ >= 201112L
#  include <c11/fmt.h>
# endif

#ifndef WS_DIR
# define WS_DIR
#endif 

#ifndef NAME 
# define NAME a.out
#endif

// SOURCES

static char *target_name = stringify_defined(NAME) ;
static char *workspace_dir = stringify_defined(WS_DIR) ;

// GLOBALS

extern int errors;
extern bool colors_enabled;
extern bool debug_enabled;

// COLORS

static const char *BLACK   = "\x1b[30m";
static const char *RED     = "\x1b[31m";
static const char *GREEN   = "\x1b[32m";
static const char *YELLOW  = "\x1b[33m";
static const char *BLUE    = "\x1b[34m";
static const char *MAGENTA = "\x1b[35m";
static const char *CYAN    = "\x1b[36m";
static const char *WHITE   = "\x1b[37m";

static const char *BOLD_BLACK   = "\x1b[1;30m";
static const char *BOLD_RED     = "\x1b[1;31m";
static const char *BOLD_GREEN   = "\x1b[1;32m";
static const char *BOLD_YELLOW  = "\x1b[1;33m";
static const char *BOLD_BLUE    = "\x1b[1;34m";
static const char *BOLD_MAGENTA = "\x1b[1;35m";
static const char *BOLD_CYAN    = "\x1b[1;36m";
static const char *BOLD_WHITE   = "\x1b[1;37m";

static const char *RESET = "\x1b[0m";

// IMPLS

// === trace ===
#ifdef TRACE
# if TRACE == 1
#  undef TRACE
#  define TRACE fprintf(stderr, "[TRACE] %s:%d:%s()\n", __FILE__, __LINE__, __func__);
# else
#  undef TRACE
#  define TRACE 
# endif 
#else 
# define TRACE  
#endif

// === common ===
static void diag_print_common(const char *file, int line, const char *func, const char *label, const char *label_color_tty) {
    
    const char *label_color   = colors_enabled ? label_color_tty : "";
    const char *reset = colors_enabled ? RESET : "";
    const char *white = colors_enabled ? BOLD_WHITE : "";
    if (!strncmp(file, workspace_dir, strlen(workspace_dir))) {
        file += strlen(workspace_dir) + 1;
    }
    if (debug_enabled)
       fprintf(stderr, "%s:%i %s() ", file, line, func);
    fprintf(stderr, "%s%s: %s", label_color, label, white);
}

# define rir_print_impl(file, line, func, verb, label, color, ...)\
    if (1) {\
        diag_print_common(file, line, func, label, color);\
        verb(stderr, __VA_ARGS__);\
        fprintf(stderr, "%s\n", RESET);\
    }

// === error ===
# define error(...)\
    if (1) {\
        errors += 1;\
        rir_print_impl(__FILE__, __LINE__, __func__ , fprintf, "error", BOLD_RED, __VA_ARGS__);\
    }
# define fmt_error(...)\
    if (1) {\
        errors += 1;\
        rir_print_impl(__FILE__, __LINE__, __func__ , fmt_printd, "error", BOLD_RED, __VA_ARGS__);\
    }

// === warning ===
# define warning(...)\
        rir_print_impl(__FILE__, __LINE__, __func__ , fprintf, "warning", BOLD_YELLOW, __VA_ARGS__)
# define fmt_warning(...)\
        rir_print_impl(__FILE__, __LINE__, __func__ , fmt_printd, "warning", BOLD_YELLOW, __VA_ARGS__)

// === notice ===
# define notice(...)\
        rir_print_impl(__FILE__, __LINE__, __func__ , fprintf, "notice", BOLD_CYAN, __VA_ARGS__)
# define fmt_notice(...)\
        rir_print_impl(__FILE__, __LINE__, __func__ , fmt_printd, "notice", BOLD_CYAN, __VA_ARGS__)

// === debug ===
# define debug(...)\
    if (debug_enabled) {\
        rir_print_impl(__FILE__, __LINE__, __func__ , fprintf, "debug", BOLD_MAGENTA, __VA_ARGS__);\
    }
# define fmt_debug(...)\
    if (debug_enabled) {\
        rir_print_impl(__FILE__, __LINE__, __func__ , fmt_printd, "debug", BOLD_MAGENTA, __VA_ARGS__);\
    }

#endif // RIR_DIAGNOSTIC_H