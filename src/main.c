#include <stdio.h>
#include "./sales/sales.h"

#define CYAN    "\033[1;36m"
#define RESET   "\033[0m"

int main(void) {
    printf("\n");
    printf(CYAN "  ╔══════════════════════════════════════════╗\n");
    printf("  ║   Pharmacy Management System  v1.0       ║\n");
    printf("  ╚══════════════════════════════════════════╝" RESET "\n\n");

    get_all_sales(1);

    printf("\n");
    return 0;
}