#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Define a struct to store a date
typedef struct {
    int year;
    int month;
    int day;
} Date;
typedef struct {
    int iror;
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
const char *month(int month){
    if (month == 0) return "Invalid";
    else if (month == 1) return "January";
    else if (month == 2) return "February";
    else if (month == 3) return "March";
    else if (month == 4) return "April";
    else if (month == 5) return "May";
    else if (month == 6) return "June";
    else if (month == 7) return "July";
    else if (month == 8) return "August";
    else if (month == 9) return "September";
    else if (month == 10) return "October";
    else if (month == 11) return "November";
    else if (month == 12) return "December";
}
void genderChecker() {
    int gender = 0;                 // 0 - Invalid; 1 - Male; 2 - Female; 3 - Non-binary
    printf("\nInput the corresponding number for gender: \n1) Male \n2) Female \n3) Non-binary \n4) Prefer not to say \n");
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

    if (birthdate.year > currentYear ||
        (birthdate.year == currentYear && birthdate.month > currentMonth) ||
        (birthdate.year == currentYear && birthdate.month == currentMonth && birthdate.day > currentDay)) {
        printf("Invalid date\n");
        state->iror = 2;
    } else {
        state->iror = 1;
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
    int factCount = 5; // Set the fact count manually for each group

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

const char **healthReco(int ageGroup) {
    static const char *infants[] = {
        "Infants are required breastfeeding since it provides the nutrients and antibodies your baby needs.",
        "Vaccinations is required to infants so that they can be protected against diseases like polio, and pertussis.",
        "Hygiene is very important to infants such as changing diapers and cleaning them with wipes and at least bath them 2 - 3 times a week so that the over - bathing can be avoided",
    };
    static const char *toddlers[] = {
        "Toddlers are required to do physical activity daily which include running, playing, dancing and other age - appropriate to ensure that bones are stretched",
        "It is required to eat nutritions such as vegetables so that having cavities for toddlers can be avoided",
        "Avoid eating too much sweets so that having broken tooths in early age can be avoided."
    };
    static const char *preSchoolers[] = {
        "Regular pediatrician visits are important to monitor growth milestones and receive necessary vaccinations.",
        "It's essential to create a safe home environment by childproofing and teaching basic safety rules.",
        "Preschoolers should have a balanced diet rich in fruits, vegetables, whole grains, and lean proteins to support their growth."
    };
    static const char *schoolAge[] = {
        "You must know the importance of personal safety, such as knowing their address and phone number, and understanding stranger danger.",
        "You must know the body image positively by emphasizing the importance of healthy eating and regular exercise, rather than focusing on weight or appearance.",
        "You must know the importance of personal safety, such as knowing their address and phone number, and understanding stranger danger."
    };
    static const char *teenagers[] = {
        "Ensure a diet rich in fruits, vegetables, whole grains, lean proteins, and dairy for growth and energy and avoid sweets like candies",
        "Balance academic, extracurricular, and leisure activities to avoid burnout.",
        "Promote positive body image and self-confidence. Remind them that social media often shows unrealistic standards."
    };
    static const char *youngAdults[] = {    
        "Take time to relax and be present, whether through yoga, hiking, or even just disconnecting from your phone for an hour.",
        "Young adulthood comes with new responsibilities, so it's important to manage stress before it overwhelms you.",
        "Practice mindfulness, journaling, or activities like yoga and deep breathing to relax your mind."
    };
    static const char *adults[] = {
        "Prioritize Sleep: Aim for 7-9 hours of quality sleep each night.  Adults often juggles demanding careers, families, and social lives, making sleep a crucial factor in managing stress, boosting energy levels, and maintaining overall well-being.",
        "Mind Your Diet:  Focus on consuming whole, unprocessed foods like fruits, vegetables, whole grains, legumes, and lean protein sources.  Limit processed foods, sugary drinks, and excessive saturated and unhealthy fats.  A balanced diet provides essential nutrients and supports overall health.",
        "Manage Stress:  Identify your stress triggers and develop healthy coping mechanisms, such as exercise, meditation, spending time in nature, or engaging in hobbies.  Chronic stress can negatively impact both physical and mental health."
    };
    static const char *middleAgeAdults[] = {
        "Engage in regular physical activity, such as brisk walking or strength training, for at least 150 minutes per week to maintain cardiovascular health and muscle strength.",
        "Prioritize a balanced diet rich in fruits, vegetables, lean proteins, whole grains, and healthy fats while limiting processed foods and added sugars.",
        "Schedule regular health checkups, including screenings for blood pressure, cholesterol, diabetes, and cancer, to catch potential issues early."
    };
    static const char *senior[] = {
        "Stay physically active with low-impact exercises like walking, swimming, or yoga to maintain mobility, strength, and balance.",
        "Focus on a nutrient-dense diet that includes adequate protein, calcium, vitamin D, and fiber to support bone health and digestion.",
        "Keep up with routine medical checkups and vaccinations, and monitor chronic conditions closely to maintain overall well-being."
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
void printHealthReco(int ageGroupInt) {
    const char **facts = healthReco(ageGroupInt); // Retrieve facts for the age group
    int factCount = 3; // Set the fact count manually for each group

    const int width = 55; // Table width

    srand(time(NULL)); // Seed random number generator
    char *selectedFact = facts[rand() % factCount];
    sprintf(selectedFact, "%s (%s)", selectedFact, ageGroup(ageGroupInt));
    printf("\n+-------------------------------------------------------+\n");
    printf("|                  Health Recommendation                |\n");
    printf("+-------------------------------------------------------+\n");
    printWrappedText(selectedFact, width);
    printf("+-------------------------------------------------------+\n");
}
ProgramState state;

void printOutFinal() {
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
    
    int age = currentYear - birthdate.year;
    int ageGroup = ageGroupIntChecker(age);
    const char *monthName = month(birthdate.month);

    genderChecker();

    printf("\n\n+-------------------------------------------------------+\n|                  Age Classification                   |\n+-------------------------------------------------------+\n");
    printf("Hello, %s! You were born on %s %d, %d and are currently %d years old.\n", 
        firstName, monthName, birthdate.day, birthdate.year, age);
    printf("\nFrom the year you were born until today, the world has experienced the following events:");
    displayEvents(birthdate.year);
    printf("\nHere are some fun facts from your age group!");
    printFunFacts(ageGroup);
    printHealthReco(ageGroup);
}

int main() {
    printOutFinal();
    
    return 0;
}