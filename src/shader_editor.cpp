#include "shader_editor.h"

ShaderEditor::ShaderEditor() {
    layout = new QVBoxLayout();
    textArea = new QTextEdit();
    errorArea = new QTextEdit();
    textArea->setAcceptRichText(false);
    errorArea->setReadOnly(true);

    layout->addWidget(textArea);
    layout->addWidget(errorArea);
    setLayout(layout);

    connect(textArea, &QTextEdit::textChanged, this, &ShaderEditor::onTextChange);
}

QString ShaderEditor::testShaderSource(const QString& source) {
    bool success = testProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, source);
    if (success) return "";
    return testProgram.log();
}

void ShaderEditor::onTextChange() {
    QString error = testShaderSource(textArea->toPlainText());
    if (error.size() > 0) {
        errorArea->setPlainText(error);
    } else {
        errorArea->setPlainText("No errors.");
    }
}
