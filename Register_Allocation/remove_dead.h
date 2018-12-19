#ifndef _REMOVE_DEAD_H_
#define _REMOVE_DEAD_H_
#include "block_design.h"
#include "gen_kill_block.h"
#include "liveness_analysis.h"
#include "peep_opti.h"
void identify_dead_code(tnode *t);
void dead_code_transverse_back(Block *t_block, tnode *t);
void dead_code_analysis(Block *t_block);
static bool check_if_block_transversed(Block *t_block);
#endif