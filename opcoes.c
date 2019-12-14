#include "main.h"

int redirect(int op,Aluno *user){
    int aux; // Auxiliary variable.
    int erro; // Recieves what a function returns.

    switch(op){
        case 1:
            clear();
            erro = cadastrar(); // Calling the register function.

            // Couldn't open the file, interrupting the function.
            if(erro == 1)
                puts("Couldn't open the file!");
        break;

        case 2:
            clear();
            erro = consultarDisc(); // Calling the subject query function.
            
            // Couldn't open the file, interrupting the function.
            if(erro == 1)
                puts("Couldn't open the file!");
        break;

        case 3:
            clear();
            erro = fazerMatricula(*user); // Calling the enrollment function.
            
            // Couldn't open the file, interrupting the function.
            if(erro == 1)
                puts("Couldn't open the file!");
        break;

        case 4:
            clear();
            erro = atualizar(*user); // Calling the function that update scores and absences.
            
            // Couldn't open the file, interrupting the function.
            if(erro == 1)
                puts("Couldn't open the file!");
        break;
        
        case 5:
            clear();
            erro = hist(*user); // Calling the function that query the record.
            
            // Couldn't open the file, interrupting the function.
            if(erro == 1)
                puts("Couldn't open the file!");
        break;
        
        case 6:
            while(erro != 0){ // This loop repeats the login until the user enters with the right credentials.
                clear();
                erro = login(user); // Calling the login function.
            }
        break;

        default:
            // Printed when the used select a unexistent option.
            puts("");
            puts("Invalid Option!");
            puts("");
    }
}
