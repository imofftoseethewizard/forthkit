primitive(pr_dash_trailing) {
    register number n = (number)*sp;
    register char *s = (char *)_to_ptr(*(sp+1));

    while (n > 0 && s[n-1] == 32)
        n--;

    *sp = n;
    _next();
}
