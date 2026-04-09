#ifndef LOT_H
#define LOT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int lot_add_quantity(LotNode *head, const char *id, int quantity);

int lot_remove_quantity(LotNode *head, const char *id, int quantity);

LotNode* sort_lots_by_fab_date(LotNode *head);

LotNode* sort_lots_by_exp_date(LotNode *head);

static inline void _swap_lot_data(LotNode *a, LotNode *b)
{
    Lot tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}


int lot_add_quantity(LotNode *head, const char *id, int quantity)
{
    if (!head || !id || quantity <= 0) return -1;

    LotNode *current = head;
    while (current) {
        if (current->data.id && strcmp(current->data.id, id) == 0) {
            current->data.available_quantity += quantity;
            return 0;
        }
        current = current->next;
    }
    return -1;
}


int lot_remove_quantity(LotNode *head, const char *id, int quantity)
{
    if (!head || !id || quantity <= 0) return -1;

    LotNode *current = head;
    while (current) {
        if (current->data.id && strcmp(current->data.id, id) == 0) {
            if (current->data.available_quantity < quantity)
                return -2; /* stock insuffisant */
            current->data.available_quantity -= quantity;
            return 0;
        }
        current = current->next;
    }
    return -1;
}

static LotNode* _sort_lots(LotNode *head,
                            int (*cmp)(const Lot*, const Lot*))
{
    if (!head || !head->next) return head;

    int swapped;
    LotNode *current;

    do {
        swapped  = 0;
        current  = head;
        while (current->next) {
            if (cmp(&current->data, &current->next->data) > 0) {
                _swap_lot_data(current, current->next);
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);

    return head;
}


static int _cmp_fab_date(const Lot *a, const Lot *b)
{

    return strncmp(a->fab_date, b->fab_date, 10);
}

static int _cmp_exp_date(const Lot *a, const Lot *b)
{
    return strncmp(a->exp_date, b->exp_date, 10);
}


LotNode* sort_lots_by_fab_date(LotNode *head)
{
    return _sort_lots(head, _cmp_fab_date);
}

LotNode* sort_lots_by_exp_date(LotNode *head)
{
    return _sort_lots(head, _cmp_exp_date);
}

#endif
