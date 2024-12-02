#include <stdio.h>  // Include the standard input/output library

// Function prototypes
int intInputChecker(const char *message);  // Function to get and validate integer input
int getAge();                              // Function to prompt and validate age input
const char * getGender();                  // Function to prompt and validate gender input

int main() {
    int age;                // Variable to store user's age
    const char *ageGroup = "Invalid"; // Store ageGroup as a string
    const char *gender;     // Pointer to store user's gender as a string

    // Initial input of age and gender
    age = getAge();           // Prompt user for age
    gender = getGender();     // Prompt user for gender

    while (1) {
        // Age classification using nested if statements
        if (age >= 0) {
            if (age <= 2) {
                // Age between 0 and 2: Infant
                ageGroup = "Infant";
            }
            if (age > 2 && age <= 4) {
                // Age between 3 and 4: Toddler
                ageGroup = "Toddler";
            }
            if (age > 4 && age <= 6) {
                // Age between 5 and 6: Preschooler
                ageGroup = "Preschooler";
            }
            if (age > 6 && age <= 12) {
                // Age between 7 and 12: School-age
                ageGroup = "School-age";
            }
            if (age > 12 && age <= 19) {
                // Age between 13 and 19: Teenager
                ageGroup = "Teenager";
            }
            if (age > 19 && age <= 29) {
                // Age between 20 and 29: Young adult
                ageGroup = "Young adult";
            }
            if (age > 29 && age <= 39) {
                // Age between 30 and 39: Adult
                ageGroup = "Adult";
            }
            if (age > 39 && age <= 59) {
                // Age between 40 and 59: Middle-aged adult\n");
                ageGroup = "Middle-aged adult";
            }
            if (age > 59) {
                // Age 60 and above: Senior
                ageGroup = "Senior";
            }
        } else {
            // Negative age entered (should not occur due to prior validation)
            printf("Invalid age entered.\n");
            // Re-prompt for age
            age = getAge();
            continue; // Restart the loop
        }

         // Confirmation step to verify user information
        int response;  // Variable to store user's response
        printf("\nIs the information correct?\n");
        printf("Age: %d\n", age);
        printf("Gender: %s\n", gender);
        printf("1) Confirm\n");
        printf("2) Change Age\n");
        printf("3) Change Gender\n");
        printf("Enter your choice: ");
        response = intInputChecker("");  // Get user's choice

        if (response == 1) {
            // Information confirmed, exit the loop
            break;
        } else if (response == 2) {
            // User wants to change age
            age = getAge();  // Prompt for new age
            // Loop will reclassify the age group with the new age
            continue;
        } else if (response == 3) {
            // User wants to change gender
            gender = getGender();  // Prompt for new gender
            // Loop will continue to confirmation
            continue;
        } else {
            // Invalid choice entered
            printf("Invalid choice. Please try again.\n");
            // Continue the loop to re-display the confirmation step
            continue;
        }
    }

    // Display the final information
    printf("\nFinal Information:\n");
    printf("Age: %d\n", age);
    printf ("Age Group: %s\n", ageGroup);
    printf("Gender: %s\n", gender);

    return 0;
}

// Function to prompt and validate the user's age
int getAge() {
    int age;  // Variable to store the age input
    while (1) {  // Loop until a valid age is entered
        age = intInputChecker("your age");  // Prompt user for age
        if (age < 0) {
            // Age cannot be negative
            printf("Please enter a valid age.\n");
            continue;  // Prompt again
        }
        return age;  // Valid age entered, return value
    }
}

// Function to prompt and validate the user's gender
const char* getGender() {
    int genderChoice;              // Variable to store the gender choice input
    const char *genderName = "Invalid";  // Pointer to store the gender as a string

    while (1) {  // Loop until a valid gender choice is made
        // Display gender options
        printf("\nInput the corresponding number for gender:\n");
        printf("1) Male\n");
        printf("2) Female\n");
        printf("3) Non-binary\n");
        printf("4) Prefer not to say\n");
        printf("Enter your gender choice: ");
        genderChoice = intInputChecker("");  // Get user's gender choice

        if (genderChoice == 1) {
            genderName = "Male";  // Set gender to Male
        } else if (genderChoice == 2) {
            genderName = "Female";  // Set gender to Female
        } else if (genderChoice == 3) {
            genderName = "Non-binary";  // Set gender to Non-binary
        } else if (genderChoice == 4) {
            genderName = "Prefer not to say";  // Set gender to Prefer not to say
        } else {
            // Invalid choice entered
            printf("Invalid input. Please try again.\n");
            continue; // Prompt again for valid input
        }
        break; // Valid input received, exit loop
    }
    return genderName;  // Return the selected gender
}

// Function to get and validate integer input from the user
int intInputChecker(const char *message) {
    int num;      // Variable to store the integer input
    char term;    // Variable to detect additional characters after integer

    while (1) {  // Loop until a valid integer is entered
        if (message[0] != '\0') {
            // Display the message prompt if provided
            printf("Enter %s: ", message);
        }
        // Use scanf to read integer and check for extra input
        if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
            // Input is invalid if not an integer followed by newline
            // Clear the input buffer in case of invalid input
            while (getchar() != '\n');
            printf("Input not an integer! Please try again.\n");
        } else {
            // Valid integer input received
            return num;  // Return the integer value
        }
    }
}