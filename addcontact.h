#ifndef ADDCONTACT_HPP
#define ADDCONTACT_HPP

#include "phonebookmodel.h"

#include <QDialog>
#include <QWidget>

namespace Ui {
class addContact;
}

class AddContact : public QDialog
{
    Q_OBJECT

public:
    explicit AddContact(QWidget *parent = 0, PhoneBookModel *pbm = 0);
    ~AddContact();

signals:
    void add(QString name, QString number);
private:
    Ui::addContact *ui;
};

#endif // ADDCONTACT_HPP
