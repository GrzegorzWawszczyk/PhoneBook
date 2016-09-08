#include "contactinfo.h"
#include "mainwindow.h"
#include "phonebookmodel.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>

const char UNIT_SEPARATOR = static_cast<char>(31);

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
    connect(ui->b_remove, &QPushButton::clicked, this, &MainWindow::removeContacts);
    connect(ui->lv_contacts, QListView::doubleClicked, this, MainWindow::showContactInfo);
    connect(ui->a_open, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->a_save, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->a_removeAll, &QAction::triggered, this, &MainWindow::removeAll);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addContact()
{
    ui->lv_contacts->model()->insertRows(0,1);
}

void MainWindow::removeContacts()
{
    auto rows = ui->lv_contacts->selectionModel()->selectedRows(0);

    if(rows.isEmpty())
    {
        return;
    }

    qDebug()<<rows.first().row()<<" "<<rows.size();
    std::sort(rows.begin(), rows.end());
    qDebug()<<rows.first().row()<<" "<<rows.size();
    ui->lv_contacts->model()->removeRows(rows.first().row(), rows.size());
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
            QString name = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::Name);
            QString lastname = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::Lastname);
            QString email = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::Email);
            QString number = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::Number);
            QString isMale = str.split(UNIT_SEPARATOR).at(PhoneBookModel::Columns::IsMale);

//            qDebug()<<name<<" "<<lastname<<" "<<email<<" "<<number<<" "<<isMale;

            auto model = ui->lv_contacts->model();
            int row = model->rowCount();
            model->insertRows(row,1); // inserting one row
            model->setData(model->index(row,PhoneBookModel::Columns::Name), name);
            model->setData(model->index(row,PhoneBookModel::Columns::Lastname), lastname);
            model->setData(model->index(row,PhoneBookModel::Columns::Email), email);
            model->setData(model->index(row,PhoneBookModel::Columns::Number), number);
            model->setData(model->index(row,PhoneBookModel::Columns::IsMale), isMale);


//            ui->list_contacts->addItem(str.split(UNIT_SEPARATOR).at(0));
        }
        file.close();
    }
}

void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this);

    QFile file(filename);
    if(file.open(QIODevice::WriteOnly)){
//        this->removeAll();
        QTextStream out(&file);

        auto model = ui->lv_contacts->model();

        for(int row = 0; row < model->rowCount(); row++)
        {
            QString name = model->data(model->index(row, PhoneBookModel::Columns::Name)).toString();
            QString lastname = model->data(model->index(row, PhoneBookModel::Columns::Lastname)).toString();
            QString email = model->data(model->index(row, PhoneBookModel::Columns::Email)).toString();
            QString number = model->data(model->index(row, PhoneBookModel::Columns::Number)).toString();
            QString isMale = model->data(model->index(row, PhoneBookModel::Columns::IsMale)).toString();

            out<< name << UNIT_SEPARATOR << lastname << UNIT_SEPARATOR << email << UNIT_SEPARATOR << number << UNIT_SEPARATOR << isMale << "\n";
        }
        file.close();
    }
}

void MainWindow::removeAll()
{
    ui->lv_contacts->model()->removeRows(0,ui->lv_contacts->model()->rowCount());
}
