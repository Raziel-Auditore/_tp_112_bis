#ifndef SALE_ITEM_H
#define SALE_ITEM_H

typedef struct {
    long id;
    long med_id;
    char sale_date[11];
    int quantity;
} SaleItem;

typedef struct SaleItemNode {
    SaleItem data;
    struct SaleItemNode *next;
} SaleItemNode;

void add_sale_item(SaleItem sale_item);
void delete_sale_item(SaleItem sale_item);
void get_sale_item(long id);
void get_all_sale_items_by_sale_id(long sales_id);
void get_sale_item_by_id(long id);

#endif
