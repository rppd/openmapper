#include "scene_widget.h"

SceneWidget::SceneWidget(Scene& scene): _scene(scene) {
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
    // std::cout << "paintevent" << std::endl;0
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.drawLine(cursor.x(), 0, cursor.x(), height());
    painter.drawLine(0, cursor.y(), width(), cursor.y());
    painter.drawPolyline(selectedPoints.data(), selectedPoints.size());
    if (!selectedPoints.empty()) painter.drawLine(selectedPoints.last(), cursor);

    _scene.paint(&painter);
}

void SceneWidget::createShape() {
    Shape shape;
    for(QPointF point: selectedPoints) {
        shape.addPoint(QVector2D(point.x(),point.y()));
    }
    shape.makeMesh();
    shape.autoCenter();
    _scene.addShape(shape, selectedGroup);
    geometryUpdated();
}