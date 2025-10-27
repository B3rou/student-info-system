#include <stdio.h>
#include <string.h>

// Function declarations
char charControl(char input); // Validate 'y'/'n' input
void bufferClear();           // Clear input buffer

int main(void) {
    // Welcome and setup
    printf("Before starting the system, you need to configure some settings.\n\n");

    int i, listSize, mainChoice, infoChoice, updateChoice, viewChoice;
    int latest = 0, lowestIndex = 0, highestIndex = 0;
    float average = 0, sum = 0;

    // Ask user for the number of students
    printf("How many students do you want to register?\n");
    scanf("%d", &listSize);

    char students[listSize][30]; // Store student names (max 29 chars)
    float grades[listSize];      // Store student grades

    char continueMain;   // For main menu loop
    char continueInput;  // For submenus

    printf("Welcome to the system! :)\n");

    do {
        // Main menu
        printf("**Student Information System**\n");
        printf("1. Enter Information\n");
        printf("2. View Average Grades\n");
        printf("3. View Lowest and Highest Grades\n");
        scanf("%d", &mainChoice);
        bufferClear();

        switch (mainChoice) {
            case 1:
                // Information submenu
                printf("\nEntering the information system...\n\n");
                printf("Successfully entered the information system!\n");
                printf("**Information Menu**\n");
                printf("1. Add New Student\n");
                printf("2. Update Student Information\n");
                printf("3. View Student Profile\n");
                scanf("%d", &infoChoice);
                bufferClear();

                switch (infoChoice) {
                    case 1:
                        // Add new student
                        do {
                            if (latest >= listSize) {
                                printf("List is full! Cannot add new student.\n");
                                break;
                            }

                            printf("\nAdding new student. Enter the student's name:\n");
                            fgets(students[latest], 30, stdin);
                            students[latest][strcspn(students[latest], "\n")] = 0; // Remove newline

                            printf("\nNew student added: %s\n", students[latest]);
                            printf("Enter the student's grade: ");
                            scanf("%f", &grades[latest]);
                            bufferClear();

                            printf("\nProfile created.\nStudent number: %d\nName: %s\nGrade: %.2f\n",
                                   latest + 1, students[latest], grades[latest]);

                            // Update lowest/highest grade indices
                            if (grades[latest] < grades[lowestIndex]) {
                                lowestIndex = latest;
                            } else if (grades[latest] > grades[highestIndex]) {
                                highestIndex = latest;
                            }

                            latest++; // Move to next student index

                            printf("Do you want to add another student? Y/N\n");
                            scanf(" %c", &continueInput);
                            bufferClear();
                            continueInput = charControl(continueInput);

                        } while (continueInput == 'y' || continueInput == 'Y');
                        break;

                    case 2:
                        // Update student information
                        printf("\nUpdate Student Information selected.\n");
                        printf("Enter the student number to update: ");
                        scanf("%d", &updateChoice);
                        bufferClear();

                        if (updateChoice <= 0 || updateChoice > latest) {
                            printf("\nNo student exists at this number.\n");
                        } else {
                            printf("\nStudent found: %d. %s\n", updateChoice, students[updateChoice - 1]);
                            printf("Enter new name: \n");
                            fgets(students[updateChoice - 1], 30, stdin);
                            students[updateChoice - 1][strcspn(students[updateChoice - 1], "\n")] = 0;

                            printf("Enter new grade: \n");
                            scanf("%f", &grades[updateChoice - 1]);
                            bufferClear();

                            printf("\nProfile updated.\nStudent number: %d\nName: %s\nGrade: %.2f\n",
                                   updateChoice, students[updateChoice - 1], grades[updateChoice - 1]);
                        }
                        break;

                    case 3:
                        // View a student's profile
                        printf("Enter the student number to view: ");
                        scanf("%d", &viewChoice);
                        bufferClear();

                        if (viewChoice <= 0 || viewChoice > latest) {
                            printf("\nNo student exists at this number.\n");
                            break;
                        }

                        printf("\nStudent number: %d\nName: %s\nGrade: %.2f\n",
                               viewChoice, students[viewChoice - 1], grades[viewChoice - 1]);
                        break;
                }
                break;

            case 2:
                // Calculate and display average
                sum = 0;
                average = 0;

                printf("\nRequest to calculate average received.\n");
                printf("Calculating average...\n");

                for (i = 0; i < latest; i++) {
                    sum += grades[i];
                }

                if (latest == 0) {
                    printf("\nNo students have been added yet. Cannot calculate average.\n");
                } else {
                    average = sum / latest;
                    printf("\nAverage calculated. List average: %.2f\n", average);
                }
                break;

            case 3:
                // Show lowest and highest grades
                printf("\nRequest to view lowest and highest grades received.\n");

                if (latest == 0) {
                    printf("\nNo students have been added yet. Please add students first.\n");
                } else {
                    printf("\nCalculating lowest grade...\n");
                    printf("Lowest grade calculated.\nLowest grade: %.2f\nStudent: %s\n",
                           grades[lowestIndex], students[lowestIndex]);

                    printf("Calculating highest grade...\n");
                    printf("Highest grade calculated.\nHighest grade: %.2f\nStudent: %s\n",
                           grades[highestIndex], students[highestIndex]);
                }
                break;
        }

        // Ask if user wants to return to main menu
        printf("\nDo you want to return to the main menu? Y/N\n");
        scanf(" %c", &continueMain);
        bufferClear();
        continueMain = charControl(continueMain);

    } while (continueMain == 'y' || continueMain == 'Y');

    printf("\nSystem closing... See you next time! :)\n");
    return 0;
}

// Validate 'y'/'n' input
char charControl(char input) {
    while (!(input == 'y' || input == 'Y' || input == 'n' || input == 'N')) {
        printf("Invalid input. Please enter Y/N\n");
        scanf(" %c", &input);
        bufferClear();
    }
    return input;
}

// Clear the input buffer
void bufferClear() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
