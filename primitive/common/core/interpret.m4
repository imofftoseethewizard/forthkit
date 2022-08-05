__primitive(pr_interpret)
{
ifdef(`__include_bootstrap', `
    register cell
      w_idx = -1,
      idx = e[ea_source_idx],
      len = e[ea_source_len],
      w_len = 0,
      value;

    register char
      *source = (char *)_to_ptr(e[ea_source_addr]),
      *word = NULL;

    register int
      idx_pr = 0,
      idx_c = 0;

    static int compiling = 1;
    static int repl = 0;

    if (!repl && (len <= 4 || strncmp(source, "    ", 4)))
        idx = len;

    else {

        while (idx < len) {
            register cell pr = 0;

            while (source[idx] <= 32 && idx < len)
                idx++;

            if (idx == len)
                break;

            w_idx = idx;
            word = &source[idx];

            while (source[idx] > 32 && idx < len)
                idx++;

            w_len = idx - w_idx;

            if (compiling) {

                if (w_len == 1 && !strncmp(word, "[", 1)) {
                    compiling = 0;
                    continue;
                }

            } else {

                /* if (w_len == 1 && !strncmp(word, ".", 1)) { */
                /*     printf("%x ", *sp++); */
                /*     continue; */
                /* } */

                if (w_len == 1 && !strncmp(word, "]", 1)) {
                    compiling = 1;
                    continue;
                }

                if (w_len == 1 && *word == 39) {

                    while (source[idx] <= 32 && idx < len)
                        idx++;

                    if (idx == len)
                        break;

                    w_idx = idx;
                    word = &source[idx];

                    while (source[idx] > 32 && idx < len)
                        idx++;

                    w_len = idx - w_idx;

                    for (idx_pr = defs.count-1; idx_pr >= 0; idx_pr--) {

                        if (strlen(defs.entries[idx_pr].name) == w_len
                            && !strncmp(defs.entries[idx_pr].name, word, w_len)) {
                            pr = defs.entries[idx_pr].value;
                            break;
                        }
                    }

                    if (!pr) {
                        _abort(err_undefined_word);
                        break;
                    }

                    *--sp = pr;
                    continue;
                }

                if (w_len == 6 && !strncmp(word, "define", 6)) {

                    while (source[idx] <= 32 && idx < len)
                        idx++;

                    if (idx == len)
                        break;

                    w_idx = idx;
                    word = &source[idx];

                    while (source[idx] > 32 && idx < len)
                        idx++;

                    w_len = idx - w_idx;

                    add_compiled_definition(&defs, word, w_len, _from_ptr(dp));
                    continue;
                }

                if (w_len == 11 && !strncmp(word, "interactive", 11)) {
                    repl = 1;
                    continue;
                }
            }

            for (idx_pr = defs.count-1; idx_pr >= 0; idx_pr--) {

                if (strlen(defs.entries[idx_pr].name) == w_len
                    && !strncmp(defs.entries[idx_pr].name, word, w_len)) {
                    pr = defs.entries[idx_pr].value;
                    break;
                }
            }

            if (pr) {

                if (compiling) {

                    /* compile */

                    *(cell *)dp = pr, dp += sizeof(cell);

                    continue;
                }

                /* interpret */

                /* This bit is a little tricky. We cannot just "call" the primitive,
                   because it may be a case in a switch statement, a local
                   subroutine, or code following a label. Instead, we have reserved
                   the cell before the one containing pr_interpret (that we are
                   currently executing), and store pr there. Moving the instruction
                   pointer back to that location prepares the primitive to be
                   evaluated and ensures that after it is finished, pr_interpret
                   will be the next to execute.
                 */

                ip = _to_ptr(e[ea_pr_interpret]) - 1;
                *ip = pr;

                /* Yield control back to the evaluator to execute the primitive. */
                break;
            }

            for (idx_c = 0; idx_c < sizeof(constant_descs)/sizeof(constant_descriptor); idx_c++) {

                if (!strncmp(constant_descs[idx_c].name, word, w_len)) {
                    value = constant_descs[idx_c].value;
                    break;
                }
            }

            if (idx_c == sizeof(constant_descs)/sizeof(constant_descriptor)) {
                char *endp;
                value = (cell)strtoll(word, &endp, 0);

                if (endp - word < w_len) {
                    _abort(err_undefined_word);
                    break;
                }
            }

            if (compiling)
                *(cell *)dp = value, dp += sizeof(cell);
            else
                *--sp = value;
        }
    }

    /* Save the state of text input. */
    e[ea_source_idx] = idx;
')
}

__end
__define_primitive("<interpret>", pr_interpret);
