#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>

static int check_passed = 0, check_failed = 0, check_skipped = 0,
           current_level = 0;

// Unicode characters, to make output pretty.
static const char *tick = "\u2713",
                 *cross = "\u2717",
                 *arrow = "\u2794";

// ANSI Escape Sequences
static const char *red = "\x1b[31m",
                *green = "\x1b[32m",
                 *blue = "\x1b[34m",
                  *end = "\x1b[0m";

#define describe(message, block) do {\
  int skip = 0; \
  indent(current_level); \
  printf("%s%s %s%s\n", blue, arrow, message, end); \
  current_level++; \
  block; \
  current_level--; \
  (void)skip; \
} while(0);

#define context describe
#define it describe

#define check(expr) checkm((expr), #expr);

#define checkm(expr, message) do {\
  indent(current_level); \
  if(skip) { \
    printf("%s? %s%s\n", blue, message, end); \
    check_skipped++; \
  } else {\
    if((expr)) {\
      printf("%s%s %s\n", green, tick, message); \
      check_passed++; \
    } else {\
      printf("%s%s %s (%s:%d)\n", red, cross, message, __FILE__, __LINE__); \
      check_failed++; \
      skip = 1; \
    } \
  } \
} while(0);

static void indent(int level) {
  while(level--) {
    printf("   ");
  }
}

static inline void check_print_stats() {
  printf("\n%s  %s %d assertions, %d passed, %d skipped, %d failed.%s\n",
         check_failed ? red : check_skipped ? blue : green,
         check_failed ? cross : tick,
         check_passed + check_failed + check_skipped,
         check_passed,
         check_skipped,
         check_failed,
         end);
}

#endif
