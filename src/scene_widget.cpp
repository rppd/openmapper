#include "scene_widget.h"

#include "shape_group.h"
#include "glwidget.h"

#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <Qt>
#include <QPalette>

SceneWidget::SceneWidget() {
    setMouseTracking(true);
    
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
}

void SceneWidget::mouseMoveEvent(QMouseEvent* e) {
    cursor = e->position();
    update();
}

void SceneWidget::mousePressEvent(QMouseEvent* e) {
    QPointF point = e->position();
    if (!selectedPoints.empty() && (point - selectedPoints.first()).manhattanLength() < 20) { 
        createShape();
        selectedPoints.clear();
    } else {
        selectedPoints.append(e->position());
    }
    update();
}

void SceneWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.drawLine(cursor.x(), 0, cursor.x(), height());
    painter.drawLine(0, cursor.y(), width(), cursor.y());
    painter.drawPolyline(selectedPoints.data(), selectedPoints.size());
    if (!selectedPoints.empty()) painter.drawLine(selectedPoints.last(), cursor);

    scene.paint(&painter);
}

void SceneWidget::createShape() {
    Shape shape;
    for(QPointF point: selectedPoints) {
        shape.addPoint(QVector2D(point.x(),point.y()));
    }
    if (scene.nGroups() == 0) createGroup();
    for(GLWidget* glw: glWidgets) {
        glw->makeCurrent(); 
        scene.addShape(shape, selectedGroup);
        glw->update();
    }
}

void SceneWidget::createGroup() {
    scene.createGroup();
}