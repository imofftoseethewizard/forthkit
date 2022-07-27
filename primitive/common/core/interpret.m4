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

    while (idx < len) {
        register cell pr = 0;

        while (source[idx] <= 32 && idx < len)
            idx++;

        if (idx == len) {
            fprintf(stderr, "\n");
            break;
        }

        w_idx = idx;
        word = &source[idx];

        while (source[idx] > 32 && idx < len)
            idx++;

        w_len = idx - w_idx;
        fprintf(stderr, "%.*s ", w_len, word);

        for (idx_pr = 0; idx_pr < sizeof(primitive_descs)/sizeof(primitive_descriptor); idx_pr++) {
            /* fprintf(stderr, "pr_interpret: checking %s\n", primitive_descs[idx_pr].name); */
            if (strlen(primitive_descs[idx_pr].name) == w_len
                && !strncmp(primitive_descs[idx_pr].name, word, w_len)) {
                pr = primitive_descs[idx_pr].value;
                break;
            }
        }

        if (pr) {

            /* fprintf(stderr, "pr_interpret: %.*s\n", w_len, word); */

            if (e[ea_state]) {

                /* compile */

                if (w_len == 1 && !strncmp(word, "[", 1))
                    /* There are currently no dictionary entries, so there is no
                       immediate flag. Lacking that, the only way to exit compile
                       mode is to hardcode the behavior of [ here.
                     */
                    e[ea_state] = 0;
                else {
                    /* compile */
                    *(cell *)dp = pr, dp += sizeof(cell);
                    fprintf(stderr, "^ ");
                }

                continue;
            }

            /* interpret */

            /* This bit is a little tricky. We cannot just "call" the primitive,
               because it may be a case in a switch statement, a local
               subroutine, or code following a label. Instead, we have reserved
               the cell before the one containing pr_interpret that we are currently
               executing, and store the primitive to be executed there. Moving the
               instruction point back to that location prepares the primitive
               to be evaluated and ensures that after it is finished, this
               primitive will be the next to execute.
             */

            ip = _to_ptr(e[ea_pr_interpret]) - 1;
            *ip = pr;

            /* Yield control back to the evaluator to execute the primitive. */
            break;
        }

        for (idx_c = 0; idx_c < sizeof(constant_descs)/sizeof(constant_descriptor); idx_c++) {
            /* fprintf(stderr, "constant: %s\n", constant_descs[idx_c].name); */
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

        if (e[ea_state])
            *(cell *)dp = value, dp += sizeof(cell);
        else
            *--sp = value;
    }

    /* Save the state of text input. */
    e[ea_source_idx] = idx;
')
}

__end
__define_primitive("<interpret>", pr_interpret);
