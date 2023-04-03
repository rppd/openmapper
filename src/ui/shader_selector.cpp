#include "shader_selector.h"

ShaderSelector::ShaderSelector(ShaderLibrary* library) {
    _library = library;
    load();
    connect(_library, &ShaderLibrary::updated, this, &ShaderSelector::load);
}

void ShaderSelector::load() {
    blockSignals(true);
    const QString& nameBefore = currentText();
    std::cout << "Loading shaders, will restore selection to " << nameBefore.toStdString() << "." << std::endl;
    clear();
    
    for (int i=0; i<_library->size(); i++) {
        addItem(_library->at(i).name());
    }
    if(_newShaderOption) addItem("New shader");
    blockSignals(false);
    if (nameBefore != "New Shader") setCurrentText(nameBefore); //needs fixing (event loops)

    std::cout << "Loaded shaders and restored selection to " << nameBefore.toStdString() << "." << std::endl;
}

Shader& ShaderSelector::selection() const {
    return _library->at(currentIndex());
}