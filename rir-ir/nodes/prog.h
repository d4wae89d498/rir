#ifndef RIR_PROG_H
# define RIR_PROG_H
# include "./../node.h"



typedef struct prog {
    node_base    

    StrPtrMap   functions;

} prog;

static prog *Prog() {
    prog *out = new(prog, 
        .functions = StrPtrMap_init()
    );

    return out;
}
# define prog() Prog()




// by default ... we should call main ?

#endif // RIR_PROG_H