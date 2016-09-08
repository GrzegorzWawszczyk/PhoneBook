#include "contactinfo.h"
#include "ui_contactinfo.h"

ContactInfo::ContactInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactInfo)
{
    ui->setupUi(this);


}

ContactInfo::ContactInfo(QString name, QString lastname, QString email, QString number, QString sexString) :
    ui(new Ui::ContactInfo)
{
    ui->setupUi(this);
    connect(ui->b_ok, &QPushButton::clicked, this, &QWidget::close);
    this->setWindowTitle(QString(name+" "+lastname+"'s detailed data"));
    ui->name_text->setText(name);
    ui->lastname_text->setText(lastname);
    ui->email_text->setText(email);
    ui->s_text->setText(sexString);
    ui->number_text->setText(number);
    QPixmap pix("./person-placeholder.jpg");
    ui->l_picture->setPixmap(pix.scaled(250,250,Qt::KeepAspectRatio));
}

ContactInfo::~ContactInfo()
{
    delete ui;
}
