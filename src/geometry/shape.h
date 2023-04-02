#ifndef SHAPE_H
#define SHAPE_H

#include "triangle.h"

#include <QList>
#include <QVector2D>

class Shape {
    public:
        Shape() {};
        Shape(QList<QVector2D> _points): points(_points) {};

        void addPoint(QVector2D xy);
        void addPoint(float x, float y) { addPoint(QVector2D(x,y)); };
        void autoCenter();
        void setCenter(QVector2D xy) { center = xy; };
        void makeMesh();

        QList<QVector2D> getPoints() const { return points; };
        QList<Triangle> getMesh() const { return mesh; };
        int nPoints() const { return points.size(); };
        int meshSize() const { return mesh.size(); };

        //for meshing
        bool validVertexTriangle(int i) const;
        int bestVertexTriangle() const;
        Triangle vertexTriangle(int i) const;
        bool counterClockwise() const;
        bool vertexCounterClockwise(int i) const;
        void orientate();
        Shape vertexRemoved(int i) const;

    private:
        QList<QVector2D> points;
        QList<Triangle> mesh;
        QVector2D center;
};

#endif