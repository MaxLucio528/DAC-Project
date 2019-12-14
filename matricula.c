#include "main.h"

int fazerMatricula(Aluno user){
    int i, j, k; // Integer auxiliary variables.
    int creditos; // Will store the students' total credits on the chosen semester.
    int semtemp; // Temporarily stores the semester number.
    int validador; // Validation auxiliary variable.
    char codigodisc[6]; // Will store de subject's code.
    char saida[6] = "XX000"; // Required string to exit function.
    Disciplina disc; // Will store the subjects.
    Matricula mat[10]; // Will store the subjects the student enrolled.
    Matricula mattemp; // Obtains the subjects the student enrolled.
    Prereq discPre[7]; // Stores the prerequisites of a subject.
    FILE *fp; // File pointer.
    
    validador = 0;
    
    // This is where the user will insert the semester he's gonna do a enrollment.
    while(validador != 1){
        // Opening this file to check the student situation.
        fp = fopen("AlunosDisciplinas.txt", "r");
    
        if(fp == NULL)
            return 1; // Couldn't open the file, interrupting the function.
        
        puts("Perform Enrollment:");
        puts("");
        printf("Type the semester: ");
        scanf("%d", &semtemp);
        getchar();
        puts("");
        
        // Used if the user types a invalid semester.
        if(semtemp < 1 || semtemp > 10){
            puts("Invalid Semester!");

			if(semtemp > 10)
				puts("Above maximum integralization!");

            continue;
        }

        // Checks if the user is trying to enroll in a semester previous to the one he is.
        while(!feof(fp)){
            fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &mattemp.ra, mattemp.codigo, &mattemp.semestre, 
                    &mattemp.nota, &mattemp.faltas);

            if(user.ra == mattemp.ra){ // Registration number
                if(semtemp >= mattemp.semestre){ // Valid semester.
                    validador = 1;
                }else{ // Invalid semester.
                    puts("It isn't possible to enroll in a previous semester!");
                    
                    validador = 2;
                    break;
                }
            }
        }
        
        // The student's registration number doesn't exist in the list yet.
        if(validador == 0)
            validador = 1;
        
        fflush(fp);
        fclose(fp);
    }
    
    // Opening this file to save in the struct the subjects the student is enrolled.
    fp = fopen("AlunosDisciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    i = 0; // Indicates the position of the array below.
    
    // Stores in the struct the subjects the student is enrolled.]
    while(!feof(fp)){
        fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &mat[i].ra, mat[i].codigo, &mat[i].semestre, &mat[i].nota, 
                &mat[i].faltas);

        // Changes the position of the array when subject is found.
        if(mat[i].ra == user.ra && mat[i].semestre == semtemp){
            i++;
        }
    }
    
    fflush(fp);
    fclose(fp);
    
    // Opening this file to read the subjects.
    fp = fopen("Disciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    creditos = 0; 

    // Checking if the number of credits per semester (32) was exceeded.
    while(!feof(fp)){
        fscanf(fp, "%5[^,],%100[^,],%d\n", disc.codigo, disc.nome, &disc.creditos);

        // Number of credits equals 32 or has surpassed the value.
        if(creditos >= 32){
            puts("It's impossible to enroll in this semester! Maximum amount of credits reached!");
            puts("Type ENTER to continue...");
            getchar();
            
            return 0;
        }
        
        // Saves the number of credits on the semester.
        for(j = 0; j < i; j++){
            // Appending the number of credits.
            if(strcmp(disc.codigo, mat[j].codigo) == 0){
                creditos += disc.creditos;
                
                break;
            }
        }
    }
    
    fflush(fp);
    fclose(fp);
    
    // This loop performs the enrollment.
    do{ 
        puts("To exit, type XX000");
        printf("Type the subject: ");
        scanf("%5s", codigodisc);
        
        for(k = 0; k < 2; k++){ // Changing to upper case the subject's code if isn't already.
            codigodisc[k] = toupper(codigodisc[k]);
        }
        
        puts("");
        getchar();

		// The user is trying to enroll in a subject that needs special permission.
		if(codigodisc[0] == 'A' && codigodisc[1] == 'A'){
			puts("Authorization! Only the coordenation can enroll you in this subject.");
			continue;
		}
        
        // Opening this file to read the subjects.
        fp = fopen("Disciplinas.txt", "r");
    
        if(fp == NULL)
            return 1; // Changing to upper case the subject's code if isn't already.
        
        validador = 0;
        
        // Checks if the subject exists.
        while(!feof(fp)){
            fscanf(fp, "%5[^,],%100[^,],%d\n", disc.codigo, disc.nome, &disc.creditos);

            // Subject found.
            if(strcmp(codigodisc, disc.codigo) == 0){
                validador = 1; // Indicating the subject was found.
                break;
            }
        }
        
        // The subject doesn't exist.
        if(validador == 0 && strcmp(codigodisc, "XX000") != 0){
            puts("This subject doesn't exist! Try again.");
            continue;
        }
        
        fflush(fp);
        fclose(fp);
        
        if(strcmp(codigodisc, saida) == 0){
            puts("Transaction made with success!");
            puts("Type ENTER to continue...");
            getchar();
            break;
        }
        
        // Adding the credit of the subject the user is enrolling.
        creditos += disc.creditos;
                
        // Credits exceeded.
        if(creditos >= 32){
            puts("Enrollment is impossible, amount of credits exceeded!");
            
            // Removing the credits from the subject chosen.
            creditos -= disc.creditos;
            
            continue;
        }
        
        // Opening this file to check if the user already attended this subject.
        fp = fopen("AlunosDisciplinas.txt", "r");

        if(fp == NULL)
            return 1; // Couldn't open the file, interrupting the function.
            
        // Saving in a struct to check if the user already attended this subject.
        while(!feof(fp)){
            fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &mattemp.ra, mattemp.codigo, &mattemp.semestre, 
                    &mattemp.nota, &mattemp.faltas);

            if(strcmp(codigodisc, mattemp.codigo) == 0 && user.ra == mattemp.ra){
                puts("Enrollment is impossible, this subject was already attended!");
                validador = 2;
                    
                break;
            }
        }
        
        fflush(fp);
        fclose(fp);
        
        // Skipping the rest of the loop if the subject was already attended.
        if(validador == 2)
            continue;
        
        // Opening this file to read the prerequisites.
        fp = fopen("Prerequisitos.txt", "r");
    
        if(fp == NULL)
            return 1; // Couldn't open the file, interrupting the function.
        
        i = 0; // Indicator of the position of the array below.
    
        // Getting the subject and it's prerequisite.
        while(!feof(fp)){
            fscanf(fp, "%5[^,],%5[^\n]\n", discPre[i].codDisc, discPre[i].codPrereq);

            // Subject found.
            if(strcmp(discPre[i].codDisc, codigodisc) == 0){
                // Subject doesn't have any prerequisite.
                if(strcmp(discPre[i].codPrereq, "0") == 0){
                    validador = 0; // Indicating the subject doesn't have prerequisites.
                    
                    break;
                }else{ // Prerequisite obtained.               
                    i++; // Changing the array position.
                }
            }
        }
        
        fflush(fp);
        fclose(fp);
        
        // Subject has prerequisite.
        if(validador != 0){
            /*
             * Opening this file to check if the student attended to the prerequisites of the subject he's 
             * trying to enroll.
             */
            fp = fopen("AlunosDisciplinas.txt", "r");

            if(fp == NULL)
                return 1; // Couldn't open the file, interrupting the function.
            
            k = 0;
            
            // Saving on struct the student enrollment to check the prerequisites attended.
            while(!feof(fp)){
                fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &mattemp.ra, mattemp.codigo, &mattemp.semestre, 
                &mattemp.nota, &mattemp.faltas);

                // Student failed one of the prerequisites.
                if(validador == -1 || validador == -2)
                    break;
                
                // Student was approved in all of the prerequisites.
                if(k == i)
                    break;
                
                // Checking if the student coursed the prerequisites.
                for(j = 0; j < i; j++){
                    // Prerequisite found.
                    if(strcmp(discPre[j].codPrereq, mattemp.codigo) == 0 && 
                            user.ra == mattemp.ra && semtemp > mattemp.semestre){
                        // Student has satisfactory performance on the subject.
                        if(mattemp.nota >= 5 && mattemp.faltas < 25){
                            validador = 1; // Indicating the student was approved on the prerequisite.
                            k++; // Increasing the number of prerequisites the student was approved.
                            break;
                        }else{ // Checking why the student failed one of the prerequisites.
                            if(mattemp.nota < 5){ // By score.
                                validador = -1;
                                break;
                            }
                            
                            if(mattemp.faltas >= 25){ // By absence.
                                validador = -2;
                                break;
                            }
                        }
                    }else{ /*
                            * Prerequisite not found, or user is trying to enroll in the same semester he
                            * attended the prerequisite.
                            */
                        validador = -3;
                    }
                }
            }

            fflush(fp);
            fclose(fp);
        }
        
        if(validador == -1){ // Student failed by score.
            puts("Enrollment is impossible, the student failed by score in one or more of the prerequisites!");
        }else{ // Student failed by absence.
            if(validador == -2){
                puts("Enrollment is impossible, the student failed by absence in one or more of the prerequisites!");
            }else{ // Student lack all of the prerequisites attended.
                if(validador == -3){
                    printf("Enrollment is impossible, the prerequisite wasn't attended, ");
                    printf("or the enrollment in this subject is trying to be made in the same semester ");
                    puts("of the prerequisite!");
                }else{ // All requirements were met.
                    // Opening this file to append the new enrollment.
                    fp = fopen("AlunosDisciplinas.txt", "a");
                    
                    if(fp == NULL)
                         return 1; // Couldn't open the file, interrupting the function.
                    
                    // Saving the data on the enrollment file.
                    fprintf(fp,"%d,%s,%d,-1.0,-1.0\n", user.ra, codigodisc, semtemp);
                    
                    puts("Transaction made with success");
                    puts("Type ENTER to continue...");
                    getchar();
                    
                    fflush(fp);
                    fclose(fp);
                }
            }
        }
    }while(strcmp(codigodisc, saida) != 0);
    
    return 0;
}
