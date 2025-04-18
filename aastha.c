#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 10
#define MAX_MEMBERS 10

typedef struct {
    char title[50];
    int bookID;
    int isBorrowed; // 0: not borrowed, 1: borrowed
} Book;

typedef struct {
    char name[50];
    int memberID;
    int borrowedBookID; // Only one book borrowed at a time for simplicity
} Member;

Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
int numBooks = 0;
int numMembers = 0;

void addBook() {
    if (numBooks < MAX_BOOKS) {
        printf("Enter book title: ");
        scanf(" %[^\n]", books[numBooks].title);
        printf("Enter book ID: ");
        scanf("%d", &books[numBooks].bookID);
        books[numBooks].isBorrowed = 0;
        numBooks++;
        printf("Book added.\n");
    } else {
        printf("Library is full.\n");
    }
}

void addMember() {
    if (numMembers < MAX_MEMBERS) {
        printf("Enter member name: ");
        scanf(" %[^\n]", members[numMembers].name);
        printf("Enter member ID: ");
        scanf("%d", &members[numMembers].memberID);
        members[numMembers].borrowedBookID = 0; // 0 means no book borrowed
        numMembers++;
        printf("Member added.\n");
    } else {
        printf("Maximum members reached.\n");
    }
}

void borrowBook() {
    int memberID, bookID;
    printf("Enter member ID: ");
    scanf("%d", &memberID);
    printf("Enter book ID: ");
    scanf("%d", &bookID);

    int memberIndex = -1, bookIndex = -1;
    for (int i = 0; i < numMembers; i++) {
        if (members[i].memberID == memberID) {
            memberIndex = i;
            break;
        }
    }
    for (int i = 0; i < numBooks; i++) {
        if (books[i].bookID == bookID) {
            bookIndex = i;
            break;
        }
    }

    if (memberIndex != -1 && bookIndex != -1 && books[bookIndex].isBorrowed == 0 && members[memberIndex].borrowedBookID == 0) {
        books[bookIndex].isBorrowed = 1;
        members[memberIndex].borrowedBookID = bookID;
        printf("Book borrowed.\n");
    } else {
        printf("Book not available, or member already borrowed a book, or member/book not found.\n");
    }
}

void returnBook() {
    int memberID;
    printf("Enter member ID: ");
    scanf("%d", &memberID);

    int memberIndex = -1, bookIndex = -1;
    for (int i = 0; i < numMembers; i++) {
        if (members[i].memberID == memberID) {
            memberIndex = i;
            break;
        }
    }

    if (memberIndex != -1 && members[memberIndex].borrowedBookID != 0) {
        for (int i = 0; i < numBooks; i++) {
            if (books[i].bookID == members[memberIndex].borrowedBookID) {
                bookIndex = i;
                break;
            }
        }
        if (bookIndex != -1)
        {
            books[bookIndex].isBorrowed = 0;
            members[memberIndex].borrowedBookID = 0;
            printf("Book returned.\n");
        }

    } else {
        printf("Member has not borrowed any book, or member not found.\n");
    }
}

void displayBooks() {
    printf("--- Books ---\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Title: %s, ID: %d, Borrowed: %s\n", books[i].title, books[i].bookID, books[i].isBorrowed ? "Yes" : "No");
    }
}
void displayMembers() {
    printf("--- Members ---\n");
    for (int i = 0; i < numMembers; i++) {
        printf("Name: %s, ID: %d, Borrowed Book ID: %d\n", members[i].name, members[i].memberID, members[i].borrowedBookID);
    }
}

int main() {
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add Book\n");
        printf("2. Add Member\n");
        printf("3. Borrow Book\n");
        printf("4. Return Book\n");
        printf("5. Display Books\n");
        printf("6. Display Members\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: addMember(); break;
            case 3: borrowBook(); break;
            case 4: returnBook(); break;
            case 5: displayBooks(); break;
            case 6: displayMembers(); break;
            case 7: printf("Exiting.\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 7);
    return 0;
}
