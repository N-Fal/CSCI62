#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "network.h"
#include "user.h"
#include <iostream>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::SocialNetworkWindow)
{
    // network setup
    // char users[] = "C:/cygwin64/home/sidek/CSCI62/Homework4_2/Homework4_2/userlist.txt", posts[] = "C:/cygwin64/home/sidek/CSCI62/Homework4_2/Homework4_2/posts.txt";
    char users[] = "userlist.txt", posts[] = "posts.txt";
    net.readUsers(users);
    net.readPosts(posts);

    ui->setupUi(this);

    // login page setup
    loginAttempts = 0;
    ui->loginErrorLabel->hide();
    connect(ui->loginButton, &QPushButton::clicked, this, &SocialNetworkWindow::loginAttempt);

    // profile page setup
    ui->profileTable->setColumnCount(1);
    ui->postsTable->setColumnCount(3);
    ui->postsTable->setColumnWidth(0, 24);
    // ui->postsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->postsTable->setColumnWidth(1, 150);
    ui->postsTable->setColumnWidth(2, 50);

    QStringList postHeaders;
    postHeaders << "likes" << "posts" << "name";
    ui->postsTable->setHorizontalHeaderLabels(postHeaders);


    // post sending setup
    connect(ui->sendButton, &QPushButton::clicked, this, &SocialNetworkWindow::sendPost);

    // ui->postsLabel->setWordWrap(true);
    connect(ui->postsTable, &QTableWidget::cellClicked, this, &SocialNetworkWindow::postClicked);
    connect(ui->profileTable, &QTableWidget::cellClicked, this, &SocialNetworkWindow::friendClicked);
    ui->profileTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->profileButton, &QPushButton::clicked, this, &SocialNetworkWindow::backToProfile);

    // suggested friends setup
    ui->suggestedLabel->setWordWrap(true);
    ui->suggestedTable->setColumnCount(1);
    ui->suggestedTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->suggestedTable, &QTableWidget::cellClicked, this, &SocialNetworkWindow::addSuggestedFriend);

    // friend button setup
    connect(ui->addButton, &QPushButton::clicked, this, &SocialNetworkWindow::addFriendClicked);

    display();
}

void SocialNetworkWindow::displayLogin(bool show)
{
    if (show)
    {
        ui->loginButton->show();
        ui->loginLabel->show();
        ui->loginTextEdit->show();
    }
    else
    {
        ui->loginButton->hide();
        ui->loginErrorLabel->hide();
        ui->loginLabel->hide();
        ui->loginTextEdit->hide();
    }
}

void SocialNetworkWindow::displayProfile(bool show)
{
    if (show)
    {
        ui->profileLabel->show();
        ui->profileTable->show();
        // ui->postsLabel->show();
        ui->postsTable->show();

        ui->sendBox->show();
        ui->sendButton->show();
        ui->sendEdit->show();

        if (otherUser != nullptr && loggedUser != nullptr)
        {
            // if the user is viewing someone else's page
            if (otherUser->getId() != loggedUser->getId())
            {
                ui->profileButton->show();
                ui->addButton->show();
            }
            else // if they're on their own page
            {
                ui->suggestedLabel->show();
                ui->suggestedTable->show();
            }
        }
    }
    else
    {
        ui->profileLabel->hide();
        ui->profileButton->hide();
        // ui->postsLabel->hide();
        ui->postsTable->hide();
        ui->profileTable->hide();
        ui->suggestedLabel->hide();
        ui->suggestedTable->hide();
        ui->addButton->hide();

        ui->sendBox->hide();
        ui->sendButton->hide();
        ui->sendEdit->hide();
    }

    if (otherUser != nullptr)
    {
        populateProfile(otherUser);
    }
}

void SocialNetworkWindow::display()
{
    // hide every component
    displayLogin(false);
    displayProfile(false);

    // if the user is not on the login page
    // std::cout << ((otherUser == nullptr) ? "true" : "false") << std::endl;
    displayLogin(otherUser == nullptr);
    displayProfile(otherUser != nullptr);
}

void SocialNetworkWindow::populateProfile(User* u)
{
    otherUser = u;

    // set the title of the profile
    if (otherUser->getId() == loggedUser->getId())
    {
        ui->profileLabel->setText(QString::fromStdString("My Profile"));
    }
    else
    {
        ui->profileLabel->setText(QString::fromStdString(otherUser->getName() + "'s Profile"));
    }

    // populate the friend table
    ui->profileTable->clearContents();
    // std::cout << "number of friends: " << otherUser->getFriends().size() << std::endl;
    ui->profileTable->setRowCount(otherUser->getFriends().size());

    std::size_t i = 0;
    for (int id : otherUser->getFriends())
    {
        QTableWidgetItem *friendLabel = new QTableWidgetItem(QString::fromStdString(net.getUser(id)->getName()));
        // std::cout << "inserting " << friendLabel->text().toStdString() << " into row " << i << " column " << 0 << std::endl;
        ui->profileTable->setItem(i++, 0, friendLabel);
    }

    // populate the list of posts
    ui->postsTable->clearContents();
    ui->postsTable->setRowCount(otherUser->getPosts().size());

    std::size_t j = 0;
    for (Post* p : otherUser->getPosts())
    {
        QTableWidgetItem *name;
        if (p->getAuthor() == "")
        {
            name = new QTableWidgetItem(QString::fromStdString(net.getUser(p->getOwnerId())->getName()));
        }
        else
        {
            name = new QTableWidgetItem(QString::fromStdString(p->getAuthor()));
        }
        QTableWidgetItem *post = new QTableWidgetItem(QString::fromStdString(p->getMessage()));
        QTableWidgetItem *likes = new QTableWidgetItem(QString::fromStdString(std::to_string(p->getLikes())));

        ui->postsTable->setItem(j, 0, likes);
        ui->postsTable->setItem(j, 1, post);
        ui->postsTable->setItem(j, 2, name);
        ui->postsTable->resizeRowToContents(j++);
    }
    // ui->postsLabel->setText(QString::fromStdString(otherUser->getPostsString(5, loggedUser->getId() != otherUser->getId())));

    // populate the friend list (if the user is on the home page)
    {
        if (otherUser->getId() == loggedUser->getId())
        {
            int score = 0;
            std::vector<int> suggestions = net.suggestFriends(otherUser->getId(), score);

            ui->suggestedLabel->setText(QString::fromStdString("These users have " + std::to_string(score) + ((score == 1) ? " friend " : " friends ") + "in common with you! Click one to add them as a friend."));

            ui->suggestedTable->clearContents();
            ui->suggestedTable->setRowCount(suggestions.size());

            std::size_t i = 0;
            for (int id : suggestions)
            {
                QTableWidgetItem *suggestion = new QTableWidgetItem(QString::fromStdString(net.getUser(id)->getName()));
                ui->suggestedTable->setItem(i++, 0, suggestion);
            }
        }
        else // show the add friend button (if the user is not on their page)
        {
            ui->addButton->setText(QString::fromStdString("Add " + otherUser->getName() + " as a friend"));
        }
    }
}

void SocialNetworkWindow::backToProfile()
{
    otherUser = loggedUser;
    display();
}

void SocialNetworkWindow::loginAttempt()
{
    // get the idea of the name of the user currently in loginTextEdit and reset the contents
    int id = net.getId(ui->loginTextEdit->toPlainText().toStdString());
    ui->loginTextEdit->setPlainText(QString::fromStdString(""));

    // if the user isn't in the id, display an error. Otherwise the login was successful
    if (id == -1)
    {
        ui->loginErrorLabel->show();
        ui->loginErrorLabel->setText(QString::fromStdString("That user could not be found in the network. (Attempts: " + std::to_string(++loginAttempts) + ")"));
    }
    else
    {
        loginAttempts = 0;
        loggedUser = net.getUser(id);
        otherUser = loggedUser;
        // std::cout << "logged in as " << loggedUser->getName() << std::endl;
        display();
    }
}

void SocialNetworkWindow::friendClicked(int row, int column)
{
    // std::cout << "Selected " << row << ", " << column << std::endl;

    otherUser = net.getUser(net.getId(ui->profileTable->item(row, column)->text().toStdString()));
    display();
}

void SocialNetworkWindow::addFriendClicked()
{
    net.addConnection(loggedUser->getName(), otherUser->getName());
    display();
    saveUserFile();
}

void SocialNetworkWindow::addSuggestedFriend(int row, int column)
{
    // std::cout << "Selected " << row << ", " << column << std::endl;
    net.addConnection(loggedUser->getName(), ui->suggestedTable->item(row, column)->text().toStdString());

    display();
    saveUserFile();
}

void SocialNetworkWindow::postClicked(int row, int column)
{
    // if one of the like buttons was clicked
    if (column == 0)
    {
        // std::cout << "Clicked the button for message: " << ui->postsTable->item(row, 1)->text().toStdString() << std::endl;

        for (Post* p : otherUser->getPosts())
        {
            // std::cout << "Checking if the message is " << p->getMessage() << std::endl;
            if(p->getMessage() == ui->postsTable->item(row, 1)->text().toStdString())
            {
                // std::cout << "Entered the if" << std::endl;

                bool alreadyLiked = false;

                for (Post* p2 : loggedUser->getLikes())
                {
                    if (p2 == p)
                    {
                        alreadyLiked = true;
                        break;
                    }
                }

                if (alreadyLiked)
                {
                    p->unlike();
                    loggedUser->unlike(p);
                }
                else
                {
                    p->like();
                    loggedUser->like(p);
                }
            }
        }

        display();
        savePostsFile();
    }

    std::cout << row << " " << column;
}

void SocialNetworkWindow::sendPost()
{
    if (otherUser->getId() == loggedUser->getId())
    {
        otherUser->addPost(new Post(net.totalPosts(), otherUser->getId(), ui->sendEdit->text().toStdString(), 0));
    }
    else
    {
        otherUser->addPost(new IncomingPost(net.totalPosts(), otherUser->getId(), ui->sendEdit->text().toStdString(), 0, ui->sendBox->isChecked(), loggedUser->getName()));
    }

    ui->sendEdit->setText(QString::fromStdString(""));

    display();
    savePostsFile();
}

void SocialNetworkWindow::saveUserFile()
{
    char users[] = "userlist.txt";
    net.writeUsers(users);
}

void SocialNetworkWindow::savePostsFile()
{
    char posts[] = "posts.txt";
    net.writePosts(posts);
}

SocialNetworkWindow::~SocialNetworkWindow()
{
    delete ui;
}

