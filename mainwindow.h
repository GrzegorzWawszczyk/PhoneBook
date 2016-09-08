#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void addContact();
    void showContactInfo(const QModelIndex &index);
    void openFile();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
