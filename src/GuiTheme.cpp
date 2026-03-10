#include "GuiTheme.h"
#include <iostream>

namespace GuiTheme {
    Font AppFont = { 0 };

    void LoadThemeResources() {
        // Load the font with bilinear filtering for smoothness
        // Assuming OBJECTSANSREGULAR.OTF is in the working directory
        AppFont = LoadFontEx("OBJECTSANSREGULAR.OTF", 64, 0, 0); // Load high res
        SetTextureFilter(AppFont.texture, TEXTURE_FILTER_BILINEAR);
        std::cout << "GuiTheme: Font Loaded" << std::endl;
    }

    void UnloadThemeResources() {
        if (IsFontValid(AppFont)) {
            UnloadFont(AppFont);
        }
    }
}
