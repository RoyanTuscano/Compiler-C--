/*
 * error.h
 *
 * Syntax and semantic errors
 */

#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdarg.h>

#define  ORDINARY    0
#define  NOCOMMA     1
#define  NOSEMICOLON 2
#define  NOLPAREN    3
#define  NORPAREN    4
#define  NORBRACE    5

#define CASSERT(cond, msg)  if (!(cond)) errmsg msg ;

void errmsg(const char *fmt, ...);

#endif /* _ERROR_H_ */
