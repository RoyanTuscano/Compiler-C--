/*
 * symbol-table.c
 *
 * Author: Saumya Debray
 */

#include <assert.h>
#include "global.h"
#include "symbol-table.h"

extern int CurrScope, CurrType, fnRetType;
extern char *fnName;
extern llistptr lptr;
extern bool is_extern;
extern symtabnode *currFun;
//extern struct tempo_stack;

#define HASHTBLSZ 512

static symtabnode *SymTab[2][HASHTBLSZ];

static int hash(char *str)
{
  int n = 0;

  for (; str != NULL && *str != '\0'; str++)
  {
    n += *str;
  }

  return n % HASHTBLSZ;
}

/*
 * SymTabInit(sc)
 *
 * Given a scope sc, initialize the symbol table for that scope by setting
 * all the hash table buckets to NULL.
 */
void SymTabInit(int sc)
{
  int i;

  for (i = 0; i < HASHTBLSZ; i++)
  {
    SymTab[sc][i] = NULL;
  }
}

/*
 * SymTabLookup(str, sc)
 *
 * Look up the string str in the symbol table with scope sc.  If found,
 * return a pointer to the corresponding symbol table node, otherwise
 * return NULL.
 */
symtabnode *SymTabLookup(char *str, int sc)
{
  int hval;
  symtabnode *stptr;

  assert(str);

  hval = hash(str);

  for (stptr = SymTab[sc][hval]; stptr != NULL; stptr = stptr->next)
  {
    if (strcmp(str, stptr->name) == 0)
    {
      return stptr;
    }
  }

  return NULL;
}

/*
 * SymTabLookupAll(str)
 *
 * Look up the string str in the symbol table, starting with the
 * local symbol table and then (if not found) in the global table.
 * If found in either table, return a pointer to the corresponding
 * symbol table node, otherwise return NULL.
 */
symtabnode *SymTabLookupAll(char *str)
{
  symtabnode *stptr;

  assert(str);

  stptr = SymTabLookup(str, Local);

  if (stptr == NULL)
  {
    stptr = SymTabLookup(str, Global);
  }

  return stptr;
}

/*
 * SymTabInsert(str, sc)
 *
 * Add string str to the symbol table with scope sc, and return a
 * pointer to the resulting entry.  This code assumes that str does not
 * already occur in that symbol table; it gives an error message if it does.
 */
symtabnode *SymTabInsert(char *str, int sc)
{
  int hval;
  symtabnode *sptr;

  assert(str != 0);

  sptr = SymTabLookup(str, sc);
  CASSERT(sptr == NULL, ("multiple declarations of %s", str));

  if (sptr != NULL)
    return sptr;

  hval = hash(str);

  sptr = (symtabnode *)zalloc(sizeof(symtabnode));
  sptr->name = str;
  sptr->scope = sc;

  sptr->next = SymTab[sc][hval];
  SymTab[sc][hval] = sptr;

  return sptr;
}

/*
 * SymTabRecordFunInfo(isProto) -- records information in the symbol
 * table about a function.  The argument isProto indicates whether or
 * not this is a prototype.  It communicates with the YACC parser
 * through the globals fnName (the name of the function), fnRetType
 * (the return type), and lptr (a linked list of information about the
 * parameters).  It returns a pointer to the symbol table record of
 * the function.
 */
symtabnode *SymTabRecordFunInfo(bool isProto)
{
  symtabnode *stptr, *func;
  llistptr ltmp;
  symtabnode *formal_list_hd, *formal_list_tl, *formal;
  int n;

  func = SymTabLookup(fnName, Global);
  /*
   * It's only OK to have an entry for this ID in the symbol table already
   * if the previous entry was the prototype and this is the actual
   * definition.
   */
  if (func != NULL)
  {
    if (func->fn_proto_state == FN_PROTO && !isProto)
    {
      /* 
       * the previous definition was a prototype, and this is the
       * real definition.  Check and make sure that the type info
       * in the prototype matches that for the definition.
       */
      formal = func->formals;
      ltmp = lptr;
      n = 1;
      while (formal != NULL && ltmp != NULL)
      {
        if ((formal->elt_type == t_None && !ltmp->is_array && formal->type != ltmp->type) // neither is an array
            || (formal->elt_type != t_None && !ltmp->is_array)                            // formal is array, but not ltmp
            || (formal->elt_type == t_None && ltmp->is_array)                             // ltmp is array, but not formal
            || (formal->elt_type != t_None && ltmp->is_array && formal->elt_type != ltmp->type /* both are arrays */))
        {
          errmsg("function %s: type of argument %d does not match that of prototype",
                 fnName, n);
        }
        n++;
        formal = formal->next;
        ltmp = ltmp->next;
      }
      if (!(formal == NULL && ltmp == NULL))
      {
        errmsg("function %s: no of arguments in definition does not match prototype",
               fnName);
      }
      if (fnRetType != func->ret_type)
      {
        errmsg("function %s: return type does not match that of prototype", fnName);
      }
      if (func->is_extern)
      {
        errmsg("function %s was previously defined as EXTERN", fnName);
      }
    }
    else
    {
      errmsg("Multiple prototypes/definitions for function %s", fnName);
    }
  }
  else
  {
    func = SymTabInsert(fnName, Global);
  }

  func->type = t_Func;
  func->ret_type = fnRetType;

  formal_list_hd = formal_list_tl = NULL;

  for (ltmp = lptr; ltmp != NULL; ltmp = ltmp->next)
  {
    if (CurrType == t_None)
    {
      errmsg("Illegal type [void] for identifier %s", lptr->name);
    }
    else
    {
      stptr = SymTabInsert(ltmp->name, CurrScope);
      stptr->formal = true;
      if (ltmp->is_array)
      {
        stptr->type = t_Array;
        stptr->elt_type = ltmp->type;
      }
      else
      {
        stptr->type = ltmp->type;
        stptr->elt_type = t_None;
      }
      /*
       * Now create a record for the list of formals, and copy over
       * info from stptr.
       */
      formal = zalloc(sizeof(*formal));
      formal->name = stptr->name;
      formal->scope = stptr->scope;
      formal->formal = stptr->formal;
      formal->type = stptr->type;
      formal->elt_type = stptr->elt_type;

      if (formal_list_hd == NULL)
      {
        formal_list_hd = formal_list_tl = formal;
      }
      else
      {
        formal_list_tl->next = formal;
        formal_list_tl = formal;
      }
    }
  } /* for */

  func->formals = formal_list_hd;

  if (isProto && func->fn_proto_state != FN_DEFINED)
  {
    func->fn_proto_state = FN_PROTO;
  }
  else
  {
    func->fn_proto_state = FN_DEFINED;
  }

  func->is_extern = is_extern;
  fnName = NULL;

  return func;
}

/*
 * CleanupFnInfo() -- clean up after processing information
 * for a function prototype/definition.
 */
void CleanupFnInfo(void)
{
  fnName = NULL;
  lptr = NULL;
  currFun = NULL;
  is_extern = false;
  CurrScope = Global;
#if 0
  DumpSymTab();
#endif
  SymTabInit(Local);
}

/*********************************************************************
 *                                                                   *
 *                           for debugging                           *
 *                                                                   *
 *********************************************************************/

void printType(symtabnode *stptr)
{
  symtabnode *formals;
  switch (stptr->type)
  {
  case t_Char:
    printf("C");
    CASSERT(stptr->elt_type == t_None, ("<?!>"));
    break;
  case t_Int:
    printf("I");
    CASSERT(stptr->elt_type == t_None, ("<?!>"));
    break;
  case t_Array:
    switch (stptr->elt_type)
    {
    case t_Char:
      printf("C[%d]", stptr->num_elts);
      break;
    case t_Int:
      printf("I[%d]", stptr->num_elts);
      break;
    default:
      printf("%d?[%d]", stptr->elt_type, stptr->num_elts);
    }
    break;
  case t_Func:
    printf("(");
    if (stptr->formals == NULL)
    {
      printf("void");
    }
    else
    {
      for (formals = stptr->formals; formals; formals = formals->next)
      {
        printType(formals);
        if (formals->next)
        {
          printf(", ");
        }
      }
    }
    printf(") -> ");
    switch (stptr->ret_type)
    {
    case t_Char:
      printf("C");
      break;
    case t_Int:
      printf("I");
      break;
    case t_None:
      printf("void");
      break;
    default:
      printf("??%d", stptr->ret_type);
    }
    break;
  case t_None:
    printf("-");
    break;
  default:
    printf("?!?%d", stptr->type);
  }
}

void printSTNode(symtabnode *stptr)
{
  printf(">> %s: scope = %c%s; type: ",
         stptr->name,
         (stptr->scope == Global ? 'G' : 'L'),
         (stptr->formal == true ? "<formal param>" : ""));
  printType(stptr);
  printf("\n");
}

void DumpSymTabLocal()
{
  int i;
  symtabnode *stptr;

  printf("-------------------- LOCAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next)
    {
      printSTNode(stptr);
    }
  }

  printf("------------------------------------------------------------\n");
}

void DumpSymTabGlobal()
{
  int i;
  symtabnode *stptr;

  printf("-------------------- GLOBAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Global][i]; stptr != NULL; stptr = stptr->next)
    {
      printSTNode(stptr);
    }
  }

  printf("------------------------------------------------------------\n");
}

void DumpSymTab()
{
  DumpSymTabGlobal();
  DumpSymTabLocal();
}

/*********************************************************************/

int local_arg()
{
  int i;
  symtabnode *stptr;
  int j = 0;

  for (i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next)
    {
      //  printSTNode(stptr);
      j++;
    }
  }
  //printf("Value of j %d", j);
  return j;
}

int formal_check(symtabnode *stptr, char *name)
{
  int i = 0;
  symtabnode *t_stptr;
  t_stptr = stptr->formals;
  //  int offset = 8;

  while (t_stptr != NULL)
  {

    if (t_stptr->name == name)
    {
      return (i * 4 + 8);
    }
    i++;
    // offset = offset + 4;
    t_stptr = t_stptr->next;
  }
}

int fill_local_stack(temp_stack *t_stack, char *fun_name)
{
  int j = 0;
  int N_offset = 0;
  symtabnode *fun_stptr = SymTabLookup(fun_name, Global); // lookup scope sc
  //assign all the locals except that have params those will occupy less space than total space
  symtabnode *stptr;
  for (int i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next)
    {
      t_stack[j].name = stptr->name;
      if (stptr->formal == false)
      {
        if (stptr->type == t_Array)
        {
          if (stptr->elt_type == t_Char)
            N_offset = N_offset - (stptr->num_elts) * 1;
          else
            N_offset = N_offset - (stptr->num_elts) * 4;
        }
        else
          N_offset = N_offset - 4;
        if (N_offset % 4 != 0)
          N_offset = N_offset - (N_offset % 4 + 4);
        t_stack[j].fp_offset = N_offset;
      }
      else
      {
        t_stack[j].fp_offset = formal_check(fun_stptr, stptr->name);
      }
      t_stack[j].stptr = stptr;
      j++;
    }
  }

  //search the global for the fun names and find the ptr
  return N_offset;
}

int find_local_var(temp_stack *t_stack, char *name)
{
  int n = local_arg();
  for (int i = 0; i < n; i++)
  {
    if (t_stack[i].name == name)
      return i;
  }
  return -1;
}

int fill_the_globs(global_var *t_global, int offset)
{
  int i;

  symtabnode *stptr;
  for (i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Global][i]; stptr != NULL; stptr = stptr->next)
    {
      //break if the global is a function
      if (stptr->type == t_Func)
        break;
      if (check_exist(t_global, stptr->name) == false)
      {
        t_global[offset].name = stptr->name;
        t_global[offset].stptr = stptr;
        offset++;
      }
    }
  }
  return offset;
}

int return_all_globes(symtabnode **t_global,char *name)
{
  int i;
  int count = 0;
  symtabnode *stptr;

  //printf("-------------------- GLOBAL SYMBOL TABLE --------------------\n");

  for (i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Global][i]; stptr != NULL; stptr = stptr->next)
    {
      t_global[count++] = stptr;
    //  printSTNode(stptr);
    }
  }

  //add the params also here if exist
  for (i = 0; i < HASHTBLSZ; i++)
  {
    for (stptr = SymTab[Local][i]; stptr != NULL; stptr = stptr->next)
    {
      if (stptr->formal == true && t_Array == stptr->type)
      {
        t_global[count++] = stptr;
        
      }
    }
  }

  return count;
}

bool check_exist(global_var *t_global, char *name)
{
  for (int i = 0; t_global[i].stptr != NULL && i < 50; i++)
  {
    if (t_global[i].name == name)
      return true;
  }
  return false;
}