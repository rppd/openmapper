#include "sidebar_widget.h"

#include "iostream"

QSize SidebarWidget::sizeHint() {
    return QSize(500,1000);
}

int SidebarWidget::minimumWidth() {
    return 600;
}

SidebarWidget::SidebarWidget(Scene& scene, ShaderLibrary* shaderLibrary): _scene(scene), shaderLibrary(shaderLibrary) {
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
    std::cout << "update sidebar widget cuz" << std::endl;
    groupSelector->clear();
    groupSelector->addItems(_scene.getGroupNames());
    selectGroup(groupSelector->currentIndex());
    std::cout << "update sidebar widget over" << std::endl;
}

void SidebarWidget::selectGroup(int index) {
    if (index == -1) index = 0;
    shapeList->clear();
    for (int i=0; i<_scene.nGroups(); i++) {
        shapeList->addItem(QString::number(i));
    }
}

void SidebarWidget::selectShader(int index) {
    if (index == -1 || groupSelector->currentIndex() == -1) return;
    Shader& shader = shaderLibrary->at(index);
    if (groupSelector->currentIndex() != -1) {
        ShapeGroup& selectedGroup = _scene.at(groupSelector->currentIndex());
        selectedGroup.shaderSource(shader.source());
    }
}