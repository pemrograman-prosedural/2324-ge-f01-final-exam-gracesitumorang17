// 12S23038 - Alya Triswani
// 12S23048 - Grace Caldera Situmorang

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"

#define MAX_DORMS 50
#define MAX_STUDENTS 50
#define LINE_LENGTH 255
#define DELIMITER "#"

int main(int _argc, char **_argv)
{   
    DORM* LEFT = (DORM*) malloc(sizeof(DORM));
    strcpy(LEFT->name,"left");
    LEFT->capacity = 10;
    LEFT->gender = GENDER_FEMALE;
    LEFT->residents_num = 0;
    DORM dorms[MAX_DORMS];
    STUDENT students[MAX_STUDENTS];
    
    unsigned short totalDorm = 0;
    unsigned short totalStudent = 0;
    char line[LINE_LENGTH];
    char* token;
    char* _dorm_name; 
    int _capacity; 

    // Reading input lines
    while (fgets(line, LINE_LENGTH, stdin) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0'; // Remove newline characters

        // Break on '---'
        if (strcmp(line, "---") == 0) break;
        
        // Process dorm and student commands
        token = strtok(line, DELIMITER);
        if (strcmp(token, "dorm-add") == 0) {
            _dorm_name = strtok(NULL, DELIMITER); 
            _capacity = atoi(strtok(NULL, DELIMITER)); 
            token = strtok(NULL, DELIMITER);
            enum gender_t _gender; 
            if (strcmp(token, "male") == 0) {
                _gender = GENDER_MALE;
            } else if (strcmp(token, "female") == 0) {
                _gender = GENDER_FEMALE;
            }
            dorms[totalDorm] = create_dorm(_dorm_name, _capacity, _gender); 
            totalDorm++;
        } else if (strcmp(token, "student-add") == 0) {
            char* _student_id = strtok(NULL, DELIMITER); 
            char* _student_name = strtok(NULL, DELIMITER); 
            int _student_year = atoi(strtok(NULL, DELIMITER)); 
            char str_year[5];
            sprintf(str_year, "%d", _student_year);
            token = strtok(NULL, DELIMITER);
            enum gender_t _gender; 
            if (strcmp(token, "male") == 0) {
                _gender = GENDER_MALE;
            } else if (strcmp(token, "female") == 0) {
                _gender = GENDER_FEMALE;
            }
            students[totalStudent] = create_student(_student_id, _student_name, str_year, _gender); 
            totalStudent++;
        } else if (strcmp(token, "assign-student") == 0) {
            char* _student_id = strtok(NULL, DELIMITER); 
            char* _dorm_name = strtok(NULL, DELIMITER); 
            short studentInd = findSTUDENTInd(_student_id, students, totalStudent);
            short dormInd = findDORMInd(_dorm_name, dorms, totalDorm);
            if (studentInd >= 0 && dormInd >= 0) {
                assign(&students[studentInd], &dorms[dormInd]);
            }
        } else if (strcmp(token, "dorm-empty") == 0) {
            _dorm_name = strtok(NULL, DELIMITER); 
            short dormInd = findDORMInd(_dorm_name, dorms, totalDorm);
            if (dormInd >= 0) {
                STUDENT *residentPtrs[MAX_STUDENTS];
                int residentCount = 0;
                for (size_t i = 0; i < totalStudent; i++) {
                    if (students[i].dorm == &dorms[dormInd]) {
                        residentPtrs[residentCount++] = &students[i];
                    }
                }
            }
          

            } else if (strcmp(token, "student-leave") == 0){
              token = strtok(NULL, DELIMITER);
              short studentInd = findSTUDENTInd(token, students,totalStudent);
              short dormInd = findDORMInd(students->dorm->name, dorms, totalDorm);
                unassign(&students[studentInd], &dorms[dormInd]);
                students[studentInd].dorm = LEFT; 
            }
        
        
        // Print student details
    for (size_t i = 0; i < totalStudent; i++) {
        printSTUDENT(students[i]);
    }

    // Print dorm details
    for (size_t i = 0; i < totalDorm; i++) {
        print_dorm(dorms[i]);
    }

    // Print unassigned students after dorm-empty
    for (size_t i = 0; i < totalStudent; i++) {
        if (students[i].dorm == NULL) {
            printStudentDetails(students[i]);
        }
    }

    // Print dorm details after dorm-empty
    for (size_t i = 0; i < totalDorm; i++) {
        print_DORMDetails(dorms[i], true);
    }
    return 0;



    }