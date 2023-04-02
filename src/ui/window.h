// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QTabWidget>
#include <QSplitter>

#include <iostream>

#include "sidebar_widget.h"
#include "glwidget.h"
#include "scene_widget.h"
#include "shader_editor.h"


class SidebarWidget;

class Window : public QMainWindow
{
public:
    Window();

    QSlider* createSlider(int min, int max);
    QSlider* createAngleSlider();

private:
    SceneWidget* sceneWidget;
    GLWidget* glWidget;
    SidebarWidget* sidebarWidget;
    QTabWidget* tabWidget;
    ShaderEditor* shaderEditor;

    ShaderLibrary* shaderLibrary; //all pointers because qt objects have to be on the heap "by design" apparently
};

#endif
