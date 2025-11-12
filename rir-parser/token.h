#include <rir.h>
#ifndef TOKEN_H
# define TOKEN_H

// basic token
typedef struct token {
    node base;
    const char *value;
} token;

static token *token_new(const char *str) {
    return new(token, 
        .base.type = "token",
        .base.accept = 0,
        .value = str
    );
}

// heap-allocated token
typedef struct htoken {
    node base;
    char *value;
} htoken;

static htoken *htoken_new(char *str) {
    return new(htoken, 
        .base.type = "htoken",
        .base.accept = 0,
        .value = str
    );
}

///////////////////////////

static void pnode_delete(node **n) {
    node *self = *n;
    if (!strcmp(self->type, "htoken")) {
        free(((htoken*)self)->value);
        free(self);
        return;
    }
    else if (!strcmp(self->type, "token")) {
        free(self);
        return;
    }
    delete_visitor_ctx ctx = {
        .ptrset = ptrset_init()
    };
    arrow(self, accept, delete_visitor, &ctx);
    delete_visitor_flush(&ctx);
}

///////////////////////////

#define i_keydrop pnode_delete
#define i_keyclone 
#define T pnode_stack, node*
#include <stc/stack.h>

#endif // TOKEN_H