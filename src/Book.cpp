#include "Book.h"
#include <iostream>
#include <sstream>
#include <vector>

Book::Book(int id, const string &title, const string &author)
    : bookID(id), bookTitle(title), authorName(author), isAvailable(true) {}

int Book::getBookID() const { return bookID; }
string Book::getTitle() const { return bookTitle; }
string Book::getAuthor() const { return authorName; }
bool Book::isBookAvailable() const { return isAvailable; }

void Book::setAvailability(bool status)
{
    isAvailable = status;
}

string Book::toString() const
{
    stringstream ss;
    ss << bookID << "|"
       << bookTitle << "|"
       << authorName << "|"
       << isAvailable;
    return ss.str();
}

Book Book::fromString(const string &data)
{
    stringstream ss(data);
    string token;
    vector<string> tokens;

    while (getline(ss, token, '|'))
    {
        tokens.push_back(token);
    }

    if (tokens.size() != 4)
    {
        throw runtime_error("Invalid book format!");
    }

    Book book(
        stoi(tokens[0]),
        tokens[1],
        tokens[2]);
    book.isAvailable = (tokens[3] == "1");
    return book;
}