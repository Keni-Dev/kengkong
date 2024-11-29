#include <stdio.h>
#include <string.h>
int ageGroupChecker(int age) {
    if (age < 0) return 0;          // Invalid
    else if (age <= 2) return 1;    // Infants 0-2
    else if (age <= 4) return 2;    // Toddlers 3-4 
    else if (age <= 6) return 3;    // Preschoolers 5-6
    else if (age <= 12) return 4;   // School-age 7-12
    else if (age <= 19) return 5;   // Teenagers 13-19
    else if (age <= 29) return 6;   // Young Adults 20-29
    else if (age <= 39) return 7;   // Adults 30-39
    else if (age <= 59) return 8;   // Middle Age Adults 40-59
    else if (age >= 60) return 9;   // Seniors 60+
    return 0;
}

int main()  {
    // Input - Name, Birthdate, gender
    // Features - chinese sign, major events, health recomendation, funfacts per age group, 
    // major events 1900 - 2024 124, health recommendations

    // Infants 0-2              1-5 infants, 1 toddlers - eunice
    // Toddlers 2-4             2-5 toddlers, 1-2 preschool - charina
    // Presschoolers 4-6        3-5 preschool, 1-3 schoolage - joseph
    // school-age 6-12          4-5 schoolage, 1-4 teenagers - kc
    // teenagers 13-19          5 teenagers, 1-5 young adults - laurice 
    // young adults 20-29       1-5 adults, 1 middle age - olive
    // adults 30 - 39           2-5 middle age, 2 senior - yangel
    // middle age adults 40-59
    // seniors 60+

    // 1900 - 1915 akira
    // 16 - 30 charina
    // 31 - 45 eunice
    // 46 - 60 jospeh 
    // 61 - 75 kc
    // 76 - 90 olive
    // 91 - 2005 yangel
    // 2006 - current laurice

    int age;
    char gender [10];

    printf("Enter your age: \n");
    scanf("%d", &age);
    printf("Enter gender M/F/Non-Binary: \n");
    scanf("%s", gender);

    if (age < 0){
        printf("Invalid age.\n");
    } else if (age <= 12){
        if (strcmp(gender, "M") == 0 || strcmp(gender, "m") == 0){
            printf("You are a young boy. \n");
        } else if (strcmp(gender, "F") == 0 || strcmp(gender, "f") == 0){
            printf("You are a young girl. \n");
        } else if (strcmp(gender, "Non-binary") == 0 || strcmp(gender, "non-binary") == 0){
            printf("You are a young non-binary. \n");
        } else {
            printf("Invalid gender.\n");
        }

    } else if (age < 18){
        if (strcmp(gender, "M") == 0 || strcmp(gender, "m") == 0){
            printf("You are a teenage boy. \n");
        } else if (strcmp(gender, "F") == 0 || strcmp(gender, "f") == 0){
            printf("You are a teenage girl. \n");
        } else if (strcmp(gender, "Non-binary") == 0 || strcmp(gender, "non-binary") == 0){
            printf("You are a teenage non-binary. \n");
        } else {
            printf("Invalid gender.\n");
        }

    } else if (age < 60){
        if (strcmp(gender, "M") == 0 || strcmp(gender, "m") == 0){
            printf("You are an adult man. \n");
        } else if (strcmp(gender, "F") == 0 || strcmp(gender, "f") == 0){
            printf("You are an adult woman. \n");
        } else if (strcmp(gender, "Non-binary") == 0 || strcmp(gender, "non-binary") == 0){
            printf("You are an adult non-binary. \n");
        } else {
            printf("Invalid gender.\n");
        }

    } else {
        if (strcmp(gender, "M") == 0 || strcmp(gender, "m") == 0){
            printf("You are a senior man. \n");
        } else if (strcmp(gender, "F") == 0 || strcmp(gender, "f") == 0){
            printf("You are a senior woman. \n");
        } else if (strcmp(gender, "Non-binary") == 0 || strcmp(gender, "non-binary") == 0){
            printf("You are a senior non-binary. \n");
        } else {
            printf("Invalid gender.\n");
        }    
    }
    return 0;
}

int age_group(int age) {
    if (age < 0) return 0;
    else if (age <= 2) return 1;
    else if (age <= 6) return 2;
    else if (age <= 12) return 3;
    else if (age <= 19) return 4;
    else if (age <= 29) return 5;
    else if (age <= 39) return 6;
    else if (age <= 59) return 7;
    else if (age >= 60) return 8;
}

    // Infants 0-2 
    // Toddlers 2-4
    // Presschoolers 4-6
    // school-age 6-12
    // teenagers 13-19
    // young adults 20-29
    // adults 30 - 39
    // middle age adults 40-59
    // seniors 60+