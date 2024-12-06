void
process_options(int argc, char *argv[])
{
    int c;

    while (1) {

        c = getopt_long(argc, argv, ":b:B:c:C:E:hiI:P:qR:r:S:s:vw:", long_options, NULL);

        if (c == -1) break;

        switch (c) {
        case 0:
            /* indicates a flag option. getopt_long has already set the flag value; nothing
               needs to be done.
            */
            break;

        case 'b':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-b, --buffer-count must have a non-negative integer argument.");
                exit(1);
            }

            buffer_count = atoi(optarg);
            break;

        case 'B':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-B, --buffer-size must have a non-negative integer argument.");
                exit(1);
            }

            buffer_size = atoi(optarg);
            break;

        case 'c':
            command = optarg;
            break;

        case 'C':
            create_image_path = optarg;
            break;

        case 'E':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-E, --evaluator-size must have a non-negative integer argument.");
                exit(1);
            }

            evaluator_size = atoi(optarg);
            break;

        case 'h':
            show_help = 1;
            break;

        case 'I':
            load_image_path = optarg;
            break;

        case 'i':
            interactive = 1;
            break;

        case 'P':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-P, --parameter-stack-size must have a non-negative integer argument.");
                exit(1);
            }

            parameter_stack_size = atoi(optarg);
            break;

        case 'q':
            quiet = 1;
            break;

        case 'R':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-R, --return-stack-size must have a non-negative integer argument.");
                exit(1);
            }

            return_stack_size = atoi(optarg);
            break;

        case 'r':

            expected_result = is_valid_integer(optarg) ? atoi(optarg) : error_code(optarg);

            if (!expected_result) {
                print_help("-r, --expected-result must have a negative integer argument or an error symbol");
                exit(1);
            }

            break;

        case 'S':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-S, --source-size must have a non-negative integer argument.");
                exit(1);
            }

            source_size = atoi(optarg);
            break;

        case 's':
            storage_path = optarg;
            break;

        case 'v':
            show_version = 1;
            break;

        case 'W':

            if (!is_valid_non_negative_integer(optarg)) {
                print_help("-W, --word-buffer-size must have a non-negative integer argument.");
                exit(1);
            }

            word_buffer_size = atoi(optarg);
            break;

        case ':':
            sprintf(message_buffer, "-%c requires an argument.", optopt);
            print_help(message_buffer);
            exit(1);

        case '?':
            sprintf(message_buffer, "-%c is not a recognized option.", optopt);
            print_help(message_buffer);
            exit(1);
        }
    }
}
