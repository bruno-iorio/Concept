#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include "todoItem.h"

class NewListAbstractModel : public QAbstractListModel {
    Q_OBJECT

public:
    enum FileRoles {
        NameRole = Qt::UserRole + 1,
        TypeRole
    };

    explicit NewListAbstractModel(QObject *parent = nullptr);

    Q_INVOKABLE QVariantList getTaskItemsForQML() const;

    Q_INVOKABLE void remove(int index, int count = 1);

    Q_INVOKABLE void add(const QString &taskname);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ToDoListItem> m_list;
    int nameIndex;
};

#endif // TODOLIST_H
