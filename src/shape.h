#ifndef SHAPE_H
#define SHAPE_H

#include "triangle.h"

#include <QList>
#include <QVector2D>

class Shape {
    public:
        Shape() {};

        enum MeshingMethod {
            CENTER,
            LADDER,
            NEAREST
        };

        void addPoint(QVector2D xy);
        void addPoint(float x, float y) { addPoint(QVector2D(x,y)); };
        void autoCenter();
        void setCenter(QVector2D xy) { center = xy; };
        void makeTriangles();
        void makeTrianglesCenter();
        void makeTrianglesNearest();
        void makeTrianglesLadder();

        QList<QVector2D> getPoints() const { return points; };
        QList<Triangle> getTriangles() const { return triangles; };
        int nPoints() const { return points.size(); };
        int nTriangles() const { return triangles.size(); };
    private:
        QList<QVector2D> points;
        QList<Triangle> triangles;
        QVector2D center;
        MeshingMethod meshing = CENTER;
};

#endif