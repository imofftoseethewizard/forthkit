/*{ title_block }*/

/*{ generation_details }*/

/*|

`CELL_TYPE` and `DOUBLE_TYPE` are intended to be compile-time
parameters.  They should both be signed integers, with double type
twice the size of cell type.  Eg, valid types for these are (`short`,
`long`), (`int`, `long long`), and (`long long`, `__int128`).  There
are of course many synonyms that would work, and the full range of
valid pairs depends on the architecture of the build system and
compilation target.  These are known to work on 64-bit Linux
(Ubuntu/Debian) with either a 32-bit -- for the first two pairs -- or
64-bit target.

  |*/

    typedef unsigned CELL_TYPE cell;
    typedef unsigned DOUBLE_TYPE double_cell;

    typedef CELL_TYPE number;
    typedef DOUBLE_TYPE double_number;

/*|

See templates/errors.md for more information about errors and error
codes.

  |*/

	enum error_codes {
		/*{ error_code_definitions }*/
	};

/*|

Given an error code, return the associated message.  This is useful
`evalautate` below returns a non-zero value.

  |*/

	extern const char *error_message(number code);

/*|

Given an error symbol, return the error code. This is useful to
understand the values the evaluator might return from an error code
that appears in Forth code.

  |*/

	extern int error_code(const char *symbol);

/*|



  |*/

/*{ declare_init_evaluator }*/

/*|


  |*/

    extern int evaluate_source(cell *evaluator, const char *source, int storage_fd);

/*|



  |*/

    extern cell *create_evaluator_image(cell *e0, cell *e1, int *image_size);

/*|



  |*/

    extern cell *load_evaluator_image(const char *image, int image_size);
