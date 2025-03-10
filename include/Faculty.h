#ifndef FACULTY_H
#define FACULTY_H

using namespace std;
#include <string>
#include "User.h"
#include "Account.h"

class Faculty : public User
{
private:
    Account account;

public:
    Faculty(int id, const string &name, const string &pwd);

    bool isAllowedToBorrow() const override;
    int maxBooksAllowed() const override;
    int maxDaysAllowed() const override;
    double lateReturnFee() const override;
    void showUserDetails() const override;

    Account &getAccount();
    bool hasOverdueBook30Days() const;
    bool hasOverdueBook60Days() const;
};

#endif