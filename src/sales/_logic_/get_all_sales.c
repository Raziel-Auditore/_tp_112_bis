#include "../sales.h"
#include <stdio.h>
#include <stdlib.h>



SaleNode* get_all_sales(){
    FILE *file = fopen("storage/sales.txt","r");
    if(file==NULL){
        printf("Sales file not found !\n");
        return 0;
    }
    SaleNode *head = NULL;
    char line[512];
    printf("..........Reading sales from file...\n");
    int line_number = 1;
    while (fgets(line,sizeof(line),file) != NULL)
    {
        SaleNode *node = malloc(sizeof(SaleNode));
        // printf("Allocating memory for a new sale node...\n");
         if(node==NULL){
            printf("Memory allocation failed !\n");
            fclose(file);
            return 0;
        }
        node->next = NULL;
        int read = sscanf(line,"%37[^,],%11[^,],%37[^,],%f",node->data.id,node->data.date,node->data.sales_id,&node->data.total_sale_price); 
        if (read != 4)
        {
            printf("Error reading sale data from file !\n");
            printf("Sale read from file: id=%s, date=%s, sales_id=%s, total_sale_price=%.2f\n", node->data.id, node->data.date, node->data.sales_id, node->data.total_sale_price);

            free(node);
            return 0;
        }
        printf("...Sale number %d...\n",line_number);
        printf(
            "ID=%s\nDATE=%s\nSALES_ID=%s\nTOTAL_SALE_PRICE=%.2f\n",
             node->data.id,
             node->data.date, 
             node->data.sales_id, 
             node->data.total_sale_price
            );

            printf("..........\n..........\n ");
        if (head == NULL)
        {
            head = node;
        }

        line_number++;
    }
    printf("Finished reading sales from file.\n");
    fclose(file);
    SaleList *sale_list = malloc(sizeof(SaleList));
    if(sale_list==NULL){
        printf("Memory allocation failed !\n");
        return 0;
    }
    sale_list->head = head;
    return head;
}