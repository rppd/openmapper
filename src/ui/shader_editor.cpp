#include "shader_editor.h"

ShaderEditor::ShaderEditor(ShaderLibrary* library): shaderLibrary(library) {
    layout = new QVBoxLayout();
    saveLayout = new QHBoxLayout();
    splitter = new QSplitter(Qt::Vertical);
    textArea = new QTextEdit();
    errorArea = new QTextEdit();
    nameInput = new QLineEdit();
    saveButton = new QPushButton("Save");
    deleteButton = new QPushButton("Delete");
    shaderSelector = new ShaderSelector(shaderLibrary);
    shaderSelector->newShaderOption(true);
    
    saveLayout->addWidget(nameInput);
    saveLayout->addWidget(saveButton);
    saveLayout->addWidget(deleteButton);
    
    textArea->setAcceptRichText(false);
    errorArea->setReadOnly(true);
    errorArea->setBaseSize(10,100);

    layout->addWidget(shaderSelector);
    layout->addLayout(saveLayout);
    splitter->addWidget(textArea);
    splitter->addWidget(errorArea);
    splitter->setSizes({400,100});
    layout->addWidget(splitter);
    setLayout(layout);

    connect(textArea, &QTextEdit::textChanged, this, &ShaderEditor::onTextChange);
    connect(shaderSelector, &QComboBox::currentTextChanged, this, &ShaderEditor::selectShaderByName);
    connect(saveButton, &QPushButton::pressed, this, &ShaderEditor::save);
    connect(deleteButton, &QPushButton::pressed, this, &ShaderEditor::deleteShader);
    connect(nameInput, &QLineEdit::returnPressed, this, &ShaderEditor::save);
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

void ShaderEditor::selectShader(const int index) {
    selectedShaderIndex = index;
    Shader& shader = shaderLibrary->at(selectedShaderIndex);
    nameInput->setText(shader.name());
    textArea->setPlainText(shader.source());
    errorArea->setPlainText("");
}

void ShaderEditor::selectShaderByName(const QString& shaderName) {
    int index = shaderLibrary->shaderIndex(shaderName);
    if (index == -1) {
        shaderLibrary->addShader(Shader(shaderName));
        index = shaderLibrary->size()-1;
    }
    selectShader(index);
}

void ShaderEditor::keyPressEvent(QKeyEvent* event) {
    const QKeyCombination& comb = event->keyCombination();
    if (comb.key() == Qt::Key_S && comb.keyboardModifiers() == Qt::ControlModifier) {
        save();
    }
}

bool ShaderEditor::event(QEvent* event) {
    // if (event->type() == QEvent::KeyPress) {
    //     QKeyEvent* keyEvent = (QKeyEvent*) event;
    //     QKeyCombination comb = keyEvent->keyCombination();
    //     std::cout << comb.key() << std::endl;
    //     if (comb.key() == Qt::Key_S && comb.keyboardModifiers() == Qt::Key_Control) {
    //         std::cout << "saving ?" << std::endl;
    //     }
    // }
    // std::cout << "shader editor event" << std::endl;
    return QWidget::event(event);
}

void ShaderEditor::save() const {
    QString currentName = shaderLibrary->at(selectedShaderIndex).name();
    QString newName = nameInput->text();
    if (currentName != newName) {
        shaderLibrary->rename(selectedShaderIndex, newName);
    }
    errorArea -> setPlainText("Saving shader...");
    shaderLibrary->saveShaderCode(selectedShaderIndex,textArea->toPlainText());
    errorArea -> setPlainText("Shader saved.");
}

void ShaderEditor::deleteShader() {
    shaderLibrary->destroy(selectedShaderIndex);
}