#include "todoList.h"
#include "todoItem.h"
#include <string>

NewListAbstractModel::NewListAbstractModel(QObject *parent)
    : QAbstractListModel(parent) {
        this->nameIndex = 1;
    }


int NewListAbstractModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return m_list.count();
}

QVariant NewListAbstractModel::data (const QModelIndex &index, int role) const {
    if (index.row() < 0 || index.row() >= m_list.count())
        return {};

    ToDoListItem listItem = m_list[index.row()];
    switch (role) {
    case NameRole:
        return QString::fromStdString(listItem.getTaskname());
    default:
        return {};
    }
}

QHash<int, QByteArray> NewListAbstractModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[TypeRole] = "type";
    return roles;
}

//Remove function: removes a certain task when button is clicked
void NewListAbstractModel::remove(int index, int count) {
    beginRemoveRows(QModelIndex(), index, index + count - 1);
    for (int row = 0; row < count; ++row) {
        m_list.removeAt(index);
    }
    endRemoveRows();
}

//Add function: A new task is created once the user clicks the "Add Task" button
void NewListAbstractModel::add(const QString &taskname) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    // save the task to DB and get location on the filesystem
    string location = "";

    int index = this->nameIndex++;

    // if no task name was provided
    if (taskname == "") {
        m_list << ToDoListItem(index, "New task " + to_string(index), location);
    }
    else {
        m_list << ToDoListItem(index, taskname.toStdString(), location);
    }

    endInsertRows();
}

QVariantList NewListAbstractModel::getTaskItemsForQML() const {
    QVariantList taskList;
    for (ToDoListItem item : m_list) {
        QVariantMap taskMap;
        taskMap["taskname"] = QString::fromStdString(item.getTaskname());
        taskList.append(taskMap);
    }
    return taskList;
}
