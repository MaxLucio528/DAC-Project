#include "main.h"

int atualizar(Aluno user){
    int i, j, k, l; // Integer auxiliary variables.
    int semtemp; // Temporarily store the semester.
    int validador; // Validation auxiliary variable.
    char codigodisc[6]; // Recieves the subject code.
    char saida[6] = "XX000"; // Stores the code that validates the exit.
    Matricula temp; // Temporarily stored to count the enrollments.
    Matricula *alunos; // Stores all the students.
    Disciplina *disc; // Stores all the subjects the student is enrolled.
    FILE *fp; // File pointer.

    
    // Opening the file to check how many enrollments there is.
    fp = fopen("AlunosDisciplinas.txt", "r"); 
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    i = 0; // Used as increment on the loop below.
    
    // This loop counts how many enrollments there is on the system.
    while(!feof(fp)){
        fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &temp.ra, temp.codigo, &temp.semestre, &temp.nota,
            &temp.faltas);
        i++;
    }
    
    fflush(fp);
    fclose(fp);
    
    // Allocating space to store the enrollments.
    alunos = (Matricula *) malloc(i * sizeof(Matricula));
    
    // Opening the file to read and save the existent enrollments.
    fp = fopen("AlunosDisciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    // Saving the remaining subjects.
    for(j = 0; j < i; j++){
        fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &alunos[j].ra, alunos[j].codigo, 
                &alunos[j].semestre, &alunos[j].nota, &alunos[j].faltas);
    }
    
    fflush(fp);
    fclose(fp);
    
    puts("Atualizar nota e falta:");
    
    validador = 0;
    
    /*
     *  Validating the chosen semester.
     *  That's the reason why zero was atributed to "validador". 
     */
    while(validador != 1){
        puts("");
        printf("Type the semester: ");
        scanf("%d", &semtemp);
        getchar();
        puts("");
        
        // Used if the user types a invalid semester.
        if(semtemp < 1 || semtemp > 10){
            puts("Invalid semester!");

			if(semtemp > 10)
				puts("Above the maximum integralization!");

            continue;
        }
        
        // Checking if the student has or not a active enrollment.
		for(j = 0; j < i; j++){
			if(user.ra == alunos[j].ra){
				validador = 1;
				break;
			}else{
				validador = 0;
			}
		}

        // Stopping the function if the student doesn't have any active enrollment.
		if(validador == 0){
			puts("There isn't any enrollment yet...");
			return 0;
		}

        // Checking if the used typed a semester where the doesn't have a enrollment yet.
        for(j = 0; j < i; j++){
            // Stopping the loop if it finds the semester.
            if(user.ra == alunos[j].ra && semtemp == alunos[j].semestre){
                validador = 1;
                break;
            }else{ // Used when the semester isn't found.
                validador = -1;
            }
        }

		// Used when the semester isn't found.
		if(validador == -1){
		        puts("You don't have any enrollment in this semester!");
		        continue;
		}
    }
    
    
    /*
     *  Opening this file to know the name of the subjects the student
     *  enrolled in the semester he selected.
     */
    fp = fopen("Disciplinas.txt", "r");
    
    if(fp == NULL)
       return 1; // Couldn't open the file, interrupting the function.
    
    k = 0; // Stores how many subjects the student enrolled in the semester selected.
    
    /*
     * Goes through the student struct to check how many subjects the student enrolled
     * in the semester, storing it in "k".
     */
    for(j = 0; j < i; j++){
        // Finding a subject the student enrolled in the semester.
        if(user.ra == alunos[j].ra && semtemp == alunos[j].semestre){
            k++;
        }
    }
    
    //alocando espaço para as disciplinas do aluno no semestre
    disc = (Disciplina *) malloc(k * sizeof(Disciplina));
    
    l = 0; // Used as array position below.
    
    while(!feof(fp)){
        fscanf(fp,"%5[^,],%100[^,],%d\n", disc[l].codigo, disc[l].nome, &disc[l].creditos);

        // Increments "l" till it finds the subject the student enrolled.
        for(j = 0; j < i; j++){
            // Checking if a subject is one the student enrolled.
            if(alunos[j].ra == user.ra && semtemp == alunos[j].semestre){
                // Finding the subject the student enrolled.
                if(strcmp(alunos[j].codigo, disc[l].codigo) == 0)
                    l++;
            }
        }
        
        // Preventing the loop to go to a unexistent position.
        if(l >= k)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    puts("Subjects:");
    
    // Printing the subjects the student enrolled in the semester chosen.
    for(l = 0; l < k; l++){
        // Goes through the struct array to print correctly the information.
        for(j = 0; j < i; j++){
            // Looking for the subjects in the semester chosen previosly.
            if(alunos[j].ra == user.ra && semtemp == alunos[j].semestre){
                // Finding the subjects in the semester chosen previosly.
                if(strcmp(alunos[j].codigo, disc[l].codigo) == 0){
                    printf("%s - %s - Score: %.1f, Absences (%%): %.1f\n", alunos[j].codigo,
                            disc[l].nome, alunos[j].nota, alunos[j].faltas);
                }         
            }
        }
    }
    
    puts("");
    
    // This loop updates the students' score.
    do{
        puts("To exit, type XX000");
        printf("Type the code of the subject you want to update: ");
        scanf("%5s", codigodisc);
        
        for(l = 0; l < 2; l++){ // Changing to upper case the subject's code if isn't already.
            codigodisc[l] = toupper(codigodisc[l]);
        }
        
        puts("");
        getchar();
        
        // This allow the program to break the loop and exit the function.
        if(strcmp(codigodisc, saida) == 0){
            puts("Successfully updated!");
            puts("Type ENTER to continue...");
            getchar();
            break;
        }
        
        // This loop verifies if the student is enrolled in the typed subject.
        for(l = 0; l < k; l++){
            // Used when the student is enrolled in the subject.
            if(strcmp(codigodisc, disc[l].codigo) == 0){
                validador = 1;
                break;
            }else{ // Subject wasn't found.
                validador = 0;
            }
        }
        
        // Restarting the loop if the subject wasn't found.
        if(validador == 0){
            puts("Subject not found!");
            continue;
        }
        
        // Saving the updated data in the struct array.
        for(j = 0; j < i; j++){
            // Subject found.
            if(user.ra == alunos[j].ra && strcmp(codigodisc, alunos[j].codigo) == 0){
                printf("Score: ");
		        // Loop that allows the user to input the new score.
                do{
					scanf("%f", &alunos[j].nota);

					if(alunos[j].nota < 0 || alunos[j].nota > 10)
						puts("Invalid score! Try again...");
				}while(alunos[j].nota < 0 || alunos[j].nota > 10);
                
				puts("");
				getchar();
                
                printf("Absence (%%): ");
		        // Loop that allows the user to input the new absence quantity.
				do{
				        	scanf("%f", &alunos[j].faltas);

					if(alunos[j].faltas < 0 || alunos[j].faltas > 100)
						puts("Invalid percentage! Try again...");
				}while(alunos[j].faltas < 0 || alunos[j].faltas > 100);                
		
				puts("");
				getchar();
                
                break;
            }
        }
        
        // Opening this file to update the score and the absence.
        fp = fopen("AlunosDisciplinas.txt", "w");
        
        if(fp == NULL)
            return 1; // Couldn't open the file, interrupting the function.
        
        // Loop that will save the updated data.
        for(j = 0; j < i; j++){
            // Saving the updated data.
            fprintf(fp, "%d,%s,%d,%.1f,%.1f\n", alunos[j].ra, alunos[j].codigo,
                    alunos[j].semestre, alunos[j].nota, alunos[j].faltas);
        }
        
        fflush(fp);
        fclose(fp);
        
        puts("Successfully updated!");
        puts("Type ENTER to continue...");
        getchar();
        
    }while(strcmp(codigodisc, saida) != 0);
        
    return 0;
}
