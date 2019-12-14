#include "main.h"

int consultarDisc(){
    int i, j, k; // Integer auxiliary variables.
    int validador; // Validation auxiliary variable, will inform the program if subject is found.
    char codigodisc[6]; // Recieves the subject's code.
    char codigotemp[6]; // Temporarily recieves the subject's prerequisite subject.
    int credtemp; // Temporarily recieves the subject's prerequisite credits to help the file navegation.
    Disciplina disc; // Recieves the subject.
    Prereq discPre[7]; // Recieves the subject's preqeuisites.
    FILE *fp; // File pointer.
    
    // Opening this file to read the subjects.
    fp = fopen("Disciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    /*  The user type the subject's code.
     *  OBS: The "scanf" will only get the first five characters the user types because
     *  all the subjects in UNICAMP have five characters, two letters and three numbers.
     */
    printf("Type a subject: ");
    scanf("%5s", codigodisc);
    
    for(k = 0; k < 2; k++){ // Changing to upper case the subject's code if isn't already.
        codigodisc[k] = toupper(codigodisc[k]);
    }
    
    getchar(); // Cleaning keyboard buffer.
    
    validador = 0; // By default, this indicates the subject wasn't found.

    // This loop look for the subject typed by the user on the file. 
    while(!feof(fp)){
        fscanf(fp, "%5[^,],%100[^,],%d\n", disc.codigo, disc.nome, &disc.creditos);

        // Subject is found.
        if(strcmp(codigodisc, disc.codigo) == 0){
            validador = 1; // Indicating the subject is found.
            break;
        }
    }
    
    // Interrupting the function if the subject wasn't found.
    if(validador == 0){
        puts("\nSubject not found!");
        puts("\nType ENTER to continue...");
        getchar();
        
        fclose(fp);
        return 0;
    }
    
    fclose(fp);
    
    // Opening this file to read the chosen subject's prerequisites.
    fp = fopen("Prerequisitos.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    i = 0; // Array's size indicator.
    
    // Getting the subject and it's prerequisite.
    while(!feof(fp)){
        fscanf(fp, "%5[^,],%5[^\n]\n", discPre[i].codDisc, discPre[i].codPrereq);

        // Found the subject is the prerequisites' list.
        if(strcmp(discPre[i].codDisc, disc.codigo) == 0){
            // Subject doesn't have a prerequisite.
            if(discPre[i].codPrereq[0] == '0'){
                validador = 0; // Indicating the subject doesn't have a prerequisite.
                break;
            }else{ // Getting the prerequisite.               
                i++; // Increasing the size of the array.
            }
        }
    }

    // Displaying the subject if it doesn't have a prerequisite.
    if(validador == 0){
        printf("\nName: %s\n", disc.nome);
        printf("Amount of Credits: %d\n", disc.creditos);
        puts("Prerequisite: None");
        puts("\nType ENTER to continue...");
        getchar();
        
        return 0;
    }
    
    fclose(fp);
    
    // Opening this file to get the prerequisites' name.
    fp = fopen("Disciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    j = 0; // Size indicator for the array below.
    
    /*
     *  Getting the subjects and codes to comparison, but the credits are only obtained
     *  to avoid conflict on the file navegation (Isn't used). 
     */
    while(!feof(fp)){
        fscanf(fp, "%5[^,],%100[^,],%d\n", codigotemp, discPre[j].nomePre, &credtemp);
        
        // Prerequisite found, changing array position to store the next prerequisite.
        if(strcmp(codigotemp, discPre[j].codPrereq) == 0){
            j++;
        }
    }
    
    // Printing the subject's information.
    printf("\nName: %s\n", disc.nome);
    printf("Amount of Credits: %d\n", disc.creditos);

    // Printing all prerequisites.
    for(j = 0; j < i; j++){
        printf("Prerequisite: %s\n", discPre[j].nomePre);    
    }
        
    puts("\nType ENTER to continue...");
    getchar();
    
    fclose(fp);
    
    return 0;
}