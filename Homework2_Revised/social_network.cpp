#include <iostream>
#include "network.h"

using namespace std;

void printMenu()
{
    cout << "Enter an integer and the requested parameters to select an option (all names should be entered as 'first last'):" << endl;
    cout << "(1 'name' 'birth year' 'zip code') - Add a user to this network" << endl;
    cout << "(2 'name 1' 'name 2') - Add a friend connection between two users" << endl;
    cout << "(3 'name 1' 'name 2') - Delete a friend connection between two users" << endl;
    cout << "(4) - print all users in the network" << endl;
    cout << "(5 'name') - print all friends of a user" << endl;
    cout << "(6 'file.txt') - save all user data to a file" << endl;
    cout << "(7 'name 1' 'name 2' - show the shortest path of friend connections between two users" << endl;
    cout << "(8 'name 1' 'distance') - show a path of friend connections to a user of the given relational distance" << endl;
    cout << "(9 'name 1') - print all suggested friends for a user" << endl;
    cout << "(10) prints every connected component of the social network" << endl;
    cout << "(11+) - exit the program" << endl;
    cout << "> ";
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "Please enter a file name as an argument to initialize the network.";
        return 1;
    }

    char* inputFile = argv[1];

    cout << "loading " << inputFile << " ..." << endl;

    Network network;

    if (network.readUsers(inputFile) == -1)
    {
        cout << "The file " << inputFile << " could not be found in the directory. Please make sure you entered the name correctly and try again";
        return 2;
    }
    
    cout << inputFile << " is loaded into the network." << endl << endl;

    while (true)
    {
        printMenu();

        int input = 0;
        cin >> input;
        cout << endl;

        if (input <= 0 || input > 10)
        {
            cout << "exiting program" << endl;
            return 0;
        }

        cout << "Selected option " << input << endl;
        string first1, last1, first2, last2;
        char* file;
        int year, zip, dist;
        
        switch (input)
        {
            case 1: // add a user to the network
            {
                cin >> first1 >> last1 >> year >> zip;
                network.addUser(new User(network.numUsers(), (first1 + " " + last1), year, zip, set<int> {}));
                break;
            }
            case 2: // create a friend connection between two users
            {
                cin >> first1 >> last1 >> first2 >> last2;
                if (network.addConnection((first1 + " " + last1), (first2 + " " + last2)) == -1)
                {
                    cout << "at least one entered user does not exist in the network" << endl;
                }
                break;
            }
            case 3: // delete a friend connection between two users
            {
                cin >> first1 >> last1 >> first2 >> last2;
                if (network.deleteConnection((first1 + " " + last1), (first2 + " " + last2)) == -1)
                {
                    cout << "at least one entered user does not exist in the network" << endl;
                }
                break;
            }
            case 4: // print all users
            {
                for (int i = 0; i < network.numUsers(); i++)
                {
                    cout << i << " " << network.getUser(i)->getName() << endl;
                }
                break;
            }
            case 5: // print all friends of a user
            {
                cin >> first1 >> last1;
                int id = network.getId(first1 + " " + last1);
                if (id == -1)
                {
                    cout << "the user does not exist in the network" << endl;
                }
                else
                {
                    for(int friends : network.getUser(id)->getFriends())
                    {
                        cout << friends << " " << network.getUser(friends)->getName() << endl;
                    }
                }
                break;
            }
            case 6: // save all user data to a file
            {
                cin >> file;
                if (network.writeUsers(file) == -1)
                {
                    cout << "the file could not be written to" << endl;;
                }
                break;
            }
            case 7: // print the shortest friend path between two users
            {
                cin >> first1 >> last1 >> first2 >> last2;
                int id1 = network.getId(first1 + " " + last1);
                int id2 = network.getId(first2 + " " + last2);

                if (id1 == -1 || id2 == -1)
                {
                    cout << "At least one user does not exist in the network." << endl;
                }
                else
                {
                    vector<int> path = network.shortestPath(id1, id2);

                    cout << "Distance: " << (path.size() - 1) << endl;
                    for (int n : path)
                    {
                        if (network.getUser(n)->getName().compare(network.getUser(id1)->getName()) != 0)
                            cout << " -> ";

                        cout << network.getUser(n)->getName();
                    }
                    cout << endl;
                }
                break;
            }
            case 8: // print a path to a user at the given distance
            {
                cin >> first1 >> last1 >> dist;
                int id = network.getId(first1 + " " + last1);
                if (id == -1)
                {
                    cout << "User does not exist in the network" << endl << endl;
                    break;
                }
                int end = -1;
                std::vector<int> path = network.distanceUser(id, end, dist);

                if (end == -1)
                {
                    cout << "No path of length " << dist << " found." << endl;
                }
                else
                {
                    cout << first1 << " " << last1 << ": ";
                    for (int n : path)
                    {
                        if (network.getUser(n)->getName().compare(network.getUser(id)->getName()) != 0)
                            cout << " -> ";

                        cout << network.getUser(n)->getName();
                    }
                    cout << endl;
                }
                break;
            }
            case 9: // print all suggested friends for a user
            {
                cin >> first1 >> last1;

                int score;
                int id = network.getId(first1 + " " + last1);
                if (id == -1)
                {
                    cout << "User does not exist in the network" << endl << endl;
                    break;
                }
                vector<int> suggestions = network.suggestFriends(id, score);

                switch(suggestions.size())
                {
                    case 0:
                        cout << "None" << endl;
                        break;
                    case 1:
                        cout << "The suggested friend is:" << endl;
                        break;
                    default:
                        cout << "The suggested friends are:" << endl;
                        break;
                }

                for (int i : suggestions)
                {
                    cout << network.getUser(i)->getName() << ": " << score << endl;
                }
                break;
            }
            case 10: // prints every connected component of the social network
            {
                vector<vector<int> > components = network.groups();
                int setNum = 1;
                for (vector<int> component : components)
                {
                    cout << "Set " << setNum++ << " => ";
                    for (int i : component)
                    {
                        cout << network.getUser(i)->getName() << ", ";
                    }
                    cout << endl;
                }
                break;
            }
            default:
                cout << endl << "You forgot a break statement." << endl;
                return 3;
        }
        cout << endl;
    }
    return 0;
}