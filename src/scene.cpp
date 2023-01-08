#include "scene.h"

#include "shape_group.h"

#include <stdio.h>
#include <QList>
#include <QPainter>

void Scene::draw() const {
    printf("Drawing scene (%d groups) \n", (int) groups.size());
    for (ShapeGroup* group: groups) {
        group->draw();
    }
}

void Scene::addShape(const Shape shape, int group) {
    groups[group]->addShape(shape);
    groups[group]->build();
}

void Scene::paint(QPainter* painter) const {
    for (ShapeGroup* group: groups) {
        group->paint(painter);
    }
}

ShapeGroup* Scene::createGroup() {
    groups.append(new ShapeGroup());
    return groups.last();
};