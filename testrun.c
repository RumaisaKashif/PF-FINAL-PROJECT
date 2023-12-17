/*
Programmers: Rumaisa Kashif , Areeba Hasnain , Emman Abrar Ali.
Flight Management System
This is specifically designed for the MacBook we ran the program on because certain windows libraries for C language are not compatible on MacOs
*/

// Basic Library Header Inclusions
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <termios.h>
#include <unistd.h>

// Defining symbolic names for literal characters.

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
#define MAX_SEATS 100
int seatAvailability[MAX_SEATS] = {0};// Global array to keep track of assigned seats

// Ticket format: (YYYY)(MM)(DD)(DEP)(ARR)(ROW)(SEAT)

// Structure to store reservation details
struct FlightReservation {
    char passport[10];
    char name[30];
    char email[30];
    char destination[30];
    int seatNumber;
    struct FlightReservation* next;
};//End of flightReservation Structure 

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
void makeReservation(struct FlightReservation** head, int* seatCounter);
void cancelReservation(struct FlightReservation** head);
void displayReservations(struct FlightReservation* head);
void saveToFile(struct FlightReservation* head);

// Function to print formatter header
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
char getChar() 
{
    char buf = 0; // Declaring variable buf of type char and giving it an initial value of 0. This will help store character taken from input of the user
    struct termios old = {0}; //Declaring a structure old of type struct termios to store the current terminal settings.
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
    
    char* date = getDate(ticket1);
    printf("Date (YYYYMMDD) is: %s\n", date);
    free(date);
    
    char* year= getYear(ticket1);
    printf("Year (YYYY) is: %s\n", year);
    free(year);
    
    char* month= getMonth(ticket1);
    printf("Month (MM) is: %s\n", month);
    free(month);
    
    char* day= getDay(ticket1);
    printf("Day (DD) is: %s\n", day);
    free(day);
    
    char* dep= getDepartureCode(ticket1);
    printf("Departure Aiport code is: %s\n", dep);
    free(dep);
    
    char* arr= getArrivalCode(ticket1);
    printf("Arrival Airport code is: %s\n", arr);
    free(arr);
    
    int row= getRow(ticket1);
    printf("Row number is: %d\n", row);
    
    char seat= getSeatNumber(ticket1);
    printf("Seat %c\n", seat);
    printf("Seat type: %s\n", getSeatType(ticket1));
    
    //Seat and row validation
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
    if (seatchange=='s')
    {
        printf("Enter new row number:\n");
        scanf(" %s", new_row);
        printf("Enter new seat number:\n");
        scanf(" %c", &new_seat);
        changeSeat(ticket1, new_row, new_seat);
        //check if new ticket is a valid ticket
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
    if (datechange=='d')
    {
        printf("Enter updated day:\n");
        scanf(" %s", new_day);
        printf("Enter updated month:\n");
        scanf(" %s", new_month);
        printf("Enter updated year:\n");
        scanf(" %s", new_year);
        char* newTicketNumber2= changeDate(ticket1, new_day, new_month, new_year);
        //check if new ticket is a valid ticket
        if (!isValidTicket(newTicketNumber2, first_row, last_row))
        {
            printf("Invalid New Ticket!\n");
        }
        printf("New ticket number is: %s\n", newTicketNumber2);
        free(newTicketNumber2);
    }
     struct FlightReservation* reservations = NULL; 
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
}//Main Function Ends

//Check and compare passwords
int checkPassword() 
{
    char storedPassword[MAX_PASSWORD_LENGTH] = "Secure123"; 
    char enteredPassword[MAX_PASSWORD_LENGTH];

    // Prompt user for password
    printf("Enter your password: ");
    fgets(enteredPassword, MAX_PASSWORD_LENGTH, stdin);

    // Remove newline character from entered password
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0';

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

//Extract date
char* getDate(char* ticket)
{
    
    int dateLen=8;
    int startIndex=0;
    //Allocate memory for the date
    char* date = (char*)malloc((dateLen + 1) * sizeof(char));
    //Check if memory allocation was successful
    if (date == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(date, ticket + startIndex, dateLen);
    date[dateLen] = '\0'; //Null-terminate the date string
    return date;
}

//Extract year, month, and day
char* getYear(char* ticket)
{
    int yearLen=4;
    int startIndex=0;
    //Allocate memory
    char* year= (char*)malloc((yearLen + 1) * sizeof(char));
    //Check if memory allocation was successful
    if (year == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(year, ticket + startIndex, yearLen);
    year[yearLen] = '\0'; //Null-terminate the year string
    return year;
}

char* getMonth(char* ticket)
{
    int monthLen=2;
    int startIndex=4;
    //Allocate memory
    char* month= (char*)malloc((monthLen + 1) * sizeof(char));
    //Check if memory allocation was successful
    if (month == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(month, ticket + startIndex, monthLen);
    month[monthLen] = '\0'; //Null-terminate the month string
    return month;
}

char* getDay(char* ticket)
{
    int dayLen=2;
    int startIndex=6;
    //Allocate memory
    char* day= (char*)malloc((dayLen + 1) * sizeof(char));
    //Check if memory allocation was successful
    if (day == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(day, ticket + startIndex, dayLen);
    day[dayLen] = '\0'; //Null-terminate the day string
    return day;
}

char* getDepartureCode(char* ticket)
{
    int depLen=3;
    int startIndex=8;
    //Allocate memory
    char* dep= (char*)malloc((depLen + 1) * sizeof(char));
    //Check if memory allocation was successful
    if (dep == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(dep, ticket + startIndex, depLen);
    dep[depLen] = '\0'; //Null-terminate the dep string
    return dep;
}

char* getArrivalCode(char* ticket)
{
    int arrLen=3;
    int startIndex=11;
    //Allocate memory
    char* arr= (char*)malloc((arrLen + 1) * sizeof(char));
    //Check if memory allocation was successful
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(arr, ticket + startIndex, arrLen);
    arr[arrLen] = '\0'; //Null-terminate the arr string
    return arr;
}

//Extract row number from ticket as an integer
int getRow(char* ticket)
{
    int rowLen=2;
    int startIndex=14;
    char rowTemp[rowLen+1];
    //Copy the row characters to a temporary string
    memcpy(rowTemp, ticket + startIndex, rowLen);
    rowTemp[rowLen] = '\0'; //Null-terminate the temporary row string
    //Convert temporary string to integer using atoi function
    int row = atoi(rowTemp);
    return row;
}

//Extract Seat
char getSeatNumber(char* ticket)
{
    int startIndex= 16;
    return ticket[startIndex];
}

//Declaring seat type
const char* getSeatType(char* ticket)
{
    
    char seat = getSeatNumber(ticket);
    if (seat== SA || seat== SF)
    {
        return WINDOW;
    }
    if (seat== SB || seat== SE)
    {
        return MIDDLE;
    }
    else
    {
        return AISLE;
    }
}

//Seat and Row Validation
bool isValidSeat(char* ticket, int first_row, int last_row)
{
    char seat= getSeatNumber(ticket);
    int row= getRow(ticket);
    return (row >= first_row && row <= last_row) &&
    (seat==SA || seat==SB || seat==SC || seat==SD || seat==SE || seat==SF);
}

//Date Validation
bool isValidDate(char* ticket)
{
    //convert year, month, and date strings to integers
    int year= atoi(getYear(ticket));
    int month= atoi(getMonth(ticket));
    int day= atoi(getDay(ticket));

    if (year<0)
    {
        return false;
    }
    if (month>=1 && month<=12)
    {
        //odd months uptill July and even months from August onward have 31 days
        if ((month<=7 && month%2==1) || (month>= 8 && month%2==0))
        {
            return day>=1 && day<=31;
        }
        //for the rest of the months apart from February, there are 30 days
        if (month!= 2)
        {
            return day>=1 && day <=30;
        }
        //if it is a leap year, number of days in February are 29
        if (year%4== 0 && !(year%200== 0 && year%800!= 0))
        {
            return day>=1 && day<=29;
        }
        //if it is not a leap year, number of days in February are 28
        return day>=1 && day<=28;
    }
    return false;
}

//verifying format of ticket string as defined initially
bool isValidFormat(char* ticket) {
    return (strlen(ticket)==17)
    && isdigit(ticket[0]) && isdigit(ticket[1]) && isdigit(ticket[2]) && isdigit(ticket[3])
           && isdigit(ticket[4]) && isdigit(ticket[5])
           && isdigit(ticket[6]) && isdigit(ticket[7])
           && isalpha(ticket[8]) && isalpha(ticket[9]) && isalpha(ticket[10])
           && isalpha(ticket[11]) && isalpha(ticket[12]) && isalpha(ticket[13])
           && isdigit(ticket[14]) && isdigit(ticket[15])
           && isalpha(ticket[16]);
    /* Alternatively, these checks could have been conducted by defining starting index values for each category as constants
  in the beginning and using indices instead of numbers. */
}

//Classifying a valid ticket
bool isValidTicket(char* ticket, int first_row, int last_row) {
    if (isValidFormat(ticket))
    {
        return (isValidSeat(ticket, first_row, last_row) && isValidDate(ticket) &&
                strcmp(getDepartureCode(ticket),getArrivalCode(ticket))!=0);
    }
    return false;
}

//to test for connecting flights
bool isConnectingFlight(char* ticket1, char* ticket2) {
    return (strcmp(getDate(ticket1), getDate(ticket2))==0) &&
           (strcmp(getArrivalCode(ticket1), getDepartureCode(ticket2))==0);
}

//to test whether two seats are adjacent to one another
bool isAdjacent(char* ticket1, char* ticket2)
{
    char seat1= getSeatNumber(ticket1);
    char seat2= getSeatNumber(ticket2);
    int row1= getRow(ticket1);
    int row2= getRow(ticket2);

    return (row1==row2) &&
           ((seat1== SA && seat2== SB) || (seat1== SB && seat2== SA) ||
            (seat1== SB && seat2== SC) || (seat1== SC && seat2== SB) ||
            (seat1== SD && seat2== SE) || (seat1== SE && seat2== SD) ||
            (seat1== SE && seat2== SF) || (seat1== SF && seat2== SE));
}

//to test whether two seats are behind one another
bool isBehind(char* ticket1, char* ticket2) {
    char seat1 = getSeatNumber(ticket1);
    char seat2 = getSeatNumber(ticket2);
    int row1 = getRow(ticket1);
    int row2 = getRow(ticket2);

    return ((row1 - row2)==1 || (row1 - row2)==-1)  && seat1==seat2;
}

//to change seat
void changeSeat(char* ticket, char* row_num, char seat) 
{
    ticket[14]=row_num[0];
    ticket[15]=row_num[1];
    ticket[16]=seat;
}

//to change date
char* changeDate(char* ticket, char* day, char* month, char* year)
{
    char* new_ticket= (char*)malloc(18 * sizeof(char));
    if (new_ticket==NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    sprintf(new_ticket, "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
            year[0], year[1], year[2], year[3],
            month[0], month[1],
            day[0], day[1],
            ticket[8], ticket[9], ticket[10], ticket[11], ticket[12], ticket[13], ticket[14], ticket[15], ticket[16]);
    return new_ticket;
    free(new_ticket);
}

// Display menu options
void showMenu() {
    printf("**********************************************\n");
    printf("        Flight Management System Menu\n");
    printf("**********************************************\n\n");
    printf("1. Make a Reservation\n");
    printf("2. Cancel a Reservation\n");
    printf("3. Display Reservations\n");
    printf("4. Save Reservations to File\n");
    printf("5. Exit\n\n");
}//End Menu 

// Function to make a reservation
void makeReservation(struct FlightReservation** head, int* seatCounter) {
    // Create a new reservation node
    struct FlightReservation* newReservation = (struct FlightReservation*)malloc(sizeof(struct FlightReservation));
    if (newReservation == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    printf("\nEnter Passport Number: ");
    scanf("%9s", newReservation->passport);

    printf("Enter Full Name: ");
    scanf(" %[^\n]s", newReservation->name);

    printf("Enter Email Address: ");
    scanf(" %[^\n]s", newReservation->email);

    printf("Enter Destination: ");
    scanf(" %[^\n]s", newReservation->destination);

    // Find an available seat
    int seatNumber = -1;
    for (int i = 1; i < MAX_SEATS; ++i) {
        if (seatAvailability[i] == 0) {
            seatNumber = i;
            seatAvailability[i] = 1; // Mark the seat as taken
            break;
        }
    }

    if (seatNumber == -1) {
        printf("\nSorry, all seats are taken.\n");
        free(newReservation);
        return;
    }

    // Assign the seat number to the new reservation
    newReservation->seatNumber = seatNumber;
    newReservation->next = NULL;

    // Add the new reservation 
    if (*head == NULL) {
        *head = newReservation;
    } else {
        struct FlightReservation* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newReservation;
    }

    printf("\nReservation Successful!");
    printf("\nYour Seat Number is: Seat %d A\n", newReservation->seatNumber);
}

// Function to cancel a reservation
void cancelReservation(struct FlightReservation** head) {
    if (*head == NULL) {
        printf("\nNo reservations to cancel.\n");
        return;
    }

    char passportToCancel[10];
    printf("\nEnter Passport Number to cancel reservation: ");
    scanf("%9s", passportToCancel);

    struct FlightReservation* current = *head;
    struct FlightReservation* prev = NULL;

    while (current != NULL && strcmp(current->passport, passportToCancel) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\nReservation not found for Passport Number: %s\n", passportToCancel);
    } else {
        if (prev == NULL) {
            *head = current->next;
        } else {
            prev->next = current->next;
        }

        printf("\nReservation with Passport Number %s has been canceled.\n", passportToCancel);
        free(current);
    }
}

// Function to display all reservations
void displayReservations(struct FlightReservation* head) {
    if (head == NULL) {
        printf("\nNo reservations to display.\n");
        return;
    }

    printf("\n****************************************************\n");
    printf("              List of Flight Reservations\n");
    printf("****************************************************\n\n");

    struct FlightReservation* current = head;
    while (current != NULL) {
        printf("Passport Number: %s\n", current->passport);
        printf("Name: %s\n", current->name);
        printf("Email Address: %s\n", current->email);
        printf("Seat Number: Seat A-%d\n", current->seatNumber);
        printf("Destination: %s\n", current->destination);
        printf("\n++*=============================================*++\n\n");
        current = current->next;
    }
}

// Function to save reservations to a file
void saveToFile(struct FlightReservation* head) {
    FILE* filePointer = fopen("FlightRecords.txt", "a");
    if (filePointer == NULL) {
        printf("\nError opening file for writing.\n");
        return;
    }

    struct FlightReservation* current = head;
    while (current != NULL) {
        fprintf(filePointer, "Passport Number: %s\n", current->passport);
        fprintf(filePointer, "Name: %s\n", current->name);
        fprintf(filePointer, "Email Address: %s\n", current->email);
        fprintf(filePointer, "Seat Number: Seat A-%d\n", current->seatNumber);
        fprintf(filePointer, "Destination: %s\n", current->destination);
        fprintf(filePointer, "\n++*=============================================*++\n\n");
        current = current->next;
    }

    printf("\nFlight reservations have been saved to 'FlightRecords.txt'.\n");

    fclose(filePointer);
}//end file 
