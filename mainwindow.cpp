#include "contactinfo.h"
#include "mainwindow.h"
#include "phonebookmodel.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PhoneBookModel* pbm = new PhoneBookModel(this);
    ui->lv_contacts->setModel(pbm);
    ui->lv_contacts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lv_contacts->setSelectionMode(QAbstractItemView::ContiguousSelection);

    connect(ui->b_add, &QPushButton::clicked, this, &MainWindow::addContact);
    connect(ui->lv_contacts, QListView::doubleClicked, this, MainWindow::showContactInfo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addContact()
{
    ui->lv_contacts->model()->insertRows(0,1);
}

void MainWindow::showContactInfo(const QModelIndex &index)
{
    QString name = ui->lv_contacts->model()->data(index.sibling(index.row(),PhoneBookModel::Columns::Name)).toString();
    QString lastname = ui->lv_contacts->model()->data(index.sibling(index.row(),PhoneBookModel::Columns::Lastname)).toString();
    QString email = ui->lv_contacts->model()->data(index.sibling(index.row(),PhoneBookModel::Columns::Email)).toString();
    QString number = ui->lv_contacts->model()->data(index.sibling(index.row(),PhoneBookModel::Columns::Number)).toString();
    QString sexString = ui->lv_contacts->model()->data(index.sibling(index.row(),PhoneBookModel::Columns::IsMale)).toString();
    ContactInfo* ci = new ContactInfo(name, lastname, email, number, sexString);
    ci->setAttribute(Qt::WA_DeleteOnClose);
    ci->show();

}
