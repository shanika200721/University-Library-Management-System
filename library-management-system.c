#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_STUDENTS 50

struct Book {
    int bookId;
    char title[100];
    char author[50];
    int isAvailable;
};

struct Student {
    int studentId;
    char name[100];
    int borrowedBooks[MAX_BOOKS];
    int numBorrowedBooks;
};

struct Book books[MAX_BOOKS];
struct Student students[MAX_STUDENTS];
int numBooks = 0;
int numStudents = 0;

// Function to add a book to the library
void addBook(int bookId, const char *title, const char *author) {
    if (numBooks >= MAX_BOOKS) {
        printf("Maximum number of books reached.\n");
        return;
    }

    struct Book newBook;
    newBook.bookId = bookId;
    strcpy(newBook.title, title);
    strcpy(newBook.author, author);
    newBook.isAvailable = 1;

    books[numBooks] = newBook;
    numBooks++;
    printf("Book added successfully.\n");
}

// Function to add a student to the library
void addStudent(int studentId, const char *name) {
    if (numStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    struct Student newStudent;
    newStudent.studentId = studentId;
    strcpy(newStudent.name, name);
    newStudent.numBorrowedBooks = 0;

    students[numStudents] = newStudent;
    numStudents++;
    printf("Student added successfully.\n");
}

// Function to find a book by its ID
int findBookById(int bookId) {
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookId == bookId) {
            return i;
        }
    }
    return -1; // Book not found
}

// Function to find a student by their ID
int findStudentById(int studentId) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].studentId == studentId) {
            return i;
        }
    }
    return -1; // Student not found
}

// Function for a student to borrow a book
void borrowBook(int studentId, int bookId) {
    int studentIndex = findStudentById(studentId);
    int bookIndex = findBookById(bookId);

    if (studentIndex == -1) {
        printf("Student with ID %d not found.\n", studentId);
    } else if (bookIndex == -1) {
        printf("Book with ID %d not found.\n", bookId);
    } else if (students[studentIndex].numBorrowedBooks >= MAX_BOOKS) {
        printf("Maximum number of borrowed books reached for this student.\n");
    } else if (!books[bookIndex].isAvailable) {
        printf("Book is not available for borrowing.\n");
    } else {
        students[studentIndex].borrowedBooks[students[studentIndex].numBorrowedBooks] = bookId;
        students[studentIndex].numBorrowedBooks++;
        books[bookIndex].isAvailable = 0;
        printf("Book successfully borrowed.\n");
    }
}

// Function for a student to return a book
void returnBook(int studentId, int bookId) {
    int studentIndex = findStudentById(studentId);
    int bookIndex = findBookById(bookId);

    if (studentIndex == -1) {
        printf("Student with ID %d not found.\n", studentId);
    } else if (bookIndex == -1) {
        printf("Book with ID %d not found.\n", bookId);
    } else {
        int i;
        for (i = 0; i < students[studentIndex].numBorrowedBooks; i++) {
            if (students[studentIndex].borrowedBooks[i] == bookId) {
                // Shift remaining books in the array to fill the gap
                for (int j = i; j < students[studentIndex].numBorrowedBooks - 1; j++) {
                    students[studentIndex].borrowedBooks[j] = students[studentIndex].borrowedBooks[j + 1];
                }
                students[studentIndex].numBorrowedBooks--;
                books[bookIndex].isAvailable = 1;
                printf("Book successfully returned.\n");
                return;
            }
        }
        printf("Student with ID %d has not borrowed book with ID %d.\n", studentId, bookId);
    }
}

// Function to display all books in the library
void displayBooks() {
    printf("===== Books in the Library =====\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Book ID: %d | Title: %s | Author: %s | Availability: %s\n", books[i].bookId, books[i].title, books[i].author, books[i].isAvailable ? "Available" : "Borrowed");
    }
    printf("===============================\n");
}

// Function to display all students in the library
void displayStudents() {
    printf("======= Students =======\n");
    for (int i = 0; i < numStudents; i++) {
        printf("Student ID: %d | Name: %s\n", students[i].studentId, students[i].name);
        printf("Borrowed Books: ");
        if (students[i].numBorrowedBooks == 0) {
            printf("None\n");
        } else {
            for (int j = 0; j < students[i].numBorrowedBooks; j++) {
                printf("%d ", students[i].borrowedBooks[j]);
            }
            printf("\n");
        }
    }
    printf("=======================\n");
}

int main() {
    int choice, bookId, studentId;
    char title[100], author[50], name[100];

    do {
        printf("\n===== University Library Management System =====\n");
        printf("1. Add Book\n");
        printf("2. Add Student\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Display All Books\n");
        printf("6. Display All Students\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &bookId);
                printf("Enter Book Title: ");
                scanf(" %[^\n]", title);
                printf("Enter Book Author: ");
                scanf(" %[^\n]", author);
                addBook(bookId, title, author);
                break;

            case 2:
                printf("Enter Student ID: ");
                scanf("%d", &studentId);
                printf("Enter Student Name: ");
                scanf(" %[^\n]", name);
                addStudent(studentId, name);
                break;

            case 3:
                printf("Enter Student ID: ");
                scanf("%d", &studentId);
                printf("Enter Book ID: ");
                scanf("%d", &bookId);
                borrowBook(studentId, bookId);
                break;

            case 4:
                printf("Enter Student ID: ");
                scanf("%d", &studentId);
                printf("Enter Book ID: ");
                scanf("%d", &bookId);
                returnBook(studentId, bookId);
                break;

            case 5:
                displayBooks();
                break;

            case 6:
                displayStudents();
                break;

            case 0:
                printf("Exiting the program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}
