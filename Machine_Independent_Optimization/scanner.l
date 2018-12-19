%x Comment

%{
/*
 *	A scanner for C--
 */
#include "global.h"
#include "syntax-tree.h"
#include "y.tab.h"

extern void *malloc();

static int id_or_keywd(char *s);

char *id_name;
int ival;
int linenum = 1;
%}

letter	    [a-zA-Z]
digit	    [0-9]
alfa	    [a-zA-Z0-9_]
whitesp	    [ \t]
%%
"/*"			BEGIN(Comment);
<Comment>[^*\n]*	;
<Comment>"*"+[^*/\n]*	;
<Comment>\n		linenum++;
<Comment>"*"+"/"	BEGIN(INITIAL);
<Comment><<EOF>>	{fprintf(stderr,
				 "syntax error: EOF inside comment: line %d\n",
				linenum);
			 exit(-1);
			}
{whitesp}*		;
\n			linenum++;
{letter}{alfa}*		return(id_or_keywd(yytext));
{digit}+		{ ival = atoi(yytext); return(INTCON);}
"'"."'"                	{ ival = yytext[1]; return(CHARCON); }
"'"\\n"'"		{ ival = '\n'; return(CHARCON); }
"'"\\0"'"		{ ival = '\0'; return(CHARCON); }
\"[^"\n]*\"		return(STRINGCON);
","			return(',');
"("			return('(');
")"			return(')');
";"			return(';');
"{"			return('{');
"}"			return('}');
"["			return('[');
"]"			return(']');
"="			return('=');
"&&"			return(AND);
"||"			return(OR);
"!"			return('!');
"=="			return(EQ);
"!="			return(NEQ);
"+"			return('+');
"-"			return('-');
"*"			return('*');
"/"			return('/');
"<="			return(LE);
"<"			return('<');
">="			return(GE);
">"			return('>');
.                       return yytext[0];
%%
/* id_or_keywd(s) checks a table of keywords to see if the string s matches
   any of them: if it does, it returns a value depending on the keyword
   (see the file tokdefs.h), otherwise it returns the value corresponding
   to ID.
*/

static struct {
     char *name;
     int val;
    } keywd_entry,
      keywd_table[] = {
       {"char",          CHAR},
       {"int",           INT},
       {"void",          VOID},
       {"extern",	 EXTERN},
       {"if",            IF},
       {"else",          ELSE},
       {"while",         WHILE},
       {"for",           FOR},
       {"return",        RETURN},
      };

static int id_or_keywd(char *s)
{
  int i, nkeywds;

  nkeywds = sizeof(keywd_table) / sizeof(keywd_entry);
  for (i = 0; i < nkeywds; i++) {
    if (!strcmp(s, keywd_table[i].name)) {
      return keywd_table[i].val;
    }
  }

  id_name = strdup(yytext);

  return ID;
}
