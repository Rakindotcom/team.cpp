#include "GuiTheme.h"
#include <bits/stdc++.h>

using namespace std;

Font AppFont = { 0 };

void LoadThemeResources() {
    // Load the font with bilinear filtering for smoothness
    // Assuming OBJECTSANSREGULAR.OTF is in the working directory
    AppFont = LoadFontEx("OBJECTSANSREGULAR.OTF", 64, 0, 0); // Load high res
    SetTextureFilter(AppFont.texture, TEXTURE_FILTER_BILINEAR);
    cout << "GuiTheme: Font Loaded" << endl;
}

void UnloadThemeResources() {
    if (IsFontValid(AppFont)) {
        UnloadFont(AppFont);
    }
}
