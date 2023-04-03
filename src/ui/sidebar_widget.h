#ifndef SIDEBAR_WIDGET_H
#define SIDEBAR_WIDGET_H

#include "glwidget.h"
#include "../geometry/scene.h"
#include "../gl/shader_library.h"
#include "shader_selector.h"
#include "../geometry/shape_group.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QLabel>

class SidebarWidget: public QWidget {
    Q_OBJECT
    
    public:
        SidebarWidget(Scene& scene, ShaderLibrary* shaderLibrary);
        QSize sizeHint();
        int minimumWidth();
        
        void setScene(Scene* scene);
        void selectGroup(int index);
        void updateShaderSelection();
        void renameGroup(const QString& name);
        void deleteGroup();
        void createGroup();

    public slots:
        void loadGroups();

    signals:
        void selectionUpdated(int index);

    private:
        QVBoxLayout* layout;
        QListWidget* shapeList;
        QComboBox* groupSelector;
        ShaderSelector* shaderSelector;
        QLineEdit* nameInput;

        Scene& _scene;
        ShaderLibrary* shaderLibrary;
};

#endif