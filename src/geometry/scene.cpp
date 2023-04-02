#include "scene.h"
#include "../gl/glpointers.h"

#include <QList>
#include <QPainter>
#include <iostream>
#include <QSize>

void Scene::addShape(const Shape shape, int group_index) {
    ShapeGroup& group = groups.at(group_index);
    group.append(shape);
}

void Scene::paint(QPainter* painter) const {
    for (const ShapeGroup& group: groups) {
        group.paint(painter);
    }
}

ShapeGroup& Scene::createGroup() {
    groups.push_back(ShapeGroup(_ctx));
    return groups.at(groups.size()-1);
};

QStringList Scene::getGroupNames() const {
    QStringList list = QStringList();
    for (const ShapeGroup& group : groups) {
        list.append(group.name());
    }
    return list;
}

int Scene::vertexCount() const {
    int count = 0;
    for (const ShapeGroup& group : groups) {
        count += group.vertexCount();
    }
    return count;
}

std::vector<GLPointers> Scene::pointers() const {
    std::vector<GLPointers> pointers;
    pointers.reserve(groups.size());
    for (const ShapeGroup& group: groups) {
        pointers.push_back(group.pointers());
    }
    return pointers;
}

void Scene::context(QOpenGLContext* ctx) {
    for (ShapeGroup& group: groups) {
        group.context(ctx);
    }
}