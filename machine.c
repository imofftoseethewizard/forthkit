#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "machine.h"
#include "log.h"

char *store_cstring(const char *s, char *here);

int
init_stack_machine(struct stack_machine *m)
{
  m->result = 0;
  m->ip = 0;
  m->cp = m->cp0 = m->context_stack;

  m->here = m->data;

  m->rp = m->rp0 = m->return_stack + RETURN_STACK_SIZE;

  m->t_sp = m->t_sp0 = m->primary_stack;
  m->sp = m->sp0 = m->primary_stack + PRIMARY_STACK_SIZE;

  m->context = 0;
  m->current = 0;
}

void
reset_stack_machine_execution_state(struct stack_machine *m)
{
  m->sp = m->sp0;
  m->rp = m->rp0;
  m->t_sp = m->t_sp0;
  m->cp = m->cp0;
  m->ip = 0;
}

int
run_stack_machine(struct stack_machine *m)
{
  /* These are the most commonly referenced variables. */
  register void **ip  = m->ip;
  register cell *sp   = m->sp;
  register cell **rp  = m->rp;

  char *here = m->here;
  cell *t_sp = m->t_sp;

  cell **cp0          = m->cp0;
  cell **cp           = m->cp;
  cell **rp0          = m->rp0;
  cell *sp0           = m->sp0;
  cell *t_sp0         = m->t_sp0;

  char *buffer        = m->buffer;
  int buffer_len      = m->buffer_len;
  char *point         = m->point;

  char *token         = m->token;
  int token_len       = m->token_len;

  cell *current       = m->current;
  cell *context       = m->context;

  int result          = m->result;
  void **operators    = m->operators;

  cell tmp0, tmp1, *xp, *yp;
  int i, j, *intp0, *intp1;
  char k, n, *chp0, *chp1;

  /* The label `__first` must appear before any labels used as a target
     of the `next()` macro immediately below. That uses the `__first` and
     `__last` labels to distinguish primitives from compiled words.
   */
 __first:

  #if (OPTIMIZE == time)

  /* This version of `next` consumes more memory, as each primitive
     will have a small amount of machine code following it to handle
     advancing through compiled words. This saves two jumps per
     primitive over the space optimizing version below.

   */

    #define next()                                \
    do                                            \
      {                                           \
        while (*ip < &&__first || *ip > &&__last) \
          *--rp = (cell *)ip, ip = (void **)*ip;  \
        goto *ip++;                               \
      }                                           \
     while (0)

  #elif (OPTIMIZE == space)

  /* Instead of handling the logic to transition to the next word or
     primitive in each primitive, this version of `next` just jumps
     back to a loop here in `run_stack_machine`.

     It may be that this version is also faster on some
     architectures. Using fewer bytes per primitive means that fewer
     cache lines are needed to keep the code in memory and L1 cache
     misses are less likely. It also may be that superscalar
     processors can retire the jumps just as quickly as the
     time-optimized version above.
   */

    #define next() goto __next

  #endif

  #define register_operator(x, y) operators[x] = y

  #include "op/abort.c"
  #include "op/branch.c"
  #include "op/call.c"
  #include "op/exit.c"
  #include "op/jump.c"
  #include "op/literal.c"

  #define c_immediate 0b0001
  #define c_inline    0b0010
  #define c_primitive 0b0100

  /* Note that this assumes that a cell is an power of 2 number of bytes.
     That seems like a safe assumption.
   */

  #define _align(x) (cell *)((cell)(x) + sizeof(cell) - 1 & ~(sizeof(cell) - 1))

  #define _store_data(x) \
    here = (char *)_align(here), *(cell *)here = (cell)(x), here += sizeof(cell)

  #define _word_header(flags)               \
  /* _word_header: ( n -- addr ) [xp] */    \
                                            \
  /* Align here to a cell boundary. */      \
  here = (char *)_align(here);              \
                                            \
  /* Save address of new word. */           \
  xp = (cell *)here;                        \
                                            \
  /* Copy name address to word entry. */    \
  _store_data(*sp++);                       \
                                            \
  /* Vocabulary list link. */               \
  _store_data(current);                     \
                                            \
  /* Add to current vocabulary. */          \
  current = xp;                             \
                                            \
  /* Word flags. */                         \
  _store_data(flags);                       \
                                            \
  /* Return the address of the new word. */ \
  *--sp = (cell)xp

  #define begin_define_primitive(s)         \
  *--sp = (cell)here;                       \
  here = store_cstring((s), here);          \

  #define define_primitive_ext(s, l, flags) \
  if (!context)                             \
    {                                       \
      begin_define_primitive(s);            \
      _word_header(c_primitive | (flags));  \
      _store_data(l);                       \
      _store_data(&&op_exit);               \
    }

  #define define_parsing_primitive(s, l)    \
  if (!context)                             \
    {                                       \
      begin_define_primitive(s);            \
      _word_header(c_primitive);            \
      _store_data(&&p1_word);               \
      _store_data(l);                       \
      _store_data(&&op_exit);               \
    }

  #define define_primitive(s, l)           define_primitive_ext(s, l, 0)
  #define define_immediate_primitive(s, l) define_primitive_ext(s, l, c_immediate)

  #define _set_word_flags(x, flags)   *((cell *)(x) + 2) |= (flags)
  #define _clear_word_flags(x, flags) *((cell *)(x) + 2) &= ~(flags)

  #include "primitive/core/align.c"
  #include "primitive/core/create.c"
  #include "primitive/core/store_data.c"

  #include "primitive/posix/emit.c"
  #include "primitive/posix/key.c"

  #include "primitive/core/word.c"
  #include "primitive/core/immediate.c"

  context = current;

  #if (OPTIMIZE == time)

    if (ip) next();

  #elif (OPTIMIZE == space)

    while (ip)
      {
        while (*ip < &&__first || *ip > &&__last)
          *--rp = (cell *)ip, ip = (void **)*ip;

        goto *ip++;
      __next:
      }

  #endif

 __last:

  return result;
}

char *
store_cstring(const char *s, char *here)
{
  cell n = strlen(s);

  here = (char *)_align(here);

  *(cell *)here = n;

  strncpy((char *)((cell *)here + 1), s, n);

  return here + sizeof(cell) + n + 1;
}
