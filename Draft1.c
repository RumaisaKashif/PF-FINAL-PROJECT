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
  */
}
