#include "mainwindow.h"
#include "phonebookmodel.h"
#include "ui_mainwindow.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addContact()
{
    ui->lv_contacts->model()->insertRows(0,1);
}
