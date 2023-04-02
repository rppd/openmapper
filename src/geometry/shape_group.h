#ifndef SHAPE_GROUP_H
#define SHAPE_GROUP_H

#include "shape.h"
#include "../ui/glwidget.h"
#include "../gl/glpointers.h"

#include <QList>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QOpenGLVertexArrayObject>
#include <QString>
#include <QOpenGLContext>

class ShapeGroup
{

public:
    ShapeGroup(QOpenGLContext* ctx): _ctx(ctx) { build(); };
    ~ShapeGroup() = default;

    GLPointers build(QOpenGLContext* ctx) const;
    void build();
    void draw(GLWidget *glWidget, QMatrix4x4 transform) const; // openGL : render
    void paint(QPainter *painter) const;                       // qpainter : ui

    QString name() const { return _name; };
    void name(QString name) { _name = name; };
    QString shaderSource() const { return _shaderSource; };
    void shaderSource(QString shaderSource) { _shaderSource = shaderSource; build(); };
    GLPointers pointers() { return _pointers; };

    void append(const Shape& shape) { shapes.push_back(shape); build(); };
    const Shape& at(const int i) const { return shapes.at(i); };

    int vertexCount() const;


private:
    QString _shaderSource = "";
    QString _name = "ShapeGroup";
    std::vector<Shape> shapes;

    GLPointers _pointers;
    QOpenGLContext* _ctx;
};

#endif