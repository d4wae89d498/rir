```C
#include <stdio.h>
#include <ffi.h>

typedef struct {
    const char *script_name;
} ScriptFunction;

void trampoline_fn(ffi_cif *cif, void *ret, void **args, void *userdata) {
    ScriptFunction *sf = userdata;
    int x = *(int *)args[0];
    int y = *(int *)args[1];

    printf("[C → Script] Calling '%s' with args: %d, %d\n", sf->script_name, x, y);

    // Here you'd invoke your interpreter and get a result
    *(int *)ret = x * y; // dummy implementation
}

int main() {
    ffi_cif cif;
    ffi_type *arg_types[2];
    ffi_closure *closure;
    void *executable_func;
    ScriptFunction sf = { "my_script_func" };

    closure = ffi_closure_alloc(sizeof(ffi_closure), &executable_func);
    arg_types[0] = &ffi_type_sint;
    arg_types[1] = &ffi_type_sint;

    ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_sint, arg_types);
    ffi_prep_closure_loc(closure, &cif, trampoline_fn, &sf, executable_func);

    int (*funcptr)(int, int) = executable_func;
    int result = funcptr(3, 4);

    printf("C → Script result: %d\n", result);

    ffi_closure_free(closure);
    return 0;
}
```