#include <stdio.h>
#include <stdarg.h>
#include "global.h"
#include "syntax-tree.h"
#include "y.tab.h"
#include "error.h"

extern int linenum, yychar, errstate;
extern char yytext[], *id_name;

/*********************************************************************
 *                                                                   *
 *             General error-handling urility functions.             *
 *                                                                   *
 *********************************************************************/

void errmsg(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  fprintf(stderr, "ERROR [line %d]: ", linenum);
  vfprintf(stderr, fmt, args);
  fprintf(stderr, "\n");

  va_end(args);
}

/*********************************************************************
 *                                                                   *
 *            Specific error-handling/reporting functions.           *
 *                                                                   *
 *********************************************************************/

void report(int tok_type)
{
  switch (tok_type) {
  case  ID :
    fprintf(stderr, "identifier \"%s\"\n", id_name); 
    break;
  case  INTCON :
    fprintf(stderr, "integer constant \"%s\"\n", yytext); 
    break;
  case  CHARCON :
    fprintf(stderr, "character constant \"%s\"\n", yytext); 
    break;
  case  CHAR :
    fprintf(stderr, "\"char\"\n"); 
    break;
  case EXTERN:
    fprintf(stderr, "\"extern\"\n"); 
    break;
  case  VOID :
    fprintf(stderr, "\"void\"\n"); 
    break;
  case  INT :
    fprintf(stderr, "\"int\"\n"); 
    break;
  case  IF :
    fprintf(stderr, "\"if\"\n"); 
    break;
  case  ELSE :
    fprintf(stderr, "\"else\"\n"); 
    break;
  case  WHILE :
    fprintf(stderr, "\"while\"\n"); 
    break;
  case  FOR :
    fprintf(stderr, "\"for\"\n"); 
    break;
  case  RETURN :
    fprintf(stderr, "\"return\""); 
    break;
  case  AND :
    fprintf(stderr, "\"&&\"\n"); 
    break;
  case  OR :
    fprintf(stderr, "\"||\"\n"); 
    break;
  case  EQ :
    fprintf(stderr, "\"==\"\n"); 
    break;
  case  NEQ :
    fprintf(stderr, "\"!=\"\n"); 
    break;
  case  LE :
    fprintf(stderr, "\"<=\"\n"); 
    break;
  case  GE :
    fprintf(stderr, "\">=\"\n"); 
    break;
  case  ',' :
  case  '(' :
  case  ')' :
  case  ';' :
  case  '{' :
  case  '}' :
  case  '[' :
  case  ']' :
  case  '=' :
  case  '!' :
  case  '+' :
  case  '-' :
  case  '*' :
  case  '/' :
  case  '<' :
  case  '>' :
    fprintf(stderr, "\"%c\"\n", tok_type); 
    break;
  case '\'' :
    fprintf(stderr, "\"'\"\n");
    break;
  default : fprintf(stderr, "UNKNOWN TOKEN VALUE: %d\n", tok_type);
  }
}

void yyerror(char *s)
{
  switch (errstate) {
  case ORDINARY:
    fprintf(stderr, "%s: line %d, near ", s, linenum);
    report(yychar);
    break;
  case NOCOMMA:
    fprintf(stderr, "%s, line %d: missing \",\"\n", s, linenum);
    errstate = ORDINARY;
    break;
  case NOSEMICOLON:
	  fprintf(stderr, "%s, line %d: missing \";\"\n", s, linenum);
	  errstate = ORDINARY;
	  break;
  case NOLPAREN:
    fprintf(stderr, "%s, line %d: missing \"(\"\n", s, linenum);
    errstate = ORDINARY;
    break;
  case NORPAREN:
    fprintf(stderr, "%s, line %d: missing \")\"\n", s, linenum);
    errstate = ORDINARY;
    break;
  case NORBRACE:
    fprintf(stderr, "%s, line %d: missing \"}\"\n", s, linenum);
    errstate = ORDINARY;
    break;
  }
}

