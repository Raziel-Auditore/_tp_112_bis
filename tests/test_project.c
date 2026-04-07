#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../src/sales/sales.h"
#include "../src/_utils_/g_utils.h"

#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define DIM     "\033[2m"
#define RESET   "\033[0m"

/* Helper: free an entire SaleNode linked list */
static void free_sale_list(SaleNode *head) {
    while (head != NULL) {
        SaleNode *tmp = head;
        head = head->next;
        free(tmp);
    }
}

/* Helper: print a section header */
static void section(int n, const char *title) {
    printf("\n" CYAN "  ── Test %d: %s " RESET "\n\n", n, title);
}

/* Helper: count nodes in a list */
static int list_count(SaleNode *head) {
    int n = 0;
    while (head != NULL) {
        n++;
        head = head->next;
    }
    return n;
}

/* Helper: search a node by ID in a list */
static SaleNode *find_in_list(SaleNode *head, const char *id) {
    while (head != NULL) {
        if (strcmp(head->data.id, id) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

int main(void) {
    printf("\n");
    printf(CYAN "  ╔══════════════════════════════════════════╗\n");
    printf("  ║        Test Suite — Sales Module          ║\n");
    printf("  ╚══════════════════════════════════════════╝" RESET "\n");

    int passed = 0;
    int failed = 0;

    /* ──────────────────────────────────────────
     *  Test 1: generate_id()
     * ────────────────────────────────────────── */
    section(1, "generate_id()");

    char *id1 = generate_id();
    char *id2 = generate_id();
    if (id1 != NULL && id2 != NULL && strlen(id1) == 36 && strlen(id2) == 36 && strcmp(id1, id2) != 0) {
        printf(GREEN "  [PASS]" RESET " Generated 2 unique UUIDs (36 chars each).\n");
        printf(DIM "         ID 1: %s\n         ID 2: %s" RESET "\n", id1, id2);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " UUID generation did not produce valid unique IDs.\n");
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 2: add_sale() — add 3 sales
     * ────────────────────────────────────────── */
    section(2, "add_sale()");

    /* Clear the storage file for a clean test */
    FILE *reset = fopen("storage/sales.txt", "w");
    if (reset) fclose(reset);

    Sale sale1 = { .date = "2025-04-07", .total_sale_price = 149.90 };
    strncpy(sale1.id, id1, 36); sale1.id[36] = '\0';
    strncpy(sale1.sales_id, id2, 36); sale1.sales_id[36] = '\0';
    add_sale(sale1);

    Sale sale2 = {
        .id = "aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee",
        .date = "2025-03-15",
        .sales_id = "11111111-2222-3333-4444-555555555555",
        .total_sale_price = 250.00
    };
    add_sale(sale2);

    Sale sale3 = {
        .id = "ffffffff-0000-1111-2222-333333333333",
        .date = "2025-04-07",
        .sales_id = "66666666-7777-8888-9999-aaaaaaaaaaaa",
        .total_sale_price = 75.50
    };
    add_sale(sale3);

    SaleNode *check_add = get_all_sales(0);
    int count_after_add = list_count(check_add);
    free_sale_list(check_add);

    if (count_after_add == 3) {
        printf(GREEN "  [PASS]" RESET " 3 sales added — storage contains %d records.\n", count_after_add);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 3 records, got %d.\n", count_after_add);
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 3: get_all_sales(1) — list mode
     * ────────────────────────────────────────── */
    section(3, "get_all_sales(1) — list all");

    SaleNode *all = get_all_sales(1);
    int count_all = list_count(all);
    free_sale_list(all);

    if (count_all == 3) {
        printf(GREEN "  [PASS]" RESET " Listed %d sales correctly.\n", count_all);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 3 listed, got %d.\n", count_all);
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 4: get_sale() — existing ID
     * ────────────────────────────────────────── */
    section(4, "get_sale() — existing ID");

    get_sale((char *)"aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee");
    printf(GREEN "  [PASS]" RESET " get_sale returned without crash for existing ID.\n");
    passed++;

    /* ──────────────────────────────────────────
     *  Test 5: get_sale() — non-existing ID
     * ────────────────────────────────────────── */
    section(5, "get_sale() — non-existing ID");

    get_sale((char *)"00000000-0000-0000-0000-000000000000");
    printf(GREEN "  [PASS]" RESET " get_sale returned without crash for missing ID.\n");
    passed++;

    /* ──────────────────────────────────────────
     *  Test 6: get_all_sales_by_date() — with matches
     * ────────────────────────────────────────── */
    section(6, "get_all_sales_by_date(\"2025-04-07\")");

    SaleNode *filtered = get_all_sales_by_date((char *)"2025-04-07");
    int count_filtered = list_count(filtered);
    free_sale_list(filtered);

    if (count_filtered == 2) {
        printf(GREEN "  [PASS]" RESET " Found %d sales for date 2025-04-07.\n", count_filtered);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 2 results, got %d.\n", count_filtered);
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 7: get_all_sales_by_date() — no matches
     * ────────────────────────────────────────── */
    section(7, "get_all_sales_by_date(\"1999-01-01\") — no matches");

    SaleNode *empty = get_all_sales_by_date((char *)"1999-01-01");
    int count_empty = list_count(empty);
    free_sale_list(empty);

    if (count_empty == 0) {
        printf(GREEN "  [PASS]" RESET " Correctly returned 0 results for non-matching date.\n");
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 0 results, got %d.\n", count_empty);
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 8: delete_sale() — existing ID
     * ────────────────────────────────────────── */
    section(8, "delete_sale() — existing ID");

    delete_sale((char *)"aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee");

    SaleNode *after_del = get_all_sales(0);
    int count_after_del = list_count(after_del);
    SaleNode *should_be_gone = find_in_list(after_del, "aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee");
    free_sale_list(after_del);

    if (count_after_del == 2 && should_be_gone == NULL) {
        printf(GREEN "  [PASS]" RESET " Sale deleted — %d records remaining, ID no longer found.\n", count_after_del);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 2 records and ID gone, got %d (found=%s).\n",
               count_after_del, should_be_gone ? "yes" : "no");
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 9: delete_sale() — already deleted ID
     * ────────────────────────────────────────── */
    section(9, "delete_sale() — already deleted ID");

    delete_sale((char *)"aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee");

    SaleNode *after_del2 = get_all_sales(0);
    int count_after_del2 = list_count(after_del2);
    free_sale_list(after_del2);

    if (count_after_del2 == 2) {
        printf(GREEN "  [PASS]" RESET " No side effect — still %d records.\n", count_after_del2);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 2 records, got %d.\n", count_after_del2);
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Test 10: get_all_sales(1) — final state
     * ────────────────────────────────────────── */
    section(10, "get_all_sales(1) — final state");

    SaleNode *final_list = get_all_sales(1);
    int count_final = list_count(final_list);
    free_sale_list(final_list);

    if (count_final == 2) {
        printf(GREEN "  [PASS]" RESET " Final state consistent — %d records.\n", count_final);
        passed++;
    } else {
        printf(RED "  [FAIL]" RESET " Expected 2 records, got %d.\n", count_final);
        failed++;
    }

    /* ──────────────────────────────────────────
     *  Summary
     * ────────────────────────────────────────── */
    printf("\n" CYAN "  ══════════════════════════════════════════" RESET "\n");
    printf("  Results: " GREEN "%d passed" RESET, passed);
    if (failed > 0)
        printf(", " RED "%d failed" RESET, failed);
    printf("  " DIM "(%d total)" RESET "\n\n", passed + failed);

    free(id1);
    free(id2);

    return failed > 0 ? 1 : 0;
}
