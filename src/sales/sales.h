#ifndef SALE_H
#define SALE_H

typedef struct {
    long id;
    char date[11];
    long sales_id;
    float total_sale_price;
} Sale;

typedef struct SaleNode {
    Sale data;
    struct SaleNode *next;
} SaleNode;

void add_sale(Sale sale);
void delete_sale(Sale sale);
void get_sale(long id);
void get_all_sales(void);
void get_all_sales_by_laboratory_id(long laboratory_id);
void get_sale_by_id(long id);

#endif
