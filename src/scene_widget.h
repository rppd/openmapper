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
        SceneWidget(QWidget* parent): QWidget(parent) { SceneWidget(); scene.setContext(QOpenGLContext::currentContext()); };
        ~SceneWidget() {};

        void mousePressEvent(QMouseEvent* e);
        void mouseMoveEvent(QMouseEvent* e);
        void paintEvent(QPaintEvent* e);
        Scene* pScene() { return &scene; };
        void addGLWidget(GLWidget* glw) { glWidgets.append(glw); }
    private:
        Scene scene;
        QPointF cursor;
        QList<QPointF> selectedPoints;
        QList<GLWidget*> glWidgets;
        int selectedGroup = 0;

        void drawSelectedPoints(QPainter painter);
        void createShape();
        void createGroup();
};

#endif