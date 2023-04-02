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

class SidebarWidget: public QWidget {
    Q_OBJECT
    
    public:
        SidebarWidget(Scene& scene, ShaderLibrary* shaderLibrary);
        QSize sizeHint();
        int minimumWidth();
        
        void setScene(Scene* scene);
        void selectGroup(int index);
        void selectShader(int index);

    public slots:
        void update();

    private:
        QVBoxLayout* layout;
        QListWidget* shapeList;
        QComboBox* groupSelector;
        ShaderSelector* shaderSelector;

        Scene& _scene;
        ShaderLibrary* shaderLibrary;
};

#endif