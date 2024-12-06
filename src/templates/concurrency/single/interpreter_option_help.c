void
print_help(char *message)
{
    print_version();

    printf("usage: %s [options] [file ...]\n", INTERPRETER_NAME);

    printf("  -B, --buffer-size           size of block buffers in bytes, default %d\n", DEFAULT_BUFFER_SIZE);
    printf("  -b, --buffer-count          number of block buffers, default %d\n", DEFAULT_BUFFER_COUNT);
    printf("  -C, --create-image          path at which to store an image of the evaluator\n");
    printf("  -c, --command               command to execute, suppresses repl\n");
    printf("  -D, --pad-buffer-size       size of memory scratch area used to hold data for intermediate processing, default %d\n", DEFAULT_PAD_BUFFER_SIZE);
    printf("  -E, --evaluator-size        size of memory area for evaluator in bytes, default %d\n", DEFAULT_EVALUATOR_SIZE);
    printf("  -h, --help                  show this message\n");
    printf("  -I, --image                 load an image file\n");
    printf("  -i, --interactive           start repl regardless of other options\n");
    printf("  -P, --parameter-stack-size  maximum depth of parameter stack, default %d\n", DEFAULT_PARAMETER_STACK_SIZE);
    printf("  -q, --quiet                 suppress greeting\n");
    printf("  -R, --return-stack-size     maximum depth of return stack, default %d\n", DEFAULT_RETURN_STACK_SIZE);
    printf("  -r, --expected-result       expected result from evaluation, default %d\n", DEFAULT_EXPECTED_RESULT);
    printf("  -S, --source-size           size of parsing buffer in bytes, default %d\n", DEFAULT_SOURCE_SIZE);
    printf("  -s, --storage               path to block storage\n");
    printf("  -v, --version               print version\n");
    printf("  -W, --word-buffer-size      maximum length of parsed word, default %d\n", DEFAULT_WORD_BUFFER_SIZE);
    printf("\n");

    if (message) {
        printf("\n");
        printf("%s\n", message);
    }

    printf("\n");
}
