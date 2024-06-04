#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H

#include <QMainWindow>
#include "network.h"
#include "user.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SocialNetworkWindow; }
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    // pre: the user is on the login page
    // post: attempts to log into the social network with the name stored in loginTextEdit. Displays an error message if the user is not in the network.
    void loginAttempt();

    // pre: the user is on the profile page
    // post: navigates to the chosen friend's profile.
    void friendClicked(int row, int column);

    // pre the user is one someone else's profile page
    // post: adds that user as a friend
    void addFriendClicked();

    // pre: the user is on their profile page
    // post: adds the selected suggested friend as a friend
    void addSuggestedFriend(int row, int column);

    // pre: the user is on the profile page
    // post: populates the profile widgets with data from the given user.
    void populateProfile(User* u);

    // pre: the user is on the profile page and isn't looking at their own profile
    // post: returns the user to their own profile
    void backToProfile();

    // pre: none
    // post: updates which UI widgets are shown or hidden based on the contents of different fields.
    void display();

    // pre: none
    // post: calles the writeUsers() method of the network
    void saveUserFile();

private:
    Ui::SocialNetworkWindow *ui;
    int loginAttempts;
    Network net;
    User* loggedUser = nullptr, *otherUser = nullptr;

    // pre: none
    // post: helper method for display(). updates the login page.
    void displayLogin(bool show);

    // pre: none
    // post: helper method for display(). updates the profile page.
    void displayProfile(bool show);
};
#endif // SOCIALNETWORKWINDOW_H
