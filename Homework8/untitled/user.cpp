#include "user.h"
#include "post.h"
#include <string>
#include <set>
#include <stack>
#include <algorithm>

User::User() {}

User::User(int id, std::string name, int year, int zip, const std::set<int> & friends)
{
    id_ = id;
    name_ = name;
    year_ = year;
    zip_ = zip;
    friends_ = friends;
}

User::~User()
{
    for (Post* postptr : posts_)
    {
        delete postptr;
    }

    posts_.clear();
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

void User::addPost(Post* postptr)
{
    posts_.push_back(postptr);
}

std::vector<Post*> & User::getPosts()
{
    return posts_;
}

std::vector<Post*> & User::getLikes()
{
    return likes_;
}

void User::like(Post*postptr)
{
    likes_.push_back(postptr);
}

void User::unlike(Post* postptr)
{
    likes_.erase(std::remove(likes_.begin(), likes_.end(), postptr), likes_.end());
}

// post: returns a string containing the [howMany] most recent posts for this user
// each post is separated by two newline characters
// each type of post should use its respective toString function
// Posts are ordered by messageId in descending order (they are stored in ascending order)
// Do not include private IncomingPosts if showOnlyPublic is true

std::string User::getPostsString(int howMany, bool showOnlyPublic)
{
    std::string output = "";
    std::stack<Post*> stk;
    for (Post* post : posts_)
    {
        stk.push(post);
    }

    Post* cur;

    while (howMany > 0 && !stk.empty())
    {
        cur = stk.top();
        stk.pop();

        if (!showOnlyPublic || (showOnlyPublic && cur->getIsPublic()))
        {
            output.append(cur->toString() + "\n\n");
            howMany--;
        }
    }

    return output;
}
