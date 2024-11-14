/*{ init_evaluator }*/

int
evaluate(cell *evaluator, const char *source, int storage_fd, cell **primitives)
{
	static cell internal_primitives[/*{ primitive_count }*/];

    if (!evaluator) {

	    /*{ initialize_primitive_registry }*/

	    if (primitives) {
		    *primitives = malloc(sizeof(internal_primitives));
            memcpy(*primitives, &internal_primitives, sizeof(internal_primitives));
	    }

        return sizeof(internal_primitives)/sizeof(cell);
    }

    int result = 0;

    register cell *e = evaluator;

    register char *top;

    register cell *rp0;
    register cell *sp0;

    register char *dp;
    register cell *sp;

    register cell *ip;
    register cell *rp;

	/*{ evaluator_variables }*/

	/*{ primitive_decls }*/

#ifdef BOOTSTRAP
    if (!e[ea_top]) {
	    /*{ bootstrap }*/
    }
#endif

    _debug("interpreting source '%s'\n", source);

    /* copy source into evaluator memory */

    memcpy(_to_ptr(e[ea_source_addr]), source, e[ea_source_len] = strlen(source));
    e[ea_source_idx] = 0;

    /*{ evaluator_core }*/

    _debug("done with run: result: %d\n", result);
    _print_stack();

    return result;
}
