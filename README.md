# CP-059 GatePass: Visitor Access and Security Management System

## Individual Project – C Track

## How to Run

Compile the program:

```bash
gcc main.c -o gatepass
```

Run on Windows:

```bash
.\gatepass.exe
```

Run on Linux:

```bash
./gatepass
```

## Features That Work

### Core Features

1. **Visitor Registration:** Register visitors by entering their name, phone number, host employee name, and purpose of visit.
2. **Automatic Visitor ID Generation:** Automatically generates a unique Visitor ID for every successfully registered visitor.
3. **Automatic GatePass Generation:** Generates a unique GatePass number after successful visitor registration.
4. **Blocked Visitor Verification:** Checks the visitor's phone number against a predefined blocked list and denies registration to blocked visitors.
5. **Visitor Entry Tracking:** Records the visitor's entry date and time automatically.
6. **Visitor Exit Tracking:** Records the actual exit date and time using the visitor's GatePass number.
7. **Display All Visitors:** Displays the details of all registered visitors.
8. **Currently Inside Monitoring:** Displays only visitors who have entered the premises but have not yet recorded their exit.

### Stretch Features

1. **File-Based Data Persistence:** Saves visitor records in a file so that information remains available after closing and restarting the application.
2. **Automatic Record Retrieval:** Loads previously saved visitor records when the program starts.
3. **Unique ID Continuity:** Continues generating Visitor IDs and GatePass numbers based on previously saved records.

## Technologies Used

- C Programming Language
- File Handling
- String Handling
- Functions
- Arrays and Structures (if used in the implementation)
- Conditional Statements
- Loops
- Date and Time Handling

## Sample Run

```text
======================================
       GATEPASS MANAGEMENT SYSTEM
======================================

1. Register New Visitor
2. Display All Visitors
3. Record Visitor Exit
4. Display Final Visitor Records
5. Show Everyone Currently Inside
6. Exit Program

Enter Your Choice: 1

======================================
        VISITOR REGISTRATION
======================================

Enter Visitor Name: Rahul
Enter Phone Number: 9876543210
Enter Host Employee Name: Arun
Enter Purpose of Visit: Meeting

Visitor Registered Successfully!

======================================
          VISITOR GATEPASS
======================================

Visitor ID: GP1001
GatePass Number: PASS2001
Visitor Name: Rahul
Phone Number: 9876543210
Host Employee: Arun
Purpose: Meeting

======================================
```

*Note: This is an illustrative sample. Replace it with actual console output from your final C program before submission.*

## Project Objective

To develop a simple and efficient visitor access and security management system that helps organizations manage visitor registration, generate GatePass numbers, verify blocked visitors, and maintain accurate visitor entry and exit records.
