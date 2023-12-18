#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PASSWORD_LENGTH 50

//Header for interface
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
/* Call using:
int main()
{
    printHeader();
}
*/

/*
Password
Description: This C program continuously prompts the user for a password, checking if it meets specified requirements 
(at least 8 characters long and contain at least one uppercase letter, one lowercase letter, and one digit) 
and grants access to flight ticket information upon correct input while providing distinct messages for incorrect passwords and those not meeting the criteria
*/

// Function to check and compare passwords
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

    for (int i = 0; i < length; ++i) 
    {
        if (isupper(enteredPassword[i])) {
            hasUppercase = 1;
        } else if (islower(enteredPassword[i])) {
            hasLowercase = 1;
        } else if (isdigit(enteredPassword[i])) {
            hasDigit = 1;
        }
    }

    // Check if all conditions are met
    if (length >= 8 && hasUppercase && hasLowercase && hasDigit)
    {
        if (strcmp(enteredPassword, storedPassword) == 0) {
            printf("Password is correct. Access granted.\n");
            return 1; // Passwords match and conditions are met
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } 
    else 
    {
        printf("Password does not meet the requirements. Access denied.\n");
    }

    return 0; // Passwords do not match or conditions are not met
}
/* Call Using
int main() {
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

    // Code to access flight ticket information would go here

    return 0;
}
*/

//function to check validity of arrival and departure airport codes
void airportCodes(char strdep[], int n, char strarr[], int a)
{
    //check if length of departure code is restricted to 3 alphabets
    if (n!=3)
    {
        printf("Invalid departure code!\n");
        return;
    }
    //all alphabets must be capital letters in a valid code
    for (int i=0;i<n;i++)
    {
        if (strdep[i]>='A' && strdep[i]<='Z')
        {

        }
        else
        {
            printf("Invalid departure code!\n");
            return;
        }
    }
    //check if length of arrival code is restricted to 3 alphabets
    if (a!=3)
    {
        printf("Invalid arrival code!\n");
        return;
    }
    //all alphabets must be capital letters in a valid code
    for (int i=0;i<a;i++)
    {
        if (strarr[i]>='A' && strarr[i]<='Z')
        {

        }
        else
        {
            printf("Invalid arrival code!\n");
            return;
        }
    }
    //if the departure code is the same as the arrival code then this is an invalid ticket
    if (strcmp(strdep, strarr)==0)
    {
        printf("Error. Arrival and Departure codes are the same, hence invalid ticket!\n");
        return;
    }
    printf("Valid Departure code is: %s\n", strdep);
    printf("Valid Arrival code is: %s\n", strarr);
}//end airportCodes


/* Call using:

int main()
{
    //declare two character arrays for departure and arrival strings
    char dep[4], arr[4];
    //take input for departure code
    printf("Please enter departure code: \n");
    scanf("%s", dep);
    int i=0;
    //to store length of departure code
    while (dep[i]!='\0')
    {
        i++;
    }
    //take input for departure code
    printf("Please enter arrival code: \n");
    scanf("%s", arr);
    int j=0;
    //to store length of departure code
    while (dep[j]!='\0')
    {
        j++;
    }
    //call function
    airportCodes(dep,i, arr, j);
    return 0;
}//end main
*/

//row validation function
void rowValidation(char row[], int n)
{
    //chck if row number has exactly 2 characters
    if (n!=2)
    {
        printf("Invalid row number. Invalid ticket.");
        return;
    }
    for (int i=0;i<n;i++)
    {
        //check whether each of these 2 characters are digits
        if (row[i]>='0' && row[i]<='9')
        {
            
        }
        else
        {
            printf("Invalid row number. Invalid ticket.\n");
            return;
        }
    }
    printf("Row number is: %s\n", row);
    printf("This is a valid row number.\n");
}//end rowValidation

/*
Call function using

int main()
{
    //declare array to store row number
    char row[3];
    printf("Enter row number: \n");
    scanf("%s", row);
    int l=0;
    //count number of characters in row number
    while (row[l]!='\0')
    {
        l++;
    }
    //call function for validation 
    rowValidation(row,l);
}//end main
*/





#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PASSWORD_LENGTH 50

//Header for interface
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
/* Call using:
int main()
{
    printHeader();
}
*/

/*
Password
Description: This C program continuously prompts the user for a password, checking if it meets specified requirements 
(at least 8 characters long and contain at least one uppercase letter, one lowercase letter, and one digit) 
and grants access to flight ticket information upon correct input while providing distinct messages for incorrect passwords and those not meeting the criteria
*/

// Function to check and compare passwords
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

    for (int i = 0; i < length; ++i) 
    {
        if (isupper(enteredPassword[i])) {
            hasUppercase = 1;
        } else if (islower(enteredPassword[i])) {
            hasLowercase = 1;
        } else if (isdigit(enteredPassword[i])) {
            hasDigit = 1;
        }
    }

    // Check if all conditions are met
    if (length >= 8 && hasUppercase && hasLowercase && hasDigit)
    {
        if (strcmp(enteredPassword, storedPassword) == 0) {
            printf("Password is correct. Access granted.\n");
            return 1; // Passwords match and conditions are met
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } 
    else 
    {
        printf("Password does not meet the requirements. Access denied.\n");
    }

    return 0; // Passwords do not match or conditions are not met
}
/* Call Using
int main() {
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

    // Code to access flight ticket information would go here

    return 0;
}
*/

//function to check validity of arrival and departure airport codes
void airportCodes(char strdep[], int n, char strarr[], int a)
{
    //check if length of departure code is restricted to 3 alphabets
    if (n!=3)
    {
        printf("Invalid departure code!\n");
        return;
    }
    //all alphabets must be capital letters in a valid code
    for (int i=0;i<n;i++)
    {
        if (strdep[i]>='A' && strdep[i]<='Z')
        {

        }
        else
        {
            printf("Invalid departure code!\n");
            return;
        }
    }
    //check if length of arrival code is restricted to 3 alphabets
    if (a!=3)
    {
        printf("Invalid arrival code!\n");
        return;
    }
    //all alphabets must be capital letters in a valid code
    for (int i=0;i<a;i++)
    {
        if (strarr[i]>='A' && strarr[i]<='Z')
        {

        }
        else
        {
            printf("Invalid arrival code!\n");
            return;
        }
    }
    //if the departure code is the same as the arrival code then this is an invalid ticket
    if (strcmp(strdep, strarr)==0)
    {
        printf("Error. Arrival and Departure codes are the same, hence invalid ticket!\n");
        return;
    }
    printf("Valid Departure code is: %s\n", strdep);
    printf("Valid Arrival code is: %s\n", strarr);
}//end airportCodes


/* Call using:

int main()
{
    //declare two character arrays for departure and arrival strings
    char dep[4], arr[4];
    //take input for departure code
    printf("Please enter departure code: \n");
    scanf("%s", dep);
    int i=0;
    //to store length of departure code
    while (dep[i]!='\0')
    {
        i++;
    }
    //take input for departure code
    printf("Please enter arrival code: \n");
    scanf("%s", arr);
    int j=0;
    //to store length of departure code
    while (dep[j]!='\0')
    {
        j++;
    }
    //call function
    airportCodes(dep,i, arr, j);
    return 0;
}//end main
*/

//row validation function
void rowValidation(char row[], int n)
{
    //chck if row number has exactly 2 characters
    if (n!=2)
    {
        printf("Invalid row number. Invalid ticket.");
        return;
    }
    for (int i=0;i<n;i++)
    {
        //check whether each of these 2 characters are digits
        if (row[i]>='0' && row[i]<='9')
        {
            
        }
        else
        {
            printf("Invalid row number. Invalid ticket.\n");
            return;
        }
    }
    printf("Row number is: %s\n", row);
    printf("This is a valid row number.\n");
}//end rowValidation

/*
Call function using

int main()
{
    //declare array to store row number
    char row[3];
    printf("Enter row number: \n");
    scanf("%s", row);
    int l=0;
    //count number of characters in row number
    while (row[l]!='\0')
    {
        l++;
    }
    //call function for validation 
    rowValidation(row,l);
}//end main
*/#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_PASSWORD_LENGTH 50

//Header for interface
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
/* Call using:
int main()
{
    printHeader();
}
*/

/*
Password
Description: This C program continuously prompts the user for a password, checking if it meets specified requirements 
(at least 8 characters long and contain at least one uppercase letter, one lowercase letter, and one digit) 
and grants access to flight ticket information upon correct input while providing distinct messages for incorrect passwords and those not meeting the criteria
*/

// Function to check and compare passwords
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

    for (int i = 0; i < length; ++i) 
    {
        if (isupper(enteredPassword[i])) {
            hasUppercase = 1;
        } else if (islower(enteredPassword[i])) {
            hasLowercase = 1;
        } else if (isdigit(enteredPassword[i])) {
            hasDigit = 1;
        }
    }

    // Check if all conditions are met
    if (length >= 8 && hasUppercase && hasLowercase && hasDigit)
    {
        if (strcmp(enteredPassword, storedPassword) == 0) {
            printf("Password is correct. Access granted.\n");
            return 1; // Passwords match and conditions are met
        } else {
            printf("Incorrect password. Access denied.\n");
        }
    } 
    else 
    {
        printf("Password does not meet the requirements. Access denied.\n");
    }

    return 0; // Passwords do not match or conditions are not met
}
/* Call Using
int main() {
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

    // Code to access flight ticket information would go here

    return 0;
}
*/

//function to check validity of arrival and departure airport codes
void airportCodes(char strdep[], int n, char strarr[], int a)
{
    //check if length of departure code is restricted to 3 alphabets
    if (n!=3)
    {
        printf("Invalid departure code!\n");
        return;
    }
    //all alphabets must be capital letters in a valid code
    for (int i=0;i<n;i++)
    {
        if (strdep[i]>='A' && strdep[i]<='Z')
        {

        }
        else
        {
            printf("Invalid departure code!\n");
            return;
        }
    }
    //check if length of arrival code is restricted to 3 alphabets
    if (a!=3)
    {
        printf("Invalid arrival code!\n");
        return;
    }
    //all alphabets must be capital letters in a valid code
    for (int i=0;i<a;i++)
    {
        if (strarr[i]>='A' && strarr[i]<='Z')
        {

        }
        else
        {
            printf("Invalid arrival code!\n");
            return;
        }
    }
    //if the departure code is the same as the arrival code then this is an invalid ticket
    if (strcmp(strdep, strarr)==0)
    {
        printf("Error. Arrival and Departure codes are the same, hence invalid ticket!\n");
        return;
    }
    printf("Valid Departure code is: %s\n", strdep);
    printf("Valid Arrival code is: %s\n", strarr);
}//end airportCodes


/* Call using:

int main()
{
    //declare two character arrays for departure and arrival strings
    char dep[4], arr[4];
    //take input for departure code
    printf("Please enter departure code: \n");
    scanf("%s", dep);
    int i=0;
    //to store length of departure code
    while (dep[i]!='\0')
    {
        i++;
    }
    //take input for departure code
    printf("Please enter arrival code: \n");
    scanf("%s", arr);
    int j=0;
    //to store length of departure code
    while (dep[j]!='\0')
    {
        j++;
    }
    //call function
    airportCodes(dep,i, arr, j);
    return 0;
}//end main
*/

//row validation function
void rowValidation(char row[], int n)
{
    //chck if row number has exactly 2 characters
    if (n!=2)
    {
        printf("Invalid row number. Invalid ticket.");
        return;
    }
    for (int i=0;i<n;i++)
    {
        //check whether each of these 2 characters are digits
        if (row[i]>='0' && row[i]<='9')
        {
            
        }
        else
        {
            printf("Invalid row number. Invalid ticket.\n");
            return;
        }
    }
    printf("Row number is: %s\n", row);
    printf("This is a valid row number.\n");
}//end rowValidation

/*
Call function using

