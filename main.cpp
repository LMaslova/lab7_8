#include <QDebug>
#include <QApplication>
#include <memory>
#include <vector>
#include "mainwindow.h"
#include "gtest/gtest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString usersTable = "users";
    QString ticketsTable = "tickets";

    w.newConnection();

    w.showAllTables();

   w.showTableDataById(ticketsTable);

    ::testing::InitGoogleTest (&argc, argv);
    int returnCode = RUN_ALL_TESTS();

    return a.exec();
}


TEST (Business_Logic, addNewTicketTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.addNewTicket("new ticket"));

    w.Close_database();
    w.close();
}

TEST (Business_Logic, removeTicketTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.deleteTicket("new ticket"));

    w.Close_database();
    w.close();
}

TEST (Business_Logic, addNewUserTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.addNewUser("new user"));

    w.Close_database();
    w.close();
}

TEST (Business_Logic, removeUserTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.deleteUser("new user"));

    w.Close_database();
    w.close();
}

TEST (Repository_logic, Show_tables)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.showAllTables());

    w.Close_database();
    w.close();
}


TEST (Repository_logic, showTableDataById)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.showTableDataById("users"));
    EXPECT_TRUE(w.showTableDataById("tickets"));

    w.Close_database();
    w.close();
}

TEST (Repository_logic, showOrderedTicketsByUserIdTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.database->showOrderedTicketsByUserId(1));

    w.Close_database();
    w.close();
}


TEST (Repository_logic, showBookedTicketsByUserIdTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_TRUE(w.database->showBookedTicketsByUserId(1));

    w.Close_database();
    w.close();
}

TEST (Repository_logic, getTicketIdByInfoTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_EQ(w.database->getTicketIdByInfo("ticket1"), 1);
    EXPECT_EQ(w.database->getTicketIdByInfo("ticket5"), 5);

    w.Close_database();
    w.close();
}

TEST (Repository_logic, getUserIdByEmailTest)
{
    MainWindow w;
    w.newConnection();

    EXPECT_EQ(w.database->getUserIdByEmail("test@gmail.com"), 1);
    EXPECT_EQ(w.database->getUserIdByEmail("test4@mail.ru"), 4);

    w.Close_database();
    w.close();
}
