#include "explorer.h"
#include "QxOrm.h"

ExplorerModel::ExplorerModel(QObject *parent) : QAbstractItemModel(parent) {
    // Get all notes
    qx_query query;
    query.orderAsc("last_modified");
    QSqlError daoError = qx::dao::fetch_by_query(query, notes);
}
