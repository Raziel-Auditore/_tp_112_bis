#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include "g_utils.h"

#define RED     "\033[1;31m"
#define RESET   "\033[0m"

char *generate_id() {
    uuid_t id;
    uuid_generate(id);

    char *buffer = malloc(37 * sizeof(char));
    if (buffer == NULL) {
        printf(RED "  [ERROR]" RESET " Memory allocation failed (generate_id).\n");
        return NULL;
    }

    uuid_unparse(id, buffer);
    return buffer;
}