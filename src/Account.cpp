#include "Account.h"
#include <iostream>
#include <sstream>
#include <algorithm>

Account::Account(int id) : accountID(id), totalFine(0.0) {}

bool Account::borrowBook(int bookID, int maxDays)
{
    BorrowRecord record;
    record.bookID = bookID;
    record.borrowDate = time(nullptr);
    record.dueDate = record.borrowDate + (maxDays * 24 * 60 * 60);
    record.returnDate = 0;
    record.fineAmount = 0.0;

    activeBorrows.push_back(record);
    return true;
}

bool Account::returnBook(int bookID)
{
    for (auto &record : activeBorrows)
    {
        if (record.bookID == bookID)
        {
            record.returnDate = time(nullptr);
            record.fineAmount = calculateFine();
            activeBorrows.erase(
                remove_if(activeBorrows.begin(), activeBorrows.end(),
                          [bookID](const BorrowRecord &r)
                          { return r.bookID == bookID; }),
                activeBorrows.end());

            return true;
        }
    }
    return false;
}

double Account::calculateFine() const
{
    double total = 0.0;
    for (const auto &record : activeBorrows)
    {
        time_t now = time(nullptr);
        if (now > record.dueDate)
        {
            double daysOverdue = difftime(now, record.dueDate) / (24 * 60 * 60);
            total += daysOverdue * 10.0;
        }
    }
    return total;
}

bool Account::payFine()
{
    if (totalFine > 0)
    {
        totalFine = 0.0;
        return true;
    }
    return false;
}

void Account::showActiveBorrows() const
{
    cout << "Active Book Borrows:\n";

    for (const auto &record : activeBorrows)
    {
        char borrowDateStr[30], dueDateStr[30];

        strftime(borrowDateStr, sizeof(borrowDateStr), "%Y-%m-%d %H:%M:%S", localtime(&record.borrowDate));
        strftime(dueDateStr, sizeof(dueDateStr), "%Y-%m-%d %H:%M:%S", localtime(&record.dueDate));

        cout << "Book ID: " << record.bookID
             << ", Borrowed on: " << borrowDateStr
             << ", Due on: " << dueDateStr << endl;
    }
}

int Account::getAccountID() const
{
    return accountID;
}

const vector<BorrowRecord> &Account::getActiveBorrows() const
{
    return activeBorrows;
}

double Account::getTotalFine() const
{
    return totalFine;
}

int Account::getActiveBorrowCount() const
{
    return activeBorrows.size();
}

string Account::toString() const
{
    stringstream ss;
    ss << accountID << "|" << totalFine << "|";

    ss << activeBorrows.size() << "|";
    for (const auto &record : activeBorrows)
    {
        ss << record.bookID << ","
           << record.borrowDate << ","
           << record.dueDate << ","
           << record.returnDate << ","
           << record.fineAmount << "|";
    }

    return ss.str();
}

Account Account::fromString(const string &data)
{
    stringstream ss(data);
    string token;
    vector<string> tokens;

    while (getline(ss, token, '|'))
    {
        tokens.push_back(token);
    }

    if (tokens.size() < 3)
    {
        throw runtime_error("Invalid account format!");
    }

    Account account(stoi(tokens[0]));
    account.totalFine = stod(tokens[1]);

    int activeBorrowsCount = stoi(tokens[2]);
    for (int i = 0; i < activeBorrowsCount; i++)
    {
        stringstream recordSS(tokens[3 + i]);
        string recordToken;
        vector<string> recordTokens;

        while (getline(recordSS, recordToken, ','))
        {
            recordTokens.push_back(recordToken);
        }

        if (recordTokens.size() == 5)
        {
            BorrowRecord record;
            record.bookID = stoi(recordTokens[0]);
            record.borrowDate = stoll(recordTokens[1]);
            record.dueDate = stoll(recordTokens[2]);
            record.returnDate = stoll(recordTokens[3]);
            record.fineAmount = stod(recordTokens[4]);
            account.activeBorrows.push_back(record);
        }
    }

    return account;
}