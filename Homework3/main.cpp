#include "user.h"
#include "network.h"
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char* argv[])
{
    

    cout << "TEST EXECUTABLE" << endl;

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
        cout << "type 0 than the params" << endl << "> ";
        string first1, last1;
        int input, dist;

        cin >> input;

        if (input != 0)
        {
            cout << "exiting";
            break;
        }
        else
        {
           vector<vector<int> > components = network.groups();
           int setNum = 1;
           for (vector<int> component : components)
           {
                cout << "Set " << setNum++ << "IS SIZE " << component.size() << " => ";
                for (int i : component)
                {
                    cout << network.getUser(i)->getName() << ", ";
                }
                cout << endl;
           }
        }
    }

    return 0;
}