#ifndef _PRINTASM_H_
#define _PRINTASM_H_

#include "assemcode.h"
#include "insert_reg.h"


void output_print_int(char *name,int vo);
void output_enter(tnode *t,temp_stack *t_stack);
void output_assn(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1);
void output_param(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1);
void output_call(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1);
void output_return(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1);
void output_retrieve(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1);
void output_Binary_operation(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1, int reg_src2, int reg_dest);
void output_unary_operation(tnode *t, instr *t_instr,temp_stack *t_stack,int reg_src1,int reg_dest);
void output_deref_operation(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1, int reg_src2, int reg_dest);
void output_comparison_operation(tnode *t,instr *t_instr,temp_stack *t_stack,int reg_src1, int reg_src2, int reg_dest);
char *comp_operation(t_instr);
void output_string_table();
int check_string(char *name);
int check_temp_stack(char *name, temp_stack *t_stack);
char *comp_operation(instr *t);
void load_reg(Operand t_operand, temp_stack *t_stack,int reg_src);
void store_reg(Operand t_operand, temp_stack *t_stack, int reg_dest, int src_type);

void load_reg_LG(Operand t_operand, temp_stack *t_stack, int reg_src);
void store_reg_LG(Operand t_operand, temp_stack *t_stack, int reg_dest, int src_type);
void stack_or_global(Operand t_operand, temp_stack *t_stack);
void output_the_globs(global_var *t_global,int num);
void print_formals_register(symtabnode *head_sym_node, temp_stack *t_stack);


#endif