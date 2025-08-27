#ifndef RIR_RET_H
# define RIR_RET_H
# include <rir.h>

typedef struct ret
{
    terminator_base
    expr    *value;
} ret;

void Ret(expr *value) {
    terminator *self = new(ret, .value = value, .terminator_type = "ret");
    terminator(self);
};

# define ret(x) Ret(x)

#endif // RIR_RET_H