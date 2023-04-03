#ifndef SCENE_H
#define SCENE_H

#include "shape_group.h"
#include "../gl/glpointers.h"

#include <QList>
#include <QPainter>
#include <QSize>
#include <QStringList>

class Scene {

public:
    Scene(QOpenGLContext* ctx = nullptr): _ctx(ctx) { createGroup(); };
    ~Scene() = default;

    void paint(QPainter* painter) const;
    void addShape(const Shape shape, int group);

    ShapeGroup& createGroup();
    void deleteGroup(int index);

    ShapeGroup& at(int i) { return groups.at(i); };
    QStringList getGroupNames() const;
    int nGroups() { return groups.size(); };
    std::vector<GLPointers> pointers() const;
    void context(QOpenGLContext* ctx);

    int vertexCount() const;

private:
    std::vector<ShapeGroup> groups;
    QOpenGLContext* _ctx;
};

#endif