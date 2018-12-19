/*********************************************************************
*                                                                    *
*                   CSC 553 : A Yacc grammar for C--                 *
*                                                                    *
*********************************************************************/

/*
 * parser.y
 *
 * Author: Saumya Debray
 */

%{
#include "global.h"
#include "error.h"
#include "syntax-tree.h"
#include "symbol-table.h"

extern int yylex();
extern void yyerror();
// extern void printSyntaxTree(tnode *t, int n, int depth);
 extern void enter_function(tnode *t, char *fun_name);

  /*
   * struct treenode *currfnbodyTree is set to point to
   * the syntax tree for the body of the current function
   * at the end of each function.  
   * NOTE: the syntax tree MUST be used before CleanupFnInfo()
   * is called at the end of the function.  After that the
   * symbol table entries for the local variables of the
   * function will go away, leaving dangling pointers from
   * the syntax tree.
   */
struct treenode *currfnbodyTree = NULL;

extern char *id_name, *yytext;
 extern int ival;
extern int linenum;
char *fnName;
symtabnode *stptr, *currFun;
int CurrType, EltType, fnRetType;
int CurrScope = Global;
llistptr lptr;
bool is_extern;
int errstate = 0;
%}

%union {
  tnptr tptr;
  llistptr idlistptr;
  char *chptr;
  int nval;
}

%token ID                                      /* IDs */
%token <nval> INTCON CHARCON                   /* constants */ 
%token STRINGCON                               /* constants */
%token CHAR INT VOID EXTERN                    /* types */
%token IF ELSE WHILE FOR RETURN                /* statements */
%token AND OR EQ NEQ LE GE '<' '>' '=' '!'     /* operators   */
%token '+' '-' '*' '/' ',' '(' ')' ';' '{' '}' /* operators   */
%token '[' ']'

%type <chptr> Ident;
%type <nval> type, ArraySize;
%type <idlistptr> parm_types, nonempty_parm_type_list, parm_type_decl;
%type <tptr> stmt_list, stmt, compound_stmt, optional_else,
   optional_assgt, optional_expr, optional_boolexp,
   assignment, boolexp, expr, fun_call, proc_call,
   variable, expr_list;

%left  AND OR
%left  '+' '-'
%left  '*' '/'

%start     prog

%%

prog 
  : /* var decl */ prog type id_list ';'
  | /* function prototypes */ 
    prog type Ident '(' SetFnInfo parm_types ')' fprotRest
  | /* function prototypes */ 
    prog Extern type Ident '(' SetFnInfo parm_types ')' fprotRest
  | /* function definition */ 
    prog type Ident '(' SetFnInfo parm_types  ')' '{' 
    { currFun = SymTabRecordFunInfo(false);} 
    var_decls stmt_list '}' 
    { 
      currfnbodyTree = AppendReturn($11);
      /*
       * At this point, currfnbodyTree points to the syntax tree
       * for the body of the current function.  This can then
       * be traversed for code generation etc.
       */
      
//#ifdef DEBUG
      //printf("@@FUN: %s\n", $3);
      //printf("@@BODY:\n");
       enter_function(currfnbodyTree,$3);
     // printSyntaxTree(currfnbodyTree, 4, 0);
     // printf("-----\n");
//#endif
      CleanupFnInfo(); 
    }
  | /* epsilon */
  ;

Extern : EXTERN { is_extern = true; }

SetFnInfo : { 
	CurrScope = Local; 
	fnRetType = CurrType;
	fnName = id_name;
	lptr = NULL;
  }
  ;

fprotRest 
  : comma { SymTabRecordFunInfo(true); } fprototype SetFnInfo fprotRest
  | ';' { SymTabRecordFunInfo(true); CleanupFnInfo(); }
  ;

fprototype
: Ident '(' parm_types ')' { 
    stptr = SymTabLookupAll($1);
    if (stptr != NULL) {
      errmsg("%s multiply declared", $1);
    }
    else {
      CurrScope = Local;
    }
 }
  ;
  
parm_types
  : VOID { $$ = NULL; }
  | nonempty_parm_type_list { $$ = $1; }
  ;

nonempty_parm_type_list
: nonempty_parm_type_list comma parm_type_decl { lptr = Attach($1, $3); $$ = lptr; }
  | parm_type_decl { $$ = $1; }
  ;

parm_type_decl
: type Ident { lptr = NewListNode($2, $1, false); $$ = lptr; }
| type Ident '['']'  { lptr = NewListNode($2, $1, true); $$ = lptr; }
  ;


type 
  : INT  { $$ = CurrType = t_Int; }
  | CHAR  { $$ = CurrType = t_Char; }
  | VOID  { $$ = CurrType = t_None; }
  ;

var_decls
  : var_decls var_decl ';'
  |    /* epsilon */ 
  ;

var_decl
  : type id_list
  ;

id_list
  : id_list comma {yyerrok;} id_decl
  | error comma {yyerrok;} id_decl
  | id_decl
  ;

id_decl
: Ident { 
    if (CurrType == t_None) {
      errmsg("Illegal type [void] for variable %s", id_name);
    }
    else {
      stptr = SymTabInsert(id_name, CurrScope); 
      stptr->type = CurrType;
      stptr->formal = stptr->is_extern = false;
      stptr->elt_type = t_None;
    }
  }
| Ident '[' ArraySize ']' { 
    if (CurrType == t_None) {
      errmsg("Illegal type [void] for variable %s", id_name);
    }
    else {
      stptr = SymTabInsert(id_name, CurrScope);
      stptr->type = t_Array;
      stptr->formal = false;
      stptr->elt_type = CurrType;
      stptr->num_elts = $3;
    }
  }
  ;

ArraySize : INTCON { $$ = atoi(yytext); }
;

stmt_list
  : stmt stmt_list { $$ = mkListNode($1, $2); }
  | { $$ = NULL; }   /* epsilon */ 
  ;

stmt
  : IF '(' boolexp ')' stmt optional_else {
      if ($3->etype != t_Bool && $3->etype != t_Error) {
        errmsg("conditional does not have Boolean type");
      }
      $$ = mkSTNode(If, t_None, $3, $5, $6, NULL);
    }
  | WHILE '(' boolexp ')' stmt {
      if ($3->etype != t_Bool && $3->etype != t_Error) {
        errmsg("conditional does not have Boolean type");
      }
      $$ = mkSTNode(While, t_None, $3, $5, NULL, NULL);
    }
  | FOR '(' optional_assgt semicolon optional_boolexp semicolon optional_assgt ')' stmt {
      if ($5 != NULL && $5->etype != t_Bool && $5->etype != t_Error) {
        errmsg("conditional does not have Boolean type");
      }
      $$ = mkSTNode(For, t_None, $3, $5, $7, $9);
    }
  | RETURN optional_expr semicolon {
      if (currFun->ret_type != t_None) {
	if ($2 == NULL) {
	  errmsg("return with no return value in non-void function");
          $$ = mkErrorNode();
	}
	else if ( !($2->etype == t_Int || $2->etype == t_Char || $2->etype == t_Error) ) {
	  errmsg("illegal return type");
          $$ = mkErrorNode();
	}
	else {
	  $$ = mkSTNode(Return, $2->etype, $2, NULL, NULL, NULL);
	}
      }
      else {
	if ($2 != NULL) {    /* there is a return expression  */
	  errmsg("non-void return expression in function with no return value");
          $$ = mkErrorNode();
	}
	else {
	  $$ = mkSTNode(Return, t_None, NULL, NULL, NULL, NULL);
	}
      }
    }
  | assignment semicolon { $$ = $1; }
  | proc_call  semicolon { $$ = $1; }
  | compound_stmt        { $$ = $1; }
  | ';'                  { $$ = NULL; }
  | error                { $$ = mkErrorNode(); }
  ;
  
/*
 * The only reason we have nonterminals semicolon and comma is to allow 
 * special handling of missing semicolon/comma errors.
 */
semicolon 
  : ';'
  | {errstate = NOSEMICOLON;} error
  ;

comma
  : ','
  | {errstate = NOCOMMA;} error 
  ;

compound_stmt
  : '{' stmt_list '}' { $$ = $2; }
  ;

optional_else
  : ELSE stmt  { $$ = $2; }
  | { $$ = NULL; } /* epsilon */
  ;

optional_assgt
  : assignment { $$ = $1; }
  | { $$ = NULL; }   /* epsilon */
  ;

optional_expr
  : expr  { $$ = $1; }
  |   { $$ = NULL; }  /* epsilon */
  ;

optional_boolexp
  : boolexp { $$ = $1; }
  | { $$ = NULL; }  /* epsilon */
  ;

assignment
: variable '=' expr {
    if ($1->ntype == Error) {
      $$ = $1;
    }
    else if ($3->ntype == Error) {
      $$ = $3;
    }
    else if (!($1->etype == t_Int || $1->etype == t_Char)) {
      errmsg("invalid LHS in assignment");
      $$ = mkErrorNode();
    }
    else if (!($3->etype == t_Int || $3->etype == t_Char)) {
      errmsg("invalid RHS in assignment");
      $$ = mkErrorNode();
    }
    else {
      $$ = mkExprNode(Assg, t_None, $1, $3);
    }
  }
  ;

boolexp 
  : expr EQ expr    { $$ = SynTreeBinExp(Equals, $1, $3); }    
  | expr NEQ expr   { $$ = SynTreeBinExp(Neq, $1, $3); }    
  | expr LE expr    { $$ = SynTreeBinExp(Leq, $1, $3); }
  | expr GE expr    { $$ = SynTreeBinExp(Geq, $1, $3); }
  | expr '<' expr   { $$ = SynTreeBinExp(Lt, $1, $3); }
  | expr '>' expr   { $$ = SynTreeBinExp(Gt, $1, $3); }
  | '!' boolexp     %prec '*' { $$ = SynTreeUnExp(LogicalNot, $2); }
  | boolexp AND boolexp  { $$ = SynTreeBinExp(LogicalAnd, $1, $3); }
  | boolexp OR  boolexp  { $$ = SynTreeBinExp(LogicalOr, $1, $3); }
  | '(' boolexp ')' { $$ = $2; }
  ;

expr
  : '-' expr        %prec '*' { $$ = SynTreeUnExp(UnaryMinus, $2); }
  | expr '+' expr   { $$ = SynTreeBinExp(Plus, $1, $3); }
  | expr '-' expr   { $$ = SynTreeBinExp(BinaryMinus, $1, $3); }
  | expr '*' expr   { $$ = SynTreeBinExp(Mult, $1, $3); }
  | expr '/' expr   { $$ = SynTreeBinExp(Div, $1, $3); }
  | fun_call        { $$ = $1; }
  | variable        { $$ = $1; }
  | '(' expr ')'    { $$ = $2; }        
  | '(' error ')'   { $$ = mkErrorNode(); }    
| INTCON { $$ = mkConstNode(Intcon, t_Int, ival); }
| CHARCON  { $$ = mkConstNode(Charcon, t_Char, ival); }
| STRINGCON  { yytext[strlen(yytext)-1] = '\0'; /* to remove the trailing " */
               $$ = mkStrNode(strdup(yytext+1)); }
  ;

fun_call
  : Ident '(' ')' {
      bool err_occurred = false;
      stptr = SymTabLookupAll($1);
      if (stptr == NULL) {
	err_occurred = true;
        errmsg("%s undeclared", $1);
      }
      else {
        if (stptr->type != t_Func) {
	  err_occurred = true;
	  errmsg("%s is not a function", $1);
        }
        else {
	  err_occurred = !ActualsMatchFormals(stptr, NULL);
        }
      }

      if (!err_occurred) {
	$$ = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, NULL);
      }
      else {
	$$ = mkErrorNode();
      }
    }
  | Ident '(' expr_list ')' {
      bool err_occurred = false;
      stptr = SymTabLookupAll($1);
      if (stptr == NULL) {
	err_occurred = true;
        errmsg("%s undeclared", $1);
      }
      else if (stptr->type != t_Func) {
	err_occurred = true;
        errmsg("%s is not a function", $1);
      }
      else {
	err_occurred = !ActualsMatchFormals(stptr, $3);
      }

      if (!err_occurred) {
	$$ = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, $3);
      }
      else {
	$$ = mkErrorNode();
      }
    }
  | Ident '(' error ')'  {
      stptr = SymTabLookupAll($1);
      if (stptr == NULL) {
        errmsg("undeclared identifier %s", $1);
      }

      $$ = mkErrorNode();
    }
  ;

proc_call
  : Ident '(' ')' {
      bool err_occurred = false;
      stptr = SymTabLookupAll($1);
      if (stptr == NULL) {
        errmsg("undeclared identifier %s", $1);
        $$ = mkErrorNode();
      }
      else if (stptr->type != t_Func) {
	err_occurred = true;
        errmsg("%s is not a function", $1);
      }
      else if (stptr->ret_type != t_None) {
	err_occurred = true;
	errmsg("non-VOID function %s used in a statement", $1);
      }
      else {
	err_occurred = !ActualsMatchFormals(stptr, NULL);
      }

      if (!err_occurred) {
	$$ = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, NULL);
      }
      else {
	$$ = mkErrorNode();
      }
    }
  | Ident '(' expr_list ')'  {
      bool err_occurred = false;
      stptr = SymTabLookupAll($1);
      if (stptr == NULL) {
        errmsg("undeclared identifier %s", $1);
        $$ = mkErrorNode();
      }
      else if (stptr->type != t_Func) {
	err_occurred = true;
        errmsg("%s is not a function", $1);
      }
      else if (stptr->ret_type != t_None) {
	err_occurred = true;
	errmsg("non-VOID function %s used in a statement", $1);
      }
      else {
	err_occurred = !ActualsMatchFormals(stptr, $3);
      }

      if (!err_occurred) {
	$$ = mkSymTabRefNode(FunCall, stptr->ret_type, stptr, $3);
      }
      else {
	$$ = mkErrorNode();
      }
    }
  | Ident '(' error ')' {
    stptr = SymTabLookupAll($1);
    if (stptr == NULL) {
      errmsg("undeclared identifier %s", $1);
    }

    $$ = mkErrorNode();
  }
  ;

variable
  : Ident  { 
	stptr = SymTabLookupAll($1);
	if (stptr == NULL) {
	  errmsg("Undeclared variable: %s", $1);
	  $$ = mkErrorNode();
	}
	else {
	  $$ = mkSymTabRefNode(Var, stptr->type, stptr, NULL);
	}
    }
  | Ident '[' expr ']' {
	bool err_occurred = false;

	stptr = SymTabLookupAll($1);

	if (stptr == NULL) {
	  errmsg("Undeclared variable: %s", $1);
	  err_occurred = true;
	}
	else if (stptr->type != t_Array) {
	  errmsg("%s not declared as an array", $1);
	  err_occurred = true;
	}
	if ( !($3->etype == t_Int || $3->etype == t_Char) ) {
	  if ($3->etype != t_Error) {
	    errmsg("subscript to array %s must be of type int or char", $1);
	    err_occurred = 1;
	  }
	}

	if (err_occurred) {
	  $$ = mkErrorNode();
	}
	else {
	  $$ = mkSymTabRefNode(ArraySubscript, stptr->elt_type, stptr, $3);
	}
    }
  | Ident '[' error ']' {
	stptr = SymTabLookupAll($1);

	if (stptr == NULL) {
	  errmsg("Undeclared variable: %s", $1);
	}
	else if (stptr->type != t_Array) {
	  errmsg("%s not declared as an array", $1);
	}

	$$ = mkErrorNode();
    }
  ;

expr_list 
  : expr comma expr_list { $$ = mkListNode($1, $3); }
  | expr     { $$ = mkListNode($1, NULL); }            
  ;

Ident : ID { $$ = id_name; } ;

%%

