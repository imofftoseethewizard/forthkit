    int result = 0;

    register cell *e = evaluator;

    register char *top;
    register cell *tp;    /* current task */
    register cell *fp;    /* current fiber */

    register cell *fp0;
    register cell *rp0;
    register cell *sp0;

    register char *dp;
    register cell *sp;

    register cell *ip;
    register cell *rp;
    register cell *rp_stop;
    register number steps;
