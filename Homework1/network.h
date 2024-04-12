#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>
#include <string>

class Network
{
public:

    // pre: none
    // post: creates an empty network object
    Network();

    // pre: none
    // post: frees dynamically allocated memory in this network object
    ~Network();
    
    // pre: none
    // post: Adds a user to this network's database
    void addUser(User* userPtr);

    // pre: none
    // post: Creates a two-direction friend connection between the users with the given names. Returns 0 on success and -1 if either user is invalid
    int addConnection(std::string s1, std::string s2);

    // pre: none
    // post: Deletes both direction friend connections of the users with the given names. Returns 0 on success and -1 if either user is invalid 
    int deleteConnection(std::string s1, std::string s2);

    // pre: none
    // post: returns the ID of the user with the given name. If the user is not present in this network, a -1 is returned
    int getId(std::string name);

    // pre: none
    // post: Populates this network with users given the name of a text file containing those users. Returns a 0 on success and a -1 on failure.
    int readUsers(char* fname);

    // pre: none
    // post: Writes the information of every user in the network to a file named with the given name. Returns a 0 on success and a -1 on failure.
    int writeUsers(char* fname);

    // pre: none
    // post: Returns the number of users in this network
    int numUsers();

    // pre: none
    // post: Returns a pointer to the user in this network with the given ID. If the user is not present in this network, a nullptr is returned.  
    User* getUser(int id);

private:
    std::vector<User*> users_;

    // INVARIANTS:
    // users_ is a vector of pointers to all of the dynamically allocated user objects that make up this network
};

#endif