// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "window.h"

Window::Window()
{
    Scene* scene = new Scene;
    glWidget = new GLWidget(*scene); //creates the OpenGL Context

    shaderLibrary = new ShaderLibrary();
    connect(glWidget, &GLWidget::glReady, shaderLibrary, &ShaderLibrary::loadShaderDir);

    sceneWidget = new SceneWidget(*scene);
    shaderEditor = new ShaderEditor(shaderLibrary);  
    tabWidget = new QTabWidget;
    tabWidget->addTab(sceneWidget, "Scene Editor");
    tabWidget->addTab(shaderEditor, "Shader Editor");

    sidebarWidget = new SidebarWidget(*scene, shaderLibrary);

    QSplitter* leftSplitter = new QSplitter();
    leftSplitter->setOrientation(Qt::Vertical);
    leftSplitter->addWidget(glWidget);
    leftSplitter->addWidget(tabWidget);
    leftSplitter->setSizes({500,500});

    QSplitter* splitter = new QSplitter();
    splitter->addWidget(leftSplitter);
    splitter->addWidget(sidebarWidget);
    setCentralWidget(splitter);

    setWindowTitle(tr("OpenGL Window"));

    connect(sceneWidget, &SceneWidget::geometryUpdated, sidebarWidget, &SidebarWidget::loadGroups);
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