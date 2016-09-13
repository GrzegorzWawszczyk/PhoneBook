#include "filehandler.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>

const char UNIT_SEPARATOR = static_cast<char>(31);

FileHandler::FileHandler(QObject *parent) : QObject(parent)
{

}

void FileHandler::readFile(QString filename, QVector<PhoneBookModel::Contact> *vector /*PhoneBookModel *pbm*/)
{
    QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            return;
        }

            QTextStream in(&file);

            QString str;

            while (!in.atEnd())
            {
                in >> str;
                if (str == "")
                    continue;
                auto columnString = [&](int column)
                {
                    return str.split(UNIT_SEPARATOR).at(column);
                };
                QString name = columnString(PhoneBookModel::Columns::Name);
                QString lastname = columnString(PhoneBookModel::Columns::Lastname);
                QString email = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::Email);
                QString number = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::Number);
                bool isMale = (str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::IsMale) == "Male");


                vector->append(PhoneBookModel::Contact(name, lastname, email, number, isMale));
            }


            file.close();
}

void FileHandler::saveFile(QString filename, QVector<PhoneBookModel::Contact> const* vector)
{

    QFile file(filename);
        if (!file.open(QIODevice::WriteOnly))
        {
            return;
        }


        QTextStream out(&file);

        for (PhoneBookModel::Contact contact :  *vector)
        {
            out << contact.name << UNIT_SEPARATOR << contact.lastname << UNIT_SEPARATOR << contact.email << UNIT_SEPARATOR
                << contact.number << UNIT_SEPARATOR << (contact.isMale ? "Male" : "Female") << "\n";
        }


        file.close();
}
