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
  O1_optimization="Garbage";
  O2_optimization="Garbage";
  if (argc == 2)
  {
    if (strcmp(argv[1], "-O1") == 0)
    {
      O1_optimization = argv[1];
    }
    if (strcmp(argv[1], "-O2") == 0)
    {
      O2_optimization = argv[1];
    }
  }
  else if (argc == 3)
  {
    if (strcmp(argv[1], "-O1") == 0)
    {
      O1_optimization = argv[1];
    }
    if (strcmp(argv[1], "-O2") == 0)
    {
      O2_optimization = argv[1];
    }
    if (strcmp(argv[2], "-O1")==0)
    {
      O1_optimization = argv[2];
    }
    if (strcmp(argv[2], "-O2") == 0)
    {
      O2_optimization = argv[2];
    }
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
