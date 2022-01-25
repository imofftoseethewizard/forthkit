define_primitive("REFILL", &&pr_refill);

if (0)
  {
  pr_refill:
    if (free) (source);

    extern char *readline(const char *prompt);
    source = readline(NULL);

    source_len = strlen(source);
    _next();
  }
