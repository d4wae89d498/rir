```C
#include <stdio.h>
#include <ffi.h>

// A normal C function we want to call from our interpreter
int add(int a, int b) {
    return a + b;
}

int main() {
    ffi_cif cif;
    ffi_type *arg_types[2];
    void *arg_values[2];
    int a, b, result;

    // Prepare types
    arg_types[0] = &ffi_type_sint;
    arg_types[1] = &ffi_type_sint;

    // Prepare CIF
    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_sint, arg_types) != FFI_OK) {
        fprintf(stderr, "ffi_prep_cif failed\n");
        return 1;
    }

    // Set arguments
    a = 5;
    b = 9;
    arg_values[0] = &a;
    arg_values[1] = &b;

    // Call C function
    ffi_call(&cif, FFI_FN(add), &result, arg_values);

    printf("Script → C result: %d\n", result);
    return 0;
}
```