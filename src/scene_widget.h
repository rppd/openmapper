#ifndef SCENE_WIDGET_H
#define SCENE_WIDGET_H

#include "scene.h"
#include "glwidget.h"

#include <QWidget>
#include <QPaintDevice>
#include <QPaintEvent>
#include <QPointF>

class SceneWidget: public QWidget {
    public:
        SceneWidget();
        SceneWidget(QWidget* parent);
        ~SceneWidget() {};

        void mousePressEvent(QMouseEvent* e);
        void mouseMoveEvent(QMouseEvent* e);
        void paintEvent(QPaintEvent* e);

        Scene* scene() const { return _scene; };
        void scene(Scene* scene) { _scene = scene; };

        void setGLWidget(GLWidget* glw) { _glw = glw; };

    private:
        Scene* _scene = nullptr;
        QPointF cursor;
        QList<QPointF> selectedPoints;
        GLWidget* _glw;
        int selectedGroup = 0;

        void drawSelectedPoints(QPainter painter);
        void createShape();
        void createGroup();
};

#endif