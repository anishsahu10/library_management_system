#include "User.h"
#include <iostream>
using namespace std;

User::User(int id, const string &name, const string &pwd)
    : userID(id), fullName(name), userPassword(pwd)
{
}

int User::getID() const
{
    return userID;
}

string User::getName() const
{
    return fullName;
}

string User::getUserType() const
{
    return userType;
}

bool User::checkPassword(const string &inputPwd) const
{
    return userPassword == inputPwd;
}