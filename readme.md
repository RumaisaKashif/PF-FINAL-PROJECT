# Flight Ticket Management System

The Flight Ticket Management System is a sophisticated software solution designed to streamline the process of managing flight tickets for the management, allowing them to efficiently cancel flights, check ticket validity, make reservations, change seats, save reservations, and delete records, thereby enhancing user experience, ensuring data accuracy, and maintaining the integrity of flight information.

## Contributors

| Name             | ID           |
| ---------------- | ------------ |
| Areeba Hasnain   | 23K-0059     |
| Rumaisa Kashif   | 23K-0744     |
| Emman Abrar      | 23K-0051     |

## Table of Contents

- [Key Features](#key-features)
  - [Ticket Validation](#ticket-validation)
  - [Password Check](#password-check)
  - [Seat Change System](#seat-change-system)
  - [Reservation and Cancellation](#reservation-and-cancellation)
  - [Display Reservations](#display-reservations)
- [Data Structures](#data-structures)
  - [Character Arrays](#character-arrays)
  - [Dynamic Memory Allocation](#dynamic-memory-allocation)
  - [Pointers](#pointers)
  - [File Handling](#file-handling)
  - [Constants](#constants)
- [Major Challenges Encountered](#major-challenges-encountered)

## Key Features

### Ticket Validation

The ticket validation mechanism is a critical component of the Flight Ticket Management System, ensuring that all reservations adhere to a standardized format and meet specific criteria. This feature contributes to data integrity, consistency, and the overall reliability of the system.

#### Format Specification

Each flight ticket follows a specific format: `(YYYY)(MM)(DD)(DEP)(ARR)(ROW)(SEAT)`, where:

- **YYYYMMDD:** Represents the date of the flight.
- **DEP:** Three-letter code for the departure airport.
- **ARR:** Three-letter code for the arrival airport.
- **ROW:** Two-digit row number.
- **SEAT:** Single-character seat identifier.

#### Validation Criteria

The ticket validation process checks the following criteria to ensure the correctness of each reservation:

1. **Length Check:** The ticket must be exactly 17 characters long, conforming to the specified format.

2. **Numeric and Alphabetic Checks:** The date components (YYYY, MM, DD) must be numeric, and the departure and arrival codes (DEP, ARR) must be alphabetic.

3. **Seat and Row Validation:** The system verifies that the seat and row numbers fall within the specified range for the aircraft configuration. Valid seats include SA, SB, SC, SD, SE, and SF.

4. **Date Validation:** The system checks the validity of the date components, ensuring that they represent a logical and possible date. This includes checking for leap years and valid months and days.

5. **Airport Code Check:** Departure and arrival airport codes are validated to ensure they are distinct, preventing the creation of invalid routes.

### Password Check

The password check mechanism is a fundamental component of the Flight Ticket Management System, providing a secure layer of access control to the system. This feature ensures that only authorized personnel can log in, safeguarding sensitive flight information and system functionality.

#### Password Requirements

The system enforces specific requirements for passwords to strike a balance between security and usability. The password must meet the following criteria:

1. **Length:** The password must be at least 8 characters long, ensuring a sufficient level of complexity.

2. **Uppercase and Lowercase Letters:** The password must contain both uppercase and lowercase letters, enhancing its resilience against unauthorized access.

3. **Digits:** Inclusion of digits in the password adds an extra layer of complexity, enhancing overall security.

### Seat Change System

The Seat Change System is a versatile feature integrated into the Flight Ticket Management System, allowing authorized personnel to modify seat assignments for flight reservations. This functionality is designed to accommodate various scenarios, such as accommodating passenger preferences, resolving seat-related issues, or optimizing seat arrangements.

#### Dynamic Seat Modification

Authorized users have the capability to dynamically change the seat assignment for a given reservation. The system prompts users to input the desired changes, including the new row number and seat identifier. Upon successful modification, the system updates the reservation details, ensuring data consistency and accuracy.

#### Validation Checks

The Seat Change System incorporates validation checks to maintain the integrity of the seating configuration. These checks include:

1. **Seat Availability:** The system verifies the availability of the specified seat, ensuring that it is not already occupied or reserved by another passenger.

2. **Row Validity:** The new row number is validated to ensure it falls within the acceptable range for the aircraft configuration.

3. **Seat Type Compatibility:** The system checks whether the new seat aligns with the designated seat types (Window, Aisle, Middle), adhering to the specific layout of the aircraft.

### Reservation and Cancellation

The Reservation and Cancellation module is a core component of the Flight Ticket Management System, enabling users to efficiently book new flight reservations and manage existing bookings.

#### Making a Reservation

The system provides a streamlined process for making reservations, ensuring a smooth and user-friendly experience for authorized personnel. Here's how the reservation process works:

1. **User Input:** Authorized users input essential passenger information, including passport details, name, email, and the desired destination.

2. **Seat Assignment:** The system automatically assigns a seat number to the reservation, considering the current seat availability and configuration.

3. **Confirmation:** Upon successful reservation, the system generates a confirmation message, including the assigned seat number and relevant details.

#### Cancellation of Reservations

The Flight Ticket Management System allows for the cancellation of reservations when necessary. The cancellation process includes the following steps:

1. **User Verification:** Users are prompted to enter the passport number associated with the reservation to be canceled.

2. **Reservation Identification:** The system identifies the corresponding reservation using the provided passport number.

3. **Cancellation Confirmation:** Once confirmed, the system cancels the reservation, freeing up the seat for future bookings.

### Display Reservations

The system offers the ability to view a comprehensive list of all current flight reservations, providing an overview of passenger details, assigned seats, and destinations.

## Data Structures

### Character Arrays 

Character arrays, commonly referred to as strings, are extensively used in the codebase:

- **Password Storage:** Character arrays store both user-entered passwords and the system's predefined secure password for comparison during the authentication process.

- **Ticket Representation:** Flight ticket details, including passport numbers, names, email addresses, and airport codes, are stored in character arrays, providing a convenient and structured representation.

- **String Manipulation:** Arrays are essential for string operations, crucial for functions such as extracting date components and airport codes from the ticket.

### Dynamic Memory Allocation

Dynamic memory allocation through `malloc` is employed to allocate memory for various components:

- **Memory for Date Components:** Memory is dynamically allocated for date, year, month, and day strings in functions like getDate, getYear, getMonth, and getDay.

- **Memory for Airport Codes:** Dynamic memory allocation is used to store departure and arrival codes (dep and arr) extracted from the ticket.

- **Memory for New Ticket:** The changeDate function dynamically allocates memory for creating a new ticket string with modified date components.

### Pointers
- Pointers are used extensively for dynamic memory allocation, string manipulation, and file handling.

### File Handling

- **Saving Reservations to File**
In the code, file handling is employed to save flight reservations to a file named "FlightRecords.txt." The functionality is encapsulated in the `saveToFile` function. Here's how it works:

1. The function opens the file "FlightRecords.txt" in append mode (`"a"`).
2. It checks if the file opening was successful; if not, it prints an error message and exits.
3. It traverses the linked list of flight reservations.
4. For each reservation, it writes details such as passport number, name, email address, seat number, destination, and a separator line to the file.
5. Finally, it prints a message to the console indicating that the flight reservations have been saved to the file.

This file handling mechanism ensures that reservation information is persisted between different program executions, allowing users to retrieve previously made reservations.

### Constants
- Constants like `SA`, `SB`, `SC`, `SD`, `SE`, `SF`, `WINDOW`, `AISLE`, `MIDDLE`, `MAX_PASSWORD_LENGTH`: Used to represent seat codes, seat types, and maximum password length.

## Major Challenges Encountered

1. **Integration of Functions:**
   - Coordinating the compilation of various functions and aligning them with their intended applications proved to be a significant challenge.

2. **Filing Process:**
   - Limited expertise in the area of filing hindered progress as we grappled with understanding and applying the concepts efficiently.

3. **Code Organization and Structure:**
   - Establishing a clear and effective organization for the entire codebase presented difficulties, impacting readability and maintainability.

4. **Function Diversity and Output Detail:**
   - Enhancing the variety of functions to generate more comprehensive and detailed outputs emerged as a priority for achieving greater utility and effectiveness.
