#include "main.h"

int login(Aluno *user){
    FILE *fp; // File pointer.
    char login[11], senha[11]; // Those string will recieve login and the password data. 
    char nomeArq[101], loginArq[11], senhaArq[11]; // Those strings will save the data obtained from the file.
    int raArq; // Will recieve the students register number from file.

    fp = fopen("Alunos.txt", "r"); // Open the file with the students data.

    if(fp == NULL){ // Couldn't open the file, interrupting the function.
        puts("Couldn't open the file!");
        exit(1);
    }

    // Recieving the user login and password.
    puts("Please, type your username and password:");
    printf("Username: ");
    scanf("%10s", login);
    printf("Password: ");
    scanf("%10s", senha);
    getchar();

    /*
     *  This loop goes through the file until it finds the corresponding login and password
     *  the user typed before. 
     */
    while(!feof(fp)){
        fscanf(fp, "%d,%100[^,],%10[^,],%10[^\n]\n", &raArq, nomeArq, loginArq, senhaArq);

        // Comparing the data for authentication.
        if(strcmp(login, loginArq) == 0 && strcmp(senha, senhaArq) == 0){
            /*
             * Putting the data obtained from the file in the global variable that
             * will be used during the program excution. 
             */
            (*user).ra = raArq;
            strcpy((*user).nome, nomeArq);
            strcpy((*user).login, loginArq);
            strcpy((*user).senha, senhaArq);

            // Printed when the user is authenticated.
            puts("");
            puts("Successfully logged in!");
            puts("Type ENTER to continue...");
            getchar();

            fclose(fp);

            return 0;
        }

    }

    // Printed when the authentication fails.
    puts("");
    puts("User not found! Try again!");
    puts("Type ENTER to continue...");
    getchar();

    fclose(fp);

    return 1;
}
