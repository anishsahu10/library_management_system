#include <iostream>
#include <limits>
#include <string>
#include "Library.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"
using namespace std;
#ifdef _WIN32
#include <windows.h>
#endif

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu()
{
    cout << "\n..... | LIBRARY MANAGEMENT SYSTEM (LMS) | .....\n"
         << "1. Login\n"
         << "2. Exit\n"
         << "Enter your choice: ";
}

void displayUserMenu(const string &role)
{
    cout << "\n..... | " << role << " MAIN MENU | .....\n";
    if (role == "Student" || role == "Faculty")
    {
        cout << "1. Check Available Books\n"
             << "2. Borrow a Book\n"
             << "3. Return a Book\n"
             << "4. Check My Borrows\n";
        if (role == "Student")
        {
            cout << "5. View/Pay Fines\n";
        }
        cout << "0. Logout\n";
    }
    else if (role == "Librarian")
    {
        cout << "1. Add a Book\n"
             << "2. Remove a Book\n"
             << "3. Add a User\n"
             << "4. Remove a User\n"
             << "5. Check All Books\n"
             << "6. Check All Users\n"
             << "0. Logout\n";
    }
    cout << "Enter your choice: ";
}

void handleStudentMenu(Library &lib, User *user)
{
    Student *student = dynamic_cast<Student *>(user);
    if (!student)
        return;

    int choice;
    do
    {
        displayUserMenu("Student");
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            lib.displayAllBooks();
            break;

        case 2:
        {
            int bookId;
            cout << "Enter Book ID to borrow: ";
            cin >> bookId;
            clearInputBuffer();

            if (lib.borrowBook(student->getID(), bookId))
            {
                cout << "Book borrowed successfully!\n";
            }
            else
            {
                cout << "Failed to borrow book. Check if:\n"
                     << "- The book is available\n"
                     << "- You have no unpaid fines\n"
                     << "- You have not exceeded limit on maximum allowed books\n";
            }
            break;
        }

        case 3:
        {
            int bookId;
            cout << "Enter Book ID to return: ";
            cin >> bookId;
            clearInputBuffer();

            if (lib.returnBook(student->getID(), bookId))
            {
                cout << "Book returned successfully!\n";
                double fine = lib.calculateFine(student->getID());
                if (fine > 0)
                {
                    cout << "You have an active fine of Rs. " << fine << " for late return/overdue borrowing.\n";
                }
            }
            else
            {
                cout << "Failed to return the book.\n";
            }
            break;
        }

        case 4:
            student->getAccount().showActiveBorrows();
            break;

        case 5:
        {
            double fine = lib.calculateFine(student->getID());
            cout << "Active fine: Rs. " << fine << "\n";
            if (fine > 0)
            {
                char pay;
                cout << "Do you want to pay the fine right now? (y/n): ";
                cin >> pay;
                clearInputBuffer();
                if (pay == 'y' || pay == 'Y')
                {
                    if (lib.payFine(student->getID()))
                    {
                        cout << "Fine paid successfully!\n";
                    }
                }
            }
            break;
        }
        }
    } while (choice != 0);
}

void handleFacultyMenu(Library &lib, User *user)
{
    Faculty *faculty = dynamic_cast<Faculty *>(user);
    if (!faculty)
        return;

    int choice;
    do
    {
        displayUserMenu("Faculty");
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
        case 1:
            lib.displayAllBooks();
            break;

        case 2:
        {
            int bookId;
            cout << "Enter Book ID to borrow: ";
            cin >> bookId;
            clearInputBuffer();

            if (lib.borrowBook(faculty->getID(), bookId))
            {
                cout << "Book borrowed successfully!\n";
            }
            else
            {
                cout << "Failed to borrow book. Check if:\n"
                     << "- The book is available\n"
                     << "- You have not exceeded limit on maximum allowed books\n"
                     << "- You do not have any borrowed books overdue for more than 60 days\n";
            }
            break;
        }

        case 3:
        {
            int bookId;
            cout << "Enter Book ID to return: ";
            cin >> bookId;
            clearInputBuffer();

            if (lib.returnBook(faculty->getID(), bookId))
            {
                cout << "Book returned successfully!\n";
            }
            else
            {
                cout << "Failed to return book.\n";
            }
            break;
        }

        case 4:
            faculty->getAccount().showActiveBorrows();
            break;
        }
    } while (choice != 0);
}

void handleLibrarianMenu(Library &lib, User *user)
{
    Librarian *librarian = dynamic_cast<Librarian *>(user);
    if (!librarian)
        return;

    int choice;
    do
    {
        displayUserMenu("Librarian");
        cin >> choice;
        clearInputBuffer();

        switch (choice)
        {
        case 1:
        {
            string title, author, publisher, isbn;
            int year;

            cout << "Enter book details:\n";
            cout << "Title of the Book: ";
            getline(cin, title);
            cout << "Author Name: ";
            getline(cin, author);
            cout << "Publisher: ";
            getline(cin, publisher);
            cout << "Year of Publishing: ";
            cin >> year;
            clearInputBuffer();
            cout << "ISBN: ";
            getline(cin, isbn);

            if (lib.addBook(title, author, publisher, year, isbn))
            {
                cout << "Book added successfully!\n";
            }
            break;
        }

        case 2:
        {
            int bookId;
            cout << "Enter Book ID to remove: ";
            cin >> bookId;
            clearInputBuffer();

            if (lib.removeBook(bookId))
            {
                cout << "Book removed successfully!\n";
            }
            else
            {
                cout << "Failed to remove book.\n";
            }
            break;
        }

        case 3:
        {
            string name, password, role;
            cout << "Enter user details:\n";
            cout << "Full Name: ";
            getline(cin, name);
            cout << "Password: ";
            getline(cin, password);
            cout << "User Role (Student/Faculty): ";
            getline(cin, role);

            bool success = false;
            if (role == "Student")
            {
                success = lib.addStudent(name, password);
            }
            else if (role == "Faculty")
            {
                success = lib.addFaculty(name, password);
            }

            if (success)
            {
                cout << "User added successfully!\n";
            }
            else
            {
                cout << "Failed to add user.\n";
            }
            break;
        }

        case 4:
        {
            int userId;
            cout << "Enter User ID to remove user: ";
            cin >> userId;
            clearInputBuffer();

            if (lib.removeUser(userId))
            {
                cout << "User removed successfully!\n";
            }
            else
            {
                cout << "Failed to remove user.\n";
            }
            break;
        }

        case 5:
            lib.displayAllBooks();
            break;

        case 6:
            lib.displayAllUsers();
            break;
        }
    } while (choice != 0);
}

int main()
{
    Library lib;
    lib.initializeWithSampleData();
    cout << "Sample data is successfully initialized.\n";
    cout << "Showing the Main Menu.\n";

    int choice;
    do
    {
        displayMainMenu();
        cin >> choice;
        clearInputBuffer();

        if (choice == 1)
        {
            int userId;
            string password;

            cout << "Enter the User ID: ";
            cin >> userId;
            clearInputBuffer();
            cout << "Enter the Password: ";
            getline(cin, password);

            User *user = lib.getUser(userId);
            if (user && user->checkPassword(password))
            {
                cout << "Login successful!\n";
                if (user->getUserType() == "Student")
                {
                    handleStudentMenu(lib, user);
                }
                else if (user->getUserType() == "Faculty")
                {
                    handleFacultyMenu(lib, user);
                }
                else if (user->getUserType() == "Librarian")
                {
                    handleLibrarianMenu(lib, user);
                }
            }
            else
            {
                cout << "Invalid details, please check again!\n";
            }
        }
    } while (choice != 2);

    cout << "Press 'Enter' to exit the Library Management System, Thank you!";
    cin.get();
    cin.get();
    return 0;
}