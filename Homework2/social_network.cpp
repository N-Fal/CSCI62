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
    cout << "(7+) - exit the program" << endl;
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

        if (input <= 0 || input >= 7)
        {
            cout << "exiting program" << endl;
            return 0;
        }

        cout << "Selected option " << input << endl;
        string first1, last1, first2, last2;
        char* file;
        int year, zip;
        
        switch (input)
        {
            case 1: // add a user to the network
                cin >> first1 >> last1 >> year >> zip;
                network.addUser(new User(network.numUsers(), (first1 + " " + last1), year, zip, set<int> {}));
                break;

            case 2: // create a friend connection between two users
                cin >> first1 >> last1 >> first2 >> last2;
                if (network.addConnection((first1 + " " + last1), (first2 + " " + last2)) == -1)
                {
                    cout << "at least one entered user does not exist in the network" << endl;
                }
                break;

            case 3: // delete a friend connection between two users
                cin >> first1 >> last1 >> first2 >> last2;
                if (network.deleteConnection((first1 + " " + last1), (first2 + " " + last2)) == -1)
                {
                    cout << "at least one entered user does not exist in the network" << endl;
                }
                break;

            case 4: // print all users
                for (int i = 0; i < network.numUsers(); i++)
                {
                    cout << i << " " << network.getUser(i)->getName() << endl;
                }
                break;

            case 5: // print all friends of a user
                cin >> first1 >> last1;
                {
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
                }
                break;

            case 6: // save all user data to a file
                cin >> file;
                if (network.writeUsers(file) == -1)
                {
                    cout << "the file could not be written to" << endl;;
                }
                break;

            default:
                cout << "something went really wrong if you're seeing this message" << endl;
                return 3;
        }

        cout << endl;
    }

    return 0;
}