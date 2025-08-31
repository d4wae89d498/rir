#ifndef RIR_RET_H
# define RIR_RET_H
# include <rir.h>

typedef struct ret
{
    terminator terminator;
    expr    *value;
} ret;

void Ret(expr *value) {
    ret *self = new(ret, 
        .terminator = {
            .type = "ret"
        },
        .value = value
    );
    terminator(&self->terminator);
};

# define ret(x) Ret(x)

#endif // RIR_RET_H