#include <sugar.h>


static inline void dtor(char **val);

#define T StringStack, char*
#define i_keydrop dtor       // destructor for each element
#define i_keyclone strdup
#include <stc/stack.h>


static inline void dtor(char **val) {
    free(*val);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stc/algorithm.h>
c_sumtype  (StackVal,
    (CharPtr, char*),
    (IRNode, void*),
);



int main(void) {
    StringStack stk = {0};

    StringStack_push(&stk, strdup("hello"));
    StringStack_push(&stk, strdup("world"));

    printf("top: %s\n", *StringStack_top(&stk));

    StringStack_drop(&stk);  // calls free() on every string automatically
}
