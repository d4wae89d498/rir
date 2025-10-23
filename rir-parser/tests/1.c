#include "../parser.h"

char src[] = {
#embed  "1.rir"
, 0
};

int main()
{
    // TEST 1.
    parse_str(src);

    return 0;
}