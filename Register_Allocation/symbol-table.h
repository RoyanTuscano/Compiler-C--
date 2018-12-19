/*
 * symbol-table.h
 *
 * Author: Saumya Debray
 */

#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_


#define Global 0
#define Local 1

typedef struct stblnode
{
  char *name;
  int scope;
  bool formal;              /* true if formal, false o/2 */
  int type;                 /* the type of the symbol */
  int elt_type;             /* the type of array elements */
  int num_elts;             /* no. of array elements */
  int ret_type;             /* the return type of a function */
  struct stblnode *formals; /* the list of formals for a function */
  int fn_proto_state;       /* status of prototype definitions for a function */
  bool is_extern;           /* whether or not an ID was declared as an extern */
  int reg_alloc;            //if reg is allocated
  char *reg_name;           //name of the reg
  int freq;
  struct stblnode *next;
} symtabnode;

/*********************************************************************
 *                                                                   *
 *                             Prototypes                            *
 *                                                                   *
 *********************************************************************/

void SymTabInit(int sc);                     // initialize the symbol table at scope sc to empty
symtabnode *SymTabLookup(char *str, int sc); // lookup scope sc
symtabnode *SymTabLookupAll(char *str);      // lookup local first, then global
symtabnode *SymTabInsert(char *str, int sc); // add ident to symbol table
symtabnode *SymTabRecordFunInfo(bool isProto);
void CleanupFnInfo(void);
/*
 * Defugging functions
 */
void printSTNode(symtabnode *stptr);
void DumpSymTabLocal();
void DumpSymTabGlobal();
void DumpSymTab();

/**** added by Roy**/

int local_arg();

typedef struct tempo_stack
{
  char *name;
  int fp_offset;
  symtabnode *stptr;
} temp_stack;

typedef struct global_v
{
  char *name;
  symtabnode *stptr;
} global_var;
int fill_local_stack(temp_stack *t_stack, char *fun_name);
int find_local_var(temp_stack *t_stack, char *name);
int fill_the_globs(global_var *t_global, int offset);
bool check_exist(global_var *t_global, char *name);
int return_all_globes(symtabnode **t_global, char *name);
/*********************************************************************
 *                                                                   *
 *          Functions: states for prototypes and definitions         *
 *                                                                   *
 *********************************************************************/

#define FN_PROTO 0   // prototype seen
#define FN_DEFINED 1 // definition seen

#endif /* _SYMBOL_TABLE_H_ */
