#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "phonebookmodel.h"

#include <QObject>

class FileHandler : public QObject
{
    Q_OBJECT
public:
    explicit FileHandler(QObject *parent = 0);
    void readFile(QString filename, QVector<PhoneBookModel::Contact> *vector);
    void saveFile(QString filename, const QVector<PhoneBookModel::Contact> &vector);


public slots:
};

#endif // FILEHANDLER_H
