/*
 * util.c -- assorted utilities
 *
 * Author: Saumya Debray
 */

#include "global.h"

/*
 * return a pointer to a zero-initialized block of n bytes.
 */
void *zalloc(int n)
{
  void *ptr;

  if (n <= 0) {
    fprintf(stderr, "Illegal memory allocation size: %d\n", n);
    abort();
  }

  ptr = calloc(n, 1);

  if (ptr == NULL) {
    fprintf(stderr, "Not enough memory\n");
    abort();
  }

  return ptr;
}

/*
 * NewListNode(x, type, is_array) -- allocate a new linked list node 
 * and set its fields appropriately;
 */
llistptr NewListNode(char *str, int Type, bool arr)
{
  llistptr ltmp;

  ltmp = zalloc(sizeof(*ltmp));
  ltmp->name = str;
  ltmp->type = Type;
  ltmp->is_array = arr;

  return ltmp;
}

/*
 * Attach(list1, list2) -- given two linked lists, attaches the second 
 * at the end of the first.
 */
llistptr Attach(llistptr list1, llistptr list2)
{
  llistptr ltmp;

  if (list1 == NULL) return list2;
  /*
   * find the last element of the list.
   */
  for (ltmp = list1; ltmp != NULL && ltmp->next != NULL; ltmp = ltmp->next) {
  }
  
  ltmp->next = list2;

  return list1;
}
