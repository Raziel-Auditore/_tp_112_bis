#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void delete_sale(char id[37]) {
    printf("Deleting sale with id: %s\n", id);
    SaleNode *head = get_all_sales(); 
    if (head == NULL) {
        printf("Sale list empty !\n");
        return;
    }

    SaleNode *curr = head;
    SaleNode *prev = NULL;

    while (curr != NULL && strcmp(curr->data.id, id) != 0) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        printf("Sale with ID %s not found !\n", id);
        return; 
    }
    if (prev == NULL) {
        head = curr->next;
    } 
    else {
        prev->next = curr->next;
        curr->next = prev->next;      
    }
    FILE *empty_file = fopen("storage/sales.txt", "w");
    fclose(empty_file);
    FILE *file = fopen("storage/sales.txt", "a");
    while(head != NULL) {
        fprintf(file, "%s,%s,%s,%.2f\n", 
            head->data.id, 
            head->data.date, 
            head->data.sales_id, 
            head->data.total_sale_price);
        head = head->next;
    }
    fclose(file);

    printf("Vente %s supprimée de la mémoire.\n", id);
    free(curr);
}