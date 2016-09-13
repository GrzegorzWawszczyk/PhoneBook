#ifndef PHONEBOOKMODEL_H
#define PHONEBOOKMODEL_H

#include <QAbstractListModel>
#include <QString>



class PhoneBookModel : public QAbstractListModel
{
    Q_OBJECT

public:

    struct Contact
    {
        Contact() = default;
        Contact(QString name, QString lastname, QString email, QString number, bool isMale);

        QString name;
        QString lastname;
        QString email;
        QString number;
        bool isMale;
    };

    enum Columns
    {
        Name,
        Lastname,
        Email,
        Number,
        IsMale,
        Fullname,
        Count
    };


    PhoneBookModel(QObject *parent = 0);
    ~PhoneBookModel();

    int rowCount(const QModelIndex& parent = {}) const override;
    int columnCount(const QModelIndex& parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void swap(QVector<Contact> newContacts);
    void changeData();
    void addContact(QString name, QString lastname, QString email, QString number, bool isMale);
    QVector<Contact> &getAll();
    void removeAll();

public slots:

private:
    QVector<Contact> contacts;
};

#endif // PHONEBOOKMODEL_H
