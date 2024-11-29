#include <stdio.h>
#include <string.h>

int main() {
    int age = intInputChecker();
    int gender;

    printf("Input the corresponding number for gender: \n1) Male \n2) Female \n3) Non-binary \n4) Prefer not to say \n");
    scanf("%d", &gender);

    if (age >= 0) {
        if (age <= 2) {
            printf("Infant\n");
        } else {
            if (age <= 4) {
                printf("Toddler\n");
            } else {
                if (age <= 6) {
                    printf("Preschooler\n");
                } else {
                    if (age <= 12) {
                        printf("School-age\n");
                    } else {
                        if (age <= 19) {
                            printf("Teenager\n");
                        } else {
                            if (age <= 29) {
                                printf("Young adult\n");
                            } else {
                                if (age <= 39) {
                                    printf("Adult\n");
                                } else {
                                    if (age <= 59) {
                                        printf("Middle age adult\n");
                                    } else {
                                        printf("Senior\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        printf("Invalid age\n");
    }
    switch(gender) {
        case 1:
            printf("Gender: Male\n");
            break;
        case 2:
            printf("Gender: Female\n");
            break;
        case 3:
            printf("Gender: Non-binary\n");
            break;
        case 4:
            printf("Gender: Not specified\n");
            break;
        case 0:
        default:
            printf("Invalid input.\n");
            break;
    }

    return 0;
}
int intInputChecker() {
    int num;
    char term;

    while (1) {  // Infinite loop, breaks when valid input is entered
        printf("Enter an age: ");
        if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');  
            printf("Input not an integer! Please try again.\n");
        } else {
            // Valid integer input
            return num;
        }
    }
}