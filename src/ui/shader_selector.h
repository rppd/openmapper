#ifndef SHADER_SELECTOR_H
#define SHADER_SELECTOR_H

#include "../gl/shader_library.h"

#include <QComboBox>

class ShaderSelector: public QComboBox {
    Q_OBJECT

    public:
        ShaderSelector(ShaderLibrary* library);

        int selection() const { return _selection; };
        void selection(int aselection) { _selection = aselection; };

        void load();
        
    private:
        ShaderLibrary* _library;
        int _selection = -1;
};

#endif