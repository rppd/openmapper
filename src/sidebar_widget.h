#ifndef SIDEBAR_WIDGET_H
#define SIDEBAR_WIDGET_H

#include "window.h"
#include "glwidget.h"
#include "scene.h"

class Window;

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>

class SidebarWidget: public QWidget {
    public:
        SidebarWidget() {};
        SidebarWidget(Window* window, GLWidget* glWidget, Scene* scene);
        QSize sizeHint();
        int minimumWidth();
        
        void setScene(Scene* scene);
        void selectGroup(int index);

    public slots:
        void update();

    private:
        QVBoxLayout* layout;
        QListWidget* shapeList;
        QComboBox* groupSelector;

        Scene* scene;
};

#endif