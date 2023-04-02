#include "sidebar_widget.h"

#include "iostream"

QSize SidebarWidget::sizeHint() {
    return QSize(500,1000);
}

int SidebarWidget::minimumWidth() {
    return 600;
}

SidebarWidget::SidebarWidget(Scene* scene, ShaderLibrary* shaderLibrary): scene(scene), shaderLibrary(shaderLibrary) {
    groupSelector = new QComboBox();
    shaderSelector = new ShaderSelector(shaderLibrary);
    shapeList = new QListWidget();
    layout = new QVBoxLayout();
    
    layout->addWidget(groupSelector);
    layout->addWidget(shaderSelector);
    layout->addWidget(shapeList);
    layout->addStretch();
    setLayout(layout);

    connect(shaderSelector, &QComboBox::currentIndexChanged, this, &SidebarWidget::selectShader);
}

void SidebarWidget::update() {
    groupSelector->clear();
    groupSelector->addItems(scene->getGroupNames());

    selectGroup(groupSelector->currentIndex());
}

void SidebarWidget::selectGroup(int index) {
    if (index == -1) index = 0;
    shapeList->clear();
    for (int i=0; i<scene->nGroups(); i++) {
        shapeList->addItem(QString::number(i));
    }
}

void SidebarWidget::selectShader(int index) {
    Shader& shader = shaderLibrary->at(index);
    ShapeGroup& selectedGroup = scene->at(groupSelector->currentIndex());
    selectedGroup.shaderSource(shader.source());
}