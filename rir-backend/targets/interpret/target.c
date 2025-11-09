#include "target.h"
#include "rir.h"

node_visitor *interpret_visitor;

///////////////////////////////////////////////////////////////////////

static void *visit_prog(prog *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    functions_value *f = functions_find(&self->functions, "main").ref;
    if (!f) {
        error("trying to interpret a prog without a main.");
        exit(1);
    }
    return dot(f->second->node, accept, visitor, ctx);
}

static void *visit_expr(expr *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return self->impl.accept(&self->node, visitor, ctx);
}

static void *visit_instr(instr *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return self->impl.accept(&self->node, visitor, ctx);
}

static void *visit_terminator(terminator *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return self->impl.accept(&self->instr.node, visitor, ctx);
}

static void *visit_function(function *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    block *b = self->start;
    return (&b->node)->accept(&b->node, visitor, ctx); 
}

static void *visit_block(block *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    instr *i = self->start;
    long last;
    while (i) {
        last = (long)(&i->node)->accept(&i->node, visitor, ctx); 
        i = i->next;
    }
    return (void*)last;
}

static void *visit_value(value *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    // TODO: store value into an hashmap
    void *result = dot(self->e->node, accept, visitor, ctx); 
    ptrmap_insert(&ctx->ptrmap, self, result);
    return 0;
}

static void *visit_arg(arg *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    // TODO
    return 0;
}

static void *visit_binop(binop *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;

    long l = (long) ptrmap_hit(&ctx->ptrmap, self->left);
    long r = (long) ptrmap_hit(&ctx->ptrmap, self->right);
   
    if (!l)
        error("Trying to interpret a malformed LHS in a binop node.");
    if (!r)
        error("Trying to interpret a malformed RHS in a binop node.");
    if (!l || !r)
        exit(1);

    if (!strcmp(self->type, "add")) {
        return (void*) (long) (l + r);
    } else if (!strcmp(self->type, "mul")) {
        return (void*) (long) (l * r);
    }
    // TODO: continue with others...
    else {
        error("unknown binop");
        exit(1);
    }

    return 0;
}

static void *visit_intlit(intlit *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return (void*)(long long)self->value;
}

static void *visit_strlit(strlit *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return (void*)self->value;
}

static void *visit_resolve(resolve *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    // TODO:: mechanism for import/export table...
    if (!strcmp(self->symbol_name, "printf")) {
        return (void*) &printf;
    }
    // TODO:: more function for toy demo 
    else {
        error("unknown symbol_name '%s'", self->symbol_name);
    }
    return 0;
}

static void *visit_call(call *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    void(*f)() = 0; // TODO: read from temp table


    // need ffi for builtins 

    // for internals : two solutions -> FFI trampoline or special switch ...
    // but FFi Trampoline needed for export table // passing func ptr anyway..

    
    return 0;
}

static void *visit_jump(jump *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    // VISIT block dest
    return 0;
}

static void *visit_ret(ret *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    
    // read and return value from temp table
    void *r =  ptrmap_hit(&ctx->ptrmap, self->value);

    debug("r=%p\n", r);
    return r;
}

static void *visit_when(when *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return 0;
}


static void *visit_var(var *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return 0;
}

static void *visit_deref(deref *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return 0;
}

static void *visit_load(load *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return 0;
}

static void *visit_ref(ref *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return 0;
}

static void *visit_store(store *self, node_visitor *visitor, interpret_ctx *ctx) 
{
    TRACE;
    return 0;
}

//////////////////////////////////////////////////////

node_visitor *interpret_visitor;

void setup_interpret_target(Targets *targets)
{
    TRACE;

    printf("setup interpret target...\n");
    static node_visitor visitor;
    interpret_visitor = &visitor;

    // Create and attach visitor
    visitor = node_visitor_init();

    visitor_method(prog)

    visitor_method(expr)
    visitor_method(instr)
    visitor_method(terminator)

    visitor_method(function)
    visitor_method(block)
    visitor_method(value)
    visitor_method(binop)
    visitor_method(arg)
    visitor_method(intlit)
    visitor_method(strlit)
    visitor_method(resolve)
    visitor_method(call)
    visitor_method(ret)
    visitor_method(when)
    visitor_method(jump)

    visitor_method(var)
    visitor_method(load)
    visitor_method(deref)
    visitor_method(ref)
    visitor_method(store)

    ensure_visitor_completed("interpret", interpret_visitor);


    Targets_emplace(targets, "interpret", new(target, 
        .name = "interpret",
        .descr = "Interpret .",
        .visitor = &visitor
    ));
}