
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_VISITORS 500
#define SIZE 100
#define BLOCKED_COUNT 2

/* Blocked phone numbers */
const char *blockedNumbers[BLOCKED_COUNT] = {
    "9999999999",
    "8888888888"
};

/* Visitor structure */
struct Visitor {
    char visitorID[20];
    char name[SIZE];
    char phone[20];
    char host[SIZE];
    char purpose[SIZE];
    char gatepassID[20];
    char entryTime[30];
    char exitTime[30];
    char status[20];
};

struct Visitor visitors[MAX_VISITORS];

int visitorCount = 0;
int visitorNumber = 1001;
int gatepassNumber = 2001;

const char FILE_NAME[] = "visitor.csv";

/* Remove newline characters */
void removeNewline(char str[])
{
    str[strcspn(str, "\r\n")] = '\0';
}

/* Safe string copying */
void copyString(char destination[], size_t destinationSize,
                const char source[])
{
    if (destinationSize == 0)
        return;

    strncpy(destination, source, destinationSize - 1);
    destination[destinationSize - 1] = '\0';
}

/* Read input safely */
void readInput(const char *prompt, char output[], size_t outputSize)
{
    int ch;

    if (outputSize == 0)
        return;

    printf("%s", prompt);
    fflush(stdout);

    if (fgets(output, (int)outputSize, stdin) == NULL) {
        output[0] = '\0';
        return;
    }

    if (strchr(output, '\n') == NULL) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    removeNewline(output);
}

/* Get current date and time */
void getCurrentTime(char output[])
{
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);

    if (localTime == NULL) {
        copyString(output, 30, "Time unavailable");
        return;
    }

    if (strftime(output, 30, "%d-%m-%Y %H:%M:%S",
                 localTime) == 0) {
        copyString(output, 30, "Time unavailable");
    }
}

/* Check blocked phone numbers */
int isBlockedPhone(const char phone[])
{
    int i;

    for (i = 0; i < BLOCKED_COUNT; i++) {
        if (strcmp(phone, blockedNumbers[i]) == 0)
            return 1;
    }

    return 0;
}

/* Save visitor details */
void saveVisitorsToCSV(void)
{
    FILE *fp = fopen(FILE_NAME, "w");
    int i;

    if (fp == NULL) {
        printf("\nError opening %s for writing!\n", FILE_NAME);
        return;
    }

    for (i = 0; i < visitorCount; i++) {

        fprintf(fp, "Visitor ID: %s\n",
                visitors[i].visitorID);

        fprintf(fp, "Visitor Name: %s\n",
                visitors[i].name);

        fprintf(fp, "Phone Number: %s\n",
                visitors[i].phone);

        fprintf(fp, "Host Employee: %s\n",
                visitors[i].host);

        fprintf(fp, "Purpose: %s\n",
                visitors[i].purpose);

        fprintf(fp, "GatePass ID: %s\n",
                visitors[i].gatepassID);

        fprintf(fp, "Entry Time: %s\n",
                visitors[i].entryTime);

        if (strcmp(visitors[i].status, "Exited") == 0) {
            fprintf(fp, "Exit Time: %s\n",
                    visitors[i].exitTime);
        }

        fprintf(fp, "Status: %s\n\n",
                visitors[i].status);
    }

    fclose(fp);
}

/* Remove leading and trailing spaces */
void trim(char str[])
{
    size_t start = 0;
    size_t length = strlen(str);
    size_t end = length;

    while (start < length &&
           isspace((unsigned char)str[start])) {
        start++;
    }

    while (end > start &&
           isspace((unsigned char)str[end - 1])) {
        end--;
    }

    if (start > 0) {
        memmove(str, str + start, end - start);
    }

    str[end - start] = '\0';
}

/* Load one field from file */
void loadField(struct Visitor *visitor, char line[])
{
    char *colon = strchr(line, ':');
    char key[SIZE];
    char value[SIZE];

    if (colon == NULL || visitor == NULL)
        return;

    *colon = '\0';

    copyString(key, sizeof(key), line);
    copyString(value, sizeof(value), colon + 1);

    trim(key);
    trim(value);

    if (strcmp(key, "Visitor ID") == 0) {

        copyString(visitor->visitorID,
                   sizeof(visitor->visitorID), value);

    } else if (strcmp(key, "Visitor Name") == 0) {

        copyString(visitor->name,
                   sizeof(visitor->name), value);

    } else if (strcmp(key, "Phone Number") == 0) {

        copyString(visitor->phone,
                   sizeof(visitor->phone), value);

    } else if (strcmp(key, "Host Employee") == 0) {

        copyString(visitor->host,
                   sizeof(visitor->host), value);

    } else if (strcmp(key, "Purpose") == 0) {

        copyString(visitor->purpose,
                   sizeof(visitor->purpose), value);

    } else if (strcmp(key, "GatePass ID") == 0) {

        copyString(visitor->gatepassID,
                   sizeof(visitor->gatepassID), value);

    } else if (strcmp(key, "Entry Time") == 0) {

        copyString(visitor->entryTime,
                   sizeof(visitor->entryTime), value);

    } else if (strcmp(key, "Exit Time") == 0) {

        copyString(visitor->exitTime,
                   sizeof(visitor->exitTime), value);

    } else if (strcmp(key, "Status") == 0) {

        copyString(visitor->status,
                   sizeof(visitor->status), value);
    }
}

/* Add loaded visitor and update ID counters */
void addLoadedVisitor(const struct Visitor *temp)
{
    int id;
    int pass;

    if (temp == NULL ||
        temp->visitorID[0] == '\0' ||
        visitorCount >= MAX_VISITORS) {
        return;
    }

    visitors[visitorCount++] = *temp;

    if (sscanf(temp->visitorID, "GP%d", &id) == 1 &&
        id >= visitorNumber) {
        visitorNumber = id + 1;
    }

    if (sscanf(temp->gatepassID, "PASS%d", &pass) == 1 &&
        pass >= gatepassNumber) {
        gatepassNumber = pass + 1;
    }
}

/* Load previous visitor records */
void loadVisitorsFromCSV(void)
{
    FILE *fp = fopen(FILE_NAME, "r");
    char line[SIZE];
    struct Visitor temp = {0};

    if (fp == NULL)
        return;

    while (fgets(line, sizeof(line), fp) != NULL) {

        removeNewline(line);

        if (line[0] == '\0') {

            addLoadedVisitor(&temp);
            memset(&temp, 0, sizeof(temp));

        } else {

            loadField(&temp, line);
        }
    }

    /* Load last record */
    addLoadedVisitor(&temp);

    fclose(fp);
}

/* Register new visitor */
void registerVisitor(void)
{
    struct Visitor temp = {0};

    if (visitorCount >= MAX_VISITORS) {
        printf("\nVisitor storage is full!\n");
        return;
    }

    printf("\n========== VISITOR REGISTRATION ==========\n");

    readInput("Enter visitor name: ",
              temp.name, sizeof(temp.name));

    if (temp.name[0] == '\0') {
        printf("\nVisitor name cannot be empty.\n");
        return;
    }

    readInput("Enter phone number: ",
              temp.phone, sizeof(temp.phone));

    if (strlen(temp.phone) != 10) {
        printf("\nPlease enter a 10-digit phone number.\n");
        return;
    }

    {
        size_t i;

        for (i = 0; i < strlen(temp.phone); i++) {
            if (!isdigit((unsigned char)temp.phone[i])) {
                printf("\nPhone number must contain digits only.\n");
                return;
            }
        }
    }

    /* Check blocked number */
    if (isBlockedPhone(temp.phone)) {
        printf("\nACCESS DENIED!\n");
        printf("Phone number is in the blocked list.\n");
        printf("Visitor registration rejected!\n");
        return;
    }

    readInput("Enter host employee name: ",
              temp.host, sizeof(temp.host));

    readInput("Enter purpose of visit: ",
              temp.purpose, sizeof(temp.purpose));

    if (temp.host[0] == '\0' ||
        temp.purpose[0] == '\0') {
        printf("\nHost employee and purpose cannot be empty.\n");
        return;
    }

    snprintf(temp.visitorID, sizeof(temp.visitorID),
             "GP%d", visitorNumber);

    snprintf(temp.gatepassID, sizeof(temp.gatepassID),
             "PASS%d", gatepassNumber);

    getCurrentTime(temp.entryTime);

    temp.exitTime[0] = '\0';

    copyString(temp.status, sizeof(temp.status), "Inside");

    visitors[visitorCount] = temp;

    visitorCount++;
    visitorNumber++;
    gatepassNumber++;

    saveVisitorsToCSV();

    printf("\nVisitor registered successfully!\n");

    printf("Visitor ID : %s\n", temp.visitorID);
    printf("GatePass ID: %s\n", temp.gatepassID);
    printf("Entry Time : %s\n", temp.entryTime);
    printf("Status     : %s\n", temp.status);
}

/* Display one visitor */
void displayVisitor(const struct Visitor *visitor)
{
    if (visitor == NULL)
        return;

    printf("\n------------------------------------------\n");

    printf("Visitor ID      : %s\n", visitor->visitorID);
    printf("Visitor Name    : %s\n", visitor->name);
    printf("Phone Number    : %s\n", visitor->phone);
    printf("Host Employee   : %s\n", visitor->host);
    printf("Purpose         : %s\n", visitor->purpose);
    printf("GatePass ID     : %s\n", visitor->gatepassID);
    printf("Entry Time      : %s\n", visitor->entryTime);

    if (strcmp(visitor->status, "Exited") == 0) {
        printf("Exit Time       : %s\n", visitor->exitTime);
    }

    printf("Status          : %s\n", visitor->status);

    printf("------------------------------------------\n");
}

/* Choice 2: Display all visitors */
void displayAllVisitors(void)
{
    int i;

    if (visitorCount == 0) {
        printf("\nNo visitor records found!\n");
        return;
    }

    printf("\n========== ALL VISITOR DETAILS ==========\n");

    for (i = 0; i < visitorCount; i++) {
        displayVisitor(&visitors[i]);
    }

    printf("\n==========================================\n");
    printf("TOTAL NUMBER OF VISITORS: %d\n", visitorCount);
    printf("==========================================\n");
}

/* Choice 3: Record visitor exit */
void recordVisitorExit(void)
{
    char searchID[20];
    int i;

    readInput("\nEnter Visitor ID: ",
              searchID, sizeof(searchID));

    for (i = 0; i < visitorCount; i++) {

        if (strcmp(visitors[i].visitorID, searchID) == 0) {

            if (strcmp(visitors[i].status, "Exited") == 0) {
                printf("\nVisitor has already exited!\n");
                return;
            }

            getCurrentTime(visitors[i].exitTime);

            copyString(visitors[i].status,
                       sizeof(visitors[i].status), "Exited");

            saveVisitorsToCSV();

            printf("\nVisitor exit recorded successfully!\n");

            printf("Visitor ID: %s\n", visitors[i].visitorID);
            printf("Exit Time : %s\n", visitors[i].exitTime);
            printf("Status    : %s\n", visitors[i].status);

            return;
        }
    }

    printf("\nVisitor ID not found!\n");
}

/* Choice 4: Display final visitor records */
void displayFinalRecords(void)
{
    int i;
    int insideCount = 0;
    int exitedCount = 0;

    if (visitorCount == 0) {
        printf("\nNo visitor records found!\n");
        return;
    }

    printf("\n========== FINAL VISITOR RECORDS ==========\n");

    for (i = 0; i < visitorCount; i++) {

        displayVisitor(&visitors[i]);

        if (strcmp(visitors[i].status, "Inside") == 0) {
            insideCount++;
        }
        else if (strcmp(visitors[i].status, "Exited") == 0) {
            exitedCount++;
        }
    }

    printf("\n========== FINAL SUMMARY ==========\n");

    printf("Total Visitors           : %d\n", visitorCount);
    printf("Visitors Currently Inside: %d\n", insideCount);
    printf("Visitors Exited          : %d\n", exitedCount);

    printf("===================================\n");
}

/* Choice 5: Display visitors currently inside */
void displayVisitorsInside(void)
{
    int i;
    int insideCount = 0;

    printf("\n========== VISITORS CURRENTLY INSIDE ==========\n");

    for (i = 0; i < visitorCount; i++) {

        if (strcmp(visitors[i].status, "Inside") == 0) {

            displayVisitor(&visitors[i]);
            insideCount++;
        }
    }

    printf("\n==========================================\n");

    printf("TOTAL VISITORS CURRENTLY INSIDE: %d\n",
           insideCount);

    printf("==========================================\n");

    if (insideCount == 0) {
        printf("No visitors are currently inside.\n");
    }
}

/* Main function */
int main(void)
{
    int choice;
    char choiceInput[20];

    loadVisitorsFromCSV();

    printf("\n==========================================\n");
    printf(" GATEPASS - VISITOR ACCESS MANAGEMENT\n");
    printf("==========================================\n");

    printf("Previously saved records: %d\n", visitorCount);

    while (1) {

        printf("\n============== MAIN MENU ==============\n");

        printf("1. Register New Visitor\n");
        printf("2. Display All Visitors\n");
        printf("3. Record Visitor Exit\n");
        printf("4. Display Final Visitor Records\n");
        printf("5. Show Visitors Currently Inside\n");
        printf("6. Exit Program\n");

        printf("=======================================\n");

        readInput("Enter your choice: ",
                  choiceInput, sizeof(choiceInput));

        if (choiceInput[0] == '\0') {
            printf("\nInvalid input! Enter a number.\n");
            continue;
        }

        {
            char *endPointer;

            long parsedChoice = strtol(choiceInput,
                                       &endPointer, 10);

            while (*endPointer != '\0' &&
                   isspace((unsigned char)*endPointer)) {
                endPointer++;
            }

            if (*endPointer != '\0' ||
                parsedChoice < 1 ||
                parsedChoice > 6) {

                printf("\nInvalid choice! Please enter a number from 1 to 6.\n");
                continue;
            }

            choice = (int)parsedChoice;
        }

        switch (choice) {

            case 1:
                registerVisitor();
                break;

            case 2:
                displayAllVisitors();
                break;

            case 3:
                recordVisitorExit();
                break;

            case 4:
                displayFinalRecords();
                break;

            case 5:
                displayVisitorsInside();
                break;

            case 6:
                saveVisitorsToCSV();

                printf("\nThank you for using GATEPASS!\n");

                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
