#ifndef SUGAR_H
# define SUGAR_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>
# include <ctype.h>

// PURE MACRO THINGS
/////////////

# define stringify_defined2(x) #x
# define stringify_defined(x) stringify_defined2(x)

//////

//

# define dot(A, V, ...) (A).V(&(A), __VA_ARGS__)
# define arrow(A, V, ...) (A)->V(A, __VA_ARGS__)

//

# define new(T, ...) ((T*)(_new( sizeof(T) , &(T) { __VA_ARGS__ } )))
static inline void *_new(size_t size, void *content) {
    void *ptr = malloc(size);
    if (ptr) {
        memcpy(ptr, content, size);
    } else {
        // TODO: error!
    }
    return ptr;
}

//

typedef struct closure
{
    int (*f)(void *);
    void        *ctx;
} closure;

# define closure(F, CTX) new(closure, .f=F, .ctx=CTX)
# define apply(cl) (cl)->f((cl)->ctx)

/////////////////////////////////////////////////////
//         POSIX POLYFILS                          //
/////////////////////////////////////////////////////

# ifndef	__USE_XOPEN2K8
    static inline size_t strnlen(const char *s, size_t maxlen)
    {
        const char *e = memchr(s, '\0', maxlen);
        return e ? (size_t)(e - s) : maxlen;
    }
# endif

# if !((defined __USE_XOPEN_EXTENDED || defined __USE_XOPEN2K8 \
        || (defined __GLIBC_USE && (__GLIBC_USE(LIB_EXT2) || __GLIBC_USE(ISOC2X)))))
    static inline char *strdup(const char *s) {
        if (!s) return NULL;
        size_t len = strlen(s) + 1;
        char *copy = malloc(len);
        if (!copy) return NULL;
        return (char*) memcpy(copy, s, len);
    }
#endif 
# if !(defined __USE_XOPEN2K8 || __GLIBC_USE (LIB_EXT2) || __GLIBC_USE (ISOC2X))
    static inline char *strndup(const char *s, size_t n) {
        if (!s) return NULL;
        size_t len = strnlen(s, n);
        char *copy = malloc(len + 1);
        if (!copy) return NULL;
        memcpy(copy, s, len);
        copy[len] = '\0';
        return copy;
    }
# endif

# if !(defined (__USE_MISC) || __GLIBC_USE (LIB_EXT2))
    static inline int vasprintf(char **strp, const char *fmt, va_list ap) {
        va_list ap_copy;
        va_copy(ap_copy, ap);

        // Determine required length
        int len = vsnprintf(NULL, 0, fmt, ap);
        if (len < 0) {
            va_end(ap_copy);
            return -1;
        }

        char *buf = malloc((size_t)len + 1);
        if (!buf) {
            va_end(ap_copy);
            return -1;
        }

        int ret = vsnprintf(buf, (size_t)len + 1, fmt, ap_copy);
        va_end(ap_copy);

        if (ret < 0) {
            free(buf);
            return -1;
        }

        *strp = buf;
        return ret;
    }

    static inline int asprintf(char **strp, const char *fmt, ...) {
        va_list ap;
        va_start(ap, fmt);
        int ret = vasprintf(strp, fmt, ap);
        va_end(ap);
        return ret;
    }
# endif

///////////////
/// OTHERS ////
///////////////

static int dump_file(FILE *dst, FILE *src) {
    if (fseek(src, 0L, SEEK_SET) != 0)
        return -1;
    char buf[BUFSIZ];
    size_t n;
    while ((n = fread(buf, 1, sizeof buf, src)) > 0) {
        if (fwrite(buf, 1, n, dst) != n)
            return -1;
    }
    if (ferror(src)) 
        return -1;
    if (fflush(dst) != 0) 
        return -1;
    return 0;
}


static void dump_cstr(FILE *dest, const char *s)
{
    for (; *s != '\0'; ++s) {
        unsigned char c = *s;
        switch (c) {
        case '\\': fputs("\\\\", dest); break;
        case '\"': fputs("\\\"", dest); break;
        case '\n': fputs("\\n",  dest); break;
        case '\r': fputs("\\r",  dest); break;
        case '\t': fputs("\\t",  dest); break;
        case '\b': fputs("\\b",  dest); break;
        case '\f': fputs("\\f",  dest); break;
        case '\v': fputs("\\v",  dest); break;
        case '\a': fputs("\\a",  dest); break;
        case '\0': fputs("\\0",  dest); break; /* defensive - won't happen due to loop condition */
        default:
            /* printable ASCII range (space .. ~) */
            if (c >= 0x20 && c <= 0x7e) {
                /* print as-is */
                fputc(c, dest);
            } else {
                /* non-printable or non-ASCII byte: use \xHH */
                /* Using %02x keeps two hex digits (lowercase) */
                fprintf(dest, "\\x%02x", (unsigned) c);
            }
        }
    }
}

// normalize a path that is already not relative,
// but still contains .. or . or //
static char *normalize_path(const char *path) {
    if (!path) return NULL;

    size_t len = strlen(path);
    char *res = malloc(len + 1);
    if (!res) return NULL;

    size_t i = 0, j = 0;
    while (i < len) {
        // Ignore multiple '/'
        if (path[i] == '/' && (j != 0 && res[j-1] == '/')) {
            i++;
            continue;
        }

        // Handle "./"
        if (path[i] == '.' && (i+1 == len || path[i+1] == '/')) {
            i += 1;
            if (i < len && path[i] == '/') i++;
            continue;
        }

        // Handle "../"
        if (path[i] == '.' && i+1 < len && path[i+1] == '.' &&
            (i+2 == len || path[i+2] == '/')) {
            i += 2;
            if (j > 0) {
                // Remove last path component
                j--;
                while (j > 0 && res[j-1] != '/') j--;
            }
            if (i < len && path[i] == '/') i++;
            continue;
        }

        // Copy normal character
        res[j++] = path[i++];
    }

    // Remove trailing '/' except for root
    if (j > 1 && res[j-1] == '/') j--;
    res[j] = '\0';

    return res;
}

#endif // SUGAR_H
