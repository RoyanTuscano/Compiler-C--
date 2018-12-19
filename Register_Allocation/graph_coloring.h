#ifndef _GRAPH_COLORING_H_
#define _GRAPH_COLORING_H_
#include "create_inter_graph.h"

graph_node *tmp_g_head;
int tmp_graph_size;
int total_reg;

typedef struct register_var
{
    int reg_num;
    char *name;
} register_alloc;
bool check_reg_num_used[20];
void start_graph_coloring(tnode *t);
void graph_coloring_algo();
bool assign_register();
int alloc_reg(bool *reg_fill);
symtabnode *spill_vertex();
#endif