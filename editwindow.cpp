#include "editwindow.h"
#include "ui_editwindow.h"

EditWindow::EditWindow(QWidget *parent, PhoneBookModel *pbm) :
    QWidget(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
    ui->tv_contacts->setModel(pbm);

    auto header = ui->tv_contacts->horizontalHeader();
    header->setSectionResizeMode(PhoneBookModel::Columns::Name,QHeaderView::Stretch);
    header->setSectionResizeMode(PhoneBookModel::Columns::Lastname,QHeaderView::Stretch);
    header->setSectionResizeMode(PhoneBookModel::Columns::Email,QHeaderView::Stretch);
    header->setSectionResizeMode(PhoneBookModel::Columns::Number,QHeaderView::Stretch);
    header->setSectionResizeMode(PhoneBookModel::Columns::IsMale,QHeaderView::Stretch);
    header->setSectionHidden(PhoneBookModel::Columns::Fullname, true);

    connect(ui->b_cancel, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->b_confirm, &QPushButton::clicked, this, &QWidget::close);

}

EditWindow::~EditWindow()
{
    delete ui;
}
