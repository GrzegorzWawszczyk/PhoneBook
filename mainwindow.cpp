#include "contactinfo.h"
#include "mainwindow.h"
#include "phonebookmodel.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>

const int UNIT_SEPARATOR_ASCII_CODE = 31;

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
    connect(ui->a_open, &QAction::triggered, this, &MainWindow::openFile);
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

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this);

    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
//        this->removeAll();
        QTextStream in(&file);

        QString fileData  = in.readAll();
        QStringList contactList = fileData.split("\n", QString::SkipEmptyParts);
        for(QString str : contactList)
        {
            QString name = str.split(static_cast<char>(UNIT_SEPARATOR_ASCII_CODE)).at(PhoneBookModel::Columns::Name);
            QString lastname = str.split(static_cast<char>(UNIT_SEPARATOR_ASCII_CODE)).at(PhoneBookModel::Columns::Lastname);
            QString email = str.split(static_cast<char>(UNIT_SEPARATOR_ASCII_CODE)).at(PhoneBookModel::Columns::Email);
            QString number = str.split(static_cast<char>(UNIT_SEPARATOR_ASCII_CODE)).at(PhoneBookModel::Columns::Number);
            bool isMale = (str.split(static_cast<char>(UNIT_SEPARATOR_ASCII_CODE)).at(PhoneBookModel::Columns::IsMale) == "Male");

//            qDebug()<<name<<" "<<lastname<<" "<<email<<" "<<number<<" "<<isMale;

            auto model = ui->lv_contacts->model();
            int row = model->rowCount();
            model->insertRows(row,1); // inserting one row
            model->setData(model->index(row,PhoneBookModel::Columns::Name), name);
            model->setData(model->index(row,PhoneBookModel::Columns::Lastname), lastname);
            model->setData(model->index(row,PhoneBookModel::Columns::Email), email);
            model->setData(model->index(row,PhoneBookModel::Columns::Number), number);
            model->setData(model->index(row,PhoneBookModel::Columns::IsMale), isMale);


//            ui->list_contacts->addItem(str.split(static_cast<char>(UNIT_SEPARATOR_ASCII_CODE)).at(0));
        }
        file.close();
    }
}
