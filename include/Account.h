#ifndef ACCOUNT_H
#define ACCOUNT_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include "Book.h"

struct BorrowRecord
{
    int bookID;
    time_t borrowDate;
    time_t dueDate;
    time_t returnDate;
    double fineAmount;
};

class Account
{
private:
    int accountID;
    vector<BorrowRecord> activeBorrows;
    double totalFine;

public:
    Account(int id);

    bool borrowBook(int bookID, int maxDays);
    bool returnBook(int bookID);
    double calculateFine() const;
    bool payFine();

    void showActiveBorrows() const;

    int getAccountID() const;
    const vector<BorrowRecord> &getActiveBorrows() const;
    double getTotalFine() const;
    int getActiveBorrowCount() const;

    string toString() const;
    static Account fromString(const string &data);
};

#endif