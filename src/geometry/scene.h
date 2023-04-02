#ifndef SCENE_H
#define SCENE_H

#include "shape_group.h"
#include "../ui/glwidget.h"

#include <QList>
#include <QPainter>
#include <QSize>
#include <QStringList>

class Scene {

public:
    Scene(QOpenGLContext* ctx): _ctx(ctx) { createGroup(); };
    ~Scene() = default;

    void draw(GLWidget* glWidget) const; // openGL
    void paint(QPainter* painter) const; // qpainter
    void addShape(const Shape shape, int group);

    ShapeGroup& createGroup();
    ShapeGroup& at(int i) { return groups.at(i); };
    QStringList getGroupNames() const;
    int nGroups() { return groups.size(); };
    std::vector<GLPointers> pointers() const;

    int vertexCount() const;

private:
    std::vector<ShapeGroup> groups;
    QOpenGLContext* _ctx;
};

#endif