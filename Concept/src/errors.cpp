#include "errors.h"

void error_popup(const QString &message) {
    QMessageBox::critical(nullptr, "Error", message);
}
