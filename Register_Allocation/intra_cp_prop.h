#ifndef _INTRA_CP_PROP_H_
#define _INTRA_CP_PROP_H_

#include "block_design.h"

void cp_prop_task(Block *t_block);
void intra_block_cp_prop(tnode *t);
void start_cp_prop(tnode *t);
bool transverse_var(Block *t_block, instr *t_instr);


#endif