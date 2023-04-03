#ifndef SCENE_WIDGET_H
#define SCENE_WIDGET_H

#include "../geometry/scene.h"
#include "glwidget.h"
#include "../geometry/shape_group.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPalette>
#include <QWidget>
#include <QPaintDevice>
#include <QPointF>

class SceneWidget: public QWidget {
    Q_OBJECT

    public:
        SceneWidget(Scene& scene);
        SceneWidget(QWidget* parent, Scene& scene);
        ~SceneWidget() {};

        void mousePressEvent(QMouseEvent* e);
        void mouseMoveEvent(QMouseEvent* e);
        void paintEvent(QPaintEvent* e);
        void build();

        Scene& scene() const { return _scene; };
        void scene(Scene& scene) { _scene = scene; };

        void setGLWidget(GLWidget* glw) { _glw = glw; };
    
    public slots:
        void updateSelection(int index);

    signals:
        void geometryUpdated();
        

    private:
        Scene& _scene;
        QPointF cursor;
        QList<QPointF> selectedPoints;
        GLWidget* _glw;
        int selectedGroup = 0;

        void drawSelectedPoints(QPainter painter);
        void createShape();
};

#endif