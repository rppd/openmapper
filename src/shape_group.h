#ifndef SHAPE_GROUP_H
#define SHAPE_GROUP_H

#include "shape.h"

#include <QList>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QOpenGLVertexArrayObject>

class ShapeGroup {
    public:
        ShapeGroup() {};
        ~ShapeGroup() { printf("Destroying a ShapeGroup.\n");}

        void build();
        void draw(); //openGL : render
        void paint(QPainter* painter) const; //qpainter : ui
        void addShape(const Shape shape) { shapes.append(shape); };
        Shape getShape(int i) const { return shapes.at(i); } ;
        int size() const { return shapes.size(); } ;
    private:
        QList<Shape> shapes;
        int vertexCount;
        void allocateVBO() const;

        QOpenGLBuffer* vbo;
        QOpenGLVertexArrayObject vao;
        QOpenGLShaderProgram* program;
};


#endif