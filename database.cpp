#include "database.h"
#include "mainwindow.h"

Database::Database(QString databaseName, QString hostname, QString username, QString password, MainWindow *window):
    mDatabaseName(databaseName),mHostname(hostname), mUsername(username), mPassword(password), mWindow(window)
{
    window->Add_widget_to_layout(&mView);

    mDatabase = QSqlDatabase::addDatabase("QMYSQL");
    mDatabase.setDatabaseName(databaseName);
    mDatabase.setHostName(hostname);
    mDatabase.setUserName(username);
    mDatabase.setPassword(password);

    mDatabase.open();
}

bool Database::showAllTables()
{
    if(!mDatabase.open())
    {
        return false;
    }
        foreach (QString str, mDatabase.tables())
        {
            qDebug()<< " table: " + str;
        }
        return true;
}

int Database::getUserIdByEmail(QString email)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "SELECT users.user_id FROM users WHERE users.user_email = '"+ email+ "'";


    mModelRead.setQuery(temp);

    return mModelRead.record(0).value(0).toInt();
}

int Database::getTicketIdByInfo(QString info)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "SELECT tickets.ticket_id FROM tickets WHERE tickets.ticket_info = '"+ info+ "'";


    mModelRead.setQuery(temp);

    return mModelRead.record(0).value(0).toInt();
}

bool Database::showTableDataById (QString table_name, int id)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "SELECT *FROM " + table_name;


    if(id != 0)
    {
        temp += " WHERE " + table_name + ".id = " + QString::number(id);
    }

    mModelRead.setQuery(temp);
    mView.setModel(&mModelRead);

    return true;
}

bool Database::insertData (QString table_name, std::vector<QString> data)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp_string = "INSERT INTO " + table_name + " VALUES (";

    for (int i = 0; i < data.size(); i++)
    {
        temp_string += data[i];
        if(i != data.size() - 1)
        {
            temp_string += ", ";
        }
    }
    temp_string += ")";

    mModelRead.setQuery(temp_string);

    mView.setModel(&mModelRead);

    return true;
}

bool Database::setOrdered(int tiketId, int userId)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "UPDATE tickets SET tickets.ordered_user_id = " + QString::number(userId) + ", tickets.booked_user_id = NULL WHERE tickets.ticket_id = " + QString::number(tiketId);

    mModelRead.setQuery(temp);
    mView.setModel(&mModelRead);

    return true;
}

bool Database::setBooked(int tiketId, int userId)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "UPDATE tickets SET tickets.booked_user_id = " + QString::number(userId) + ", tickets.ordered_user_id = NULL WHERE tickets.ticket_id = " + QString::number(tiketId);

    mModelRead.setQuery(temp);
    mView.setModel(&mModelRead);

    return true;
}

bool Database::showOrderedTicketsByUserId(int id)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "SELECT users.user_email, tickets.ticket_info FROM tickets LEFT JOIN users  ON tickets.ordered_user_id = users.user_id" ;

    if(id != 0)
    {
        temp += " WHERE users.user_id = " + QString::number(id);
    }

    mModelRead.setQuery(temp);
    mView.setModel(&mModelRead);

    return true;
}

bool Database::showBookedTicketsByUserId(int id)
{
    if(!mDatabase.open())
    {
        return false;
    }
    QString temp = "SELECT users.user_email, tickets.ticket_info FROM tickets LEFT JOIN users  ON tickets.booked_user_id = users.user_id" ;

    if(id != 0)
    {
        temp += " WHERE users.user_id = " + QString::number(id);
    }

    mModelRead.setQuery(temp);
    mView.setModel(&mModelRead);

    return true;
}

bool Database::Remove_raw(QString table_name, QString column, QString data)
{
    if(!mDatabase.open())
    {
        return false;
    }
    mModelRead.setQuery("DELETE FROM " + table_name + " WHERE " + column + " = " + "'" + data + "'");
    mView.setModel(&mModelRead);

    return true;
}


bool Database::Close_database()
{
    if(!mDatabase.open())
    {
        return false;
    }
    QSqlDatabase::removeDatabase(mDatabase.connectionName());
    return true;
}
