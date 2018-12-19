#ifndef _PEEP_OPTI_H_
#define _PEEP_OPTI_H_

#include <ctype.h>
#include "three.h"

void machine_independent_optimization_jump(tnode *t);
int identify_the_chains(int label_name, tnode *t);
instr *delete_instr(instr *prev, instr *t_instr);
bool check_label(tnode *t, int label_name);

void machine_independent_optimization_const(tnode *t);
void machine_independent_optimization_Bin_Unary(tnode *t);
void machine_independent_optimization_if_goto_con(tnode *t);
void remove_if(tnode *t);



#endif