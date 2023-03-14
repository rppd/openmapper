// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QSlider>

#include "sidebar_widget.h"
#include "glwidget.h"
#include "scene_widget.h"
#include "iostream"

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
};

#endif