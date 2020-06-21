#ifndef DATABASELOGIC_H
#define DATABASELOGIC_H

#include <QCoreApplication>
#include<iostream>
#include <QtSql>
#include <QTableView>
#include <QApplication>


class MainWindow;


class Database
{
public:

    Database() = default;

    Database (QString DatabaseName_, QString hostname_, QString username_, QString password_, MainWindow *window_);

    int getUserIdByEmail(QString email);
    int getTicketIdByInfo(QString info);

    bool showAllTables();
    bool showTableDataById(QString table_name, int id = 0);
    bool showOrderedTicketsByUserId(int id);
    bool showBookedTicketsByUserId(int id);
    bool insertData (QString table_name, std::vector<QString> data);
    bool setOrdered(int tiketId, int userId);
    bool setBooked(int tiketId, int userId);
    bool deleteRaw(QString table_name, QString column, QString data);
    bool Close_database();

private:
    QString mDatabaseName,
            mHostname,
            mUsername,
            mPassword;

    QTableView mView;
    QSqlQueryModel mModelRead;
    QSqlTableModel mModelReadWrite;
    QSqlDatabase mDatabase;
    MainWindow *mWindow;
};

#endif // DATABASELOGIC_H
