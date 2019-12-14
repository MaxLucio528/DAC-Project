#include "main.h"

int hist(Aluno user){
    int i, j, k, l, m, n; // Integer auxiliary variables.
    int contcred; // Students' total credits counter.
    float contcn; // Students' total credits * score counter.
    int validador; // Validation auxiliary variable.
    float aux; // Ordering auxilirary variable.
    char ra[11]; // Stores the registration number to be the file name.
    int pos; // Stores the logged student's classification.
    float valpos; // Stores the user's coeficient.
    Aluno alunotmp; // Temporarily stores the student count.
    Aluno *aluno; // Stores all the students.
    Matricula temp; // Temporarily stores the enrollment count.
    Matricula *alunos; // Stores all the students enrollments.
    Disciplina tmp; // Temporarily stores the subjects count.
    Disciplina *disc; // Stores all the subjects.
    FILE *fp; // File pointer.
    
    getchar();
    
    // Opening this file to get the user registration number.
    fp = fopen("Alunos.txt", "r");
    
    if(fp == NULL)
       return 1; // Couldn't open the file, interrupting the function.
    
    while(!feof(fp)){
        fscanf(fp, "%6s,%100[^,],%10[^,],%10[^\n]", ra, alunotmp.nome, alunotmp.login, 
            alunotmp.senha);

        // Registration number found.
        if(atoi(ra) == user.ra)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    // Manually completing the string.
    ra[6] = '.';
    ra[7] = 't';
    ra[8] = 'x';
    ra[9] = 't';
    ra[10] = '\0';
    
    // Opening this file to count all the registered students.
    fp = fopen("Alunos.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    m = 0; // Will be the total size of the array "coeficiente".
    
    // Counting how many students are registered.
    while(!feof(fp)){
        fscanf(fp, "%d,%100[^,],%10[^,],%10[^\n]", &alunotmp.ra, alunotmp.nome, alunotmp.login,
        alunotmp.senha);

        m++;
    }
    
    // Will store all the efficiency coeficient.
    float coeficiente[m];
    
    fflush(fp);
    fclose(fp);
    
    // Will store all the students.
    aluno = (Aluno *) malloc(m * sizeof(Aluno));
    
    // Opening this file to get all the students.
    fp = fopen("Alunos.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    l = 0; // Will indicate the positions of the array below.
    
    // Storing all the students on the struct.
    while(!feof(fp)){
        fscanf(fp, "%d,%100[^,],%10[^,],%10[^\n]", &aluno[l].ra, aluno[l].nome, aluno[l].login,
        aluno[l].senha);
        
        l++;
        
        // Preventing the loop from going to a unexistent position.
        if(l >= m)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    // Opening this file to count the number of enrollments.
    fp = fopen("AlunosDisciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    i = 0; // Will be the counter of enrollments.
    
    // Counts how many enrollments there is.
    while(!feof(fp)){
        fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &temp.ra, temp.codigo, &temp.semestre, &temp.nota,
        &temp.faltas);

        i++;
    }
    
    fflush(fp);
    fclose(fp);
    
    // Will store the enrollments.
    alunos = (Matricula *) malloc(i * sizeof(Matricula));
    
    // Opening this file to save all the enrollments on a struct.
    fp = fopen("AlunosDisciplinas.txt", "r");
    
    if(fp == NULL)
        return 1; // Couldn't open the file, interrupting the function.
    
    // Saving all the enrollments.
    for(j = 0; j < i; j++){
        fscanf(fp, "%d,%5[^,],%d,%f,%f\n", &alunos[j].ra, alunos[j].codigo, &alunos[j].semestre,
        &alunos[j].nota, &alunos[j].faltas);
    }
    
    fflush(fp);
    fclose(fp);
    
    // Ordering the students by registration number in crescent order via bubble sort.
    for(j = 0; j < i; j++){
        for(l = (j+1); l < i; l++){
            if(alunos[l].ra < alunos[j].ra){
                temp = alunos[j];
                alunos[j] = alunos[l];
                alunos[l] = temp;
            }
        }
    }
    
    // Adjusting the students semesters order via bubble sort.
    for(j = 0; j < i; j++){
        for(l = (j+1); l < i; l++){
            if(alunos[l].ra == alunos[j].ra && alunos[l].semestre < alunos[j].semestre){
                temp = alunos[j];
                alunos[j] = alunos[l];
                alunos[l] = temp;
            }
        }
    }
    
    // Checks if the student has any enrollment.
    for(j = 0; j < i; j++){
        if(user.ra == alunos[j].ra){
            validador = 1;
            
            break;
        }else{
            validador = 0;
        }
    }
    
    // Student doesn't have any enrollments.
    if(validador == 0){
        // Creating student record file.
        fp = fopen(ra, "w");
    
        if(fp == NULL)
           return 1; // Couldn't create the file, interrupting the function.
        
        fputs("School of Technology - UNICAMP\n", fp);
        fputs("\n", fp);
        fputs("Enrollment Report\n", fp);
        fputs("\n", fp);

        fprintf(fp, "Full Name: %s\n", user.nome);
        fprintf(fp, "Registration Number: %d\n", user.ra);
        fprintf(fp, "Efficiency Coeficient: None\n");
        fprintf(fp, "Student classification on class: N/A of %d\n", m);
        
        fputs("\n", fp);
    
        fputs("Subject\t\tScore\tAbsences(%)\tSituation\n", fp);
        
        fputs("The student doesn't have any enrollments!\n", fp);
        
        fflush(fp);
        fclose(fp);
        
        puts("Record file generated successfully!");
        puts("Type ENTER to continue...");
        getchar();

        return 0;
    }
    
    // Opening this file to count the number of subjects on the file.
    fp = fopen("Disciplinas.txt", "r");
    
    if(fp == NULL)
       return 1; // Couldn't open the file, interrupting the function.
    
    k = 0; // Will store the number of subjects the student enrolled in the semester.
    
    // Counting the number of subjects the student enrolled in the semester. 
    while(!feof(fp)){
        fscanf(fp,"%5[^,],%100[^,],%d\n", tmp.codigo, tmp.nome, &tmp.creditos);

        k++;
    }
    
    fflush(fp);
    fclose(fp);
    
    // Opening this file to save the subjects on a struct.
    fp = fopen("Disciplinas.txt", "r");
    
    if(fp == NULL)
       return 1; // Couldn't open the file, interrupting the function.
    
    // Will store the subjects the student enrolled.
    disc = (Disciplina *) malloc(k * sizeof(Disciplina));
    
    l = 0; // Will indicate the position of the array below.
    
    // Saving the subjects the student enrolled.
    while(!feof(fp)){
        fscanf(fp,"%5[^,],%100[^,],%d\n", disc[l].codigo, disc[l].nome, &disc[l].creditos);

        l++;
                    
        // Preventing the loop from going to a unexistent position.
        if(l >= k)
            break;
    }
    
    fflush(fp);
    fclose(fp);
    
    // Initializing those variables.
    contcn = 0;
    contcred = 0;
    
    // Calculates the students' efficiency coeficient.
    for(l = 0; l < m; l++){ // 1st loop repeats by the amount of registered students.
       for(j = 0; j < i; j++){ // 2nd loop repeats by the amount of enrollments.
           // Student found.
           if(aluno[l].ra == alunos[j].ra){
               for(n = 0; n < k; n++){ // 3rd loop repeats by the amount of subjects.
                   //Subject found.
                   if(strcmp(alunos[j].codigo, disc[n].codigo) == 0){
                       if(alunos[j].nota == -1)
                           break;
                       
                       contcn += (disc[n].creditos * alunos[j].nota);
                       contcred += disc[n].creditos;
                       
                       break;
                   }
               }
           }
       }
       
       coeficiente[l] = (contcn / contcred); // Calculating the coeficient.
       
       // Score and absence wasn't updated.
       if(contcn == 0 && contcred == 0)
           coeficiente[l] = 0;
       
       contcn = 0; // Attibuting zero to use again.
       contcred = 0; // Attibuting zero to use again.
       
       // Record being made is of the user.
       if(user.ra == aluno[l].ra){
           valpos = coeficiente[l]; // Saving the user coeficient value.
       }
    }

    // Ordering the array via bubble sort.
    for(l = 0; l < m; l++){
        for(j = (l+1); j < m; j++){
            if(coeficiente[j] < coeficiente[l]){
                aux = coeficiente[l];
                coeficiente[l] = coeficiente[j];
                coeficiente[j] = aux;
            }
        }
    }
    
    // Finding the student position in the classification.
    for(l = 0; l < m; l++){
        // Position found.
        if(valpos == coeficiente[l]){
            pos = l+1;
        }
    }
    
    // Creating student record file.
    fp = fopen(ra, "w");
    
    if(fp == NULL)
       return 1; // Couldn't create the file, interrupting the function.
        
    fputs("School of Technology - UNICAMP\n", fp);
    fputs("\n", fp);
    fputs("Enrollment Report\n", fp);
    fputs("\n", fp);
    
    fprintf(fp, "Full Name: %s\n", user.nome);
    fprintf(fp, "Registration Number: %d\n", user.ra);
    
    // Score and absence weren't updated.
    if(valpos == 0){
        fprintf(fp, "Efficiency Coeficient: None\n");
        fprintf(fp, "Student position on class: N/A of %d\n", m);
    }else{ // Score and absence were updated.
        fprintf(fp, "Efficiency Coeficient: %.2f\n", valpos);
        fprintf(fp, "Student position on class: %d of %d\n", (m+1-pos), m);
    }
    
    fputs("\n", fp);
    
    fputs("Subject\t\tScore\tAbsences(%)\tSituation\n", fp);
    
    // Saving the enrollments on the record file.
    for(j = 0; j < i; j++){
        if(user.ra == alunos[j].ra){
            // Score and absence weren't updated.
            if(alunos[j].nota == -1){
                fprintf(fp, "%s\t\tN/A\t\tN/A\t\t\tUndefined, score and absence weren't updated!\n", 
                        alunos[j].codigo);
                
                continue;
            }
            
            if(alunos[j].nota >= 5 && alunos[j].faltas < 25){
                fprintf(fp, "%s\t\t%.1f\t\t%.1f\t\t\tApproved by Score and Frequency\n", 
                        alunos[j].codigo, alunos[j].nota, alunos[j].faltas);
            }else{
                if(alunos[j].nota < 5){
                    fprintf(fp, "%s\t\t%.1f\t\t%.1f\t\tFailed by Score\n", 
                            alunos[j].codigo, alunos[j].nota, alunos[j].faltas);
                }else{
                    fprintf(fp, "%s\t\t%.1f\t\t%.1f\t\tFailed by Frequency\n", 
                        alunos[j].codigo, alunos[j].nota, alunos[j].faltas);
                }
            }
        }
    }
    
    fflush(fp);
    fclose(fp);
    
    puts("Record file generated successfully!");
    puts("Type ENTER to continue...");
    getchar();
    
    return 0;
}