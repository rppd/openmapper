#include "scene.h"

#include <QList>
#include <QPainter>
#include <iostream>
#include <QSize>

Scene::Scene() {
    createGroup();
}

QList<GLWidget::GLPointers> Scene::build(QOpenGLContext* ctx) const {
    ctx->makeCurrent(ctx->surface());
    QList<GLWidget::GLPointers> list = QList<GLWidget::GLPointers>();
    for (const ShapeGroup& group : *this) {
        list.append(group.build(ctx));
    }
    return list;
}

void Scene::addShape(const Shape shape, int group_index) {
    ShapeGroup& group = (*this)[group_index];
    group.append(shape);
    emit updated();
}

void Scene::paint(QPainter* painter) const {
    for (const ShapeGroup& group: *this) {
        group.paint(painter);
    }
}

ShapeGroup& Scene::createGroup() {
    append(ShapeGroup());
    emit updated();
    return last();
};

QStringList Scene::getGroupNames() const {
    QStringList list = QStringList();
    for (const ShapeGroup& group : *this) {
        list.append(group.name());
    }
    return list;
}

int Scene::vertexCount() const {
    int count = 0;
    for (const ShapeGroup& group : *this) {
        count += group.vertexCount();
    }
    return count;
}