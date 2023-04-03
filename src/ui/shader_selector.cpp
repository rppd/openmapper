#include "shader_selector.h"

ShaderSelector::ShaderSelector(ShaderLibrary* library) {
    _library = library;
    load();
    connect(_library, &ShaderLibrary::updated, this, &ShaderSelector::load);
}

void ShaderSelector::load() {
    bool before = blockSignals(true);
    const QString& nameBefore = currentText();
    clear();
    blockSignals(before);
    
    for (int i=0; i<_library->size(); i++) {
        addItem(_library->at(i).name());
    }
    if(_newShaderOption) addItem("New shader");
    setCurrentText(nameBefore);
}

Shader& ShaderSelector::selection() const {
    return _library->at(currentIndex());
}