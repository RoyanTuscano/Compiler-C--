#ifndef _BLOCK_DESIGN_H_
#define _BLOCK_DESIGN_H_

#include <ctype.h>
#include "three.h"

typedef enum Block_branch
{
    No_Branch,
    Branch,
    Finish
} Block_branch;

struct bin_child
{
    struct Block_design *l_child;
    struct Block_design *r_child;
};
struct bin_parent
{
    struct Block_design *l_parent;
    struct Block_design *r_parent;
};

struct child
{
    struct Block_design *child;
};

struct symtabnode_struct
{
    symtabnode *kill_gen_in_out;
    struct symtabnode_struct *next;
};
struct symtabnode_set
{
    symtabnode *kill_dest_i;
    symtabnode *gen_src1_i;
    symtabnode *gen_src2_i;
    struct symtabnode_set *next;
};

typedef struct Block_design
{
    int iteration_num;
    enum Block_branch b_type;
    instr *above_head;
    instr *head;
    instr *tail;
    struct symtabnode_set *head_gk_set;     //head of gen and kill set
    struct symtabnode_set *tail_gk_set;
    struct symtabnode_set *instr_gen_kill_set;  ///gen and kill for every instriction
    struct symtabnode_struct *kill;
    struct symtabnode_struct *gen;
    struct symtabnode_struct *in;
    struct symtabnode_struct *out;
    struct symtabnode_struct *prev_in;
    struct symtabnode_struct *prev_out;
    union {
        struct bin_child binary_node;
        struct child child_node;
        //struct bin_parent l_parent
    } val;
    struct Block_design *next;
} Block;

typedef struct leader_sety
{
    instr *curr;
    Block *curr_block;
    struct leader_sety *next;
} leader_set;

Block *block_head;
Block *block_tail;

void begin_live_analysis(tnode *t);
instr *find_the_child(int label_name, tnode *t);
leader_set *check_if_leader(leader_set *t_leader, instr *t_instr);

void identify_all_leaders(leader_set *t_leader, tnode *t);
void print_Block(Block *t_block);
void print_instruction_block(instr *in);
void print_all_Blocks(int print_block);

#define child(x) x->val.child_node.child

#define l_child(x) x->val.binary_node.l_child

#define r_child(x) x->val.binary_node.r_child

#define i_kill_dest(x) x->kill_dest_i
#define i_gen_src1(x) x->gen_src1_i
#define i_gen_src2(x) x->gen_src2_i

#define head_instr(x) x->head;
#define tail_instr(x) x->tail;

#define kill(x) x.kill.kill_gen_in_out
#define gen(x) x.gen.kill_gen_in_out
#define in(x) x.in.kill_gen_in_out
#define out(x) x.out.kill_gen_in_out

#endif