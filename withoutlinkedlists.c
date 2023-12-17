#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

#define MAX_PASSWORD_LENGTH 50

// Ticket format: (YYYY)(MM)(DD)(DEP)(ARR)(ROW)(SEAT)

struct FlightReservation {
    char passport[10];
    char name[30];
    char email[30];
    char destination[30];
    int seatNumber;
}; // End of FlightReservation Structure

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
void makeReservation(int* seatCounter);
void cancelReservation();
void displayReservations();
void saveToFile();

// Flight Ticket Header Format.

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

// Alternative for getch on Mac
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

// Main Function Starts
int main() {
    printHeader();
    printf("\n");
    printf("\n");

    int isAuthenticated = 0;

    // Continuously prompt for password until correct password is entered
    while (!isAuthenticated) {
        // Call the function to check and compare passwords
        isAuthenticated = checkPassword();

        if (!isAuthenticated) {
            // Code to execute if the password is incorrect or does not meet the conditions
            printf("Please try again.\n");
        }
    }

    // Code to execute if the password is correct and meets the conditions
    printf("Welcome to the system! Accessing flight ticket information...\n");

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
    printf("Departure Aiport code is: %s\n", dep);
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
    }

    printf("Adjacent: %s\n", isAdjacent(ticket1, ticket2) ? "true" : "false");

    printf("Behind: %s\n", isBehind(ticket1, ticket2) ? "true" : "false");

    printf("Connecting flight: %s\n", isConnectingFlight(ticket1, ticket2) ? "true" : "false");

    char seatchange, new_seat;
    char new_row[3];
    printf("Press 's' to change seat, press any other alphabet to skip.\n");
    scanf(" %c", &seatchange);
    if (seatchange == 's') {
        printf("Enter new row number:\n");
        scanf(" %s", new_row);
        printf("Enter new seat number:\n");
        scanf(" %c", &new_seat);
        changeSeat(ticket1, new_row, new_seat);
        // Check if new ticket is a valid ticket
        if (!isValidTicket(ticket1, first_row, last_row)) {
            printf("Invalid Ticket!\n");
            return 0;
        }
        printf("New Ticket: %s\n", ticket1);
    }

    char day_change[3], month_change[3], year_change[5];
    char* new_date;
    printf("Press 'd' to change date, press any other alphabet to skip.\n");
    scanf(" %c", &seatchange);
    if (seatchange == 'd') {
        printf("Enter new day (DD):\n");
        scanf(" %s", day_change);
        printf("Enter new month (MM):\n");
        scanf(" %s", month_change);
        printf("Enter new year (YYYY):\n");
        scanf(" %s", year_change);
        new_date = changeDate(ticket1, day_change, month_change, year_change);
        // Check if new ticket is a valid ticket
        if (!isValidTicket(new_date, first_row, last_row)) {
            printf("Invalid Ticket!\n");
            return 0;
        }
        printf("New Ticket: %s\n", new_date);
        free(new_date);
    }

    showMenu();

    // Main Menu Loop Starts
    int choice;
    int seatCounter = 1;
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                makeReservation(&seatCounter);
                break;
            case 2:
                cancelReservation();
                break;
            case 3:
                displayReservations();
                break;
            case 4:
                saveToFile();
                break;
            case 5:
                printf("Thank you for using the Flight Ticket System. Have a great day!\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } // End of Main Menu Loop
}

// Function to check if a character is a digit
int isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Function to check if a character is an uppercase alphabet
int isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

// Function to check if a character is a lowercase alphabet
int isLowerCase(char c) {
    return c >= 'a' && c <= 'z';
}

// Function to check if a character is an alphabet
int isAlphabet(char c) {
    return isUpperCase(c) || isLowerCase(c);
}

// Function to check if a character is alphanumeric
int isAlphanumeric(char c) {
    return isDigit(c) || isAlphabet(c);
}

// Function to check if a character is a valid seat letter (A, B, C, ...)
int isValidSeatLetter(char c) {
    return isUpperCase(c) && c >= 'A' && c <= 'Z';
}

// Function to check if a character is a valid row number (1-99)
int isValidRowNumber(char c) {
    return isDigit(c) && c >= '1' && c <= '9';
}

// Function to check if a character is a valid month number (01-12)
int isValidMonth(char* str) {
    int month = atoi(str);
    return month >= 1 && month <= 12;
}

// Function to check if a character is a valid day number (01-31)
int isValidDay(char* str) {
    int day = atoi(str);
    return day >= 1 && day <= 31;
}

// Function to check if a character is a valid year number (1900-9999)
int isValidYear(char* str) {
    int year = atoi(str);
    return year >= 1900 && year <= 9999;
}

// Function to check if a character is a valid date (YYYYMMDD)
int isValidDateChar(char c, int position) {
    switch (position) {
        case 0: // First digit of year (thousands)
            return isDigit(c) && c >= '1' && c <= '9';
        case 1: // Second digit of year (hundreds)
        case 2: // Third digit of year (tens)
        case 3: // Fourth digit of year (units)
            return isDigit(c);
        case 4: // First digit of month
            return isValidMonth(&c);
        case 5: // Second digit of month
            return isDigit(c) || (c == '1' && isValidMonth("0"));
        case 6: // First digit of day
            return isDigit(c) || (c == '3' && isValidMonth("0"));
        case 7: // Second digit of day
            return isDigit(c);
        default:
            return 0;
    }
}

// Function to check if a character is a valid ticket character
int isValidTicketChar(char c, int position) {
    switch (position) {
        case 0: // First digit of year (thousands)
        case 1: // Second digit of year (hundreds)
        case 2: // Third digit of year (tens)
        case 3: // Fourth digit of year (units)
            return isDigit(c);
        case 4: // First digit of month
        case 5: // Second digit of month
        case 6: // First digit of day
        case 7: // Second digit of day
            return isValidDateChar(c, position - 4);
        case 8: // Departure airport code (alphabet)
        case 9: // Arrival airport code (alphabet)
            return isAlphabet(c);
        case 10: // First digit of row
            return isDigit(c) && c >= '1' && c <= '9';
        case 11: // Second digit of row (optional)
            return isDigit(c);
        case 12: // Seat letter
            return isValidSeatLetter(c);
        case 13: // Seat type
            return isAlphabet(c);
        default:
            return 0;
    }
}

// Function to check if a character is a valid seat (A01A)
int isValidSeat(char* ticket, int first_row, int last_row) {
    int len = strlen(ticket);
    return len == 14 && isValidTicketChar(ticket[0], 0) && isValidTicketChar(ticket[1], 1)
        && isValidTicketChar(ticket[2], 2) && isValidTicketChar(ticket[3], 3)
        && isValidTicketChar(ticket[4], 4) && isValidTicketChar(ticket[5], 5)
        && isValidTicketChar(ticket[6], 6) && isValidTicketChar(ticket[7], 7)
        && isValidTicketChar(ticket[8], 8) && isValidTicketChar(ticket[9], 9)
        && isValidTicketChar(ticket[10], 10) && isValidTicketChar(ticket[11], 11)
        && isValidTicketChar(ticket[12], 12) && isValidTicketChar(ticket[13], 13)
        && getRow(ticket) >= first_row && getRow(ticket) <= last_row;
}

// Function to check if a character is a valid date (YYYYMMDD)
int isValidDate(char* ticket) {
    int len = strlen(ticket);
    return len == 
