#include "explorer.h"

#include "QxOrm.h"

ExplorerItem::ExplorerItem(const QVector<QVariant> &data, ExplorerItem *parent)
        : m_itemData(data), m_parentItem(parent)
{}

ExplorerItem::~ExplorerItem()
{
    qDeleteAll(m_childItems);
}

void ExplorerItem::appendChild(ExplorerItem *item)
{
    m_childItems.append(item);
}

ExplorerItem *ExplorerItem::child(int row)
{
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int ExplorerItem::childCount() const
{
    return m_childItems.count();
}

int ExplorerItem::columnCount() const
{
    return m_itemData.count();
}

QVariant ExplorerItem::data(int column) const
{
    if (column < 0 || column >= m_itemData.size())
        return {};
    return m_itemData.at(column);
}

int ExplorerItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<ExplorerItem*>(this));

    return 0;
}

ExplorerItem *ExplorerItem::parentItem()
{
    return m_parentItem;
}

ExplorerModel::ExplorerModel(QObject *parent)
        : QAbstractItemModel(parent)
{
    generate_model();
}

ExplorerModel::~ExplorerModel()
{
    delete rootItem;
}

void ExplorerModel::generate_model()
{
    beginResetModel();

    rootItem = new ExplorerItem({ tr("id") });

    list_note notes_without_folder;
    qx_query query;
    query.where("folder_id").isNull();
    qx::dao::fetch_by_query_with_all_relation(query, notes_without_folder);

    for (auto &note : notes_without_folder) {
        QVector<QVariant> noteColumnData;
        noteColumnData << QVariant::fromValue(note->id);
        rootItem->appendChild(new ExplorerItem(noteColumnData, rootItem));
    }

    list_folder folders;
    qx::dao::fetch_all_with_all_relation(folders);

    for (auto &folder : folders) {
        QVector<QVariant> folderColumnData;
        folderColumnData << QVariant::fromValue(folder->id);
        auto *folderItem = new ExplorerItem(folderColumnData, rootItem);

        for (auto &note : folder->notes) {
            QVector<QVariant> noteColumnData;
            noteColumnData << QVariant::fromValue(note->id);
            auto *noteItem = new ExplorerItem(noteColumnData, folderItem);
            folderItem->appendChild(noteItem);
        }

        rootItem->appendChild(folderItem);
    }

    endResetModel();
}

QModelIndex ExplorerModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return {};

    ExplorerItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ExplorerItem*>(parent.internalPointer());

    ExplorerItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return {};
}

QModelIndex ExplorerModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return {};

    auto *childItem = static_cast<ExplorerItem*>(index.internalPointer());
    ExplorerItem *parentItem = childItem->parentItem();

    if (parentItem == rootItem)
        return {};

    return createIndex(parentItem->row(), 0, parentItem);
}

int ExplorerModel::rowCount(const QModelIndex &parent) const
{
    ExplorerItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<ExplorerItem*>(parent.internalPointer());

    return parentItem->childCount();
}

int ExplorerModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return static_cast<ExplorerItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QVariant ExplorerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};

    if (role != Qt::DisplayRole)
        return {};

    auto *item = static_cast<ExplorerItem*>(index.internalPointer());

    return item->data(index.column());
}

Qt::ItemFlags ExplorerModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant ExplorerModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return {};
}

QString ExplorerModel::getTitle(int id, int type) {
    if (type == ExplorerModel::OBJECT_TYPE::NOTE) {
        Note_ptr note; note.reset(new Note());
        note->id = id;
        qx::dao::fetch_by_id(note);
        return note->title;
    } else if (type == ExplorerModel::OBJECT_TYPE::FOLDER) {
        Folder_ptr folder; folder.reset(new Folder());
        folder->id = id;
        qx::dao::fetch_by_id(folder);
        return folder->name;
    }
    return "";
}
