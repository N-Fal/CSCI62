/********************************************************************************
** Form generated from reading UI file 'socialnetworkwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOCIALNETWORKWINDOW_H
#define UI_SOCIALNETWORKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SocialNetworkWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *loginTextEdit;
    QLabel *loginLabel;
    QPushButton *loginButton;
    QLabel *loginErrorLabel;
    QLabel *profileLabel;
    QTableWidget *profileTable;
    QLabel *postsLabel;
    QPushButton *profileButton;
    QTableWidget *suggestedTable;
    QLabel *suggestedLabel;
    QPushButton *addButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SocialNetworkWindow)
    {
        if (SocialNetworkWindow->objectName().isEmpty())
            SocialNetworkWindow->setObjectName("SocialNetworkWindow");
        SocialNetworkWindow->resize(800, 600);
        centralwidget = new QWidget(SocialNetworkWindow);
        centralwidget->setObjectName("centralwidget");
        loginTextEdit = new QTextEdit(centralwidget);
        loginTextEdit->setObjectName("loginTextEdit");
        loginTextEdit->setGeometry(QRect(290, 290, 171, 31));
        loginLabel = new QLabel(centralwidget);
        loginLabel->setObjectName("loginLabel");
        loginLabel->setGeometry(QRect(290, 330, 91, 20));
        loginButton = new QPushButton(centralwidget);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(390, 330, 71, 24));
        loginErrorLabel = new QLabel(centralwidget);
        loginErrorLabel->setObjectName("loginErrorLabel");
        loginErrorLabel->setGeometry(QRect(210, 360, 341, 21));
        profileLabel = new QLabel(centralwidget);
        profileLabel->setObjectName("profileLabel");
        profileLabel->setGeometry(QRect(110, 60, 281, 21));
        profileTable = new QTableWidget(centralwidget);
        profileTable->setObjectName("profileTable");
        profileTable->setGeometry(QRect(110, 80, 161, 401));
        postsLabel = new QLabel(centralwidget);
        postsLabel->setObjectName("postsLabel");
        postsLabel->setGeometry(QRect(298, 86, 221, 391));
        profileButton = new QPushButton(centralwidget);
        profileButton->setObjectName("profileButton");
        profileButton->setGeometry(QRect(120, 490, 121, 24));
        suggestedTable = new QTableWidget(centralwidget);
        suggestedTable->setObjectName("suggestedTable");
        suggestedTable->setGeometry(QRect(540, 80, 161, 401));
        suggestedLabel = new QLabel(centralwidget);
        suggestedLabel->setObjectName("suggestedLabel");
        suggestedLabel->setGeometry(QRect(540, 30, 181, 51));
        addButton = new QPushButton(centralwidget);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(289, 490, 221, 24));
        SocialNetworkWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SocialNetworkWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SocialNetworkWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(SocialNetworkWindow);
        statusbar->setObjectName("statusbar");
        SocialNetworkWindow->setStatusBar(statusbar);

        retranslateUi(SocialNetworkWindow);

        QMetaObject::connectSlotsByName(SocialNetworkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SocialNetworkWindow)
    {
        SocialNetworkWindow->setWindowTitle(QCoreApplication::translate("SocialNetworkWindow", "SocialNetworkWindow", nullptr));
        loginLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Enter your name.", nullptr));
        loginButton->setText(QCoreApplication::translate("SocialNetworkWindow", "login", nullptr));
        loginErrorLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "That user could not be found in the network.", nullptr));
        profileLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "My Profile", nullptr));
        postsLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "TextLabel", nullptr));
        profileButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Back to Profile", nullptr));
        suggestedLabel->setText(QCoreApplication::translate("SocialNetworkWindow", "Suggested Friends:", nullptr));
        addButton->setText(QCoreApplication::translate("SocialNetworkWindow", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SocialNetworkWindow: public Ui_SocialNetworkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOCIALNETWORKWINDOW_H
