#include "shape.h"

#include <QList>
#include <QVector2D>
#include <QPointF>
#include <QDebug>

void Shape::addPoint(QVector2D xy) {
    points.append(xy);
}

void Shape::autoCenter() {
    center = QVector2D(0,0);
    for (int i=0; i<points.size(); i++) {
        center += points.at(i);
    }
    center /= points.size();
}

void Shape::makeMesh() {
    orientate();
    Shape shape(*this);
    mesh = QList<Triangle>();
    while (shape.nPoints() > 2) {
        int vertex = shape.bestVertexTriangle();
        if (vertex == -1) {
            qDebug() << "Meshing failed : no valid vertex triangle.";
            return;
        }
        mesh.append(shape.vertexTriangle(vertex));
        shape = shape.vertexRemoved(vertex);
    }
}

Triangle Shape::vertexTriangle(int i) const {
    int n = nPoints();
    return Triangle(
        points[ (n+i-1)%n ],
        points[  i        ],
        points[ (i+1)%n   ]
    );
}

bool Shape::validVertexTriangle(int i) const {
    if (!vertexCounterClockwise(i)) return false;
    Triangle triangle = vertexTriangle(i);
    for (const QVector2D& point: points) {
        if (triangle.pointInside(point)) return false;
    }
    return true;
}

int Shape::bestVertexTriangle() const {
    float max_grade = -1;
    float max_index = -1;
    for (int i=0; i<nPoints(); i++) {
        float grade = vertexTriangle(i).grade();
        if (grade > max_grade && validVertexTriangle(i)) {
            max_grade = grade;
            max_index = i;
        }
    }
    return max_index;
}

bool Shape::counterClockwise() const { // https://en.wikipedia.org/wiki/Curve_orientation
    int hull_vertex = 0;
    float min_x = points[0].x();
    for (int i=1; i<nPoints(); i++) {
        if (points[i].x() < min_x) {
            hull_vertex = i;
            min_x = points[i].x();
        }
    }
    return vertexCounterClockwise(hull_vertex);
}

bool Shape::vertexCounterClockwise(int i) const {
    int n = nPoints();
    QVector2D seg1 = (points[i] - points[(n+i-1)%n]);
    QVector2D seg2 = (points[(i+1)%n] - points[i]);
    QVector2D normal1 = QVector2D(-seg1.y(),seg1.x());
    return QVector2D::dotProduct(normal1, seg2) < 0;
}

void Shape::orientate() { //make sure the points are in counter-clockwise order
    if (!counterClockwise()) { //if not, reverse them
        int n = nPoints();
        QList<QVector2D> copy = QList<QVector2D>(points);
        points = QList<QVector2D>();
        for (int i=0; i<n; i++) {
            points.append(copy[n-1-i]);
        }
    }
}

Shape Shape::vertexRemoved(int i) const {
    Shape shape;
    for (int j=0; j<nPoints(); j++) {
        if (i!=j) shape.addPoint(points[j]);
    }
    return shape;
}