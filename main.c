#include "main.h"

/*  
 *  DAC-Project
 *  FINAL PROJECT FOR SI200 A - GROUP 5
 *  CONTRIBUITORS:
 * -> Andrey Toshiro Okamura (GitHub - okamuratoshi)
 * -> Gustavo Adrien Polli (GitHub - gapolli)
 * -> Max Lucio Martins de Assis (GitHub - MaxLucio528)
 * 
 *  PURPOSE: This project is a fictional system which simulates a enrollment system and a
 *  enrollment control system for a student from UNICAMP, being capable of generate a school 
 *  record to the user as well.
 */

Aluno user; // Global variable that recieves the student data when he logs in.

int main()
{
    int erro; // This variable indicates if everything went well in functions that were called.
    int opcao; // This variable will have control on the chosen options from the menu.

    erro = 1;
    opcao = -1;

    /*  
     *  This loop repeats the login until the user enters with the right credentials.
     *  That's the reason why the number one was attributed to the "erro" variable.
     */
    while(erro != 0){
        clear();
        erro = login(&user); // Calling the login function; throwing the result in "erro".
    }

    /*  
     *  This loop repeats executes the program actions.
     *  That's the reason why the number minus one was attributed to the "opcao" variable.
     */
    while(opcao != 0){
        clear();
        opcao = menu();

        if(opcao == 0)  // Finalizing the program when the user selects the option zero.
            exit(0);

        // Calling the function responsible for redirecting the program to the right function.
        redirect(opcao, &user);
    }
}
