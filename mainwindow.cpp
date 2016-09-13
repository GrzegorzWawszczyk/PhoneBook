#include "addcontact.h"
#include "contactinfo.h"
#include "editwindow.h"
#include "filehandler.h"
#include "mainwindow.h"
#include "phonebookmodel.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFuture>
#include <QtConcurrent>
#include <cstddef>

const char UNIT_SEPARATOR = static_cast<char>(31);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PhoneBookModel* pbm = new PhoneBookModel(this);
    ui->lv_contacts->setModel(pbm);
    ui->lv_contacts->setModelColumn(PhoneBookModel::Columns::Fullname);
    ui->lv_contacts->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->lv_contacts->setSelectionMode(QAbstractItemView::ContiguousSelection);

    if (ui->lv_contacts->model()->rowCount()==0)
        openFile();

    connect(ui->b_add, &QPushButton::clicked, this, &MainWindow::addContact);
    connect(ui->b_remove, &QPushButton::clicked, this, &MainWindow::removeContacts);
    connect(ui->lv_contacts, &QListView::activated, this, MainWindow::showContactInfo);
//    connect(ui->lv_contacts, &QListView)
    connect(ui->a_open, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->a_save, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->a_removeAll, &QAction::triggered, this, &MainWindow::removeAll);
    connect(ui->a_edit, &QAction::triggered, this, &MainWindow::editContacts);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addContact()
{
    PhoneBookModel *pbm = dynamic_cast<PhoneBookModel*>(ui->lv_contacts->model());
    AddContact *ac = new AddContact(nullptr, pbm);
    ac->setAttribute(Qt::WA_DeleteOnClose);
    ac->show();
}

void MainWindow::removeContacts()
{
    auto rows = ui->lv_contacts->selectionModel()->selectedRows(0);

    if (rows.isEmpty())
    {
        return;
    }

    std::sort(rows.begin(), rows.end());
    ui->lv_contacts->model()->removeRows(rows.first().row(), rows.size());
}

void MainWindow::showContactInfo(const QModelIndex &index)
{
    auto columnString = [&](int column)
    {
        return ui->lv_contacts->model()->data(index.sibling(index.row(), column)).toString();
    };

    QString name = columnString(PhoneBookModel::Columns::Name);
    QString lastname = columnString(PhoneBookModel::Columns::Lastname);
    QString email = columnString(PhoneBookModel::Columns::Email);
    QString number = columnString(PhoneBookModel::Columns::Number);
    QString sexString = columnString(PhoneBookModel::Columns::IsMale);
    ContactInfo* ci = new ContactInfo(name, lastname, email, number, sexString);
    ci->setAttribute(Qt::WA_DeleteOnClose);
    ci->show();

}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this);


        removeAll();

        QVector<PhoneBookModel::Contact> *vector = new QVector<PhoneBookModel::Contact>();
        QFuture<void> loadFuture = QtConcurrent::run(new FileHandler(), &FileHandler::readFile, filename, vector/*dynamic_cast<PhoneBookModel*>(ui->lv_contacts->model())*/);
        QFutureWatcher<void>* watcher = new QFutureWatcher<void>(this);
        connect(watcher, &QFutureWatcher<void>::finished, [this, vector]()
        {
            PhoneBookModel *model = dynamic_cast<PhoneBookModel*>(ui->lv_contacts->model());
            model->swap(*vector);
            model->changeData();
        });

        watcher->setFuture(loadFuture);

}

void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this);

    FileHandler *fh = new FileHandler();
    fh->saveFile(filename, dynamic_cast<PhoneBookModel*>(ui->lv_contacts->model())->getAll());
}

void MainWindow::removeAll()
{
    dynamic_cast<PhoneBookModel*>(ui->lv_contacts->model())->removeAll();
}

void MainWindow::editContacts()
{
    EditWindow *ew = new EditWindow(nullptr, dynamic_cast<PhoneBookModel*>(ui->lv_contacts->model()));
    ew->setAttribute(Qt::WA_DeleteOnClose);
    ew->show();
}
