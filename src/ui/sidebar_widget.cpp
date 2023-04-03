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
    nameInput = new QLineEdit();
    QPushButton* deleteButton = new QPushButton("Delete");
    QPushButton* createButton = new QPushButton("Create");
    QLabel* topLabel = new QLabel("Shape groups");

    topLabel->setAlignment(Qt::AlignHCenter);

    QHBoxLayout* topLayout = new QHBoxLayout();
    topLayout->addWidget(createButton);
    topLayout->addWidget(deleteButton);
    
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(new QLabel("Name"),0,0);
    gridLayout->addWidget(nameInput,0,1);
    gridLayout->addWidget(new QLabel("Shader"),1,0);
    gridLayout->addWidget(shaderSelector,1,1);
    
    layout->addWidget(topLabel);
    layout->addWidget(groupSelector);
    layout->addLayout(topLayout);
    layout->addLayout(gridLayout);
    layout->addWidget(shapeList);
    layout->addStretch();
    setLayout(layout);

    connect(groupSelector, &QComboBox::currentIndexChanged, this, &SidebarWidget::selectGroup);
    connect(shaderSelector, &QComboBox::currentIndexChanged, this, &SidebarWidget::updateShaderSelection);
    connect(nameInput, &QLineEdit::textChanged, this, &SidebarWidget::renameGroup);
    connect(createButton, &QPushButton::pressed, this, &SidebarWidget::createGroup);
    connect(deleteButton, &QPushButton::pressed, this, &SidebarWidget::deleteGroup);

    loadGroups();
}

void SidebarWidget::loadGroups() {
    int before = groupSelector->currentIndex();
    groupSelector->blockSignals(true);
    groupSelector->clear();
    groupSelector->addItems(_scene.getGroupNames());
    groupSelector->blockSignals(false);
    selectGroup(before);
}

void SidebarWidget::selectGroup(int index) {
    if (index == -1) return;
    ShapeGroup& selectedGroup = _scene.at(index);
    nameInput->blockSignals(true);
    nameInput->setText(selectedGroup.name());
    nameInput->blockSignals(false);

    shapeList->clear();
    for (int i=0; i<selectedGroup.nShapes(); i++) {
        shapeList->addItem(QString::number(i));
    }

    selectionUpdated(index);
}

void SidebarWidget::updateShaderSelection() {
    if (groupSelector->currentIndex() == -1) return;
    Shader& shader = shaderSelector->selection();
    ShapeGroup& selectedGroup = _scene.at(groupSelector->currentIndex());
    selectedGroup.shaderSource(shader.source());
}

void SidebarWidget::renameGroup(const QString& name) {
    if (groupSelector->currentIndex() == -1) return;
    ShapeGroup& selectedGroup = _scene.at(groupSelector->currentIndex());
    selectedGroup.name(name);
    loadGroups();
}

void SidebarWidget::deleteGroup() {
    if (groupSelector->currentIndex() == -1) return;
    _scene.deleteGroup(groupSelector->currentIndex());
    selectGroup(0);
    loadGroups();
}

void SidebarWidget::createGroup() {
    _scene.createGroup();
    selectGroup(_scene.nGroups()-1);
    loadGroups();
}