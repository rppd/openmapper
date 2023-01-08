#ifndef SIDEBAR_WIDGET_H
#define SIDEBAR_WIDGET_H

#include "window.h"
#include "glwidget.h"

class Window;

#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QPushButton>

class SidebarWidget: public QWidget {
    public:
        SidebarWidget() {};
        SidebarWidget(Window* window, GLWidget* glWidget);
        QSize sizeHint();
        int minimumWidth();
    private:
        QVBoxLayout* layout;
        QSlider* slider;
};

#endif