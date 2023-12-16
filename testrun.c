//Only for modifications
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

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

struct FlightReservation {
    char passport[10];
    char name[30];
    char email[30];
    char destination[30];
    int seatNumber;
    struct FlightReservation* next;
};

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
const char* getSeatType(char* ticket);
bool isValidSeat(char* ticket, int first_row, int last_row);
bool isValidDate(char* ticket);
bool isValidTicket(char* ticket, int first_row, int last_row);
bool visits_airport(char* ticket, char* airport);
bool isConnectingFlight(char* ticket1, char* ticket2);
bool isAdjacent(char* ticket1, char* ticket2);
bool isBehind(char* ticket1, char* ticket2);
bool isValidFormat(char* ticket);
void changeSeat(char* ticket, char* row_num, char seat);
char* changeDate(char* ticket, char* day, char* month, char* year);
void printHeader();

// Reservation system function prototypes
void showMenu();
void makeReservation(struct FlightReservation** head, int* seatCounter);
void cancelReservation(struct FlightReservation** head);
void displayReservations(struct FlightReservation* head);
void saveToFile(struct FlightReservation* head);

// Main function
int main() {
    printHeader();
    printf("\n\n");

    int isAuthenticated = 0;

    while (!isAuthenticated) {
        isAuthenticated = checkPassword();

        if (!isAuthenticated) {
            printf("Please try again.\n");
        }
    }

    printf("Welcome to the system! Accessing flight ticket information...\n");

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

    struct FlightReservation* reservations = NULL;
    int seatCounter = 1;

    int choice;
    do {
        system("cls");
        showMenu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        fflush(stdin);

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
            getch();
        }

    } while (choice != 5);

    struct FlightReservation* current = reservations;
    struct FlightReservation* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    return 0;
}

// The rest of the code remains unchanged
// ...

