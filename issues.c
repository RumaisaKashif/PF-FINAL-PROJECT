// For Windows compatibility
#ifdef _WIN32
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define SA 'A'
#define SB 'B'
#define SC 'C'
#define SD 'D'
#define SE 'E'
#define SF 'F'
#define WINDOW "Window"
#define AISLE "Aisle"
#define MIDDLE "Middle"
#define MAX_PASSWORD_LENGTH 50

// Function prototypes
int checkPassword();
char* getDate(char* ticket);
char* getYear(char* ticket);
char* getMonth(char* ticket);
char* getDay(char* ticket);
char* getDepartureCode(char* ticket);
char* getArrivalCode(char* ticket);
int getRow(char* ticket);
char getSeatNumber(char* ticket);
bool isValidSeat(char* ticket, int first_row, int last_row);
bool isValidDate(char* ticket);
bool isValidTicket(char* ticket, int first_row, int last_row);
bool visits_airport(char* ticket, char* airport);
bool isConnectingFlight(char* ticket1, char* ticket2);
bool isAdjacent(char* ticket1, char* ticket2);
bool isBehind(char* ticket1, char* ticket2);
const char* getSeatType(char* ticket);
bool isValidFormat(char* ticket);
void changeSeat(char* ticket, char* row_num, char seat);
char* changeDate(char* ticket, char* day, char* month, char* year);
void showMenu();
void makeReservation();
void cancelReservation();
void displayReservations();
void saveToFile();

void printHeader() {
    printf("*********************************************************************************\n");
    printf("*###############################################################################*\n");
    printf("*#*****************************************************************************#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                           FLIGHT TICKET SYSTEM                            *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*                                                                           *#*\n");
    printf("*#*****************************************************************************#*\n");
    printf("*###############################################################################*\n");
    printf("*********************************************************************************\n");
}

// Alternative for getch on Windows
#ifdef _WIN32
char getChar() {
    return _getch();
}
#else
char getChar() {
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}

int main() {
   
// Main Function Starts
int main()
{
    printHeader();
    printf("\n");
    printf("\n");

    int isAuthenticated = 0;

    // Check password conditions
    int length = strlen(enteredPassword);
    int hasUppercase = 0;
    int hasLowercase = 0;
    int hasDigit = 0;

    for (int i = 0; i < length; ++i) {
        if (isupper(enteredPassword[i])) {
            hasUppercase = 1;
        } else if (islower(enteredPassword[i])) {
            hasLowercase = 1;
        } else if (isdigit(enteredPassword[i])) {
            hasDigit = 1;
        }
    }

    // Check if all conditions are met
    if (length >= 8 && hasUppercase && hasLowercase && hasDigit) {
        if (strcmp(enteredPassword, storedPassword) == 0) {
            printf("Password is correct. Access granted.\n");
            return 1; // Passwords match and conditions are met
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } else {
        printf("Password does not meet the requirements. Access denied.\n");
    }

    return 0; // Passwords do not match or conditions are not met
}
    // test cases
    char ticket1[] = "20231121ABCDEF25A";
    char ticket2[] = "20231121DEFGHI26A";

    int first_row, last_row;
    printf("Enter the number of the first row and the last row: \n");
    scanf("%d %d", &first_row, &last_row);

    char* date = getDate(ticket1);
    printf("Date (YYYYMMDD) is: %s\n", date);
    free(date);

    char* year = getYear(ticket1);
    printf("Year (YYYY) is: %s\n", year);
    free(year);

    char* month = getMonth(ticket1);
    printf("Month (MM) is: %s\n", month);
    free(month);

    char* day = getDay(ticket1);
    printf("Day (DD) is: %s\n", day);
    free(day);

    char* dep = getDepartureCode(ticket1);
    printf("Departure Airport code is: %s\n", dep);
    free(dep);

    char* arr = getArrivalCode(ticket1);
    printf("Arrival Airport code is: %s\n", arr);
    free(arr);

    int row = getRow(ticket1);
    printf("Row number is: %d\n", row);

    char seat = getSeatNumber(ticket1);
    printf("Seat %c\n", seat);
    printf("Seat type: %s\n", getSeatType(ticket1));

    // Seat and row validation
    printf("Is valid seat: %s\n", isValidSeat(ticket1, first_row, last_row) ? "true" : "false");
    printf("Is valid date: %s\n", isValidDate(ticket1) ? "true" : "false");
    printf("Is valid ticket: %s\n", isValidTicket(ticket1, first_row, last_row) ? "true" : "false");
    if (!isValidTicket(ticket1, first_row, last_row))
    {
        printf("Invalid Ticket!\n");
        return 0;
    }

    printf("Adjacent: %s\n", isAdjacent(ticket1, ticket2) ? "true" : "false");

    printf("Behind: %s\n", isBehind(ticket1, ticket2) ? "true" : "false");

    printf("Connecting flight: %s\n", isConnectingFlight(ticket1, ticket2) ? "true" : "false");

    char seatchange, new_seat;
    char new_row[3];
    printf("Press 's' to change seat, press any other alphabet to skip.\n");
    scanf(" %c", &seatchange);
    if (seatchange == 's')
    {
        printf("Enter new row number:\n");
        scanf(" %s", new_row);
        printf("Enter new seat number:\n");
        scanf(" %c", &new_seat);
        changeSeat(ticket1, new_row, new_seat);
        // check if the new ticket is a valid ticket
        if (!isValidTicket(ticket1, first_row, last_row))
        {
            printf("Invalid New Ticket!\n");
            return 0;
        }
        printf("New ticket number is: %s\n", ticket1);
    }

    char datechange;
    char new_year[5], new_month[3], new_day[3];
    printf("Press 'd' to change date, press any other alphabet to skip.\n");
    scanf(" %c", &datechange);
    if (datechange == 'd')
    {
        printf("Enter new year (YYYY):\n");
        scanf(" %s", new_year);
        printf("Enter new month (MM):\n");
        scanf(" %s", new_month);
        printf("Enter new day (DD):\n");
        scanf(" %s", new_day);
        changeDate(ticket1, new_day, new_month, new_year);
        // check if the new ticket is a valid ticket
        if (!isValidTicket(ticket1, first_row, last_row))
        {
            printf("Invalid New Ticket!\n");
            return 0;
        }
        printf("New ticket number is: %s\n", ticket1);
    }

    // Flight reservation system
    struct FlightReservation* reservationList = NULL;
    int seatCounter = 1;

    int choice;
    do
    {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            makeReservation(&reservationList, &seatCounter);
            break;
        case 2:
            cancelReservation(&reservationList);
            break;
        case 3:
            displayReservations(reservationList);
            break;
        case 4:
            saveToFile(reservationList);
            break;
        case 5:
            printf("Exiting the Flight Reservation System. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    // Free allocated memory for reservation list
    struct FlightReservation* current = reservationList;
    struct FlightReservation* next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

// Function to check the entered password against the correct password
int checkPassword()
{
    // Your password comparison logic here
    char enteredPassword[MAX_PASSWORD_LENGTH];
    char correctPassword[] = "your_password";  // Replace with your actual password

    printf("Enter the password: ");
    scanf("%s", enteredPassword);

    return strcmp(enteredPassword, correctPassword) == 0;
}

// Function to get the date from the ticket
char* getDate(char* ticket)
{
    char* date = malloc(9);
    strncpy(date, ticket, 8);
    date[8] = '\0';
    return date;
}

// Function to get the year from the ticket
char* getYear(char* ticket)
{
    char* year = malloc(5);
    strncpy(year, ticket, 4);
    year[4] = '\0';
    return year;
}

// Function to get the month from the ticket
char* getMonth(char* ticket)
{
    char* month = malloc(3);
    strncpy(month, ticket + 4, 2);
    month[2] = '\0';
    return month;
}

// Function to get the day from the ticket
char* getDay(char* ticket)
{
    char* day = malloc(3);
    strncpy(day, ticket + 6, 2);
    day[2] = '\0';
    return day;
}

// Function to get the departure airport code from the ticket
char* getDepartureCode(char* ticket)
{
    char* dep = malloc(4);
    strncpy(dep, ticket + 8, 3);
    dep[3] = '\0';
    return dep;
}

// Function to get the arrival airport code from the ticket
char* getArrivalCode(char* ticket)
{
    char* arr = malloc(4);
    strncpy(arr, ticket + 11, 3);
    arr[3] = '\0';
    return arr;
}

// Function to get the row number from the ticket
int getRow(char* ticket)
{
    char row[4];
    strncpy(row, ticket + 14, 3);
    row[3] = '\0';
    return atoi(row);
}

// Function to get the seat number from the ticket
char getSeatNumber(char* ticket)
{
    return ticket[17];
}

// Function to check if a seat is valid for a given range of rows
bool isValidSeat(char* ticket, int first_row, int last_row)
{
    int row = getRow(ticket);
    return row >= first_row && row <= last_row;
}

// Function to check if the date in the ticket is valid
bool isValidDate(char* ticket)
{
    char* year = getYear(ticket);
    char* month = getMonth(ticket);
    char* day = getDay(ticket);

    int intYear = atoi(year);
    int intMonth = atoi(month);
    int intDay = atoi(day);

    free(year);
    free(month);
    free(day);

    if (intMonth < 1 || intMonth > 12 || intDay < 1 || intDay > 31)
    {
        return false;
    }

    if ((intMonth == 4 || intMonth == 6 || intMonth == 9 || intMonth == 11) && intDay > 30)
    {
        return false;
    }

    if (intMonth == 2)
    {
        if ((intYear % 4 == 0 && intYear % 100 != 0) || (intYear % 400 == 0))
        {
            if (intDay > 29)
            {
                return false;
            }
        }
        else if (intDay > 28)
        {
            return false;
        }
    }

    return true;
}

// Function to check if a ticket is valid based on seat and date
bool isValidTicket(char* ticket, int first_row, int last_row)
{
    return isValidSeat(ticket, first_row, last_row) && isValidDate(ticket);
}

// Function to check if a ticket visits a specific airport
bool visits_airport(char* ticket, char* airport)
{
    char* dep = getDepartureCode(ticket);
    char* arr = getArrivalCode(ticket);

    int dep_visits = strcmp(dep, airport) == 0;
    int arr_visits = strcmp(arr, airport) == 0;

    free(dep);
    free(arr);
        return dep_visits || arr_visits;
}

// Function to check if two tickets are connecting flights
bool isConnectingFlight(char* ticket1, char* ticket2)
{
    char* dep1 = getDepartureCode(ticket1);
    char* arr1 = getArrivalCode(ticket1);
    char* dep2 = getDepartureCode(ticket2);
    char* arr2 = getArrivalCode(ticket2);

    int connecting = strcmp(arr1, dep2) == 0;

    free(dep1);
    free(arr1);
    free(dep2);
    free(arr2);

    return connecting;
}

// Function to check if two tickets have adjacent seats
bool isAdjacent(char* ticket1, char* ticket2)
{
    int row1 = getRow(ticket1);
    int row2 = getRow(ticket2);

    char seat1 = getSeatNumber(ticket1);
    char seat2 = getSeatNumber(ticket2);

    return row1 == row2 && abs(seat1 - seat2) == 1;
}

// Function to check if one ticket is behind another
bool isBehind(char* ticket1, char* ticket2)
{
    int row1 = getRow(ticket1);
    int row2 = getRow(ticket2);

    return row1 > row2;
}

// Function to get the seat type based on the seat number
const char* getSeatType(char* ticket)
{
    char seat = getSeatNumber(ticket);

    if (seat == SA || seat == SD)
    {
        return WINDOW;
    }
    else if (seat == SC || seat == SE)
    {
        return AISLE;
    }
    else
    {
        return MIDDLE;
    }
}

// Function to change the seat of a ticket
void changeSeat(char* ticket, char* row_num, char seat)
{
    // Update the row and seat in the ticket
    sprintf(ticket + 14, "%03s%c", row_num, seat);
}

// Function to change the date of a ticket
char* changeDate(char* ticket, char* day, char* month, char* year)
{
    // Update the date in the ticket
    sprintf(ticket, "%s%s%s%s%s", year, month, day, ticket + 8, ticket + 11);

    // Return the modified ticket
    return ticket;
}

// Function to display the main menu
void showMenu()
{
    printf("\n*********************\n");
    printf("Flight Reservation System Menu:\n");
    printf("1. Make Reservation\n");
    printf("2. Cancel Reservation\n");
    printf("3. Display Reservations\n");
    printf("4. Save Reservations to File\n");
    printf("5. Exit\n");
}

// Function to make a reservation
void makeReservation(struct FlightReservation** head, int* seatCounter)
{
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

    // Sample code to add a reservation to the linked list
    struct FlightReservation* newReservation = (struct FlightReservation*)malloc(sizeof(struct FlightReservation));

    // Initialize the new reservation (you may need to get user input for these values)
    strcpy(newReservation->passport, "123456789");
    strcpy(newReservation->name, "John Doe");
    strcpy(newReservation->email, "john.doe@example.com");
    strcpy(newReservation->destination, "LHR");
    newReservation->seatNumber = (*seatCounter)++;
    
    // Insert the new reservation at the beginning of the list
    newReservation->next = *head;
    *head = newReservation;

    printf("Reservation made successfully!\n");
}

// Function to cancel a reservation
void cancelReservation(struct FlightReservation** head)
{
    // Code to cancel a reservation
    // ...

    // Sample code to cancel the first reservation in the list
    if (*head != NULL)
    {
        struct FlightReservation* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Reservation canceled successfully!\n");
    }
    else
    {
        printf("No reservations to cancel.\n");
    }
}

// Function to display all reservations
void displayReservations(struct FlightReservation* head)
{
    // Code to display reservations
    // ...

    printf("Flight Reservations:\n");

    // Iterate through the list and print each reservation
    struct FlightReservation* current = head;
    while (current != NULL)
    {
        printf("Passport: %s, Name: %s, Email: %s, Destination: %s, Seat: %d\n",
               current->passport, current->name, current->email, current->destination, current->seatNumber);
        current = current->next;
    }
}

// Function to save reservations to a file
void saveToFile(struct FlightReservation* head)
{
    // Code to save reservations to a file
    // ...

    FILE* file = fopen("reservations.txt", "w");

    if (file != NULL)
    {
        // Iterate through the list and write each reservation to the file
        struct FlightReservation* current = head;
        while (current != NULL)
        {
            fprintf(file, "%s,%s,%s,%s,%d\n",
                    current->passport, current->name, current->email, current->destination, current->seatNumber);
            current = current->next;
        }

        fclose(file);
        printf("Reservations saved to file 'reservations.txt'.\n");
    }
    else
    {
        printf("Error opening file for writing.\n");
    }
}




