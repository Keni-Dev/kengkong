#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Define a struct to store a date
typedef struct {
    int year;
    int month;
    int day;
} Date;
typedef struct {
    int iror;
    // Add other global variables you might need
} ProgramState;
void displayEvents(int birthYear) {
    FILE *file = fopen("World_Events.csv", "r"); // Open the CSV file
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[512];
    int year;
    char event[500];

    // Define column widths
    const int yearWidth = 10;
    const int eventWidth = 40; // Max characters per line for event descriptions

    // Print table header
    printf("\n+------------+------------------------------------------+\n");
    printf("|    YEAR    | EVENT                                    |\n");
    printf("+------------+------------------------------------------+\n");

    int eventFound = 0; // Flag to check if any events are found

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d,%[^\n]", &year, event); // Read year and event
        if (year >= birthYear) { // Show events starting from birth year
            eventFound = 1; // Mark that at least one event is found

            // Print the year in the first column
            printf("| %-10d | ", year);

            // Break the event description into lines of `eventWidth` characters
            int len = strlen(event);
            for (int i = 0; i < len; i += eventWidth) {
                if (i > 0) {
                    // Print padding for subsequent lines
                    printf("| %-10s | ", "");
                }

                // Print up to `eventWidth` characters for each line
                printf("%-40.*s |\n", eventWidth, &event[i]);
            }
            // Print a separator between events
            printf("+------------+------------------------------------------+\n");
        }
    }

    if (!eventFound) {
        printf("| No events found for the given birth year onwards.       |\n");
        printf("+------------+------------------------------------------+\n");
    }

    fclose(file); // Close the file
}

int ageGroupIntChecker(int age) {
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
const char *ageGroup (int age) {
    if (age == 0) return "Invalid";
    else if (age == 1) return "Infants";
    else if (age == 2) return "Toddlers";
    else if (age == 3) return "Preschoolers";
    else if (age == 4) return "School-age";
    else if (age == 5) return "Teenagers";
    else if (age == 6) return "Young Adults";
    else if (age == 7) return "Adults";
    else if (age == 8) return "Middle Age Adults";
    else if (age == 9) return "Senior";
    else return "Invalid";

}
void genderChecker() {
    int gender = 0;                 // 0 - Invalid; 1 - Male; 2 - Female; 3 - Non-binary
    printf("Input the corresponding number for gender: \n1) Male \n2) Female \n3) Non-binary \n4) Prefer not to say \n");
    scanf("%d", &gender);

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
}

// int intInput() {
//     int num;
//     char term;
//
//     while (1) {  // Infinite loop, breaks when valid input is entered
//         printf("Enter an integer: ");
//         if (scanf("%d%c", &num, &term) != 2 || term != '\n') {
//             // Clear the input buffer in case of invalid input
//             while (getchar() != '\n');  
//             printf("Input not an integer! Please try again.\n");
//         } else {
//             // Valid integer input
//             return num;
//         }
//     }
// }

// Function to check if the input is a valid date
int isValidDate(int year, int month, int day, int yearNow, int monthNow, int dayNow) {
    if (year < 1900 || year > yearNow)
        return 0;
    if (month < 1 && month <= monthNow || month > 12 && month <= monthNow)
        return 0;
    if (day < 1 && day <= dayNow|| day > 31 && day <= dayNow)
        return 0;

    // Check months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return 0;

    // Check February
    if (month == 2) {
        int isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeapYear ? 29 : 28))
            return 0;
    }

    return 1;
}

// Function to calculate age
void calculateAge(Date birthdate, struct tm *current, ProgramState *state) {
    // Set Philippine time zone
    // setenv("TZ", "Asia/Manila", 1);
    // tzset();
    int currentYear = current->tm_year + 1900;
    int currentMonth = current->tm_mon + 1;
    int currentDay = current->tm_mday;

    int ageYears = currentYear - birthdate.year;
    int ageMonths = currentMonth - birthdate.month;
    int ageDays = currentDay - birthdate.day;

    // Adjust for negative days or months
    if (ageDays < 0) {
        ageDays += 30; // Assume 30 days in the previous month
        ageMonths--;
    }
    if (ageMonths < 0) {
        ageMonths += 12;
        ageYears--;
    } // 2024 1 1

    
    if (currentYear >= birthdate.year) {        
        if (currentMonth >= birthdate.month) {
            if (currentDay >= birthdate.day) {
                printf("\nYour age is: %d years, %d months, and %d days.\n", ageYears, ageMonths, ageDays);
                state->iror = 1;
            } else {
                printf("Day is invalid\n");
                state->iror = 2;
            }
        } else {
            printf("Month is invalid\n");
            state->iror = 2;
        }
    } else {
        printf("Year is invalid\n");
        state->iror = 2;
    }
}

void printCenteredText(const char *text, int width) {
    int len = strlen(text);
    int padding = (width - len) / 2; // Calculate left padding

    if (padding < 0) padding = 0; // Ensure no negative padding
    printf("|%*s%s%*s|\n", padding, "", text, width - len - padding, "");
}

// Function to wrap text within a specific width
void printWrappedText(const char *text, int width) {
    char buffer[256]; // Allocate a sufficiently large buffer for safety
    int len = strlen(text);

    for (int i = 0; i < len; i += width) {
        strncpy(buffer, &text[i], width);
        buffer[width] = '\0'; // Null-terminate explicitly
        printCenteredText(buffer, width);
    }
}


const char **funFacts(int ageGroup) {
    static const char *infants[] = {
        "The brain of 0 - 2 years undergoes in rapid development or growth",
        "The brain of 2 to 3 weeks babies will start to recognize the faces of the human faces",
        "The newborns has a better hearing than vision since their vision is still  blurry of and in tact of developing.",
        "A year old child is able to understand simple words such as 'no' and 'bye-bye'",
        "An infant is able to recognize music" 

    };
    static const char *toddlers[] = {
        "They are able to engage the imaginative play like thinking of self that they are able to fly and etc.",
        "The attention span of a toddler is usually about 3-5 minutes for every year of age. This is why they switch from one activity to another so quickly!",
        "Toddlers love to imitate adults and older children, copying behaviors, words, and even chores as they try to understand the world.",
        "By 3-4 years old, you often recognize and remember people you have met, even if you haven't seen them in a while. This is a big part of your social development.",
        "Many toddlers like you go through a picky eating phase, while some of you enjoy experimenting with new foods."

    };
    static const char *preSchoolers[] = {
        "Preschool age groups have an impressive memory, often recalling events and information better than adults.",
        "Preschool age might have imaginary friends, which is a normal part of development and enhances creativity.",
        "During these years, preschool age groups will experience a number of exciting events, like learning to read, entering school, and losing their first tooth.",
        "Children  in this age range frequently show their affection in public, whether through hugs, or drawings.",
        "Preschool age group loves experimenting with the world around them, whether it's mixing colors, building with blocks, or observing bugs in the yard."
    };
    static const char *schoolAge[] = {
        "Kids like you have developed logical thinking, understanding cause and effect, and solving problems step-by-step!",
        "School-age starts understanding and following complex rules, making games with structured rules appealing!",
        "School-age children need about 9-12 hours of sleep per night to support their growth!",
        "School-aged kids are pros at creative excuses. From 'the dog ate my homework' to 'I left it in another dimension', they've got it all covered!",
        "School aged kids can hide almost anything on their desks—snacks, toys, notes, or even last month's sandwich!"
    };
    static const char *teenagers[] = {
        "Teenagers can spend hours mastering a 15-second dance move but claim they don't have time to clean their room!",
        "Teenagers create and adopt slang so quickly that by the time parents figure it out, it's already outdated!",
        "Teenagers need about 8-10 hours of sleep a night but often act like sleep-deprived zombies. Yet, they can somehow sleep 14 hours straight on weekends!",
        "Teenagers claim they have no homework… until 10 PM, when suddenly they have a massive project due the next day!",
        "Teens like you can stay up all night binge-watching shows but will fight tooth and nail to avoid waking up before noon. Breakfast? What’s that?!"
    };
    static const char *youngAdults[] = {    
        "Young adults are often associated with peak creativity. Many artists, scientists, and entrepreneurs make groundbreaking achievements in their 20s and 30s!",
        "If there is a viral dance, quirky slang, or a questionable new drink at Starbucks, young adults are to blame!",
        "Young adults are somehow simultaneously the most active and the most exhausted humans on the planet. Nap culture is real!"
        "Young adults like you got LinkedIn, a résumé, and five side hustles, but they're still Googling, “What job suits my vibe?”",
        "Young adults like you tend to have smaller but more meaningful social circles as they prioritize close friendships and relationships over larger social groups!"
    };
    static const char *adults[] = {
        "Adults juggling so much that those 'brain farts' and moments of complete forgetfulness are practically a badge of honor.  Don't worry, it happens to the best of us!",
        "Adults become a master of pretending they know what they're doing, even when they are completely clueless. That's adulting, baby!",
        "After years of late nights, adults discovered the simple joy of a cozy night in, complete with pajamas and a good movie.  Embrace the chill!",
        "Your online presence is picture-perfect, but behind the scenes, you're battling laundry mountains and existential crises.  It's the curated life, my friend!",
        "You've mastered the art of the power nap. It's your secret weapon for surviving the day. You can fall asleep practically anywhere, anytime!"
    };
    static const char *middleAgeAdults[] = {
        "You've ascended to the throne of corny dad jokes. Prepare for a never-ending stream of groan-worthy puns and terrible jokes.  You're not trying to be funny; it's just who you are now.  Embrace your inner dad joke king/queen!",
        "Middle aged adults often have valuable skills and knowledge from years of work and life.",
        "Middle aged adults like you are good at giving advice they've been through a lot and have a lot to share.",
        "Middle aged adults learned that true happiness comes from experiences and relationships, not material possessions.",
        "They've seen a lot and have learned to laugh at life's ups and downs."
    };
    static const char *senior[] = {
        "Many seniors prioritize their health and wellbeing and enjoy activities like walking, gardening, and dancing.",
        "They've learned to prioritize what matters most and let go of things they can't control.",
        "They've learned to enjoy their own thoughts and appreciate quiet moments of reflection.",
        "Older adults tend to experience more positive emotions than younger adults."
        "Loss of mobility, hearing, and vision are the most common health complaints."
    };
    static const char *nullFact[] = {
        "Not a valid age group!"
    };

    // Return the appropriate array based on the age group
    if (ageGroup == 1) return infants;
    else if (ageGroup == 2) return toddlers;
    else if (ageGroup == 3) return preSchoolers;
    else if (ageGroup == 4) return schoolAge;
    else if (ageGroup == 5) return teenagers;
    else if (ageGroup == 6) return youngAdults;
    else if (ageGroup == 7) return adults;
    else if (ageGroup == 8) return middleAgeAdults;
    else if (ageGroup == 9) return senior;
    else return nullFact;
}

void printFunFacts(int ageGroupInt) {
    const char **facts = funFacts(ageGroupInt); // Retrieve facts for the age group
    int factCount = 2; // Set the fact count manually for each group

    const int width = 55; // Table width

    srand(time(NULL)); // Seed random number generator
    char *selectedFact = facts[rand() % factCount];
    sprintf(selectedFact, "%s (%s)", selectedFact, ageGroup(ageGroupInt));
    printf("\n+-------------------------------------------------------+\n");
    printf("|                     DID YOU KNOW?                     |\n");
    printf("+-------------------------------------------------------+\n");
    printWrappedText(selectedFact, width);
    printf("+-------------------------------------------------------+\n");
}
ProgramState state;
int main() {
    printf("+-------------------------------------------------------+\n|                  Age Classification                   |\n+-------------------------------------------------------+\n");

    // Getting name 
    printf("Enter your full name: ");
    char name[64];
    char firstName[32];
    fgets(name, sizeof(name), stdin);
    sscanf(name, "%s", firstName);  // Extract the first word (until a space)


    // Getting birthdate
    Date birthdate;
    time_t now = time(NULL);
    struct tm *current = localtime(&now);
    int currentYear = current->tm_year + 1900;
    int currentMonth = current->tm_mon + 1;
    int currentDay = current->tm_mday;

    state.iror = 1;

    while (1) {
        printf("Enter your birthdate (YYYY MM DD): ");
        state.iror =1;
        // Validate input
        if (scanf("%d %d %d", &birthdate.year, &birthdate.month, &birthdate.day) != 3) {
            printf("Invalid input. Please enter numeric values for year, month, and day.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Check if the date is valid
        if (!isValidDate(birthdate.year, birthdate.month, birthdate.day,  currentYear, currentMonth, currentDay)) {
            printf("Invalid date. Please try again.\n");
            continue;
        }
        printf("%d", state.iror);
        // If valid, calculate age and exit loop
        if (state.iror == 1) {
            calculateAge(birthdate, current, &state);
            if (state.iror == 2) {
                printf("Invalid date. Please try again.\n");\
                continue;
            }
        }
        else if (state.iror == 2) {
            printf("Invalid date. Please try again.\n");
            continue;
        }
        break;
    }

    // Birthdate stored in the `birthdate` struct can be used later
    // printf("Stored birthdate: %d-%02d-%02d\n", birthdate.year, birthdate.month, birthdate.day);

    int age = currentYear - birthdate.year;
    int ageGroup = ageGroupIntChecker(age);

    genderChecker();
    displayEvents(birthdate.year);
    printFunFacts(ageGroup);
    // printf("%d", ageGroupChecker(birthYear));
    return 0;
}
