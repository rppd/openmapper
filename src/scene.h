#ifndef GRAPHICS_MANAGER_H
#define GRAPHICS_MANAGER_H

#include "shape_group.h"

#include <QList>
#include <QPainter>

class Scene {

    public:
        Scene() {};
        Scene(QOpenGLContext* ctx): glctx(ctx) {};

        void draw() const; //openGL
        void paint(QPainter* painter) const; //qpainter
        void addShape(const Shape shape, int group);
        ShapeGroup* createGroup();
        int nGroups() const { return groups.size(); };
        void setContext(QOpenGLContext* ctx) { glctx = ctx; };

    private:
        QList<ShapeGroup*> groups;
        QOpenGLContext* glctx = nullptr;
};

#endif