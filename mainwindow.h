#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void Add_widget_to_layout(QWidget *object);

    void newConnection();
    bool showAllTables();
    int getUserIdByEmail(QString email);
    int getTicketIdByInfo(QString info);
    bool showTableDataById(QString table_name, int id = 0);
    bool showOrderedTicketsByUserId(int id = 0);
    bool showBookedTicketsByUserId(int id = 0);
    bool setBooked(int tiketId, int userId);
    bool setOrdered(int tiketId, int userId);
    bool insertData (QString table_name, std::vector<QString> data);
    bool deleteRaw(QString table_name, QString column, QString data);
    bool Close_database();


    bool addNewTicket(QString ticketInfo);
    bool deleteTicket(QString ticketInfo);
    bool addNewUser(QString email);
    bool deleteUser(QString email);

private:
    Ui::MainWindow *ui;
public:
    std::unique_ptr<Database> database;
};
#endif // MAINWINDOW_H
