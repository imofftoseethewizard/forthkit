define_primitive("word", &&p1_word);

if (0)
  {
  p1_word:
    /* Skip leading delimiters. */
    do _key();
    while (*sp == ' ');

    /* Check if input is exhausted. */
    if (!*sp)
        *--sp = 0;
    else
      {
        /* Newlines are tricky. They are word delimiters, but also a single
           newline is a word. An initial newline will skip the loop body below,
           so the length needs to be initialized to 1, otherwise a zero length
           string would result.
        */
        i = *sp == '\n' ? 1 : 0;

        /* intp0 the address of the string. The first byte is the
           length.
        */
        intp0 = (int *)here;

        /* chp0 is the pointer used to fill the characters of the string.
         */
        chp0 = (char *)(intp0 + 1);

        /* The word ends with the end of the input, a space, or a newline.
         */
        while (*sp && *sp != ' ' && *sp != '\n')
          {
            /* Copy character, increment length, get next character.
             */
            *chp0++ = (char)*sp++;
            i++;
            _key();
          }

        /* Copy the delimiting character, or single newline. */
        *chp0++ = (char)*sp++;

        /* Store the length of the string. */
        *intp0 = i;

        /* Advance here to include the length of the string, the characters of
           the string, and the delimiting character */
        here += (sizeof(int) + (i + 1) + sizeof(cell) - 1) / sizeof(cell);

        /* Return the string address. */
        *--sp = (cell)intp0;
      }

    next();
  }
