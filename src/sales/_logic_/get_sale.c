#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define DIM     "\033[2m"
#define RESET   "\033[0m"

void get_sale(char id[37]) {
    SaleNode *head = get_all_sales(0);
    if (head == NULL) {
        printf(YELLOW "  [INFO]" RESET " No sales found in storage.\n");
        return;
    }

    SaleNode *curr = head;
    while (curr != NULL && strcmp(curr->data.id, id) != 0) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf(RED "  [NOT FOUND]" RESET " No sale matches ID: %s\n", id);
    } else {
        printf(GREEN "  [FOUND]" RESET " Sale details:\n");
        printf(DIM "  ──────────────────────────────────────────" RESET "\n");
        printf("  ID          : %s\n", curr->data.id);
        printf("  Date        : %s\n", curr->data.date);
        printf("  Sales ID    : %s\n", curr->data.sales_id);
        printf("  Total Price : %.2f\n", curr->data.total_sale_price);
        printf(DIM "  ──────────────────────────────────────────" RESET "\n");
    }

    /* Free the entire list */
    while (head != NULL) {
        SaleNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}