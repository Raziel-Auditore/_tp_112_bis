#ifndef MEDICAMENT_H
#define MEDICAMENT_H

typedef struct {
    long id;
    char *common_name;
    char *molecular_name;
    char *description;
    char *dosage;
    float public_price;
    char *side_effects;
    char *precautions;
} Medicament;

typedef struct MedicamentNode {
    Medicament data;
    struct MedicamentNode *next;
} MedicamentNode;

void add_medicament(Medicament medicament);
void update_medicament(Medicament medicament);
void delete_medicament(Medicament medicament);
void get_medicament(long id);
void get_all_medicaments(void);
void get_medicament_by_name(char *name);

#endif
