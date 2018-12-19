#include "global.h"
#include "symbol-table.h"

extern int yydebug;
extern int yyparse();
extern char *O1_optimization;
extern char *O2_optimization;
int status = 0;

int main(int argc, char *argv[])
{
  //printf("Start\n");
  SymTabInit(Global);
  SymTabInit(Local);
  if (argc == 2)
  {
    O1_optimization = argv[1];
  }
  else
  {
    O1_optimization = "garbage";
  }

  if (yyparse() < 0)
  {
    printf("main: syntax error\n");
    status = 1;
  }

  return status;
}
