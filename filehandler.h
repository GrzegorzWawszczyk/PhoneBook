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

signals:
    fileRead();

public slots:
};

#endif // FILEHANDLER_H
