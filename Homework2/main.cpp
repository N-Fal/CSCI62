#include "user.h"
#include <iostream>
#include <set>

using namespace std;

void printUsers(User * users)
{
    for (int i = 0; i < 2; i++)
    {
        cout << "id: " << users[i].getId() << endl;
        cout << "name: " << users[i].getName() << endl;
        cout << "year: " << users[i].getYear() << endl;
        cout << "zip: " << users[i].getZip() << endl;


        cout << "friends: ";
        std::set<int> userFriends = users[i].getFriends();
        for (auto j = userFriends.begin(); j != userFriends.end(); j++)
        {
            cout << *j << " ";
        }
        cout << endl << endl;
    }
}


int main()
{

    // should compile but would break if anything is called
    User emptyUser;


    std::set<int> nolanList;
    User nolan(0, "Nolan Fallin", 2005, 95052, nolanList);

    std::set<int> seanList;
    User sean(1, "Sean Talley", 2005, 94501, seanList);

    std::set<int> evanList;
    User evan(2, "Evan Yip", 2005, 94501, evanList);

    nolan.addFriend(sean.getId());
    sean.addFriend(nolan.getId());
    nolan.addFriend(evan.getId());
    cout << "sean and nolan are square waves now! :>" << endl << endl;

    User users[] {nolan, sean, evan};

    printUsers(users);


    // set<int> list = nolan.getFriends();
    // for (auto i = list.begin(); i != list.end(); i++)
    // {
    //     cout << *i << " ";
    // }
    // cout << endl;

    printUsers(users);

    return 0;
}