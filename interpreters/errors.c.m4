include(`errors.m4')dnl
dnl
#include <stdlib.h>
#include <string.h>

include(`types.h')dnl

#include "errors.h"

typedef struct {
    number code;
    const char *symbol;
    const char *message;
} error_descriptor;

static const error_descriptor error_descriptors[] = {
    __initialize_error_descriptors()
};

const char *
error_message(number code)
{
    for (int i = 0; i < sizeof(error_descriptors)/sizeof(error_descriptor); i++)
        if (error_descriptors[i].code == code)
            return error_descriptors[i].message;

    return NULL;
}

int
error_code(const char *symbol)
{
    for (int i = 0; i < sizeof(error_descriptors)/sizeof(error_descriptor); i++)
        if (!strcmp(error_descriptors[i].symbol, symbol))
            return error_descriptors[i].code;

    return 0;
}
