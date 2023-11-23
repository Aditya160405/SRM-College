#include <stdio.h>
#include <string.h>

// Define constants for maximum students and rooms
#define MAX_STUDENTS 100
#define MAX_ROOMS 50

// Arrays to store student and room information
char studentNames[MAX_STUDENTS][50];
int studentRollNumbers[MAX_STUDENTS];
int studentRoomNumbers[MAX_STUDENTS];

int roomNumbers[MAX_ROOMS];
int roomCapacities[MAX_ROOMS];
int roomOccupied[MAX_ROOMS];

int studentCount = 0;
int roomCount = 0;

void saveStudentsToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < studentCount; i++) {
        fprintf(file, "%s %d %d\n", studentNames[i], studentRollNumbers[i], studentRoomNumbers[i]);
    }

    fclose(file);
}

void loadStudentsFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        printf("No previous student data found.\n");
        return;
    }

    while (fscanf(file, "%s %d %d", studentNames[studentCount], &studentRollNumbers[studentCount], &studentRoomNumbers[studentCount]) != EOF) {
        studentCount++;
    }

    fclose(file);
}

void saveRoomsToFile() {
    FILE *file = fopen("rooms.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < roomCount; i++) {
        fprintf(file, "%d %d %d\n", roomNumbers[i], roomCapacities[i], roomOccupied[i]);
    }

    fclose(file);
}

void loadRoomsFromFile() {
    FILE *file = fopen("rooms.txt", "r");
    if (file == NULL) {
        printf("No previous room data found.\n");
        return;
    }

    while (fscanf(file, "%d %d %d", &roomNumbers[roomCount], &roomCapacities[roomCount], &roomOccupied[roomCount]) != EOF) {
        roomCount++;
    }

    fclose(file);
}

// Function to display the menu and handle user input
void displayMenu() {
    printf("\nHostel Accommodation System\n");
    printf("1. Add a Student\n");
    printf("2. Allocate a Room\n");
    printf("3. Check Room Availability\n");
    printf("4. Display Student Information\n");
    printf("5. Vacate a Room\n");
    printf("6. Exit\n");
}

// Function to add a student
void addStudent() {
     if (studentCount < MAX_STUDENTS) {
        printf("Enter student name: ");
        scanf("%s", studentNames[studentCount]);
        printf("Enter roll number: ");
        scanf("%d", &studentRollNumbers[studentCount]);
        studentRoomNumbers[studentCount] = 0; // Initialize room number
        studentCount++;
        printf("Student added successfully.\n");
    } else {
        printf("Maximum number of students reached.\n");
    }
}

// Function to allocate a room
void allocateRoom() {
    if (studentCount > 0) {
        printf("Enter student's roll number: ");
        int rollNumber;
        scanf("%d", &rollNumber);

        // Find the student by roll number
        int studentIndex = -1;
        for (int i = 0; i < studentCount; i++) {
            if (studentRollNumbers[i] == rollNumber) {
                studentIndex = i;
                break;
            }
        }

        if (studentIndex != -1) {
            if (roomCount < MAX_ROOMS) {
                int roomIndex = roomCount;
                for (int i = 0; i < roomCount; i++) {
                    if (roomOccupied[i] == 0) {
                        roomIndex = i;
                        break;
                    }
                }
                studentRoomNumbers[studentIndex] = roomNumbers[roomIndex];
                roomOccupied[roomIndex] = 1;
                roomCount++;
                printf("Room allocated successfully.\n");
            } else {
                printf("All rooms are occupied.\n");
            }
        } else {
            printf("Student not found.\n");
        }
    } else {
        printf("No students added.\n");
    }
}

// Function to check room availability
void checkRoomAvailability() {
    printf("Room Availability:\n");
    printf("Room Number\tStatus\n");
    printf("----------------------------\n");
    
    for (int i = 0; i < roomCount; i++) {
        printf("%d\t\t", roomNumbers[i]);
        if (roomOccupied[i] == 0) {
            printf("Vacant\n");
        } else {
            printf("Occupied\n");
        }
    }
}

// Function to display student information
void displayStudentInfo() {
     printf("Enter the student's roll number: ");
    int rollNumber;
    scanf("%d", &rollNumber);

    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentRollNumbers[i] == rollNumber) {
            studentIndex = i;
            break;
        }
 }

    if (studentIndex != -1) {
        printf("Student Name: %s\n", studentNames[studentIndex]);
        printf("Roll Number: %d\n", studentRollNumbers[studentIndex]);
        printf("Room Number: %d\n", studentRoomNumbers[studentIndex]);
        // You can display other information here if needed
    } else {
        printf("Student not found.\n");
    }
}

// Function to vacate a room
void vacateRoom() {
  printf("Enter student's roll number to vacate the room: ");
    int rollNumber;
    scanf("%d", &rollNumber);

    int studentIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentRollNumbers[i] == rollNumber) {
            studentIndex = i;
            break;
        }
    }

    if (studentIndex != -1) {
        int roomIndex = -1;
        for (int i = 0; i < roomCount; i++) {
            if (studentRoomNumbers[studentIndex] == roomNumbers[i]) {
                roomIndex = i;
                break;
            }
        }

        if (roomIndex != -1) {
            roomOccupied[roomIndex] = 0;
            studentRoomNumbers[studentIndex] = 0;
            printf("Room vacated successfully.\n");
        } else {
            printf("Room not found.\n");
        }
    } else {
        printf("Student not found.\n");
    }  
}

int main() {
    loadStudentsFromFile();
    loadRoomsFromFile();

    int choice;

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                allocateRoom();
                break;
            case 3:
                checkRoomAvailability();
                break;
            case 4:
                displayStudentInfo();
                break;
            case 5:
                vacateRoom();
                break;
            case 6:
                saveStudentsToFile();
                saveRoomsToFile();
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}