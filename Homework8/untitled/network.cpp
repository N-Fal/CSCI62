#include "network.h"
#include "user.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

Network::Network() {}

Network::~Network()
{
    for (User* userptr : users_)
    {
        delete userptr;
    }

    users_.clear();
}

void Network::addUser(User* userPtr)
{
    users_.push_back(userPtr);
}

int Network::addConnection(std::string s1, std::string s2)
{
    int id1 = getId(s1), id2 = getId(s2);

    if (id1 == -1 || id2 == -1)
        return -1;

    getUser(getId(s1))->addFriend(id2);
    getUser(getId(s2))->addFriend(id1);

    return 0;
}

int Network::deleteConnection(std::string s1, std::string s2)
{
    int id1 = getId(s1), id2 = getId(s2);

    if (id1 == -1 || id2 == -1)
        return -1;

    getUser(getId(s1))->deleteFriend(id2);
    getUser(getId(s2))->deleteFriend(id1);

    return 0;
}

int Network::getId(std::string name)
{
    for (auto i = users_.begin(); i != users_.end(); i++)
    {
        if ((*i)->getName().compare(name) == 0)
        {
            return (*i)->getId();
        }
    }

    return -1;
}

int Network::readUsers(char* fname)
{
    std::string fLine;
    std::ifstream fileReader(fname);

    if (!fileReader.is_open())
        return -1;

    // stores the read values before allocating space for a new user
    int id;
    std::string name;
    int year;
    int zip;
    int friendID;

    std::stringstream ss("");

    // get rid of the list size at the start of the file
    std::getline(fileReader, fLine);

    // read the next line of the text file into fLine until all lines have been read
    while (std::getline(fileReader, fLine))
    {
        // read the id
        ss.str(fLine);
        ss >> id;
        ss.clear();

        // read the name
        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();
        std::getline(ss, name);
        ss.clear();

        // read the year
        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();
        ss >> year;
        ss.clear();

        // read the zip code
        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();
        ss >> zip;
        ss.clear();

        // read the friend IDs
        std::set<int> friends;

        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();

        while (ss >> friendID)
        {
            friends.insert(friendID);
        }
        ss.clear();

        addUser(new User(id, name, year, zip, friends));
    }

    fileReader.close();
    return 0;
}

int Network::writeUsers(char* fname)
{
    std::ofstream fileWriter(fname);

    if (!fileWriter.is_open())
    {
        return -1;
    }

    // print the size of the network at the beginning
    fileWriter << numUsers() << std::endl;

    for (User* u : users_)
    {
        fileWriter << u->getId() << std::endl;
        fileWriter << '\t' << u->getName() << std::endl;
        fileWriter << '\t' << u->getYear() << std::endl;
        fileWriter << '\t' << u->getZip() << std::endl;
        fileWriter << '\t';
        
        for (int i : u->getFriends())
        {
            fileWriter << i << ' ';
        }

        fileWriter << std::endl;
    }

    fileWriter.close();
    return 0;
}

int Network::numUsers()
{
    return users_.size();
}

User* Network::getUser(int id)
{
    for (auto i = users_.begin(); i != users_.end(); i++)
    {
        if ((*i)->getId() == id)
        {
            return *i;
        }
    }
    return nullptr;
}

std::vector<int> Network::bfs(int origin)
{
    assert(origin < numUsers());
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), 0);
    std::vector<int> prev(numUsers(), -1);

    // breadth-first search  
    visited[origin] = true;
    // prev[from] = -1;
    q.push(origin);

    while(q.size() > 0)
    {
        int cur = q.front();
        q.pop();

        for (int id : getUser(cur)->getFriends())
        {
            if (!visited[id])
            {
                prev[id] = cur;
                visited[id] = true;
                q.push(id);
            }
        }
    }
    // end breadth-first search
    return prev;
}

std::vector<int> Network::shortestPath(int from, int to)
{
    assert(from < numUsers() && to < numUsers());
    if (from == to)
    {
        std::vector<int> same;
        same.push_back(from);
        return same;
    }

    std::vector<int> prev = bfs(from);
    std::vector<int> path;
    for(int i = to; i != -1; i = prev[i])
    {
        path.push_back(i);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance)
{
    assert(from < numUsers());
    std::vector<int> prev = bfs(from);
    std::vector<int> path;
    int cur = 0;
    for (int id : prev)
    {
        path.push_back(cur++);
        for (int i = id; i != -1; i = prev[i])
        {
            path.push_back(i);
        }

        if (path.size() != distance + 1)
        {
            path.clear();
        }
        else
        {
            to = path.front();
            std::reverse(path.begin(), path.end());
            return path;
        }
    }
    // there was no valid path of length 'distance'
    to = -1;
    return path;
}

std::vector<int> Network::suggestFriends(int who, int& score)
{
    assert(who < numUsers());
    std::vector<int> prev = bfs(who); // breadth-first search to determine relational distances
    std::vector<int> reccomendations; // output
    score = -1;

    for (User* u : users_)
    {
        int id = u->getId();

        // find distance between each user and 'who'
        int distance = 0;
        for(int i = id; i != -1; i = prev[i])
            distance++;

        // if this user is a friend of a friend of 'who' (a strong candidate)
        if (distance == 3)
        {
            int currentScore = 0;
            // check if each item in 'who's friend list is in this user's friend list:
            for (int i : getUser(who)->getFriends())
            {
                if (getUser(id)->getFriends().find(i) != getUser(id)->getFriends().end())
                    currentScore++;
            }

            if (currentScore >= score)
            {
                // delete the list if it's the new greatest
                if (currentScore > score)
                    reccomendations.clear();
                
                // add onto the list if it's the same greatest
                score = currentScore;
                reccomendations.push_back(id);
            }
        }
    }

    return reccomendations;
}

std::vector<std::vector<int> > Network::groups()
{
    std::vector<std::vector<int> > components;
    std::vector<bool> visited(numUsers(), 0);

    // if a user isn't already part of an added component, perform a depth first search and add every connected user to a new component
    for(User* u : users_)
    {
        int id = u->getId();
        if (!visited[id])
        {
            std::vector<int> component;
            std::stack<int> s;

            visited[id] = true;
            component.push_back(id);
            s.push(id);

            while (s.size() > 0)
            {
                int cur = s.top();
                s.pop();

                for (int i : getUser(cur)->getFriends())
                {
                    if (!visited[i])
                    {
                        visited[i] = true;
                        s.push(i);
                        component.push_back(i);
                    }
                }
            }
            components.push_back(component);
        }
    }

    return components;
}

int Network::totalPosts()
{
    int totalPosts = 0;

    for (User* user : users_)
    {
        totalPosts += user->getPosts().size();
    }

    return totalPosts;
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic)
{
    User* u = getUser(ownerId);

    int messageId = totalPosts();
    std::cout << "there are " << messageId << "posts in the entire system." << std::endl;


    if (isIncoming)
    {
        u->addPost(new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName));
    }
    else
    {
        u->addPost(new Post(messageId, ownerId, message, likes));
    }
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic)
{
    return getUser(ownerId)->getPostsString(howMany, showOnlyPublic);
}

int Network::readPosts(char* fname)
{
    std::string fLine;
    std::ifstream fileReader(fname);

    if (!fileReader.is_open())
        return -1;

    std::string message, author;
    int postId, ownerId, likes;
    bool isPublic;

    std::stringstream ss("");

    // get rid of the list size at the start of the file
    std::getline(fileReader, fLine);

    while(std::getline(fileReader, fLine))
    {
        //read the id
        ss.str(fLine);
        ss >> postId;
        ss.clear();

        // read the message
        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();
        std::getline(ss, message);
        ss.clear();

        // read the ownerId
        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();
        ss >> ownerId;
        ss.clear();

        // read the likes
        std::getline(fileReader, fLine);
        ss.str(fLine);
        ss.get();
        ss >> likes;
        ss.clear();

        // read public/private
        std::getline(fileReader, fLine);
        ss.str(fLine);

        if (ss.str() == "\tpublic")
        {
            isPublic = true;
        }
        else if (ss.str() == "\tprivate")
        {
            isPublic = false;
        }
        ss.clear();

        // read author
        std::getline(fileReader, fLine);
        ss.str(fLine);
        if (ss.str() != (""))
        {
            ss.get();
            std::getline(ss, author);
        }
        ss.clear();

        if (author == "")
        {
            getUser(ownerId)->addPost(new Post(postId, ownerId, message, likes));
        }
        else
        {
            getUser(ownerId)->addPost(new IncomingPost(postId, ownerId, message, likes, isPublic, author));
        }
    }

    fileReader.close();
    return 0;
}

int Network::writePosts(char* fname)
{
    std::ofstream fileWriter(fname);

    if (!fileWriter.is_open())
    {
        return -1;
    }

    std::vector<Post*> all;
    for (User* u : users_)
    {
        for (Post* p : u->getPosts())
        {
            all.push_back(p);
        }
    }
    std::sort(all.begin(), all.end(), [](const Post* a, const Post* b) {
        return a->getMessageId() < b->getMessageId();
    });

    // single number representing how many posts are in the file
    fileWriter << all.size() << std::endl;

    for (Post* p : all)
    {
        // std::cout << p->getMessageId() << ": " << p->toString();

        fileWriter << p->getMessageId() << std::endl;
        fileWriter << '\t' << p->getMessage() << std::endl;
        fileWriter << '\t' << p->getOwnerId() << std::endl;
        fileWriter << '\t' << p->getLikes() << std::endl;
        
        // if this post is a Post
        if (p->getAuthor() == "")
        {
            fileWriter << '\t' << std::endl << '\t' << std::endl;
        }
        else // if this post is an IncomingPost
        {
            fileWriter << '\t' << (p->getIsPublic() ? "public" : "private") << std::endl;
            fileWriter << '\t' << p->getAuthor() << std::endl;
        }
    }

    return 0;
}
