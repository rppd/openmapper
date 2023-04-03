#ifndef SHAPE_GROUP_H
#define SHAPE_GROUP_H

#include "shape.h"
#include "../gl/glpointers.h"
// #include "qopengl.h"

#include <iostream>

#include <QList>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QOpenGLVertexArrayObject>
#include <QString>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

class ShapeGroup
{

public:
    ShapeGroup(QOpenGLContext* ctx = nullptr): _ctx(ctx) { build(); };
    ~ShapeGroup() = default;

    GLPointers build(QOpenGLContext* ctx) const;
    void build();
    void paint(QPainter *painter) const;   

    QString name() const { return _name; };
    void name(QString name) { _name = name; };
    QString shaderSource() const { return _shaderSource; };
    void shaderSource(QString shaderSource) { _shaderSource = shaderSource; build(); };
    QOpenGLContext* context() const { return _ctx; };
    void context(QOpenGLContext* ctx) { _ctx = ctx; build(); }
    GLPointers pointers() const { return _pointers; };

    int nShapes() const { return shapes.size(); };
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