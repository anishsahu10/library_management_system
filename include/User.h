#ifndef USER_H
#define USER_H

using namespace std;
#include <string>

class User
{
protected:
    int userID;
    string fullName;
    string userPassword;
    string userType;

public:
    User(int id, const string &name, const string &pwd);
    virtual ~User() = default;

    int getID() const;
    string getName() const;
    string getUserType() const;

    virtual bool isAllowedToBorrow() const = 0;
    virtual int maxBooksAllowed() const = 0;
    virtual int maxDaysAllowed() const = 0;
    virtual double lateReturnFee() const = 0;

    bool checkPassword(const string &inputPwd) const;
    virtual void showUserDetails() const = 0;
};

#endif