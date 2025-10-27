#include <stdio.h>
#include <string.h>

// Function to validate Y/N input
char charControl(char input);

// Function to clear the input buffer
void bufferClear();

int main(void){
    // Open file to read and append student records
    FILE *fp = fopen("student_records.csv", "a+");

    if (!fp){
        printf("Could not open file!\n");
        return 1;
    }

    printf("Please set up the necessary configurations before starting the system.\n\n");

    int i, x = 100, mainChoice, infoChoice, updateChoice, viewChoice;
    int latest = 0, minIndex = 0, maxIndex = 0; // Track student count and min/max indices
    float average = 0, sum = 0;
    char names[x][30]; // Array to store student names (max 100 students, name length max 29)
    char continueMain; // Y/N input for main menu
    char continueInfo; // Y/N input for information system
    float grades[x]; // Array to store student grades (max 100 students)

    // Load existing student data from file
    fseek(fp, 0, SEEK_SET);
    while (fscanf(fp, "%29[^,],%f\n", names[latest], &grades[latest]) == 2) {
        if (latest > 0) { // Update min/max grade indices
            if (grades[latest] < grades[minIndex]) minIndex = latest;
            if (grades[latest] > grades[maxIndex]) maxIndex = latest;
        }
        if (!names[latest][0]) { // Stop if name is empty
            break;
        }
        latest++; // Increment the student counter
    }
    fclose(fp);
    printf("%d students successfully loaded.\n", latest);
    printf("Welcome to the Interface. :)\n");

    do{
        // Main menu
        printf("**Student Information System**\n");
        printf("1. Enter Information\n");
        printf("2. View Averages\n");
        printf("3. View Lowest and Highest Grades\n");
        scanf("%d", &mainChoice);
        bufferClear();

        switch(mainChoice){
            case 1:
                printf("\nEntering the information system...\n\n");
                printf("Login successful!\n");
                // Sub-menu for information system
                printf("**Information System**\n");
                printf("1. New Entry\n");
                printf("2. Update Information\n");
                printf("3. View Profile\n");
                scanf("%d", &infoChoice);
                bufferClear();

                switch(infoChoice){
                    case 1:
                        // New student entry
                        do{
                        if (latest >= x){
                            printf("The list is full! Cannot add new information.\n");
                            break;
                        }
                        printf("\nNew Entry selected.\nPlease enter the student's name:\n");
                        fgets(names[latest], 30, stdin);
                        names[latest][strcspn(names[latest], "\n")] = 0; // Remove newline character
                        printf("\nNew Student Added: %s", names[latest]);
                        printf("\nEnter the student's grade: ");
                        scanf("%f", &grades[latest]);
                        bufferClear();
                        printf("\nProfile Created.\nStudent Index: %d\nName: %s\nGrade: %.2f\n", latest + 1, names[latest], grades[latest]);
                        // Update min/max indices if necessary
                        if (grades[latest] < grades[minIndex]){
                            minIndex = latest;
                        }
                        else if (grades[latest] > grades[maxIndex]){
                            maxIndex = latest;
                        }
                        latest++; // Increment student counter
                        printf("Do you want to add another student? Y/N\n");
                        scanf(" %c", &continueInfo);
                        bufferClear();
                        continueInfo = charControl(continueInfo);
                        }
                        while (continueInfo == 'y' || continueInfo == 'Y');
                    break;

                    case 2:
                        // Update existing student information
                        printf("\nUpdate Profile selected.\n");
                        printf("Please enter the student index: ");
                        scanf("%d", &updateChoice);
                        bufferClear();
                        if (updateChoice <= 0 || updateChoice > latest)
                            printf("\nNo student found at this index.\n");
                        else{
                            printf("\nRecord Found: %d. %s", updateChoice, names[updateChoice - 1]);
                            printf("\nEnter the student's new name:\n");
                            fgets(names[updateChoice - 1], 30, stdin);
                            names[updateChoice - 1][strcspn(names[updateChoice - 1], "\n")] = 0; // Remove newline
                            printf("\nEnter the student's new grade:\n");
                            scanf("%f", &grades[updateChoice - 1]);
                            bufferClear();
                            printf("\nProfile Updated.\nStudent Index: %d\nName: %s\nGrade: %.2f\n", updateChoice, names[updateChoice - 1], grades[updateChoice - 1]);
                        }
                    break;

                    case 3:
                        // View a student profile
                        printf("Please enter the student index: ");
                        scanf("%d", &viewChoice);
                        bufferClear();
                        if (viewChoice <= 0 || viewChoice > latest){
                            printf("\nNo student found at this index.\n"); 
                            break;
                        }
                        printf("\nStudent Index: %d\nName: %s\nGrade: %.2f\n", viewChoice, names[viewChoice - 1], grades[viewChoice - 1]);
                    break;
                }
            break;  

            case 2:
                // Calculate average grade
                sum = 0;
                average = 0;
                printf("\nRequest to calculate average received.\n");
                printf("Calculating average...\n");
                for (i = 0; i < latest; i++){
                    sum += grades[i];
                }
                if (latest == 0) {
                    printf("\nNo student entries yet. Cannot calculate average.\n");
                } else {
                    average = sum / latest;
                    printf("\nAverage calculated. List Average: %.2f\n", average);
                }
                break;

            case 3:
                // Display lowest and highest grades
                printf("\nRequest to view lowest and highest grades received.\n");
                if (latest == 0) {
                    printf("\nNo students yet. Please add students first.\n");
                } else {
                    printf("\nCalculating lowest grade...\n");
                    printf("Lowest Grade Calculated.\nLowest Grade: %.2f\nStudent: %s\n", grades[minIndex], names[minIndex]);
                    printf("Calculating highest grade...\n");
                    printf("Highest Grade Calculated.\nHighest Grade: %.2f\nStudent: %s\n", grades[maxIndex], names[maxIndex]);
                }   
            break;
        }

        // Ask user if they want to return to main menu
        printf("\nDo you want to return to the main menu? Y/N\n");
        scanf(" %c", &continueMain);
        bufferClear();
        continueMain = charControl(continueMain);
    }
    while (continueMain == 'y' || continueMain == 'Y');

    // Save all student data to file before exiting
    printf("\nShutting down system... See you! :)\n");
    FILE *fpw = fopen("student_records.csv", "w");
    for (int i = 0; i < latest; i++) {
        fprintf(fpw, "%s,%.2f\n", names[i], grades[i]);
    }
    fclose(fpw);
    return 0;
}

// Validate Y/N input
char charControl(char input){
    while (!(input == 'y' || input == 'Y' || input == 'n' || input == 'N')){
        printf("Invalid input. Please enter Y/N\n");
        scanf(" %c", &input);
        bufferClear();
    }
    return input;
}

// Clear input buffer to prevent unwanted characters
void bufferClear(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
