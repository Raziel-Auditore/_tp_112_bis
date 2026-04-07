#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

void delete_sale(char id[37]) {
    SaleNode *head = get_all_sales(0);
    if (head == NULL) {
        printf(YELLOW "  [INFO]" RESET " No sales found in storage.\n");
        return;
    }

    SaleNode *curr = head;
    SaleNode *prev = NULL;

    while (curr != NULL && strcmp(curr->data.id, id) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        printf(RED "  [NOT FOUND]" RESET " No sale matches ID: %s\n", id);
        /* Free the entire list */
        while (head != NULL) {
            SaleNode *tmp = head;
            head = head->next;
            free(tmp);
        }
        return;
    }

    /* Unlink the node */
    if (prev == NULL) {
        head = curr->next;
    } else {
        prev->next = curr->next;
    }
    free(curr);

    /* Rewrite the file without the deleted sale */
    FILE *file = fopen("storage/sales.txt", "w");
    if (file == NULL) {
        printf(RED "  [ERROR]" RESET " Could not open sales storage file.\n");
        return;
    }

    SaleNode *it = head;
    while (it != NULL) {
        fprintf(file, "%s,%s,%s,%.2f\n",
                it->data.id,
                it->data.date,
                it->data.sales_id,
                it->data.total_sale_price);
        it = it->next;
    }
    fclose(file);

    printf(GREEN "  [OK]" RESET " Sale %s deleted successfully.\n", id);

    /* Free remaining list */
    while (head != NULL) {
        SaleNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}