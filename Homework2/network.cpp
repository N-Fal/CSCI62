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
    // breadth-first search  
    assert(origin < numUsers());
    std::queue<int> q;
    std::vector<bool> visited(numUsers(), 0);
    std::vector<int> prev(numUsers(), -1);

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
    int count = 0;
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


/*
    // depth-first search  
    assert(origin < numUsers());
    std::stack<int> s;
    std::vector<bool> visited(numUsers(), 0);
    std::vector<int> prev(numUsers(), -1);

    visited[origin] = true;
    // prev[from] = -1;
    s.push(origin);

    while(s.size() > 0)
    {
        int cur = s.top();
        s.pop();

        for (int i : getUser(cur)->getFriends())
        {
            if (!visited[i])
            {
                prev[i] = cur;
                visited[i] = true;
                s.push(i);
            }
        }
    }
    // end depth-first search
    return prev;
*/

/*
    // start by looping through friends of friends:

    for (int friends : getUser(who)->getFriends())
    {
        for (int friendsOfFriends : getUser(friends)->getFriends())
        {
            // count how many friends in common this user has with 'who':
            int currentScore = 0;

            // check if each item in 'who's friend list is in this user's friend list:
            for (int i : getUser(who)->getFriends())
            {
                if (getUser(friendsOfFriends)->getFriends().find(i) != getUser(friendsOfFriends)->getFriends().end())
                    currentScore++;
            }

            // if this score is greater than the previous greatest score, and who and this user aren't already friends AND this user is not 'who'
            if (friendsOfFriends != who && currentScore >= score && getUser(who)->getFriends().find(friendsOfFriends) == getUser(who)->getFriends().end())
            {
                // delete the list if it's the new greatest
                if (currentScore > score)
                    reccomendations.clear();
                
                // add onto the list if it's the same greatest
                score = currentScore;
                reccomendations.push_back(friendsOfFriends);
            }
        }
    }
*/

/*
// iterate through all friends of friends
    for (int id1 : getUser(who)->getFriends())
    {
        for (int id2 : getUser(id1)->getFriends())
        {
            int curScore = 0;
            for (int id3 : getUser(id1)->getFriends())
            {
                // if a friend of 'who' (id3) is shared with the current friend of friend (id2):
                if (getUser(id2)->getFriends().find(id3) != getUser(id2)->getFriends().end())
                {
                    score++;
                }
            }

            // return (friends_.find(id) != friends_.end());

            if (curScore >= score && getUser(who)->getFriends().find(id2) == getUser(who)->getFriends().end())
            {
                if (curScore > score)
                    reccomendations.clear();
                
                score = curScore;
                reccomendations.push_back(id2);
            }
            // get the score
            // if score is the greatest score so far AND user is not already a friend of who
            //  add to rec vector
            // if score is less than greatest score so far
            // skip
            // if score is greater than greatest score so far
            // clear rec vector -> add code
*/