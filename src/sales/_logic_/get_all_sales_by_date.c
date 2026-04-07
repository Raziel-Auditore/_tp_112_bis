#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define DIM     "\033[2m"
#define RESET   "\033[0m"

SaleNode *get_all_sales_by_date(char date[11]) {
    FILE *file = fopen("storage/sales.txt", "r");
    if (file == NULL) {
        printf(RED "  [ERROR]" RESET " Could not open sales storage file.\n");
        return NULL;
    }

    SaleNode *head = NULL;
    SaleNode *curr = NULL;
    char line[512];
    int count = 0;
    int total = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        total++;
        SaleNode *node = malloc(sizeof(SaleNode));
        if (node == NULL) {
            printf(RED "  [ERROR]" RESET " Memory allocation failed.\n");
            fclose(file);
            return NULL;
        }
        node->next = NULL;

        int read = sscanf(line, "%37[^,],%11[^,],%37[^,],%f",
                          node->data.id,
                          node->data.date,
                          node->data.sales_id,
                          &node->data.total_sale_price);
        if (read != 4) {
            free(node);
            continue;
        }

        if (strcmp(node->data.date, date) == 0) {
            if (head == NULL) {
                head = node;
                curr = head;
            } else {
                curr->next = node;
                curr = node;
            }
            count++;
        } else {
            free(node);
        }
    }
    fclose(file);

    printf(CYAN "  ┌── Sales filtered by date: %s " DIM "(%d/%d)" RESET "\n", date, count, total);

    if (count == 0) {
        printf(DIM "  │" RESET "\n");
        printf(YELLOW "  │  No sales found for this date." RESET "\n");
    } else {
        SaleNode *it = head;
        int i = 1;
        while (it != NULL) {
            printf(DIM "  │" RESET "\n");
            printf(DIM "  │" CYAN "  #%d" RESET "\n", i);
            printf(DIM "  │" RESET "  ID          : %s\n", it->data.id);
            printf(DIM "  │" RESET "  Date        : %s\n", it->data.date);
            printf(DIM "  │" RESET "  Sales ID    : %s\n", it->data.sales_id);
            printf(DIM "  │" RESET "  Total Price : %.2f\n", it->data.total_sale_price);
            it = it->next;
            i++;
        }
    }

    printf(DIM "  │" RESET "\n");
    printf(DIM "  └──────────────────────────────────────────" RESET "\n");
    printf(GREEN "  [OK]" RESET " %d result%s.\n", count, count > 1 ? "s" : "");

    return head;
}