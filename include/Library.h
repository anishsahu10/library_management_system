#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <map>
#include <memory>
#include "Book.h"
#include "User.h"
#include "Student.h"
#include "Faculty.h"
#include "Librarian.h"
using namespace std;

class Library
{
private:
    map<int, unique_ptr<Book>> books;
    map<int, unique_ptr<User>> users;
    int nextBookId;
    int nextUserId;

    void loadData();
    void saveData() const;

public:
    Library();
    ~Library();

    bool addBook(const string &title, const string &author,
                 const string &publisher, int year, const string &isbn);
    bool removeBook(int bookID);
    Book *getBook(int bookID);
    void displayAllBooks() const;

    bool addStudent(const string &name, const string &password);
    bool addFaculty(const string &name, const string &password);
    bool addLibrarian(const string &name, const string &password);
    bool removeUser(int userId);
    User *getUser(int userId);
    void displayAllUsers() const;

    bool borrowBook(int userId, int bookID);
    bool returnBook(int userId, int bookID);

    double calculateFine(int userId);
    bool payFine(int userId);

    void initializeWithSampleData();
};

#endif