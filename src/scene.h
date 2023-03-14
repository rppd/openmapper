#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "shape_group.h"
#include "glwidget.h"

#include <QList>
#include <QPainter>
#include <QSize>
#include <QStringList>

class Scene : public QObject, public QList<ShapeGroup>
{
    Q_OBJECT

public:
    Scene();
    ~Scene() = default;

    QList<GLWidget::GLPointers> build(QOpenGLContext* ctx) const;
    void draw(GLWidget* glWidget) const; // openGL
    void paint(QPainter* painter) const; // qpainter
    void addShape(const Shape shape, int group);

    ShapeGroup &createGroup();
    QStringList getGroupNames() const;

    int vertexCount() const;
signals:
    void updated();
};

#endif