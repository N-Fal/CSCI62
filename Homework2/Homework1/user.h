#ifndef USER_H
#define USER_H

#include <string>
#include <set>

class User
{
public:

    // default constructor
    // pre: none
    // post: creates a new user with empty parameters (check if this is what you're meant to do) 
    User();

    // constructor
    // pre: none
    // post: creates a new user with the given ID, name, year, zip code, and friend list
    User(int id, std::string name, int year, int zip, const std::set<int> & friends);

    // pre: none
    // post: returns the id of this user
    int getId();

    // pre: none
    //post: returns the name of this user
    std::string getName();

    // pre: none
    // post: returns the birth year of this user
    int getYear();

    // pre: none
    // post: returns the zip code of this user
    int getZip();

    // pre: none
    // post: returns a reference to a set of IDs of friends of this user
    std::set<int> & getFriends();

    // pre: none
    // post: adds the given ID to the friend list for this user. If the given ID is already in the list, nothing happens
    void addFriend(int id);

    // pre: none
    // post: removes the given ID from the friend list for this user. If the given ID is not in the list, nothing happens
    void deleteFriend(int id);

private:
    int id_, year_, zip_;
    std::string name_;
    std::set<int> friends_;

    // INVARIANTS:
    // id_ stores the index of this user in the Network class's vector (default is 0)
    // name_ stores the first and last name of this user, separated by spaces
    // year_ stores the birth year of this user
    // zip_ stores the zip code of this user
    // friends_ is a set of the IDs of every friend of this user



    // PRIVATE MEMBER FUNCTIONS:
    
    //pre: none
    // post: returns true if the given id is present in this user's friend list, and false otherwise
    bool isFriend(int id);
};

#endif