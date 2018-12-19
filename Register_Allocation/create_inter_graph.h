#ifndef _CREATE_INTER_GRAPH_H_
#define _CREATE_INTER_GRAPH_H_
#include "cal_live_range.h"

#define print_graph 0
struct symtabnode_struct *head_live_now;

int trans_instr_backwards(struct symtabnode_set *t_gk, Block *t_block);
void reg_alloc_cal_live_range(tnode *t);
void create_interference_graph(tnode *t);
void transverse_the_blocks_backwards(Block *t_block, tnode *t);
bool check_if_the_block_transversed(Block *t_block);
void live_range_block(struct symtabnode_set *t_gk);
void add_live_now_vertices(struct symtabnode_struct **t_node_head);
void create_graph_node_live_range(tnode *t);
void print_gk(struct symtabnode_set *t_gk);
void transverse_instruction_backwards(Block *t_block, instr *t_instr);
void live_range_instruction(Block *t_block, instr *t_instr);
void calculate_cost(tnode *t);
void find_the_loop(instr *temp_instr);
void assign_loop_value(instr *start, instr *end);
#endif