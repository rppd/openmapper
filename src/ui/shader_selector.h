#ifndef SHADER_SELECTOR_H
#define SHADER_SELECTOR_H

#include "../gl/shader_library.h"

#include <QComboBox>

class ShaderSelector: public QComboBox {
    Q_OBJECT

    public:
        ShaderSelector(ShaderLibrary* library);

        Shader& selection() const;
        bool newShaderOption() const { return _newShaderOption; };
        void newShaderOption(bool newShaderOption) { _newShaderOption = newShaderOption; };

        void load();
        
    private:
        ShaderLibrary* _library;
        int _selection = -1;
        bool _newShaderOption = false;
};

#endif