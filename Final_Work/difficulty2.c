#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_BOOKS 100
#define MAX_STUDENTS 100

typedef struct {
    char login[50];
    char password[50];
    int book_access;
    int student_access;
} User;

typedef struct {
    char isbn[15];
    char author[50];
    char title[100];
    int total_copies;
    int available_copies;
} Book;

typedef struct {
    char student_id[10];
    char last_name[50];
    char first_name[50];
    char middle_name[50];
    char department[50];
    char course[100];
} Student;

User users[MAX_USERS];
int num_users = 0;

Book books[MAX_BOOKS];
int num_books = 0;

Student students[MAX_STUDENTS];
int num_students = 0;

void loadUsers(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open users file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        strcpy(users[num_users].login, token);

        token = strtok(NULL, ";");
        strcpy(users[num_users].password, token);

        token = strtok(NULL, ";");
        users[num_users].book_access = atoi(token);

        token = strtok(NULL, ";");
        users[num_users].student_access = atoi(token);

        num_users++;
    }

    fclose(file);
}

void loadBooks(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open books file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        strcpy(books[num_books].isbn, token);

        token = strtok(NULL, ";");
        strcpy(books[num_books].author, token);

        token = strtok(NULL, ";");
        strcpy(books[num_books].title, token);

        token = strtok(NULL, ";");
        books[num_books].total_copies = atoi(token);

        token = strtok(NULL, ";");
        books[num_books].available_copies = atoi(token);

        num_books++;
    }

    fclose(file);
}

void loadStudents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open students file.\n");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        strcpy(students[num_students].student_id, token);

        token = strtok(NULL, ";");
        strcpy(students[num_students].last_name, token);

        token = strtok(NULL, ";");
        strcpy(students[num_students].first_name, token);

        token = strtok(NULL, ";");
        strcpy(students[num_students].middle_name, token);

        token = strtok(NULL, ";");
        strcpy(students[num_students].department, token);

        token = strtok(NULL, ";");
        strcpy(students[num_students].course, token);

        num_students++;
    }

    fclose(file);
}

int login() {
    char login[50];
    char password[50];

    printf("Login: ");
    scanf("%s", login);

    printf("Password: ");
    scanf("%s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].login, login) == 0 && strcmp(users[i].password, password) == 0) {
            return i; // Return the index of the user
        }
    }

    return -1; // User not found
}

void showBooksMenu() {
    printf("Books Menu\n");
    printf("1) Add New Book\n");
    printf("2) Edit Book Information\n");
    printf("0) Return to Main Menu\n");
}

void showStudentsMenu() {
    printf("Students Menu\n");
    printf("1) Add New Student\n");
    printf("2) Create Backup\n");
    printf("0) Return to Main Menu\n");
}

void addNewBook() {
    if (num_books >= MAX_BOOKS) {
        printf("Maximum number of books reached.\n");
        return;
    }

    printf("Enter ISBN: ");
    scanf("%s", books[num_books].isbn);

    printf("Enter author: ");
    scanf("%s", books[num_books].author);

    printf("Enter title: ");
    scanf("%s", books[num_books].title);

    printf("Enter total copies: ");
    scanf("%d", &books[num_books].total_copies);

    printf("Enter available copies: ");
    scanf("%d", &books[num_books].available_copies);

    num_books++;
    printf("Book added successfully.\n");
}

void editBookInformation() {
    char isbn[15];
    printf("Enter ISBN of the book to edit: ");
    scanf("%s", isbn);

    int bookIndex = -1;
    for (int i = 0; i < num_books; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            bookIndex = i;
            break;
        }
    }

    if (bookIndex == -1) {
        printf("Book not found.\n");
        return;
    }

    printf("Enter new author: ");
    scanf("%s", books[bookIndex].author);

    printf("Enter new title: ");
    scanf("%s", books[bookIndex].title);

    printf("Enter new total copies: ");
    scanf("%d", &books[bookIndex].total_copies);

    printf("Enter new available copies: ");
    scanf("%d", &books[bookIndex].available_copies);

    printf("Book information updated successfully.\n");
}

void addNewStudent() {
    if (num_students >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    printf("Enter student ID: ");
    scanf("%s", students[num_students].student_id);

    printf("Enter last name: ");
    scanf("%s", students[num_students].last_name);

    printf("Enter first name: ");
    scanf("%s", students[num_students].first_name);

    printf("Enter middle name: ");
    scanf("%s", students[num_students].middle_name);

    printf("Enter department: ");
    scanf("%s", students[num_students].department);

    printf("Enter course: ");
    scanf("%s", students[num_students].course);

    num_students++;
    printf("Student added successfully.\n");
}

void createBackup() {
    char filename[100];
    time_t current_time = time(NULL);
    struct tm *timeinfo = localtime(&current_time);
    strftime(filename, sizeof(filename), "students_%Y-%m-%d_%H-%M-%S.csv", timeinfo);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Failed to create backup.\n");
        return;
    }

    for (int i = 0; i < num_students; i++) {
        fprintf(file, "%s;%s;%s;%s;%s;%s\n",
                students[i].student_id,
                students[i].last_name,
                students[i].first_name,
                students[i].middle_name,
                students[i].department,
                students[i].course);
    }

    fclose(file);

    printf("Backup created successfully. Filename: %s\n", filename);
}

int main() {
    loadUsers("users.csv");
    loadBooks("books.csv");
    loadStudents("students.csv");

    int userIndex = login();
    if (userIndex == -1) {
        printf("Invalid login or password.\n");
        return 0;
    }

    User currentUser = users[userIndex];

    if (currentUser.book_access && !currentUser.student_access) {
        // User has access only to books
        int choice;
        do {
            showBooksMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addNewBook();
                    break;
                case 2:
                    editBookInformation();
                    break;
                case 0:
                    // Return to main menu
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        } while (choice != 0);
    } else if (!currentUser.book_access && currentUser.student_access) {
        // User has access only to students
        int choice;
        do {
            showStudentsMenu();
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addNewStudent();
                    break;
                case 2:
                    createBackup();
                    break;
                case 0:
                    // Return to main menu
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        } while (choice != 0);
    } else if (currentUser.book_access && currentUser.student_access) {
        // User has access to both books and students
        int choice;
        do {
            printf("Main Menu\n");
            printf("1) Books\n");
            printf("2) Students\n");
            printf("0) Exit\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    showBooksMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addNewBook();
                            break;
                        case 2:
                            editBookInformation();
                            break;
                        case 0:
                            // Return to main menu
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                    break;
                case 2:
                    showStudentsMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            addNewStudent();
                            break;
                        case 2:
                            createBackup();
                            break;
                        case 0:
                            // Return to main menu
                            break;
                        default:
                            printf("Invalid choice.\n");
                            break;
                    }
                    break;
                case 0:
                    // Exit
                    break;
                default:
                    printf("Invalid choice.\n");
                    break;
            }
        } while (choice != 0);
    }

    return 0;
}