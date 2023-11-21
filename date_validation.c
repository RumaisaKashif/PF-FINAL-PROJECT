#include <stdio.h>

#define MAX_YR 2100  // Define MAX_YR and MIN_YR if not already defined
#define MIN_YR 1900

// Define the Date structure
struct Date {
    int yyyy;  // Year
    int mm;    // Month
    int dd;    // Day
};

// Function that checks for a leap year
int check_for_leapyear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Function to check if a date is valid
int ValidDate(struct Date *validDate) {
    // Range of Year check
    if (validDate->yyyy > MAX_YR || validDate->yyyy < MIN_YR)
        return 0;

    // Range of Month check
    if (validDate->mm < 1 || validDate->mm > 12)
        return 0;

    // Range of Day check
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;

    // Separate check for February in leap year
    if (validDate->mm == 2) {
        if (check_for_leapyear(validDate->yyyy))
            return (validDate->dd <= 29);
        else
            return (validDate->dd <= 28);
    }

    // Months with 30 days
    if (validDate->mm == 4 || validDate->mm == 6 || validDate->mm == 9 || validDate->mm == 11)
        return (validDate->dd <= 30);

    // All other months with 31 days
    return 1;
}
/*
int main() {
    struct Date myDate = {2023, 11, 21};  // Example date
    int isValid = ValidDate(&myDate);

    if (isValid) {
        printf("Date is valid.\n");
    } else {
        printf("Date is invalid.\n");
    }

    return 0;
}
*/

