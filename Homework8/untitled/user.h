#ifndef USER_H
#define USER_H

#include "post.h"
#include <string>
#include <set>
#include <vector>

class User
{
public:

    // default constructor
    // pre: none
    // post: creates a new user with empty parameters (check if this is what you're meant to do) 
    User();

    // pre: none
    // post: frees dynamically allocated memory in this user object
    ~User();

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

    // pre: none
    // post: stores a pointer to a *dynamically allocated* Post object in posts_
    void addPost(Post* postptr);

    // pre: none
    // post: returns a reference to a vector of user posts and incoming posts for this user 
    std::vector<Post*> & getPosts();

    // pre: none
    // post: returns a reference toa vector of user/incoming posts this user has liked
    std::vector<Post*> & getLikes();

    // pre: none
    // post: adds the liked post to the vector
    void like(Post*postptr);

    // pre: the post being unliked is already in the likes vector
    // post: removes the post from the likes vector
    void unlike(Post* postptr);

    // pre: none
    // post: returns a string containing the [howMany] most recent posts for this user
    //       each post is separated by two newline characters
    //       each type of post should use its respective toString function
    //       Posts are ordered by messageId in descending order (they are stored in acending order)
    //       Do not include private IncomingPosts if showOnlyPublic is true
    std::string getPostsString(int howMany, bool showOnlyPublic);

private:
    int id_, year_, zip_;
    std::string name_;
    std::set<int> friends_;
    std::vector<Post*> posts_;
    std::vector<Post*> likes_;

    // INVARIANTS:
    // id_ stores the index of this user in the Network class's vector (default is 0)
    // name_ stores the first and last name of this user, separated by spaces
    // year_ stores the birth year of this user
    // zip_ stores the zip code of this user
    // friends_ is a set of the IDs of every friend of this user
    // posts_ is a vector of both owner posts and incoming post for this user
    // likes_ is a vecotr of all the posts this user has liked


    // PRIVATE MEMBER FUNCTIONS:
    
    //pre: none
    // post: returns true if the given id is present in this user's friend list, and false otherwise
    bool isFriend(int id);
};

#endif
