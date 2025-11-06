#include "diag.h"

int errors = 0;

bool colors_enabled = true;

#ifndef DEBUG
# define DEBUG 0
#endif
bool debug_enabled = DEBUG;