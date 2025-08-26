#ifndef RIR_RET_H
# define RIR_RET_H
# include "./../instr.h"
# include "./../expr.h"

typedef struct ret
{
    instr_base

    expr    *value;
} ret;


static void* Ret_accept() {

}

static instr* Ret(expr *value) {
    return new(ret, 
        .instr_type = "ret", 
        .accept = &Ret_accept
    );
};

#endif // RIR_RET_H