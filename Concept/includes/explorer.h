//
// Created by hung3a8 on 29/12/2023.
//

#ifndef CONCEPTAPP_EXPLORER_H
#define CONCEPTAPP_EXPLORER_H

#include <QtQuick/QQuickTextDocument>
#include <QAbstractItemModel>
#include "database/database.h"

class ExplorerModel : public QAbstractItemModel {
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
private:
    struct IndexData
    {
        QVector<QModelIndex> parents;
    };

public:
    explicit ExplorerModel(QObject *parent = nullptr);
    ~ExplorerModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;
protected:
    IndexData * indexData(const QModelIndex &index) const;
    QList<int> indexPath(const QModelIndex &index) const;
    QString indexString(const QModelIndex &index) const;
    QString indexString(int row, int column, const QModelIndex &parent) const;
public:
    int indexDepth(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    QMap<QString, IndexData*> indexData_;
    list_note notes;
};

#endif //CONCEPTAPP_EXPLORER_H
