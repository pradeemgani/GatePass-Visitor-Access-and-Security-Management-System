# CP-059 GatePass: Visitor Access and Security Management System

## Team
Pradeem Gani(1AT24EC110), PavanKalyan B T (1AT24EC107), C track

## How to Run

**Compile the program:**
```bash
gcc main.c -o gatepass.exe
```

**Execute on Windows:**
```bash
./gatepass.exe
```

## Features That Work

### Core Features

1. **Register a Visitor:** Allows security personnel to enter the visitor's name, phone number, host employee name, and purpose of visit.
2. **Generate Visitor ID:** Automatically generates a unique Visitor ID for every successfully registered visitor.
3. **Generate GatePass:** Automatically generates a unique GatePass number for approved visitors.
4. **Blocked Visitor Verification:** Checks the visitor's phone number against a predefined blocked list and denies registration if the visitor is blocked.
5. **Record Visitor Entry:** Automatically records the date and time of visitor entry.
6. **Record Visitor Exit:** Records the visitor's exit time using their GatePass number.
7. **Display All Visitors:** Displays the details of all registered visitors.
8. **Show Currently Inside Visitors:** Displays visitors who have entered the premises but have not yet recorded their exit.

### Stretch Features

1. **File-Based Data Storage:** Saves visitor records permanently using file handling.
2. **Automatic Record Retrieval:** Loads previously saved visitor records when the program starts.
3. **Persistent ID Generation:** Continues Visitor ID and GatePass number generation based on previously stored records.

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

*Note: The above is an illustrative sample. Replace it with actual console output or screenshots from your final application.*

## Project Objective

The objective of GatePass is to develop a simple and efficient Visitor Access and Security Management System that simplifies visitor registration, improves security through blocked visitor verification, generates unique GatePass numbers, and maintains accurate visitor entry and exit records.
