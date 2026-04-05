#ifndef LABORATORY_H
#define LABORATORY_H


typedef struct {
    long id;
    char *name;
    char phone[9];
    char *email;
} Laboratory;

typedef struct LaboratoryNode {
    Laboratory data;
    struct LaboratoryNode *next;
} LaboratoryNode;

void add_laboratory(Laboratory laboratory);
void update_laboratory(Laboratory laboratory);
void delete_laboratory(Laboratory laboratory);
void get_laboratory(long id);
void get_all_laboratories(void);
void get_laboratory_by_name(char *name);

#endif
