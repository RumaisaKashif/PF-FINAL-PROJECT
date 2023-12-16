#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

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
char *getDate(char *ticket);
char *getYear(char *ticket);
char *getMonth(char *ticket);
char *getDay(char *ticket);
char *getDepartureCode(char *ticket);
char *getArrivalCode(char *ticket);
int getRow(char *ticket);
char getSeatNumber(char *ticket);
bool isValidSeat(char *ticket, int first_row, int last_row);
bool isValidDate(char *ticket);
bool isValidTicket(char *ticket, int first_row, int last_row);
bool isConnectingFlight(char *ticket1, char *ticket2);
bool isAdjacent(char *ticket1, char *ticket2);
bool isBehind(char *ticket1, char *ticket2);
const char *getSeatType(char *ticket);
bool isValidFormat(char *ticket);
void changeSeat(char *ticket, char *row_num, char seat);
char *changeDate(char *ticket, char *day, char *month, char *year);

void printHeader()
{
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

// Main Function Starts
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
    printf("Welcome to the system! Accessing flight ticket information...\n");

    // Test cases
    char ticket1[] = "20231121ABCDEF25A";
    char ticket2[] = "20231121DEFGHI26A";

    int first_row, last_row;
    printf("Enter the number of the first row and the last row: \n");
    scanf("%d %d", &first_row, &last_row);

    char *date = getDate(ticket1);
    printf("Date (YYYYMMDD) is: %s\n", date);
    free(date);

    char *year = getYear(ticket1);
    printf("Year (YYYY) is: %s\n", year);
    free(year);

    char *month = getMonth(ticket1);
    printf("Month (MM) is: %s\n", month);
    free(month);

    char *day = getDay(ticket1);
    printf("Day (DD) is: %s\n", day);
    free(day);

    char *dep = getDepartureCode(ticket1);
    printf("Departure Aiport code is: %s\n", dep);
    free(dep);

    char *arr = getArrivalCode(ticket1);
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
        // check if new ticket is a valid ticket
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
        printf("Enter updated day:\n");
        scanf(" %s", new_day);
        printf("Enter updated month:\n");
        scanf(" %s", new_month);
        printf("Enter updated year:\n");
        scanf(" %s", new_year);
        char *newTicketNumber2 = changeDate(ticket1, new_day, new_month, new_year);
        // check if new ticket is a valid ticket
        if (!isValidTicket(newTicketNumber2, first_row, last_row))
        {
            printf("Invalid New Ticket!\n");
            return 0;
        }
        printf("New ticket number is: %s\n", newTicketNumber2);
        free(newTicketNumber2);
    }

    // Rest of the code

    return 0;
}

// Rest of the functions
