    /* FLUSH ( -- )

       Performs the function of SAVE-BUFFERS then unassigns all
       block buffers.  (This may be useful for mounting or changing
       mass storage media).

       |   : flush
       |       save-buffers
       |       buffer-count 0 do
       |           -1 buffer-map i cells + !
       |       loop
       |   ;
     */

    __compiled_word("FLUSH", cw_flush, 0)

    _compile_pr(pr_save_buffers);

    _compile_literal(e[ea_buffer_count]);
    _compile_literal(0);
    _compile_do();

    _compile_literal(-1);
    _compile_literal(e[ea_buffer_map]);
    _compile_pr(pr_i);
    _compile_literal(sizeof(cell));
    _compile_pr(pr_times);
    _compile_pr(pr_plus);
    _compile_pr(pr_store);

    _compile_loop();

    _compile_pr(op_exit);
