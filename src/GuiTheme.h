#pragma once
#include "raylib.h"

namespace GuiTheme {
    // Global Font
    extern Font AppFont;
    
    void LoadThemeResources();
    void UnloadThemeResources();

    // Professional Modern Dark Palette (Slate/Blue)
    // Backgrounds
    const Color COL_BACKGROUND = { 15, 23, 42, 255 };      // Slate 900
    const Color COL_SURFACE    = { 30, 41, 59, 255 };      // Slate 800
    const Color COL_SURFACE_HOVER = { 51, 65, 85, 255 };   // Slate 700
    
    // Accents
    const Color COL_PRIMARY       = { 59, 130, 246, 255 }; // Blue 500
    const Color COL_PRIMARY_HOVER = { 37, 99, 235, 255 };  // Blue 600
    const Color COL_SECONDARY     = { 16, 185, 129, 255 }; // Emerald 500
    const Color COL_ACCENT        = { 239, 68, 68, 255 };  // Red 500
    
    // Text
    const Color COL_TEXT_PRIMARY   = { 248, 250, 252, 255 }; // Slate 50
    const Color COL_TEXT_SECONDARY = { 148, 163, 184, 255 }; // Slate 400
    const Color COL_TEXT_MUTED     = { 71, 85, 105, 255 };   // Slate 600

    // UI Elements
    const Color COL_BORDER = { 51, 65, 85, 255 };            // Slate 700
    const Color COL_SHADOW = { 0, 0, 0, 80 };                // Subtle shadow

    // Dimensions
    const int PADDING = 24;
    const float BORDER_RADIUS = 6.0f;
    const int FONT_SIZE_HEADER = 36;
    const int FONT_SIZE_TITLE = 20;
    const int FONT_SIZE_BODY = 16;
    const int FONT_SIZE_SMALL = 13;

    // Helper
    inline Color GetColorAlpha(Color c, float alpha) {
        return Fade(c, alpha);
    }
}
