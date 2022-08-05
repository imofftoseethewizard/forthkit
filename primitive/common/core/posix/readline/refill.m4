
if (0)
  {  pr_refill:
    if (free) (source);

    extern char *readline(const char *prompt);
    source = readline(NULL);

    source_len = strlen(source);
}
__end
  }
__define_primitive("refill", pr_refill);
