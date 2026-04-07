#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>


void add_sale(Sale sale) {
    FILE *file = fopen("storage/sales.txt", "a");
    if (file == NULL) {
        printf("\033[1;31mErreur : Impossible d'ouvrir le fichier des ventes !\033[0m\n");
        return;
    }

    fprintf(file, "%s,%s,%s,%.2f\n", 
            sale.id, 
            sale.date, 
            sale.sales_id, 
            sale.total_sale_price);

    // 3. Fermeture immédiate
    fclose(file);
    printf("\033[1;32mVente enregistrée avec succès dans le stockage.\033[0m\n");
}