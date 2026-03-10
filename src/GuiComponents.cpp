#include "GuiComponents.h"

namespace GuiComponents {

    bool IsMouseOver(Rectangle bounds) {
        return CheckCollisionPointRec(GetMousePosition(), bounds);
    }

    // Helper for centering text
    void DrawTextCentered(const std::string& text, Rectangle bounds, int fontSize, Color color) {
        Vector2 textSize = MeasureTextEx(GuiTheme::AppFont, text.c_str(), fontSize, 1.0f);
        Vector2 pos = {
            bounds.x + (bounds.width - textSize.x) / 2.0f,
            bounds.y + (bounds.height - textSize.y) / 2.0f
        };
        DrawTextEx(GuiTheme::AppFont, text.c_str(), pos, fontSize, 1.0f, color);
    }

    bool DrawButton(Rectangle bounds, const std::string& text) {
        bool hovered = IsMouseOver(bounds);
        bool clicked = false;
        
        Color bg = hovered ? GuiTheme::COL_PRIMARY_HOVER : GuiTheme::COL_PRIMARY;
        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) clicked = true;

        // Subtle Shadow
        DrawRectangleRounded({bounds.x, bounds.y + 2, bounds.width, bounds.height}, GuiTheme::BORDER_RADIUS/bounds.height, 10, GuiTheme::COL_SHADOW);
        
        // Background
        DrawRectangleRounded(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 10, bg);
        
        DrawTextCentered(text, bounds, GuiTheme::FONT_SIZE_BODY, WHITE);
        
        return clicked;
    }

    bool DrawButtonSecondary(Rectangle bounds, const std::string& text) {
        bool hovered = IsMouseOver(bounds);
        bool clicked = false;
        
        Color bg = hovered ? GuiTheme::COL_SURFACE_HOVER : GuiTheme::COL_SURFACE;
        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) clicked = true;

        DrawRectangleRounded(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 10, bg);
        DrawRectangleRoundedLinesEx(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 10, 1.5f, GuiTheme::COL_BORDER);
        
        DrawTextCentered(text, bounds, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_PRIMARY);
        
        return clicked;
    }

    void DrawCard(Rectangle bounds) {
        DrawRectangleRounded({bounds.x, bounds.y + 2, bounds.width, bounds.height}, GuiTheme::BORDER_RADIUS/bounds.height, 10, GuiTheme::COL_SHADOW);
        DrawRectangleRounded(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 10, GuiTheme::COL_SURFACE);
        DrawRectangleRoundedLinesEx(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 10, 1.0f, GuiTheme::COL_BORDER);
    }

    bool DrawInput(Rectangle bounds, std::string& buffer, int maxLen, bool active) {
        bool changed = false;
        
        Color bg = GuiTheme::COL_BACKGROUND; // Input usually darker/inset
        Color border = active ? GuiTheme::COL_PRIMARY : GuiTheme::COL_BORDER;
        
        DrawRectangleRounded(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 6, bg);
        DrawRectangleRoundedLinesEx(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 6, active ? 2.0f : 1.0f, border);
        
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
        
        Vector2 textSize = MeasureTextEx(GuiTheme::AppFont, buffer.c_str(), GuiTheme::FONT_SIZE_BODY, 1.0f);
        float textY = bounds.y + (bounds.height - textSize.y) / 2.0f;
        DrawTextEx(GuiTheme::AppFont, buffer.c_str(), {bounds.x + 12, textY}, GuiTheme::FONT_SIZE_BODY, 1.0f, GuiTheme::COL_TEXT_PRIMARY);
        
        if (active && ((int)(GetTime() * 2.0f) % 2 == 0)) {
            DrawRectangle(bounds.x + 12 + textSize.x + 2, bounds.y + 10, 2, bounds.height - 20, GuiTheme::COL_PRIMARY);
        }

        return changed;
    }

    bool DrawNavButton(Rectangle bounds, const std::string& text, bool selected, Icon icon) {
        bool hovered = IsMouseOver(bounds);
        
        Color bg = selected ? GuiTheme::COL_SURFACE_HOVER : (hovered ? Fade(GuiTheme::COL_SURFACE_HOVER, 0.5f) : BLANK);
        Color textColor = selected ? GuiTheme::COL_PRIMARY : GuiTheme::COL_TEXT_SECONDARY;
        
        if (selected || hovered) {
             DrawRectangleRounded(bounds, GuiTheme::BORDER_RADIUS/bounds.height, 10, bg);
        }
        if (selected) {
             DrawRectangle(bounds.x, bounds.y + 10, 3, bounds.height - 20, GuiTheme::COL_PRIMARY);
        }

        if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return true;

        DrawTextEx(GuiTheme::AppFont, text.c_str(), {bounds.x + 24, bounds.y + (bounds.height - GuiTheme::FONT_SIZE_BODY)/2.0f}, GuiTheme::FONT_SIZE_BODY, 1.0f, textColor);
        return false;
    }

    void DrawLabel(const std::string& text, Vector2 pos, int fontSize, Color color) {
        DrawTextEx(GuiTheme::AppFont, text.c_str(), pos, fontSize, 1.0f, color);
    }
    
    void DrawHeader(const std::string& title) {
         Vector2 size = MeasureTextEx(GuiTheme::AppFont, title.c_str(), GuiTheme::FONT_SIZE_HEADER, 1.0f);
         DrawTextEx(GuiTheme::AppFont, title.c_str(), {1280/2 - size.x/2, 20}, GuiTheme::FONT_SIZE_HEADER, 1.0f, GuiTheme::COL_TEXT_PRIMARY);
    }

}
