#include "shader_selector.h"

ShaderSelector::ShaderSelector(ShaderLibrary* library) {
    _library = library;
    load();
    connect(library, &ShaderLibrary::updated, this, &ShaderSelector::load);
}

void ShaderSelector::load() {
    bool before = blockSignals(true); //to avoid event loops
    clear();
    blockSignals(before);

    for (int i=0; i<_library->size(); i++) {
        addItem(_library->at(i).name());
    }
    addItem("New shader");
    setCurrentIndex(_selection);
}