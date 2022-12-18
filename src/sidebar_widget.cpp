#include "sidebar_widget.h"

QSize SidebarWidget::sizeHint() {
    return QSize(500,1000);
}

int SidebarWidget::minimumWidth() {
    return 400;
}