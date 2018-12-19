#ifndef _THREE_H_
#define _THREE_H_

#include "global.h"
#include "protos.h"
#include "syntax-tree.h"
#include "symbol-table.h"


symtabnode *newtemp(int type);
instr *newinstr(Optype opType, Operandtype src1, Operandtype src2, Operandtype dest);
void enter_function(tnode *t, char *fun_name);
void printUnop(int op);
void printBinop(int op);
void indent(int n);
void print_3_add(tnode *t);
void transverse_tree(tnode *t, int n, int depth);
void print_instruction(instr *in);
void find_operand(Operand t_oprnd);



void free_malloc_t_code(tnode *t, int n, int depth);

void return_inst(tnode *t);
void Intcon_code_assign(tnode *t);
void Charcon_code_assign(tnode *t);

void codegen_funcall(tnode *t);
void codeGen_express(tnode *t, int lr);
void insert_code(struct instruction** t_instr,struct instruction* insert);
void string_code_assign(tnode *t);
void code_gen_binary(tnode *t, Optype LogicalOr_op,int lr);
void code_gen_unary(tnode *t, Optype OP, int lr);
void code_gen_array(tnode *t,int lr);
void code_gen_assg(tnode *t,int lr);
int width(symtabnode *str);
void code_gen_stmt(tnode *t);
instr *newlabel();

void add_param(tnode *t,tnode *tntmp0,int *arg_num);

Operandtype give_operandtype(SyntaxNodeType ntype);
char  *printBinary_op(instr *t);

void code_gen_if_else(tnode *t);
void code_gen_BOOL_EX(tnode *t, instr *L_then, instr *L_else);

void Code_gen_BOOL_MAIN(tnode *t, instr *L_then, instr *L_else);
void code_gen_BOOL_AND(tnode *t, instr *L_then, instr *L_else);
void code_gen_BOOL_OR(tnode *t, instr *L_then, instr *L_else);
void code_gen_BOOL_NOT(tnode *t, instr *L_then, instr *L_else);

void code_gen_while(tnode *t);
void code_gen_for(tnode *t);



Optype find_op(tnode *t);
extern void generate_assm(tnode *t);
void insert_string(char *temp, char *s_name);
static char temp_var[500][8];
static int sym_temp_ref=0;     //for naming the temp variables
//static char op_sign[15][3]={"0","1","2","3","4","5","+","7","8","*","10","11","12","13","14"};

typedef struct string_table{
    char *temp_name;
    char *str_name;
    struct string_table *next;
}str_table;


typedef struct arg_list{
    char *name;
    struct arg_list *prev;
}arg_l;


      


#endif
