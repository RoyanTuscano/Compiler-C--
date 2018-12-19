#ifndef _CAL_LIVE_RANGE_H_
#define _CAL_LIVE_RANGE_H_

#include "block_design.h"
#include "gen_kill_block.h"
#include "liveness_analysis.h"




typedef struct graph_node
{
    symtabnode *g_node;
    int neighbours;
    int reg_used;
    float spill_cost;
    struct sym_node *adj_head;
    struct graph_node *next_node;
} graph_node;

typedef struct sym_node
{
    graph_node *vertex;
    struct sym_node *next;
} sym_node;

typedef struct graph
{
    int size;
    struct graph_node *g_head;
} graph;

graph_node *g_head;
int graph_size;



bool add_graph_edge(symtabnode *src_node, symtabnode *dest_node, graph_node **src_head);
bool delete_graph_vertex(symtabnode *s_node, graph_node **src_head,int *g_size);
bool add_graph_vertex(symtabnode *s_node, graph_node **src_head,int *g_size);
void print_the_graph(graph_node **src_head, int *g_size);
int copy_the_graph(graph_node **src_head, graph_node **dest_head);
symtabnode *least_neighbours(graph_node **src_head, int reg_num, int *num_neighbours);
graph_node *graph_node_vertex(symtabnode *t_stptr, graph_node **src_head);
int return_reg_allocated(symtabnode *t_stptr, graph_node **src_head);
void print_reg_assigned(graph_node **src_head);
bool check_vertex_exist(symtabnode *s_node, graph_node **src_head);

#endif