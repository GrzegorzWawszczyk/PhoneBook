#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include "phonebookmodel.h"

#include <QWidget>

namespace Ui {
class EditWindow;
}

class EditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = 0, PhoneBookModel *pbm = 0);
    ~EditWindow();

private:
    Ui::EditWindow *ui;
};

#endif // EDITWINDOW_H
