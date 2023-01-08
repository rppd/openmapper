#include "shape.h"

#include <QList>
#include <QVector2D>
#include <QPointF>

void Shape::addPoint(QVector2D xy) {
    points.append(xy);
    makeTriangles();
    autoCenter();
}

void Shape::autoCenter() {
    center = QVector2D(0,0);
    for (int i=0; i<points.size(); i++) {
        center += points.at(i);
    }
    center /= points.size();
}

void Shape::makeTriangles() {
    if (points.size() == 3) {
        triangles = QList<Triangle>();
        triangles.append(Triangle(points[0],points[1],points[2]));
        return;
    }
    switch(meshing) {
        case CENTER:
            makeTrianglesCenter();
        break;
        case NEAREST:
            makeTrianglesNearest();
        break;
        case LADDER:
            makeTrianglesLadder();
        break;
    }
}

void Shape::makeTrianglesCenter() {
    triangles = QList<Triangle>();
    triangles.append(Triangle(
        center,
        points[points.size()-1],
        points[0]
    ));
    for (int i = 1; i < points.size(); i++) {
        triangles.append(Triangle(
            center,
            points.at(i-1),
            points.at(i)
        ));
    }
}

void Shape::makeTrianglesNearest() {
    triangles = QList<Triangle>();
}

void Shape::makeTrianglesLadder() {
    triangles = QList<Triangle>();
}