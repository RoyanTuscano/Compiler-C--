/*
 * util.h 
 */

typedef struct lnode {
  char *name;
  int type;
  bool is_array;
  struct lnode *next;
} llist, *llistptr;

void *zalloc(int n);

llistptr NewListNode(char *str, int Type, bool arr);
llistptr Attach(llistptr list1, llistptr list2);
