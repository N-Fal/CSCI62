#include "user.h"
#include <string>
#include <set>

User::User() {}

User::User(int id, std::string name, int year, int zip, const std::set<int> & friends)
{
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
}

int User::getId()
{
    return id_;
}

std::string User::getName()
{
    return name_;
}

int User::getYear()
{
    return year_;
}

int User::getZip()
{
    return zip_;
}

std::set<int> & User::getFriends()
{
    return friends_;
}

void User::addFriend(int id)
{
    if (!isFriend(id))
    {
        friends_.insert(id);
    }
}

void User::deleteFriend(int id)
{
    if (isFriend(id))
    {
        friends_.erase(id);
    }
}

bool User::isFriend(int id)
{  
    return (friends_.find(id) != friends_.end());
}

