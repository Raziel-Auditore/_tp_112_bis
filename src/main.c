#include <stdio.h>
#include "./sales/sales.h"
#include <uuid/uuid.h>

int main() { 
    printf("Welcome to the Pharmacy Management System !\n");

    delete_sale((char*)"123e4567-e89b-12d3-a456-426614174000");

     return 0;
}