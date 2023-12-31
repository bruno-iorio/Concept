//
// Created by hung3a8 on 29/12/2023.
//

#ifndef CONCEPTAPP_EXPLORER_H
#define CONCEPTAPP_EXPLORER_H

#include <QtQuick/QQuickTextDocument>
#include <QAbstractItemModel>
#include "database/database.h"

class ExplorerItem {
public:
    explicit ExplorerItem(const QVector<QVariant> &data, ExplorerItem *parentItem = nullptr);
    ~ExplorerItem();

    void appendChild(ExplorerItem *child);

    ExplorerItem *child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    ExplorerItem *parentItem();

private:
    QVector<ExplorerItem*> m_childItems;
    QVector<QVariant> m_itemData;
    ExplorerItem *m_parentItem;
};

class ExplorerModel : public QAbstractItemModel
{
Q_OBJECT
QML_ELEMENT
QML_SINGLETON

public:
    explicit ExplorerModel(QObject *parent = nullptr);
    ~ExplorerModel() override;

    QVariant data(const QModelIndex &index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE void generate_model();

private:
    ExplorerItem *rootItem;
};

#endif //CONCEPTAPP_EXPLORER_H
