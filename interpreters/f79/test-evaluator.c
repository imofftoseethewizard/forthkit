#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evaluator.h"

#include "test-config.h"

static cell evaluator[TEST_EVALUATOR_SIZE_BYTES / sizeof(cell)];

static int expected_result = 0;
static struct option long_options[] = {
    {"expected-result", required_argument, NULL, 0},
    {0, 0, 0, 0}
};

void
show_help(void)
{
    printf("usage: test-forth [-r/--expected-result <throw code>] file ...\n");
    printf("\n");
    printf("  <throw code> should be a decimal integer in the range -999999999 to 0.\n");
    printf("\n");
}

int
is_valid_signed_integer(char *s)
{
    if (*s == '-')
        s++;

    while (*s == '0' && *(s+1) != 0)
        s++;

    if (strlen(s) > 9)
        return 0;

    while (*s && *s >= '0' && *s <= '9')
        s++;

    return *s == 0;
}

int
evaluate_file(char *path)
{
    int result = 0;
    char line[SOURCE_SIZE] = {0};

    FILE *file = fopen(path, "r");

    if (!file) {
        fprintf(stderr, "failed to open file \"%s\" with errno %d\n", path, errno);
        exit(2);
    }

    while (!result && fgets(line, SOURCE_SIZE, file))
        result = evaluate(evaluator, line, 0);

    if (fclose(file)) {
        fprintf(stderr, "failed to close file \"%s\" with errno %d\n", path, errno);
        exit(3);
    }

    printf("result: %d\n", result);
    return result;
}

int
main(int argc, char **argv)
{
    int c;
    int idx;
    int result = 0;

    init_evaluator(evaluator, sizeof(evaluator));

    while (1) {

        c = getopt_long(argc, argv, "r:", long_options, NULL);

        if (c == -1) break;

        switch (c) {
        case 0:
        case 'r':

            if (!is_valid_signed_integer(optarg)) {
                show_help();
                exit(1);
            }

            expected_result = atoi(optarg);
            break;

        default: /* ':' or '?': missing value for -r or unknown opt, resp. */
            show_help();
            exit(1);
        }
    }

    for (idx = optind; !result && idx < argc; idx++)
        result = evaluate_file(argv[idx]);

    exit(!(result == expected_result && idx == argc));
}
