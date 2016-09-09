#include "addcontact.h"
#include "phonebookmodel.h"
#include "ui_addcontact.h"

#include <QDebug>
#include <QSignalMapper>
#include <QMessageBox>

AddContact::AddContact(QWidget *parent, PhoneBookModel *pbm) :
    QDialog(parent),
    ui(new Ui::addContact)
{
    ui->setupUi(this);
    connect(ui->b_cancel, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->b_add, &QPushButton::clicked, this, [this, pbm]()
    {
//        qDebug()<<pbm->rowCount();
        if (ui->le_name->text().isEmpty() || ui->le_number->text().isEmpty() || ui->le_email->text().isEmpty() || ui->le_lastname->text().isEmpty())
        {
            QMessageBox::warning(this, "Empty contact details", "You must enter contact details");
        }
        else{
            QString name = std::move(ui->le_name->text());
            QString lastname = std::move(ui->le_lastname->text());
            QString email = std::move(ui->le_email->text());
            QString number = std::move(ui->le_number->text());
            bool isMale = std::move(ui->rb_male->isChecked());
            pbm->addContact(name, lastname, email, number, isMale);
            this->close();
        }
    });
}


//AddContact::AddContact(QString name, QString number): ui(new Ui::addContact)
//{
//    ui->setupUi(this);
//    ui->b_add->setText("Edit");
//    ui->le_name->setText(name);
//    ui->le_number->setText(number);
//    QString oldName = name;
//    connect(ui->b_cancel, &QPushButton::clicked, this, &QWidget::close);
//    connect(ui->b_add, &QPushButton::clicked, this, [this,oldName]()
//    {
//        if(ui->le_name->text().isEmpty() || ui->le_number->text().isEmpty())
//        {
//            QMessageBox::warning(this, "Empty contact details", "You must enter contact details");
//        }
//        else{
//                    //item->setText(ui->le_name->text());
//                    emit edit(oldName, ui->le_name->text(), ui->le_number->text());
//                    this->close();
//        }
//    });
//}


AddContact::~AddContact()
{
    delete ui;
}
