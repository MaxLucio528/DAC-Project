#include "main.h"

int cadastrar(){
    Aluno cad; // Temporarily storing the students' data that will be registered.
    FILE *fp; // File pointer.

    // Opening this file to append the new information.
    fp = fopen("Alunos.txt", "a");

    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.

    // Temporarily storing the data on the struct to later, store on the file.
    puts("Students Registration:");
    puts("");
    printf("Type the student's registration number: ");
    scanf("%6d", &cad.ra);
    getchar(); // Cleaning the keyboard buffer.

    printf("\nType the student's name: ");
    scanf("%99[^\n]s", cad.nome); // Allowing the "scanf" to save strings with space, if that's the case.
    printf("\nType the login: ");
    scanf("%10s", cad.login);

    printf("\nType the password: ");
    scanf("%10s", cad.senha);
    getchar();
    puts("");

    // Saving the new student in the file.
    fprintf(fp, "%d,%s,%s,%s\n", cad.ra, cad.nome, cad.login, cad.senha);

    puts("Student registered successfully!");
    puts("Type ENTER to continue...");
    getchar();
    
    fclose(fp);

    return 0;
}
