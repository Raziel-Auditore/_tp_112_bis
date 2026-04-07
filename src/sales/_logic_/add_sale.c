#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>

#define GREEN   "\033[1;32m"
#define RED     "\033[1;31m"
#define RESET   "\033[0m"

void add_sale(Sale sale) {
    FILE *file = fopen("storage/sales.txt", "a");
    if (file == NULL) {
        printf(RED "  [ERROR]" RESET " Could not open sales storage file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%.2f\n",
            sale.id,
            sale.date,
            sale.sales_id,
            sale.total_sale_price);

    fclose(file);
    printf(GREEN "  [OK]" RESET " Sale recorded successfully.\n");
}