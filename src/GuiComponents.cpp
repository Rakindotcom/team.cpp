#include "GuiComponents.h"

bool IsMouseOver(Rectangle bounds) {
    return CheckCollisionPointRec(GetMousePosition(), bounds);
}

// Helper for centering text
void DrawTextCentered(string text, Rectangle bounds, int fontSize, Color color) {
    Vector2 textSize = MeasureTextEx(AppFont, text.c_str(), fontSize, 1.0f);
    Vector2 pos = {
        bounds.x + (bounds.width - textSize.x) / 2.0f,
        bounds.y + (bounds.height - textSize.y) / 2.0f
    };
    DrawTextEx(AppFont, text.c_str(), pos, fontSize, 1.0f, color);
}

bool DrawButton(Rectangle bounds, string text) {
    bool hovered = IsMouseOver(bounds);
    bool clicked = false;
    
    Color bg = hovered ? COL_PRIMARY_HOVER : COL_PRIMARY;
    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) clicked = true;

    // Subtle Shadow
    DrawRectangleRounded({bounds.x, bounds.y + 2, bounds.width, bounds.height}, BORDER_RADIUS/bounds.height, 10, COL_SHADOW);
    
    // Background
    DrawRectangleRounded(bounds, BORDER_RADIUS/bounds.height, 10, bg);
    
    DrawTextCentered(text, bounds, FONT_SIZE_BODY, WHITE);
    
    return clicked;
}

bool DrawButtonSecondary(Rectangle bounds, string text) {
    bool hovered = IsMouseOver(bounds);
    bool clicked = false;
    
    Color bg = hovered ? COL_SURFACE_HOVER : COL_SURFACE;
    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) clicked = true;

    DrawRectangleRounded(bounds, BORDER_RADIUS/bounds.height, 10, bg);
    DrawRectangleRoundedLinesEx(bounds, BORDER_RADIUS/bounds.height, 10, 1.5f, COL_BORDER);
    
    DrawTextCentered(text, bounds, FONT_SIZE_BODY, COL_TEXT_PRIMARY);
    
    return clicked;
}

void DrawCard(Rectangle bounds) {
    DrawRectangleRounded({bounds.x, bounds.y + 2, bounds.width, bounds.height}, BORDER_RADIUS/bounds.height, 10, COL_SHADOW);
    DrawRectangleRounded(bounds, BORDER_RADIUS/bounds.height, 10, COL_SURFACE);
    DrawRectangleRoundedLinesEx(bounds, BORDER_RADIUS/bounds.height, 10, 1.0f, COL_BORDER);
}

bool DrawInput(Rectangle bounds, string& buffer, int maxLen, bool active) {
    bool changed = false;
    
    Color bg = COL_BACKGROUND; // Input usually darker/inset
    Color border = active ? COL_PRIMARY : COL_BORDER;
    
    DrawRectangleRounded(bounds, BORDER_RADIUS/bounds.height, 6, bg);
    DrawRectangleRoundedLinesEx(bounds, BORDER_RADIUS/bounds.height, 6, active ? 2.0f : 1.0f, border);
    
    if (active) {
        int key = GetCharPressed();
        while (key > 0) {
            if ((key >= 32) && (key <= 125) && (buffer.length() < maxLen)) {
                buffer += (char)key;
                changed = true;
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
             if (buffer.length() > 0) {
                buffer.pop_back();
                changed = true;
            }
        }
    }
    
    Vector2 textSize = MeasureTextEx(AppFont, buffer.c_str(), FONT_SIZE_BODY, 1.0f);
    float textY = bounds.y + (bounds.height - textSize.y) / 2.0f;
    DrawTextEx(AppFont, buffer.c_str(), {bounds.x + 12, textY}, FONT_SIZE_BODY, 1.0f, COL_TEXT_PRIMARY);
    
    if (active && ((int)(GetTime() * 2.0f) % 2 == 0)) {
        DrawRectangle(bounds.x + 12 + textSize.x + 2, bounds.y + 10, 2, bounds.height - 20, COL_PRIMARY);
    }

    return changed;
}

bool DrawNavButton(Rectangle bounds, string text, bool selected, Icon icon) {
    bool hovered = IsMouseOver(bounds);
    
    Color bg = selected ? COL_SURFACE_HOVER : (hovered ? Fade(COL_SURFACE_HOVER, 0.5f) : BLANK);
    Color textColor = selected ? COL_PRIMARY : COL_TEXT_SECONDARY;
    
    if (selected || hovered) {
         DrawRectangleRounded(bounds, BORDER_RADIUS/bounds.height, 10, bg);
    }
    if (selected) {
         DrawRectangle(bounds.x, bounds.y + 10, 3, bounds.height - 20, COL_PRIMARY);
    }

    if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;

    DrawTextEx(AppFont, text.c_str(), {bounds.x + 24, bounds.y + (bounds.height - FONT_SIZE_BODY)/2.0f}, FONT_SIZE_BODY, 1.0f, textColor);
    return false;
}

void DrawLabel(string text, Vector2 pos, int fontSize, Color color) {
    DrawTextEx(AppFont, text.c_str(), pos, fontSize, 1.0f, color);
}

void DrawHeader(string title) {
     Vector2 size = MeasureTextEx(AppFont, title.c_str(), FONT_SIZE_HEADER, 1.0f);
     DrawTextEx(AppFont, title.c_str(), {1280/2 - size.x/2, 20}, FONT_SIZE_HEADER, 1.0f, COL_TEXT_PRIMARY);
}
