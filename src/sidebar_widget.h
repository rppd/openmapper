#ifndef SIDEBAR_WIDGET_H
#define SIDEBAR_WIDGET_H

#include <QWidget>

class SidebarWidget: public QWidget {
    public:
        QSize sizeHint();
        int minimumWidth();
};

#endif