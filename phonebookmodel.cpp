#include "phonebookmodel.h"

#include <QDebug>

PhoneBookModel::PhoneBookModel(QObject *parent)
    : QAbstractListModel(parent)
{
//    contacts.append(Contact("Jan", "Kowalski", "jk@abc.com", "1234", true));
//    contacts.append(Contact("Piotr", "Nowak", "pn@abc.com", "9876", true));
//    contacts.append(Contact("Janina", "Kowalska", "jka@abc.com", "4321", false));
//    contacts.append(Contact("Stefan", "Polak", "sp@abc.com", "6789", true));

}

PhoneBookModel::~PhoneBookModel()
{

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

    if (!index.isValid() || index.row() >= contacts.size() || role != Qt::DisplayRole )
    {
        return QVariant();
    }

    const PhoneBookModel::Contact& contact = contacts[index.row()];
    switch (index.column())
    {
    case Columns::Fullname:
        return contact.name + " " + contact.lastname;

    case Columns::Name:
        return contact.name;

    case Columns::Lastname:
        return contact.lastname;

    case Columns::Email:
        return contact.email;

    case Columns::Number:
        return contact.number;

    case Columns::IsMale:
        if (contact.isMale)
            return "Male";
       else
            return "Female";

    }

    return QVariant();
}

QVariant PhoneBookModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
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
    contacts.insert(contacts.begin() + row, Contact());
    endInsertRows();
//    qDebug()<<"Row inserted, new size - "<<contacts.size();
    return true;
}

bool PhoneBookModel::removeRows(int row, int count, const QModelIndex &/*parent*/)
{
    beginRemoveRows(QModelIndex(), row, row + count-1);
    contacts.erase(contacts.begin() + row, contacts.begin()+row+count);
    endRemoveRows();

    return true;
}

bool PhoneBookModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
//    qDebug()<<"setData "<<index;
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    int row = index.row();

    Contact tmp_cont = std::move(contacts.at(row));


    switch (index.column()) {
    case Columns::Name:
        tmp_cont.name = value.toString();
        break;
    case Columns::Lastname:
        tmp_cont.lastname = value.toString();
        break;
    case Columns::Email:
        tmp_cont.email = value.toString();
        break;
    case Columns::Number:
        tmp_cont.number = value.toString();
        break;
    case Columns::IsMale:
        tmp_cont.isMale = value.toBool();
        break;
    default:
        return false;
    }

    contacts.replace(row, tmp_cont);
//    qDebug()<<contacts.size();
    emit dataChanged(index ,index);
    return true;
}

void PhoneBookModel::addContact(QString name, QString lastname, QString email, QString number, bool isMale)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    contacts.insert(contacts.begin() + rowCount(), Contact(std::move(name), std::move(lastname), std::move(email), std::move(number), std::move(isMale)));
    endInsertRows();
}

PhoneBookModel::Contact::Contact(QString name, QString lastname, QString email, QString number, bool isMale)
    : name(std::move(name)),
      lastname(std::move(lastname)),
      email(std::move(email)),
      number(std::move(number)),
      isMale(std::move(isMale))
{

}
