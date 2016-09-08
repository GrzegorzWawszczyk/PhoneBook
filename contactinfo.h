#ifndef CONTACTINFO_HPP
#define CONTACTINFO_HPP


#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class ContactInfo;
}

class ContactInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ContactInfo(QWidget *parent = 0);
    explicit ContactInfo(QString name, QString lastname, QString email, QString number, QString sexString);
    ~ContactInfo();

private:
    Ui::ContactInfo *ui;
};

#endif // CONTACTINFO_HPP
