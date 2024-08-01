#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATA_SIZE 1000
#define MAX_ROOMS 100 // Maximum number of rooms that can be added


struct Room {
int number;
int capacity;
int isOccupied;
char occupantName[50];
};


// Function declarations
void displayMenu();
void showRooms(struct Room rooms[], int numRooms);
void addRoom(struct Room rooms[], int *numRooms);
void removeRoom(struct Room rooms[], int *numRooms);
void bookRoom(struct Room rooms[], int numRooms);
void assignOccupant(struct Room rooms[], int numRooms);

FILE * fPtr;


int main() {
    /* Variable to store user content */
    char data[DATA_SIZE];

    fPtr = fopen("hostelData.txt", "a+");

    if(fPtr == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    struct Room rooms[MAX_ROOMS];
    int numRooms = 0;
    int choice;
    // Display menu and get user input

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            showRooms(rooms, numRooms);
            break;
        case 2:
            addRoom(rooms, &numRooms);
            break;
        case 3:
            removeRoom(rooms, &numRooms);
            break;
        case 4:
            bookRoom(rooms, numRooms);
            break;
        case 5:
            assignOccupant(rooms, numRooms);
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    // Close file
    fclose(fPtr);
    return 0;
}


// Displays the main menu
void displayMenu() {
printf("\n");
printf("================= Hostel Management Application ==================\n");
printf("1. Show all rooms\n");
printf("2. Add a room\n");
printf("3. Remove a room\n");
printf("4. Book a room\n");
printf("5. Assign occupant to a room\n");
printf("6. Exit\n");
}

// Shows all the rooms and their details
void showRooms(struct Room rooms[], int numRooms) {
    printf("\n********************************************************************\n");

    if (numRooms == 0) {
        printf("\t\tNo rooms added yet.\n");
        printf("\t\tPlease select Option 2 to Add a Room\n");
        printf("********************************************************************\n\n");

        return;

    }


    printf("\t\tRoom No. \tCapacity \tOccupied by\n");

    for (int i = 0; i < numRooms; i++) {
        printf("\t\t%d \t\t%d \t\t", rooms[i].number, rooms[i].capacity);
        if (rooms[i].isOccupied) {
            printf("\t\t%s\n", rooms[i].occupantName);
        } else {
            printf("\t\tVacant\n");
        }
    }
    printf("********************************************************************\n\n");

}


// Adds a new room to the list of rooms
void addRoom(struct Room rooms[], int *numRooms) {
    printf("\n********************************************************************\n");

    if (*numRooms >= MAX_ROOMS) {
        printf("\t\tCannot add more rooms. Maximum limit reached.\n");
        printf("********************************************************************\n\n");

        return;
    }
    printf("\t\tEnter details of new room:\n");
    printf("\t\t\nRoom No.: ");
    scanf("%d", &rooms[*numRooms].number);
    printf("Capacity: ");
    scanf("%d", &rooms[*numRooms].capacity);

    // Write the Same content to file
    fprintf(fPtr,"\nRoom No: %d\n", rooms[*numRooms].number);
    fprintf(fPtr,"\nCapacity: %d\n",rooms[*numRooms].capacity);
//

    rooms[*numRooms].isOccupied = 0;
    strcpy(rooms[*numRooms].occupantName, "");
    (*numRooms)++;
    printf("\n\t\t ROOM ADDED SUCCESSFULLY!\n");

    printf("********************************************************************\n\n");

}


// Removes an existing room from the list of rooms
void removeRoom(struct Room rooms[], int *numRooms) {
    printf("\n********************************************************************\n");
    if (*numRooms == 0) {
        printf("\t\tNo rooms added yet.\n");
        printf("********************************************************************\n\n");
        return;

    }

    int roomNumber;
    printf("\t\tEnter room number to remove: ");
    scanf("%d", &roomNumber);
    int foundIndex = -1;

    for (int i = 0; i < *numRooms; i++) {
        if (rooms[i].number == roomNumber) {
        foundIndex = i;
        break;
        }
    }

    if (foundIndex == -1) {
        printf("\t\tRoom not found.\n");
    } else {
        for (int i = foundIndex; i < *numRooms - 1; i++) {
            rooms[i] = rooms[i + 1];
        }
        (*numRooms)--;
        printf("\t\tRoom removed successfully.\n");
    }

    printf("********************************************************************\n\n");

}

// Books a room for a given occupant
void bookRoom(struct Room rooms[], int numRooms) {
    printf("\n********************************************************************\n");

    if (numRooms == 0) {
        printf("\t\tNo rooms added yet.\n");
        printf("********************************************************************\n\n");

        return;
    }

    int roomNumber;
    printf("\t\tEnter room number to book: ");
    scanf("%d", &roomNumber);
    int foundIndex = -1;
    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].number == roomNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\t\tRoom not found.\n");

    } else if (rooms[foundIndex].isOccupied) {
        printf("\t\tRoom already occupied.\n");

    } else {
        rooms[foundIndex].isOccupied = 1;
        printf("\t\tRoom booked successfully.\n");
    }

    printf("********************************************************************\n\n");

}


// Assigns an occupant to a room
void assignOccupant(struct Room rooms[], int numRooms) {
    printf("\n********************************************************************\n");

    if (numRooms == 0) {
        printf("\t\tNo rooms added yet.\n");
        printf("********************************************************************\n\n");

        return;
    }

    int roomNumber;
    printf("\t\tEnter room number: ");
    scanf("%d", &roomNumber);
    int foundIndex = -1;

    for (int i = 0; i < numRooms; i++) {
        if (rooms[i].number == roomNumber) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("\t\tRoom not found.\n");
    }
    else if (!rooms[foundIndex].isOccupied) {
        printf("\t\tRoom not occupied.\n");
    }
     else {
        printf("\t\tEnter occupant name: ");
        scanf("%s", rooms[foundIndex].occupantName);
        printf("\t\t%s assigned to Room %d successfully.\n", rooms[foundIndex].occupantName, roomNumber);

        // Write Details to file
        fprintf(fPtr,"\nRoom No: %d\n", roomNumber);
        fprintf(fPtr,"Occupant: %s\n",rooms[foundIndex].occupantName);
    }

    printf("********************************************************************\n\n");

}
