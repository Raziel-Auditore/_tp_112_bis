#ifndef SALE_H
#define SALE_H

#include <uuid/uuid.h>


typedef struct {
    char id[37];
    char date[11];
    char sales_id[37];
    float total_sale_price;
} Sale;

typedef struct SaleNode {
    Sale data;
    struct SaleNode *next;
} SaleNode;

typedef struct {
    struct SaleNode *head;
    struct SaleNode *tail;
} SaleList;

void add_sale(Sale sale);
void delete_sale(char id[37]);
void get_sale(char id[37]);
SaleNode* get_all_sales(int list_sales);
SaleNode* get_all_sales_by_date(char date[11]);
void get_sale_by_id(char id[37]);

#endif
