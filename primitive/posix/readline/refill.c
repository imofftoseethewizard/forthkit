define_primitive("refill", &&p1_refill);

if (0)
  {
  p1_refill:
    if (free) (source);

    extern char *readline(const char *prompt);
    source = readline(NULL);

    source_len = strlen(source);
    next();
  }
