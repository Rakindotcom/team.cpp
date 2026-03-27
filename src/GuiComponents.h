#ifndef GUICOMPONENTS_H
#define GUICOMPONENTS_H

#include "raylib.h"
#include "GuiTheme.h"
#include <bits/stdc++.h>

using namespace std;

enum Icon {
    ICON_NONE,
    ICON_HOME,
    ICON_USER,
    ICON_SETTINGS
};

// Draw a primary action button
// Returns true if clicked
bool DrawButton(Rectangle bounds, string text);

// Draw a secondary/outline button
bool DrawButtonSecondary(Rectangle bounds, string text);

// Draw a card background with shadow
void DrawCard(Rectangle bounds);

// Draw a text input field
// buffer: string to store input
// active: whether this field currently has focus
// Returns true if content changed
bool DrawInput(Rectangle bounds, string& buffer, int maxLen, bool active);

// Draw a navigation tab/item
// Returns true if clicked
bool DrawNavButton(Rectangle bounds, string text, bool selected, Icon icon = ICON_NONE); // Icon is placeholder

// Draw a label with specific style
void DrawLabel(string text, Vector2 pos, int fontSize, Color color);

// Simple Header with Title
void DrawHeader(string title);

// Check collision with mouse
bool IsMouseOver(Rectangle bounds);

#endif
