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
    gridLayout = new QGridLayout();
    nameInput = new QLineEdit();
    gridLayout->addWidget(new QLabel("Name"),0,0);
    gridLayout->addWidget(nameInput,0,1);
    gridLayout->addWidget(new QLabel("Shader"),1,0);
    gridLayout->addWidget(shaderSelector,1,1);
    
    layout->addWidget(groupSelector);
    layout->addLayout(gridLayout);
    layout->addWidget(shapeList);
    layout->addStretch();
    setLayout(layout);
    
    connect(shaderSelector, &QComboBox::currentIndexChanged, this, &SidebarWidget::updateShaderSelection);
    connect(nameInput, &QLineEdit::textChanged, this, &SidebarWidget::renameGroup);
}

void SidebarWidget::update() {
    groupSelector->clear();
    groupSelector->addItems(_scene.getGroupNames());
    selectGroup(groupSelector->currentIndex());
}

void SidebarWidget::selectGroup(int index) {
    if (index == -1) return;
    ShapeGroup& selectedGroup = _scene.at(index);
    nameInput->setText(selectedGroup.name());

    shapeList->clear();
    for (int i=0; i<selectedGroup.nShapes(); i++) {
        shapeList->addItem(QString::number(i));
    }
}

void SidebarWidget::updateShaderSelection() {
    if (shaderSelector->currentIndex() == -1 || groupSelector->currentIndex() == -1) return;
    Shader& shader = shaderSelector->selection();
    ShapeGroup& selectedGroup = _scene.at(groupSelector->currentIndex());
    selectedGroup.shaderSource(shader.source());
}

void SidebarWidget::renameGroup(const QString& name) {
    if (groupSelector->currentIndex() == -1) return;
    ShapeGroup& selectedGroup = _scene.at(groupSelector->currentIndex());
    selectedGroup.name(name);
    update();
}