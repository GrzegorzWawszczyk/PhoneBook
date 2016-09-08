#include "phonebookmodel.h"

#include <QDebug>

PhoneBookModel::PhoneBookModel(QObject *parent)
    : QAbstractListModel(parent)
{
    contacts.append(Contact("Jan", "Kowalski", "jk@abc.com", "1234", true));
    contacts.append(Contact("Piotr", "Nowak", "pn@abc.com", "9876", true));
    contacts.append(Contact("Janina", "Kowalska", "jka@abc.com", "4321", false));
    contacts.append(Contact("Stefan", "Polak", "sp@abc.com", "6789", true));
}

int PhoneBookModel::rowCount(const QModelIndex& /*parent*/) const
{
    return contacts.size();
}

int PhoneBookModel::columnCount(const QModelIndex& /*parent*/) const
{
    return Columns::Count;
}

QVariant PhoneBookModel::data(const QModelIndex &index, int role) const
{
    //qDebug() <<index <<" "<< role;

    if(!index.isValid() || index.row() >= contacts.size() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    const PhoneBookModel::Contact& contact = contacts[index.row()];
    switch(index.column())
    {
    case Columns::Name:
        return contact.name;

    case Columns::Lastname:
        return contact.lastname;

    case Columns::Email:
        return contact.email;

    case Columns::Number:
        return contact.number;

    case Columns::IsMale:
        if(contact.isMale)
            return "Male";
       else
            return "Female";

    }

    return QVariant();
}

QVariant PhoneBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case Columns::Name:
            return "Name";
        case Columns::Lastname:
            return "Lastname";
        case Columns::Email:
            return "E-mail";
        case Columns::Number:
            return "Number";
        case Columns::IsMale:
            return "Sex";

        }
    }
    return QVariant();
}

bool PhoneBookModel::insertRows(int row, int count, const QModelIndex &/*parent*/)
{
//    qDebug() << row << " " << count;

    beginInsertRows(QModelIndex(), row, row+count-1);
    contacts.insert(contacts.begin()+row, Contact("Imie", "Nazwisko", "email", "1234", true));
    endInsertRows();

    return true;
}

bool PhoneBookModel::removeRows(int row, int count, const QModelIndex &/*parent*/)
{
    beginRemoveRows(QModelIndex(), row, row+count-1);
    contacts.erase(contacts.begin()+row, contacts.begin()+count);
    endRemoveRows();

    return true;
}

PhoneBookModel::Contact::Contact(QString name, QString lastname, QString email, QString number, bool isMale)
    : name(std::move(name)),
      lastname(std::move(lastname)),
      email(std::move(email)),
      number(std::move(number)),
      isMale(std::move(isMale))
{

}
