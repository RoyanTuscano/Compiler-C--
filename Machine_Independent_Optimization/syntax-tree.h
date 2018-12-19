/*
 * syntax-tree.h
 *
 * Author: Saumya Debray
 */

#ifndef _SYNTAX_TREE_H_
#define _SYNTAX_TREE_H_

#include "symbol-table.h"

typedef enum SyntaxNodeType
{
  Error,
  Intcon,
  Charcon,
  Stringcon,
  Var,
  ArraySubscript,
  Plus,
  UnaryMinus,
  BinaryMinus,
  Mult,
  Div,
  Equals,
  Neq,
  Leq,
  Lt,
  Geq,
  Gt,
  LogicalAnd,
  LogicalOr,
  LogicalNot,
  FunCall,
  Assg,
  Return,
  For,
  While,
  If,
  STnodeList
} SyntaxNodeType;

struct stref
{ // symbol table reference: subscripted expr or function call
  symtabnode *stptr;
  struct treenode *exp;
};

struct expr
{ // unary and binary expressions, and expression lists
  struct treenode *lchild, *rchild;
};

struct stmt
{ // statements
  struct treenode *child0, *child1, *child2, *child3;
};

/**************Royan*****************/



typedef enum Optype{
  Enter_op,
  Call_op,
  Param_op,
  Leave_op,
  Return_op,
  Retrieve_op,
  Assn_op,
  Plus_op,
  BinaryMinus_op,
  Mult_op,
  Div_op,
  Equals_op,
  Neq_op,
  Leq_op,
  Lt_op,
  Geq_op,
  Gt_op,
  LogicalAnd_op,
  LogicalOr_op,
  UnaryMinus_op,
  LogicalNot_op,
Deref_op,
Label_op,
Goto_op,
If_Equals_op,
If_Neq_op,
If_Leq_op,
If_Lt_op,
If_Geq_op,
If_Gt_op,
If_LogicalAnd_op,
If_LogicalOr_op,
NONE_op
}Optype;

typedef enum Operandtype{
  Intcon_operand,
  Stringcon_operand,
  SymtabPtr_operand,
  Charcon_operand,
  Address_operand,
  idLoc_operand,
  Deref_operand,
  NONE
}Operandtype;

typedef struct Oper{
  Operandtype operand_type;
  union{
    int i_const;
    symtabnode *stptr;
    int char_const;
    char *str_const;
  }val;
}Operand;

typedef struct instruction{
  Optype op;
  Operand src1;
  Operand src2;
  Operand dest;
  struct instruction *next; 
}instr;


/************end*********************/

typedef struct treenode
{
  enum SyntaxNodeType ntype; // the node type for a syntax tree node
  int etype;                 // the type of the value of a syntax tree node, once that
                             // node has been evaluated.  For nodes that don't have a
                             // value, e.g., statements, this is set to t_None.
  union {
    int iconst;
    char *strconst;
    struct stref strefNode;
    struct expr exprNode;
    struct stmt stmtNode;
  } val;
  //the code ptr
  instr *code;
  symtabnode *place;
  symtabnode *loc;
  //the place ptr
} tnode, *tnptr;

tnode *mkConstNode(SyntaxNodeType ntype, int etype, int n);
tnode *mkStrNode(char *s);
tnode *mkSymTabRefNode(SyntaxNodeType ntype, int etype, symtabnode *stptr, tnode *t0);
tnode *mkExprNode(SyntaxNodeType ntype, int etype, tnode *e1, tnode *e2);
tnode *mkSTNode(SyntaxNodeType ntype, int etype, tnode *x0, tnode *x1, tnode *x2, tnode *x3);
tnode *mkErrorNode(void);
tnode *mkListNode(tnode *hd, tnode *tl);
tnode *AppendReturn(tnode *t);

bool ActualsMatchFormals(symtabnode *fn, tnode *actuals);
tnode *SynTreeUnExp(SyntaxNodeType ntype, tnode *e1);
tnode *SynTreeBinExp(SyntaxNodeType ntype, tnode *e1, tnode *e2);

#define ConstVal(x) (x)->val.iconst
#define StrVal(x) (x)->val.strconst

#define SymTabPtr(x) (x)->val.strefNode.stptr
#define ExprPtr(x) (x)->val.strefNode.exp

#define LChild(x) (x)->val.exprNode.lchild
#define RChild(x) (x)->val.exprNode.rchild

#define Child0(x) (x)->val.stmtNode.child0
#define Child1(x) (x)->val.stmtNode.child1
#define Child2(x) (x)->val.stmtNode.child2
#define Child3(x) (x)->val.stmtNode.child3

#define ListNode(x) (x)->val.exprNode.lchild
#define ListNext(x) (x)->val.exprNode.rchild

#endif /* _SYNTAX_TREE_H_ */
