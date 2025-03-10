#include "Librarian.h"
#include <iostream>

Librarian::Librarian(int id, const string &name, const string &pwd)
    : User(id, name, pwd)
{
    userType = "Librarian";
}

bool Librarian::isAllowedToBorrow() const
{
    return false;
}

int Librarian::maxBooksAllowed() const
{
    return 0;
}

int Librarian::maxDaysAllowed() const
{
    return 0;
}

double Librarian::lateReturnFee() const
{
    return 0.0;
}

void Librarian::showUserDetails() const
{
    cout << "Librarian ID: " << getID() << "\n"
         << "Full Name: " << getName() << "\n"
         << "User Role: " << getUserType() << "\n";
}

bool Librarian::addBook(Book *book)
{
    if (book == nullptr)
        return false;
    return true;
}

bool Librarian::removeBook(int bookId)
{
    return true;
}

bool Librarian::updateBook(int bookId, const Book &newInfo)
{
    return true;
}

bool Librarian::addUser(User *user)
{
    if (user == nullptr)
        return false;
    return true;
}

bool Librarian::removeUser(int userId)
{
    return true;
}