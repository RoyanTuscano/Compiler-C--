/*
 * protos.h
 *
 * Author: Saumya Debray
 */
#ifndef _PROTOS_H_
#define _PROTOS_H_

#include "syntax-tree.h"

/*********************************************************************
 *                                                                   *
 *                   SYNTAX TREE ACCESSOR FUNCTIONS                  *
 *                                                                   *
 *********************************************************************/

/* returns the integer value for an Intcon node. */
int stIntcon(tnode *t);

/* returns the integer value for a Charcon node. */
int stCharcon(tnode *t);

/* returns the string for a Stringcon node. */
char *stStringcon(tnode *t);

/* returns the symbol table entry for a Var node. */
symtabnode *stVar(tnode *t);

/* returns the symbol table entry of the array for an ArraySubscript node. */
symtabnode *stArraySubscript_Array(tnode *t);

/* returns the syntax tree of the subscript expression for an ArraySubscript 
   node. */
tnode *stArraySubscript_Subscript(tnode *t);

/* returns the syntax tree for the first operand of a binary operand node. */
tnode *stBinop_Op1(tnode *t);

/* returns the syntax tree for the second operand for a binary operand node. */
tnode *stBinop_Op2(tnode *t);

/* returns the syntax tree for the operand for a unary operand node.
 */
tnode *stUnop_Op(tnode *t);

/* returns the symbol table entry of the function being called for a 
   FunCall node. */
symtabnode *stFunCall_Fun(tnode *t);

/*
 * , returns a pointer to the
 * syntax tree node for the argument list of the call for a FunCall node.
 */
tnode *stFunCall_Args(tnode *t);

/* returns the syntax tree of the LHS for an Assg node. */
tnode *stAssg_Lhs(tnode *t);

/* returns the syntax tree of the RHS for an Assg node. */
tnode *stAssg_Rhs(tnode *t);

/* returns the syntax tree of the expression whose value is to be returned
   for a Return node. */
tnode *stReturn(tnode *t);

/* returns the syntax tree of the initialization stmt of a For node. */
tnode *stFor_Init(tnode *t);

/* returns the syntax tree of the test expression of a For node. */
tnode *stFor_Test(tnode *t);

/* returns the syntax tree of the update statement of a For node. */
tnode *stFor_Update(tnode *t);

/* returns the syntax tree of the body of a For node. */
tnode *stFor_Body(tnode *t);

/* returns the syntax tree of the test of a While node. */
tnode *stWhile_Test(tnode *t);

/* returns the syntax tree of the body of a While node. */
tnode *stWhile_Body(tnode *t);

/* returns the syntax tree of the test of an If node. */
tnode *stIf_Test(tnode *t);

/* returns the syntax tree of the then-part of an If node. */
tnode *stIf_Then(tnode *t);

/* returns the syntax tree of the else-part of an If node. */
tnode *stIf_Else(tnode *t);

/* returns the syntax tree at the head of the list for a STnodeList node. */
tnode *stList_Head(tnode *t);

/* returns the syntax tree at the tail of the list for a STnodeList node. */
tnode *stList_Rest(tnode *t);

#endif /* _PROTOS_H_ */
