#ifndef RIR_VISITOR_H
# define RIR_VISITOR_H
# include <rir.h>

#include "./visitors/clone/clone.h"
#include "./visitors/default/default.h"
//#include "./visitors/delete/delete.h"
#include "./visitors/print/print.h"


static void setup_visitors(void)
{
    setup_clone_visitor();
    setup_default_visitor();
//    setup_delete_visitor();
    setup_print_visitor();
}

#endif