#include "main.h"

int menu(){
    // Will store the option selected.
    int op;

    puts("Options Menu:");
    puts("");
    puts("1 - Students Registration");
    puts("2 - Subject's Query");
    puts("3 - Perform Enrollment");
    puts("4 - Update Score and Absence");
    puts("5 - Query Student Record");
    puts("6 - Switch User");
    puts("0 - Exit");
    puts("");
    printf("Choose a option: ");
    scanf("%d", &op);

    return op;
}
