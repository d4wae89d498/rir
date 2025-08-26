#ifndef SUGAR_H
# define SUGAR_H
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <stdarg.h>

# define new(T, ...) _new( sizeof(T) , &(T) { __VA_ARGS__ } )
# define ull unsigned long long



static inline void *_new(size_t size, void *content) {
    void *ptr = malloc(size);
    if (ptr) {
        memcpy(ptr, content, size);
    }
    return ptr;
}

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

#endif // SUGAR_H
