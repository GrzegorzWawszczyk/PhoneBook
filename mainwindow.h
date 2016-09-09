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
    void removeContacts();
    void showContactInfo(const QModelIndex &index);
    void openFile();
    void saveFile();
    void removeAll();
    void editContacts();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
