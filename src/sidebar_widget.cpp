#include "sidebar_widget.h"
#include "glwidget.h"
#include "window.h"

#include "iostream"

#include <QSlider>

QSize SidebarWidget::sizeHint() {
    return QSize(500,1000);
}

int SidebarWidget::minimumWidth() {
    return 600;
}

SidebarWidget::SidebarWidget(Window* window, GLWidget* glWidget, Scene* scene): scene(scene) {
    groupSelector = new QComboBox(this);
    shapeList = new QListWidget(this);
    layout = new QVBoxLayout();
    
    layout->addWidget(groupSelector);
    layout->addWidget(shapeList);
    layout->addStretch();
    setLayout(layout);
    
    update();
    connect(scene, &Scene::updated, this, &SidebarWidget::update);
}

void SidebarWidget::update() {
    groupSelector->clear();
    groupSelector->addItems(scene->getGroupNames());

    selectGroup(groupSelector->currentIndex());
}

void SidebarWidget::selectGroup(int index) {
    if (index == -1) index = 0;
    ShapeGroup group = scene->value(index);
    shapeList->clear();
    for (int i=0; i<group.size(); i++) {
        shapeList->addItem(QString::number(i));
    }
}