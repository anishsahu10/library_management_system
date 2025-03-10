#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
#include <string>
#include "User.h"
#include "Account.h"

class Student : public User
{
private:
    Account account;

public:
    Student(int id, const string &name, const string &pwd);

    bool isAllowedToBorrow() const override;
    int maxBooksAllowed() const override;
    int maxDaysAllowed() const override;
    double lateReturnFee() const override;
    void showUserDetails() const override;

    Account &getAccount();
    bool hasOverdueBook15Days() const;
};

#endif