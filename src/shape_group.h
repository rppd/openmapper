#ifndef SHAPE_GROUP_H
#define SHAPE_GROUP_H

#include "shape.h"
#include "glwidget.h"

#include <QList>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QOpenGLVertexArrayObject>
#include <QString>

class ShapeGroup : public QList<Shape>
{
public:
    ShapeGroup(){};
    ~ShapeGroup() { printf("Destroying a ShapeGroup.\n"); }

    GLWidget::GLPointers build(QOpenGLContext* ctx) const;
    void draw(GLWidget *glWidget, QMatrix4x4 transform) const; // openGL : render
    void paint(QPainter *painter) const;                       // qpainter : ui

    QString name() const { return _name; };
    void name(QString name) { _name = name; };
    QString shaderSource() const { return _shaderSource; };
    void shaderSource(QString shaderSource) { _shaderSource = shaderSource; };

    int vertexCount() const;

signals:
    void update();

private:
    QString _shaderSource = "";
    QString _name = "ShapeGroup";
    void allocateVBO() const;
};

#endif