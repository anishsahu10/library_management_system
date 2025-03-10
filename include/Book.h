#ifndef BOOK_H
#define BOOK_H

using namespace std;
#include <string>

class Book
{
private:
    int bookID;
    string bookTitle;
    string authorName;
    bool isAvailable;

public:
    Book(int id, const string &title, const string &author);

    int getBookID() const;
    string getTitle() const;
    string getAuthor() const;

    bool isBookAvailable() const;
    void setAvailability(bool status);

    string toString() const;
    static Book fromString(const string &data);
};

#endif