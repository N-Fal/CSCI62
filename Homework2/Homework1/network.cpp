#include "network.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

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