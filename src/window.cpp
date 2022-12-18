// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include "sidebar_widget.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include <QSplitter>

Window::Window(MainWindow *mw)
    : mainWindow(mw)
{
    glWidget = new GLWidget;

    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    dockBtn = new QPushButton(tr("Undock"), this);

    connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
    connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
    connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
    connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
    connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
    connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);
    connect(dockBtn, &QPushButton::clicked, this, &Window::dockUndock);

    QVBoxLayout *sidebarLayout = new QVBoxLayout();
    sidebarLayout->addWidget(xSlider);
    sidebarLayout->addWidget(ySlider);
    sidebarLayout->addWidget(zSlider);
    sidebarLayout->addWidget(dockBtn);
    sidebarLayout->addStretch();

    SidebarWidget *sidebarWidget = new SidebarWidget();
    sidebarWidget->setLayout(sidebarLayout);

    QSplitter* splitter = new QSplitter();
    splitter->addWidget(glWidget);
    splitter->addWidget(sidebarWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(splitter);
    setLayout(mainLayout);
    //mw->setCentralWidget(glWidget);

    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);

    setWindowTitle(tr("OpenGL Window"));
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

void Window::dockUndock()
{
    if (parent()) {
        setParent(nullptr);
        setAttribute(Qt::WA_DeleteOnClose);
        move(QGuiApplication::primaryScreen()->size().width() / 2 - width() / 2,
             QGuiApplication::primaryScreen()->size().height() / 2 - height() / 2);
        dockBtn->setText(tr("Dock"));
        show();
    } else {
        if (!mainWindow->centralWidget()) {
            if (mainWindow->isVisible()) {
                setAttribute(Qt::WA_DeleteOnClose, false);
                dockBtn->setText(tr("Undock"));
                mainWindow->setCentralWidget(this);
            } else {
                QMessageBox::information(nullptr, tr("Cannot dock"),
                                         tr("Main window already closed"));
            }
        } else {
            QMessageBox::information(nullptr, tr("Cannot dock"),
                                     tr("Main window already occupied"));
        }
    }
}
