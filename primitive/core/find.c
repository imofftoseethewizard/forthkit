define_parsing_primitive("find", &&p1_do_find);

#define _string_len(x)  *(int *)(x)
#define _string_addr(x) (char *)((int *)(x) + 1)

#define _lowercase_ascii(x) ((x) < 'A' || (x) > 'Z' ? (x) : (x) - 'A' + 'a')

if (0)
  {
  p1_do_find:

    /* Save the length of the target string into k. */
    k = _string_len(*sp);

    /* xp will hold the address of the word being checked for a matching
       name.
    */
    xp = context;

    while (xp)
      {
        /* Address of the name of the word at xp. */
        yp = (cell *)*xp;

        /* Check that the name of the current word is the same as the target
           string.
        */
        if (_string_len(yp) == k)
          {
            chp0 = _string_addr(*sp);
            chp1 = _string_addr(yp);

            for (i = 0; i < k; i++, chp0++, chp1++)
              if (_lowercase_ascii(*chp0) != _lowercase_ascii(*chp1))
                break;

            if (i == k)
              break;
          }
      }

    *--sp = (cell)xp;
    next();
  }
