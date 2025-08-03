#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RECORDS 100

// Making a  structure for student
typedef struct {
    int id;
    char name[50];
    int age;
} Student;

// This is Global array
Student students[MAX_RECORDS];
int student_count = 0;

// This is for adding a new student
void add_student() {
    if (student_count >= MAX_RECORDS) {
        printf("Database is full!\n");
        return;
    }

    Student s;
    printf("Enter ID ");
    scanf("%d", &s.id);
    getchar(); // to clear the newline

    printf("Enter Name ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &s.age);

    students[student_count++] = s;
    printf("Student added successfully \n");
}

// Display all students
void display_students() {
    if (student_count == 0) {
        printf("No students to display \n");
        return;
    }

    printf("\n<---- Student Records ---->\n");
    for (int i = 0; i < student_count; i++) {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Age: %d\n\n", students[i].age);
    }
}

// For deleting a student Id
void delete_student_by_id() {
    if (student_count == 0) {
        printf("No students to delete \n");
        return;
    }

    int id;
    printf("Enter the ID of the student to delete ");
    scanf("%d", &id);

    int found = -1;
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Student with ID %d not found\n", id);
        return;
    }

    for (int i = found; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;
    printf("Student with ID %d deleted\n", id);
}

// Save database to file
void save_to_file() {
    FILE *fp = fopen("students.dat", "wb");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(&student_count, sizeof(int), 1, fp);
    fwrite(students, sizeof(Student), student_count, fp);
    fclose(fp);
    printf("Data saved to file.\n");
}

// Load database from file
void load_from_file() {
    FILE *fp = fopen("students.dat", "rb");
    if (fp == NULL) {
        return; // no file, start fresh
    }

    fread(&student_count, sizeof(int), 1, fp);
    fread(students, sizeof(Student), student_count, fp);
    fclose(fp);
    printf("Data loaded from file.\n");
}

// Main menu
int main() {
    int choice;

    load_from_file();

    while (1) {
        printf("\n<---- Mini Database Menu ---->\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Delete Student by ID\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_students();
                break;
            case 3:
                delete_student_by_id();
                break;
            case 4:
                save_to_file();
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}