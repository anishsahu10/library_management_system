#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(int id, const string &name, const string &pwd)
    : User(id, name, pwd), account(id)
{
    userType = "Student";
}

bool Student::isAllowedToBorrow() const
{
    return account.getActiveBorrowCount() < maxBooksAllowed() && !hasOverdueBook15Days();
}

int Student::maxBooksAllowed() const
{
    return 3;
}

int Student::maxDaysAllowed() const
{
    return 15;
}

double Student::lateReturnFee() const
{
    return 10;
}

void Student::showUserDetails() const
{
    cout << "Student ID: " << getID() << "\n"
         << "Full Name: " << getName() << "\n"
         << "User Role: " << getUserType() << "\n"
         << "Active Book Borrows: " << account.getActiveBorrowCount() << "\n";
}

Account &Student::getAccount()
{
    return account;
}

bool Student::hasOverdueBook15Days() const
{
    time_t now = time(nullptr);
    const auto &borrows = account.getActiveBorrows();

    for (const auto &record : borrows)
    {
        double daysOverdue = difftime(now, record.dueDate) / (24 * 60 * 60);
        if (daysOverdue > 15)
        {
            return true;
        }
    }
    return false;
}