#ifndef _GEN_KILL_BLOCK_H_
#define _GEN_KILL_BLOCK_H_
#include "block_design.h"

void find_gen_kill(tnode *t);
void transverse_backwards(Block *t_block, instr *t_instr);
void gen_kill_instruction(Block *t_block, instr *t_instr);
void generator(Block *t_block, symtabnode *dest, symtabnode *src1, symtabnode *src2);
void killer(Block *t_block, symtabnode *dest, symtabnode *src1, symtabnode *src2);
void add_var_in_gkio(struct symtabnode_struct **gkio, symtabnode *var);
void min_var_in_gkio(struct symtabnode_struct **gkio, symtabnode *var);
void print_gen_kill(struct symtabnode_struct **gkio);
void transverse_for_gen_kill(Block *t_block, struct symtabnode_set *t_instr_kg);
void complete_gen_kill(Block *t_block);
#endif