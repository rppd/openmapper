// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "window.h"
#include "glwidget.h"
#include "sidebar_widget.h"

#include <QSlider>
#include <QSplitter>

Window::Window()
{
    sceneWidget = new SceneWidget();
    glWidget = new GLWidget(sceneWidget->pScene());
    sceneWidget->addGLWidget(glWidget);

    sidebarWidget = new SidebarWidget(this, glWidget);

    QSplitter* leftSplitter = new QSplitter();
    leftSplitter->setOrientation(Qt::Vertical);
    leftSplitter->addWidget(glWidget);
    leftSplitter->addWidget(sceneWidget);

    QSplitter* splitter = new QSplitter();
    splitter->addWidget(leftSplitter);
    splitter->addWidget(sidebarWidget);
    setCentralWidget(splitter);

    setWindowTitle(tr("OpenGL Window"));
}

QSlider* Window::createSlider(int min, int max) {
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(min, max);
    slider->setSingleStep(1);
    slider->setPageStep(10);
    slider->setTickInterval(10);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QSlider* Window::createAngleSlider() {
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}