#ifndef SHADER_EDITOR_H
#define SHADER_EDITOR_H

#include <QTextEdit>
#include <QWidget>
#include <QOpenGLShaderProgram>
#include <QLayout>

class ShaderEditor: public QWidget {
    public:
        ShaderEditor();

        QString testShaderSource(const QString& source);
        void onTextChange();

    private:
        QOpenGLShaderProgram testProgram;
        QLayout* layout;

        QSplitter* textSplitter;
        QTextEdit* textArea;
        QTextEdit* errorArea;

};

#endif