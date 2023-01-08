#include "sidebar_widget.h"
#include "glwidget.h"
#include "window.h"

#include <QSlider>

QSize SidebarWidget::sizeHint() {
    return QSize(500,1000);
}

int SidebarWidget::minimumWidth() {
    return 600;
}

SidebarWidget::SidebarWidget(Window* window, GLWidget* glWidget) {
    slider = window->createAngleSlider();
    
    layout = new QVBoxLayout();
    layout->addWidget(slider);
    layout->addStretch();
    setLayout(layout);
}