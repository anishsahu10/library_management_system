#include "Faculty.h"
#include <iostream>

Faculty::Faculty(int id, const string &name, const string &pwd)
    : User(id, name, pwd), account(id)
{
    userType = "Faculty";
}

bool Faculty::isAllowedToBorrow() const
{
    return account.getActiveBorrowCount() < maxBooksAllowed() && !hasOverdueBook60Days();
}

int Faculty::maxBooksAllowed() const
{
    return 5;
}

int Faculty::maxDaysAllowed() const
{
    return 30;
}

double Faculty::lateReturnFee() const
{
    return 0.0;
}

void Faculty::showUserDetails() const
{
    cout << "Faculty ID: " << getID() << "\n"
         << "Full Name: " << getName() << "\n"
         << "User Role: " << getUserType() << "\n"
         << "Active Book Borrows: " << account.getActiveBorrowCount() << "\n";
}

Account &Faculty::getAccount()
{
    return account;
}

bool Faculty::hasOverdueBook30Days() const
{
    time_t now = time(nullptr);
    const auto &borrows = account.getActiveBorrows();

    for (const auto &record : borrows)
    {
        double daysOverdue = difftime(now, record.dueDate) / (24 * 60 * 60);
        if (daysOverdue > 30)
        {
            return true;
        }
    }
    return false;
}

bool Faculty::hasOverdueBook60Days() const
{
    time_t now = time(nullptr);
    const auto &borrows = account.getActiveBorrows();

    for (const auto &record : borrows)
    {
        double daysOverdue = difftime(now, record.dueDate) / (24 * 60 * 60);
        if (daysOverdue > 60)
        {
            return true;
        }
    }
    return false;
}