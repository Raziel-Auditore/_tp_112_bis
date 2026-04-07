#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include "g_utils.h"

char* generate_id() {
    uuid_t id;
    uuid_generate(id);
     if(id==NULL){
        printf("Id generation failed !\n");
        return NULL;
    }
    char *buffer = malloc(37 * sizeof(char));
    if(buffer==NULL){
        printf("Memory allocation failed !\n");
        return NULL;
    }

    uuid_unparse(id, buffer);
    return buffer;
}