#ifndef _LIVENESS_ANALYSIS_H
#define _LIVENESS_ANALYSIS_H

#include "block_design.h"
#include "gen_kill_block.h"

void find_in_out(tnode *t);
void transverse_blocks_backwards(Block *t_block, tnode *t);
void assign_gen_to_in();
void in_out_analysis(Block *t_block);
void free_symnode_struct(struct symtabnode_struct **gkio);
void copy_symnode_block(struct symtabnode_struct **src,struct symtabnode_struct **dest);
bool compare_symnode_struct(struct symtabnode_struct **src, struct symtabnode_struct **dest);
bool compare_blocks();
void print_in_out_analysis(Block *t_block);
void copy_symnode_struct(struct symtabnode_struct **src, struct symtabnode_struct **dest);
static bool check_if_block_transversed(Block *t_block);
#endif