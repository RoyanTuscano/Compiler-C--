/*
 * syntax-tree.c
 * code to construct and manage syntax trees.
 *
 * Author: Saumya Debray
 */
#include <stdarg.h>
#include "error.h"
#include "global.h"
#include "syntax-tree.h"

static char *nodeTypeName[] =
  {
    "Error",
    "Intcon",
    "Charcon",
    "Stringcon",
    "Var",
    "ArraySubscript",
    "Plus",
    "UnaryMinus",
    "BinaryMinus",
    "Mult",
    "Div",
    "Equals",
    "Neq",
    "Leq",
    "Lt",
    "Geq",
    "Gt",
    "LogicalAnd",
    "LogicalOr",
    "LogicalNot",
    "FunCall",
    "Assg",
    "Return",
    "For",
    "While",
    "If",
    "STnodeList"
  };

static void chkNodeType(tnode *t, int expected, char *where);

/*********************************************************************
 *                                                                   *
 *                         ACCESSOR FUNCTIONS                        *
 *                                                                   *
 *********************************************************************/

/*
 * stIntcon(t) -- given an Intcon node, returns the integer value.
 */
int stIntcon(tnode *t)
{
  chkNodeType(t, Intcon, "stIntcon");
  return ConstVal(t);
}

/*
 * stCharcon(t) -- given a Charcon node, returns the integer value.
 */
int stCharcon(tnode *t)
{
  chkNodeType(t, Charcon, "stCharcon");
  return ConstVal(t);
}

/*
 * stStringcon(t) -- given a Stringcon node, returns a pointer to
 * the string.
 */
char *stStringcon(tnode *t)
{
  chkNodeType(t, Stringcon, "stStringcon");
  return StrVal(t);
}

/*
 * stVar(t) -- given a Var node, returns a pointer to its symbol
 * table entry.
 */
symtabnode *stVar(tnode *t)
{
  chkNodeType(t, Var, "stVar");
  return SymTabPtr(t);
}

/*
 * stArraySubscript_Array(t) -- given an ArraySubscript node,
 * returns a pointer to the symbol table entry of the array.
 */
symtabnode *stArraySubscript_Array(tnode *t)
{
  chkNodeType(t, ArraySubscript, "stArraySubscript_Array");
  return SymTabPtr(t);
}

/*
 * stArraySubscript_Subscript(t) -- given an ArraySubscript node,
 * returns a pointer to the syntax tree of the subscript expression.
 */
tnode *stArraySubscript_Subscript(tnode *t)
{
  chkNodeType(t, ArraySubscript, "stArraySubscript_Subscript");
  return ExprPtr(t);
}

/*
 * stBinop_Op1(tnode *t) -- given a syntax tree node t for a binary
 * operator, returns a pointer to the syntax tree node for the the
 * first operand, i.e., the left child.
 */
tnode *stBinop_Op1(tnode *t)
{
  if (t == NULL) {
    fprintf(stderr, "[ERROR] stBinop_Op1: NULL argument\n");
    abort();
  }

  switch (t->ntype) {
  case Plus:
  case BinaryMinus:
  case Mult:
  case Div:
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
  case LogicalAnd:
  case LogicalOr:
    return LChild(t);

  default:
    fprintf(stderr, "[ERROR] stBinop_Op1: expected binary operator, given %s\n",
	    nodeTypeName[t->ntype]);
    abort();
  }
}

/*
 * stBinop_Op2(tnode *t) -- given a syntax tree node t for a binary
 * operator, returns a pointer to the syntax tree node for the the
 * second operand, i.e., the right child.
 */
tnode *stBinop_Op2(tnode *t)
{
  if (t == NULL) {
    fprintf(stderr, "[ERROR] stBinop_Op2: NULL argument\n");
    abort();
  }

  switch (t->ntype) {
  case Plus:
  case BinaryMinus:
  case Mult:
  case Div:
  case Equals:
  case Neq:
  case Leq:
  case Lt:
  case Geq:
  case Gt:
  case LogicalAnd:
  case LogicalOr:
    return RChild(t);

  default:
    fprintf(stderr, "[ERROR] stBinop_Op2: expected binary operator, given %s\n",
	    nodeTypeName[t->ntype]);
    abort();
  }
}

/*
 * stUnop_Op(t) -- given a syntax tree node for a unary operator, returns
 * a pointer to the syntax tree node for the operand.
 */
tnode *stUnop_Op(tnode *t)
{
  if (t == NULL) {
    fprintf(stderr, "[ERROR] stUnop_Op: NULL argument\n");
    abort();
  }

  switch (t->ntype) {
  case UnaryMinus:
  case LogicalNot:
    return LChild(t);

  default:
    fprintf(stderr, "[ERROR] stUnop_Op: expected unary operator, given %s\n",
	    nodeTypeName[t->ntype]);
    abort();
  }
}

/*
 * stFunCall_Fun(t) -- given a FunCall node, returns a pointer to the
 * symbol table entry of the callee, i.e., the function being called.
 */
symtabnode *stFunCall_Fun(tnode *t)
{
  chkNodeType(t, FunCall, "stFunCall_Fun");
  return SymTabPtr(t);
}

/*
 * stFunCall_Args(t) -- given a FunCall node, returns a pointer to the
 * syntax tree node for the argument list of the call.
 */
tnode *stFunCall_Args(tnode *t)
{
  chkNodeType(t, FunCall, "stFunCall_Args");
  return ExprPtr(t);
}

/*
 * stAssg_Lhs(t) -- given an Assg node, returns a pointer to the syntax
 * tree node of the left hand side of the assignment.
 */
tnode *stAssg_Lhs(tnode *t)
{
  chkNodeType(t, Assg, "stAssg_Lhs");
  return LChild(t);
}

/*
 * stAssg_Rhs(t) -- given an Assg node, returns a pointer to the syntax
 * tree node of the right hand side of the assignment.
 */
tnode *stAssg_Rhs(tnode *t)
{
  chkNodeType(t, Assg, "stAssg_Rhs");
  return RChild(t);
}

/*
 * stReturn(t) -- given a Return node, returns a pointer to the syntax
 * tree node of the expression whose value is to be returned.
 */
tnode *stReturn(tnode *t)
{
  chkNodeType(t, Return, "stReturn");
  return Child0(t);
}

/*
 * stFor_Init(t) -- given a For node, returns a pointer to the syntax
 * tree node of its initialization statement.
 */
tnode *stFor_Init(tnode *t)
{
  chkNodeType(t, For, "stFor_Init");
  return Child0(t);
}

/*
 * stFor_Test(t) -- given a For node, returns a pointer to the syntax
 * tree node of its test expression.
 */
tnode *stFor_Test(tnode *t)
{
  chkNodeType(t, For, "stFor_Test");
  return Child1(t);
}

/*
 * stFor_Update(t) -- given a For node, returns a pointer to the syntax
 * tree node of its update statement.
 */
tnode *stFor_Update(tnode *t)
{
  chkNodeType(t, For, "stFor_Update");
  return Child2(t);
}

/*
 * stFor_Body(t) -- given a For node, returns a pointer to the syntax
 * tree node of its body.
 */
tnode *stFor_Body(tnode *t)
{
  chkNodeType(t, For, "stFor_Body");
  return Child3(t);
}

/*
 * stWhile_Test(t) -- given a While node, returns a pointer to the
 * syntax tree node of its test.
 */
tnode *stWhile_Test(tnode *t)
{
  chkNodeType(t, While, "stWhile_Test");
  return Child0(t);
}

/*
 * stWhile_Body(t) -- given a While node, returns a pointer to the
 * syntax tree node of its body.
 */
tnode *stWhile_Body(tnode *t)
{
  chkNodeType(t, While, "stWhile_Body");
  return Child1(t);
}

/*
 * stIf_Test(t) -- given an If node, returns a pointer to the syntax 
 * tree node of its test.
 */
tnode *stIf_Test(tnode *t)
{
  chkNodeType(t, If, "stIf_Test");
  return Child0(t);
}

/*
 * stIf_Then(t) -- given an If node, returns a pointer to the syntax 
 * tree node of its then-part.
 */
tnode *stIf_Then(tnode *t)
{
  chkNodeType(t, If, "stIf_Then");
  return Child1(t);
}

/*
 * stIf_Else(t) -- given an If node, returns a pointer to the syntax 
 * tree node of its else-part.
 */
tnode *stIf_Else(tnode *t)
{
  chkNodeType(t, If, "stIf_Else");
  return Child2(t);
}

/*
 * stList_Head(t) -- given a STnodeList node, i.e., a syntax tree
 * for a linked list of syntax trees, returns a pointer to the syntax 
 * tree at the head of the list.
 */
tnode *stList_Head(tnode *t)
{
  chkNodeType(t, STnodeList, "stList_Head");
  return ListNode(t);
}

/*
 * stList_Rest(t) -- given a STnodeList node, i.e., a syntax tree
 * for a linked list of syntax trees, returns a pointer to the syntax 
 * tree list node for the rest of the list.
 */
tnode *stList_Rest(tnode *t)
{
  chkNodeType(t, STnodeList, "stList_Rest");
  return ListNext(t);
}


/*********************************************************************
 *                                                                   *
 *                       CONSTRUCTOR FUNCTIONS                       *
 *                                                                   *
 *********************************************************************/

/*
 * mkConstNode(n) -- create a syntax tree node for int and char constants.
 */
tnode *mkConstNode(SyntaxNodeType ntype, int etype, int n)
{
  tnode *tn = zalloc(sizeof(*tn));

  tn->ntype = ntype;
  tn->etype = etype;
  ConstVal(tn) = n;

  return tn;
}

/*
 * mkStrNode(s) -- create a syntax tree node for a string constant s
 */
tnode *mkStrNode(char *s)
{
  tnode *tn = zalloc(sizeof(*tn));

  tn->ntype = Stringcon;
  tn->etype = t_Array;
  StrVal(tn) = s;

  return tn;
}

/*
 * mkSymTabRefNode(stptr, t0) -- create a syntax tree node for a symbol table
 * reference stptr plus a pointer to (a list of) syntax tree node t0.
 */
tnode *mkSymTabRefNode(SyntaxNodeType ntype, int etype, symtabnode *stptr, tnode *t0)
{
  tnode *tn = zalloc(sizeof(*tn));

  tn->ntype = ntype;
  tn->etype = etype;

  SymTabPtr(tn) = stptr;
  ExprPtr(tn) = t0; 

  return tn;
}

/*
 * mkExprNode(e1, e2) -- create a syntax tree node for an expression with
 * subexpressions e1 and e2.
 */
tnode *mkExprNode(SyntaxNodeType ntype, int etype, tnode *e1, tnode *e2)
{
  tnode *tn = zalloc(sizeof(*tn));

  tn->ntype = ntype;
  tn->etype = etype;

  LChild(tn) = e1;
  RChild(tn) = e2;

  return tn;
}

/*
 * mkSTNode(x0,x1,x2,x3) -- create a syntax tree node with children 
 * x0, x1, x2, x3.
 */
tnode *mkSTNode(SyntaxNodeType ntype, 
		  int etype, 
		  tnode *x0, 
		  tnode *x1, 
		  tnode *x2, 
		  tnode *x3)
{
  tnode *tn = zalloc(sizeof(*tn));

  tn->ntype = ntype;
  tn->etype = etype;

  Child0(tn) = x0;
  Child1(tn) = x1;
  Child2(tn) = x2;
  Child3(tn) = x3;

  return tn;
}

/*
 * mkErrorNode() -- create a syntax tree node indicating an error of
 * some sort underneath.
 */
tnode *mkErrorNode(void)
{
  return mkSTNode(Error, t_Error, NULL, NULL, NULL, NULL);
}

/*
 * mkListNode(hd, tl) -- create a syntax tree node for a list of syntax
 * tree nodes with first element hd and remainder tl.
 */
tnode *mkListNode(tnode *hd, tnode *tl)
{
  tnode *tn = zalloc(sizeof(*tn));

  tn->ntype = STnodeList;
  tn->etype = t_None;

  LChild(tn) = hd;
  RChild(tn) = tl;

  return tn;
}

/*
 * ActualsMatchFormals(fn, list_of_actuals) -- traverse the lists
 * of actual and formal parameters in a function call to ensure
 * that they match in number and type.
 * Return value: true if they match, false otherwise.
 */
bool ActualsMatchFormals(symtabnode *fn, tnode *actuals)
{
  symtabnode *formals;
  tnode *argNode;
  int t0, t1, n;
  bool err_occurred = false;

  assert(fn);

  for (formals = fn->formals, n = 1;
       formals != NULL && actuals != NULL;
       formals = formals->next, actuals = ListNext(actuals), n++) {
    if (actuals->ntype == Error) continue;

    argNode = ListNode(actuals);

    t0 = formals->type;
    t1 = argNode->etype;

    if (t0 != t_Array && t1 != t_Array    /* neither is an array */
	&& (t0 == t_Int || t0 == t_Char) 
	&& (t1 == t_Int || t1 == t_Char)) {
      continue;
    }
    else if (t0 == t_Array && t1 == t_Array) {     /* both are arrays */
      if ((argNode->ntype == Stringcon && formals->elt_type == t_Char)
	  || formals->elt_type == SymTabPtr(argNode)->elt_type) {
	continue;
      }
      else {
	err_occurred = true;
	errmsg("argument %d: type mismatch between actual and formal parameter [callee: %s]", 
	       n, fn->name);
      }
    }
  }

  if (!(formals == NULL && actuals == NULL)) {
    err_occurred = true;
    errmsg("number of arguments in function call does not match function definition [callee: %s]",
	   fn->name);
  }

  return !err_occurred;
}


/*
 * SynTreeUnExp(op, e1) -- process a syntax tree for unary expressions.
 * If the subexpression has appropriate type, construct a syntax tree
 * for the entire expression and return a pointer to this; otherwise
 * give an error message and return a pointer to an error node.
 */
tnode *SynTreeUnExp(SyntaxNodeType ntype, tnode *e1)
{
  int t1, r1;
  bool err_occurred = false;

  assert(e1 != NULL);

  if (e1->ntype == Error) {
    return e1;
  }

  t1 = e1->etype;

  if (ntype == UnaryMinus) {
    if ( !(t1 == t_Int || t1 == t_Char) ) {
      errmsg("illegal type in arithmetic expression");
      err_occurred = true;
    }
    else {
      r1 = t_Int;
    }
  }
  else if (ntype == LogicalNot) {
    if (t1 != t_Bool) {
      errmsg("illegal type in Boolean expression");
      err_occurred = true;
    }
    else {
      r1 = t_Bool;
    }
  }
  else {
    errmsg("unrecognized binary operator %d\n", ntype);
    err_occurred = true;
  }

  if (err_occurred) {
    return mkErrorNode();
  }
  else {
    return mkExprNode(ntype, r1, e1, NULL);
  }
}


/*
 * SynTreeBinExp(op, e1, e2) -- process a syntax tree for binary expressions.
 * If the subexpressions have appropriate type, construct a syntax tree
 * for the entire expression and return a pointer to this; otherwise
 * give an error message and return a pointer to an error node.
 */
tnode *SynTreeBinExp(SyntaxNodeType ntype, tnode *e1, tnode *e2)
{
  int t1, t2;

  assert(e1 != NULL && e2 != NULL);

  if (e1->ntype == Error) {
    return e1;
  }

  if (e2->ntype == Error) {
    return e2;
  }

  t1 = e1->etype;
  t2 = e2->etype;

  switch (ntype) {
  case Plus:          /* arithmetic */
  case BinaryMinus:   /* arithmetic */
  case Mult:          /* arithmetic */
  case Div:           /* arithmetic */
    if ((t1 == t_Int || t1 == t_Char) && (t2 == t_Int || t2 == t_Char)) {
      return mkExprNode(ntype, t_Int, e1, e2);
    }
    else {
      errmsg("type error in arithmetic expression");
      return mkErrorNode();
    }
    break;

  case Equals:        /* boolean */
  case Neq:           /* boolean */
  case Leq:           /* boolean */
  case Lt:            /* boolean */
  case Geq:           /* boolean */
  case Gt:            /* boolean */
    if ((t1 == t_Int || t1 == t_Char) && (t2 == t_Int || t2 == t_Char)) {
      return mkExprNode(ntype, t_Bool, e1, e2);
    }
    else {
      errmsg("type error in logical expression");
      return mkErrorNode();
    }
    break;

    case LogicalAnd:    /* boolean */
    case LogicalOr:       /* boolean */
    if (t1 == t_Bool && t2 == t_Bool) {
      return mkExprNode(ntype, t_Bool, e1, e2);
    }
    else {
      errmsg("type error in logical expression");
      return mkErrorNode();
    }
    break;

  default:
    errmsg("unrecognized binary operator %d\n", ntype);
    return mkErrorNode();
  }
}

/*
 * AppendReturn() -- given a syntax tree for the body of a function
 * (which is a list of syntax trees for statements), it traverses the
 * list to the end and checks to see whether the last element of the 
 * list is a "return".  If not, it appends a Return node at the end
 * of the list.
 */
tnode *AppendReturn(tnode *t)
{
  tnode *tmp0, *tmp1 = t;

  if (t == NULL) {
    return mkSTNode(Return, t_None, NULL, NULL, NULL, NULL);
  }

  while (tmp1->ntype == STnodeList && ListNext(tmp1) != NULL) {
    tmp1 = ListNext(tmp1);
  }
  /*
   * Check the last tree on the list: if its type is Return, do nothing;
   * else create a list node containing only a Return node, and attach
   * this to the end of the list.
   */    
  if (ListNode(tmp1)->ntype != Return) {
    tmp0 = mkListNode(mkSTNode(Return, t_None, NULL, NULL, NULL, NULL),
		      NULL);
    ListNext(tmp1) = tmp0;
  }

  return t;
}

/*********************************************************************
 *                                                                   *
 *                          HELPER FUNCTIONS                         *
 *                                                                   *
 *********************************************************************/

/* 
 * chkNodeType(t, n, w) -- given a syntax tree node t and a node type n,
 * checks to make sure that t is not NULL and has type n.  If either
 * of these is not true, gives an error message and exits.
 */
static void chkNodeType(tnode *t, int expected, char *where)
{
  if (t == NULL) {
    fprintf(stderr, "[ERROR] %s: NULL argument\n", where);
    abort();
  }

  if (t->ntype != expected) {
    fprintf(stderr, "[ERROR] %s: expected type %s, given %s\n",
	    where,
	    nodeTypeName[expected],
	    nodeTypeName[t->ntype]);
    abort();
  }
  
  return;
}
