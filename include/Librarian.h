#ifndef LIBRARIAN_H
#define LIBRARIAN_H

using namespace std;
#include <string>
#include "User.h"
#include "Book.h"
#include <vector>

class Librarian : public User
{
public:
    Librarian(int id, const string &name, const string &pwd);

    bool isAllowedToBorrow() const override;
    int maxBooksAllowed() const override;
    int maxDaysAllowed() const override;
    double lateReturnFee() const override;
    void showUserDetails() const override;

    bool addBook(Book *book);
    bool removeBook(int bookID);
    bool updateBook(int bookID, const Book &newInfo);
    bool addUser(User *user);
    bool removeUser(int userId);
};

#endif