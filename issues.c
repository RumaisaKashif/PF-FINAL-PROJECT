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
}//first half of the code 







int main() {
    printHeader();
    printf("\n");
    printf("\n");

    int isAuthenticated = 0;

    // Password authentication
    if (!checkPassword()) {
        printf("Authentication failed. Exiting...\n");
        return 0;
    }

    // Test cases
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
    if (!isValidTicket(ticket1, first_row, last_row)) {
        printf("Invalid Ticket!\n");
        return 0;
    }//second half of the code 






    // Remaining code for flight reservation system
    // ...

    return 0;
}

// Remaining code for the flight reservation system
//Function to change the seat
void changeSeat(char* ticket, char* row_num, char seat) {
    // Validate row number and seat
    int new_row = atoi(row_num);
    if (new_row <= 0 || new_row > 999 || !isupper(seat)) {
        printf("Invalid row number or seat. Seat change failed.\n");
        return;
    }

    // Update the row and seat in the ticket
    sprintf(ticket + 14, "%03d%c", new_row, seat);

    printf("Seat changed successfully. New ticket: %s\n", ticket);
}

// Function to get the seat type based on the seat number
const char* getSeatType(char seat) {
    // Implementation for getting the seat type
    // Placeholder logic, replace with actual logic
    if (seat == SA || seat == SD) {
        return WINDOW;
    } else if (seat == SC || seat == SE) {
        return AISLE;
    } else {
        return MIDDLE;
    }
}

// Function to change the date of a reservation
char* changeDate(char* ticket, const char* day, const char* month, const char* year) {
    // Validate day, month, and year
    int new_day = atoi(day);
    int new_month = atoi(month);
    int new_year = atoi(year);

    if (new_month < 1 || new_month > 12 || new_day < 1 || new_day > 31) {
        printf("Invalid date. Date change failed.\n");
        return ticket;
    }

    if ((new_month == 4 || new_month == 6 || new_month == 9 || new_month == 11) && new_day > 30) {
        printf("Invalid date. Date change failed.\n");
        return ticket;
    }

    if (new_month == 2) {
        if ((new_year % 4 == 0 && new_year % 100 != 0) || (new_year % 400 == 0)) {
            if (new_day > 29) {
                printf("Invalid date. Date change failed.\n");
                return ticket;
            }
        } else if (new_day > 28) {
            printf("Invalid date. Date change failed.\n");
            return ticket;
        }
    }

    // Update the date in the ticket
    sprintf(ticket, "%04d%02d%02d%s%s", new_year, new_month, new_day, ticket + 8, ticket + 11);

    printf("Date changed successfully. New ticket: %s\n", ticket);

    return ticket;
}

    // Placeholder return, replace with actual logic
    return ticket;
}

// Function to determine if a passenger visits a specific airport
bool visits_airport(char* ticket, char* airport) {
    // Implementation for determining if a passenger visits an airport
    // ...

    return false;  // Placeholder return, replace with actual logic
}

// Function to determine if two tickets represent connecting flights
bool isConnectingFlight(char* ticket1, char* ticket2) {
    // Implementation for determining if two tickets are connecting flights
    // ...

    return false;  // Placeholder return, replace with actual logic
}

// Function to determine if two seats are adjacent
bool isAdjacent(char* ticket1, char* ticket2) {
    // Implementation for determining if two seats are adjacent
    // ...

    return false;  // Placeholder return, replace with actual logic
}

// Function to determine if one seat is behind another
bool isBehind(char* ticket1, char* ticket2) {
    // Implementation for determining if one seat is behind another
    // ...

    return false;  // Placeholder return, replace with actual logic
}

// Function to get the seat type based on the seat number
const char* getSeatType(char* ticket) {
    // Implementation for getting the seat type
    // ...

    return "Unknown";  // Placeholder return, replace with actual logic
}

// Function to validate the format of a ticket
bool isValidFormat(char* ticket) {
    // Implementation for validating the format of a ticket
    // ...

    return false;  // Placeholder return, replace with actual logic
}

// Function to make a reservation
void makeReservation() {
    // Implementation for making a reservation
    // ...
}

// Function to cancel a reservation
void cancelReservation() {
    // Implementation for canceling a reservation
    // ...
}

// Function to display reservations
void displayReservations() {
    // Implementation for displaying reservations
    // ...
}

// Function to save reservations to a file
void saveToFile() {
    // Implementation for saving reservations to a file
    // ...
}

//3rd part of the code 


// Show the main menu
void showMenu() {
    printf("1. Make Reservation\n");
    printf("2. Cancel Reservation\n");
    printf("3. Display Reservations\n");
    printf("4. Save to File\n");
    printf("5. Exit\n");
}

// Function to make a reservation
void makeReservation() {
    // Implementation for making a reservation
    // ...
}

// Function to cancel a reservation
void cancelReservation() {
    // Implementation for canceling a reservation
    // ...
}

// Function to display reservations
void display

//fourth part








// This part includes the end of the code

// Other functions (implementation remains unchanged)
// ...

