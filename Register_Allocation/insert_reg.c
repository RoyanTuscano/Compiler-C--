#include "insert_reg.h"

bool check_register(symtabnode *t_stptr, int *reg_num)
{
    bool register_found = false;
    int register_number = -1;
    graph_node *t_g = g_head;
    while (t_g != NULL)
    {
        if (t_g->g_node == t_stptr)
        {
            register_found = true;
            register_number = t_g->reg_used;
            break;
        }
        t_g = t_g->next_node;
    }
    //if the register number is between 0 and 5 allocate it registers between 17 and 23
    register_number = register_number + 5;
    /*
    if (register_number >= 0 && register_number <= 5)
    {
        register_number = register_number + 17;
    }
    */
    *reg_num = register_number;
    return register_found;
}