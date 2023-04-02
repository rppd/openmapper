#ifndef SHADER_EDITOR_H
#define SHADER_EDITOR_H

#include "../gl/shader_library.h"
#include "../ui/shader_selector.h"

#include <QTextEdit>
#include <QWidget>
#include <QOpenGLShaderProgram>
#include <QLayout>
#include <QSplitter>
#include <QComboBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QPushButton>

class ShaderEditor: public QWidget {
    public:
        ShaderEditor(ShaderLibrary* library);

        QString testShaderSource(const QString& source);
        void onTextChange();

        void save() const;
        void deleteShader();
        void keyPressEvent(QKeyEvent* event) override;
        bool event(QEvent* event) override;

    public slots:
        void reloadLibrary();
        void selectShader(const int index);
        void selectShaderByName(const QString& shaderName);

    private:
        QOpenGLShaderProgram testProgram;

        QVBoxLayout* layout;
        QHBoxLayout* saveLayout;
        QSplitter* textSplitter;
        QTextEdit* textArea;
        QTextEdit* errorArea;
        QSplitter* splitter;
        ShaderSelector* shaderSelector;
        QLineEdit* nameInput;
        QPushButton* saveButton;
        QPushButton* deleteButton;

        ShaderLibrary* shaderLibrary;
        int selectedShaderIndex;
};

#endif