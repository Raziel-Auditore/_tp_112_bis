#ifndef LOT_H
#define LOT_H


typedef struct {
    char* id;
    char* med_id;
    char* lab_id;
    char entry_date[11];
    char fab_date[11];
    char exp_date[11];
    int available_quantity;
    float unit_price;
} Lot;

typedef struct {
    char* med_id;
    char* lab_id;
    char entry_date[11];
    char fab_date[11];
    char exp_date[11];
    int available_quantity;
    float unit_price;
} LotUpdate;

typedef struct LotNode {
    Lot data;
    struct LotNode *next;
} LotNode;

void add_lot(Lot lot);
void update_lot(char *id, LotUpdate lot_update);
void delete_lot(char *id);
void get_lot(char *id);
LotNode* get_all_lots(void);

#endif
