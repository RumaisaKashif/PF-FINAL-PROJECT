// Function to display menu options
void showMenu();

int main()
{
    printHeader();
    printf("\n");
    printf("\n");

    int isAuthenticated = 0;

    // Continuously prompt for password until correct password is entered
    while (!isAuthenticated) 
    {
        // Call the function to check and compare passwords
        isAuthenticated = checkPassword();

        if (!isAuthenticated) 
        {
            // Code to execute if the password is incorrect or does not meet the conditions
            printf("Please try again.\n");
        }
    }

    // Code to execute if the password is correct and meets the conditions
    printf("\nWelcome to the system! Accessing flight ticket information...\n\n");

    //test cases
    char ticket1[] = "20231121ABCDEF25A";
    char ticket2[] = "20231121DEFGHI26A";
    
    int first_row, last_row;
    printf("Enter the number of the first row and the last row: \n");
    scanf("%d %d", &first_row, &last_row);
    
    char* date = getDate(ticket1);
    printf("Date (YYYYMMDD) is: %s\n", date);
    free(date);
    
    // ... (rest of your code)

    // Display menu and handle reservations
    struct FlightReservation* reservations = NULL; // Head of the linked list
    int seatCounter = 1; // Counter for seat numbers

    int choice;
    do {
        system("cls"); // Clear the console
        showMenu(); // Display menu options
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        fflush(stdin); // Clear input buffer

        switch (choice) {
            case 1:
                makeReservation(&reservations, &seatCounter);
                break;
            case 2:
                cancelReservation(&reservations);
                break;
            case 3:
                displayReservations(reservations);
                break;
            case 4:
                saveToFile(reservations);
                break;
            case 5:
                printf("\nThank you for using the Flight Management System!\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a number between 1 and 5.\n");
        }

        if (choice != 5) {
            printf("\nPress Enter to continue...");
            getChar(); // Wait for user to press Enter
        }

    } while (choice != 5);

    // Free allocated memory before exiting
    struct FlightReservation* current = reservations;
    struct FlightReservation* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    return 0;
}

// Function to display menu options
void showMenu() {
    printf("**********************************************\n");
    printf("        Flight Management System Menu\n");
    printf("**********************************************\n\n");
    printf("1. Make a Reservation\n");
    printf("2. Cancel a Reservation\n");
    printf("3. Display Reservations\n");
    printf("4. Save Reservations to File\n");
    printf("5. Exit\n\n");
}
