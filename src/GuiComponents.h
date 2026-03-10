#pragma once
#include "raylib.h"
#include "GuiTheme.h"
#include <string>

namespace GuiComponents {
    
    enum Icon {
        ICON_NONE,
        ICON_HOME,
        ICON_USER,
        ICON_SETTINGS
    };
    
    // Draw a primary action button
    // Returns true if clicked
    bool DrawButton(Rectangle bounds, const std::string& text);

    // Draw a secondary/outline button
    bool DrawButtonSecondary(Rectangle bounds, const std::string& text);

    // Draw a card background with shadow
    void DrawCard(Rectangle bounds);

    // Draw a text input field
    // buffer: string to store input
    // active: whether this field currently has focus
    // Returns true if content changed
    bool DrawInput(Rectangle bounds, std::string& buffer, int maxLen, bool active);

    // Draw a navigation tab/item
    // Returns true if clicked
    bool DrawNavButton(Rectangle bounds, const std::string& text, bool selected, Icon icon = ICON_NONE); // Icon is placeholder

    // Draw a label with specific style
    void DrawLabel(const std::string& text, Vector2 pos, int fontSize, Color color);

    // Simple Header with Title
    void DrawHeader(const std::string& title);

    // Check collision with mouse
    bool IsMouseOver(Rectangle bounds);
}
