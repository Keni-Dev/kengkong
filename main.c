#include <stdio.h>
#include <string.h>

// Function prototypes
int intInputChecker(const char *message);
int getAge();
const char * getGender();

int main() {
    int age;
    const char *gender;

    // Initial input of age and gender
    age = getAge();
    gender = getGender();

    while (1) {
        // Age classification using nested if statements
        if (age >= 0) {
            if (age <= 2) {
                printf("Age group: Infant\n");
            } else {
                if (age <= 4) {
                    printf("Age group: Toddler\n");
                } else {
                    if (age <= 6) {
                        printf("Age group: Preschooler\n");
                    } else {
                        if (age <= 12) {
                            printf("Age group: School-age\n");
                        } else {
                            if (age <= 19) {
                                printf("Age group: Teenager\n");
                            } else {
                                if (age <= 29) {
                                    printf("Age group: Young adult\n");
                                } else {
                                    if (age <= 39) {
                                        printf("Age group: Adult\n");
                                    } else {
                                        if (age <= 59) {
                                            printf("Age group: Middle-aged adult\n");
                                        } else {
                                            printf("Age group: Senior\n");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            printf("Invalid age entered.\n");
            // Re-prompt for age
            age = getAge();
            continue; // Go back to the start of the loop
        }

        // Confirmation step
        int response;
        printf("\nIs the information correct?\n");
        printf("Age: %d\n", age);
        printf("Gender: %s\n", gender);
        printf("1) Confirm\n");
        printf("2) Change Age\n");
        printf("3) Change Gender\n");
        printf("Enter your choice: ");
        response = intInputChecker("");

        if (response == 1) {
            // Information confirmed, exit the loop
            break;
        } else if (response == 2) {
            // User wants to change age
            age = getAge();
            // Reclassify the age group with the new age
            continue;
        } else if (response == 3) {
            // User wants to change gender
            gender = getGender();
            // Continue to confirmation
            continue;
        } else {
            printf("Invalid choice. Please try again.\n");
            // Continue the loop to re-display the confirmation step
            continue;
        }
    }

    // Display the final information
    printf("\nFinal Information:\n");
    printf("Age: %d\n", age);
    printf("Gender: %s\n", gender);

    return 0;
}

int getAge() {
    int age;
    while (1) {
        age = intInputChecker("your age");
        if (age < 0 || age > 130) {
            printf("Please enter a valid age between 0 and 130.\n");
            continue;
        }
        return age;
    }
}

const char* getGender() {
    int genderChoice;
    const char *genderName = "Invalid";

    while (1) {
        printf("Input the corresponding number for gender:\n");
        printf("1) Male\n");
        printf("2) Female\n");
        printf("3) Non-binary\n");
        printf("4) Prefer not to say\n");
        printf("Enter your gender choice: ");
        genderChoice = intInputChecker("");

        if (genderChoice == 1) {
            genderName = "Male";
        } else if (genderChoice == 2) {
            genderName = "Female";
        } else if (genderChoice == 3) {
            genderName = "Non-binary";
        } else if (genderChoice == 4) {
            genderName = "Prefer not to say";
        } else {
            printf("Invalid input. Please try again.\n");
            continue; // Prompt again for valid input
        }
        break; // Valid input received
    }
    return genderName;
}

int intInputChecker(const char *message) {
    int num;
    char term;

    while (1) {
        if (message[0] != '\0') {
            printf("Enter %s: ", message);
        }
        if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
            printf("Input not an integer! Please try again.\n");
        } else {
            // Valid integer input received
            return num;
        }
    }
}

// Enter your age: 18
// Input the corresponding number for gender:
// 1) Male
// 2) Female
// 3) Non-binary
// 4) Prefer not to say
// Enter your gender choice: 2
// Age group: Teenager

// Is the information correct?
// Age: 18
// Gender: Female
// 1) Confirm
// 2) Change Age
// 3) Change Gender
// Enter your choice: 2
// Enter your age: 19
// Age group: Teenager

// Is the information correct?
// Age: 19
// Gender: Female
// 1) Confirm
// 2) Change Age
// 3) Change Gender
// Enter your choice: 1

// Final Information:
// Age: 19
// Gender: Female