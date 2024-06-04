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

    // pre: 'from' and 'to' are IDs in the users_ vector
    // post: returns a vector containing a shortest path of friend connections (as IDs) from User "from" to user "to."
    std::vector<int> shortestPath(int from, int to);

    // pre: 'from' is an ID in the users_ vector
    // post: returns a vector containing a path of relational distance 'distance' starting at the User with ID 'from.' 'to' is updated to the User at the end of this path.
    //       if no path of the given distance exists than 'to' is set to -1 and an empty vector is returned.
    std::vector<int> distanceUser(int from, int& to, int distance);

    // pre: 'who' is an ID in the users_ vector
    // post: returns a vector of IDs of relational distance 2 that share the highest "friendship score" (the number of common friends they share with user 'who').
    //       'score' is updated to the highest found score. If no candidates are found score is set to 0 and an empty vector is returned.
    std::vector<int> suggestFriends(int who, int& score);

    // pre: none
    // post: retuns a vector of vectors of all connected components in this network
    std::vector<std::vector<int> > groups();

    // pre: none
    // post: adds a new (dynamically allocated!) post object to the messages vector of the user 'ownerId'
    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    // pre: none
    // post: returns the value returned by the 'getPostsString' function of the user 'ownedId'
    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);
    
    // pre: none
    // post: Populates each user in this network with posts given the name of a text file containing those posts. Returns a 0 on success and a -1 on failure.
    int readPosts(char* fname);

    // pre: none
    // post: Writes the information of every post for every user in this network to a file named with the given name. Returns a 0 on success and a -1 on failure.
    int writePosts(char* fname);

private:
    std::vector<User*> users_;

    // INVARIANTS:
    // users_ is a vector of pointers to all of the dynamically allocated user objects that make up this network
    


    // PRIVATE MEMBER FUNCTIONS:
    
    // pre: 'origin' is an ID in the users_ vector
    // post: returns a 'prev' vector containing the paths obtained from a breadth-first search of the network starting at 'origin'
    std::vector<int> bfs(int origin); 
};

#endif