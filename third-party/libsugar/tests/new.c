#include <sugar.h>
#include <assert.h>

int main(void) {
    int *i = new(int, 5);

    assert(*i == 5);

    free(i);

    return 0;
}