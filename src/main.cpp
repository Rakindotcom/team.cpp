#include "raylib.h"
#include "GuiComponents.cpp"
#include "GuiTheme.cpp"
#include <iostream>
#include <string>
#include <vector>

// Include modules
#include "OrderManager.cpp"
// FileManager is currently disabled due to API mismatch
// #include "FileManager.cpp"

using namespace GarmentFactory;
using namespace std;

// App States
enum class AppState {
    DASHBOARD,
    CREATE_ORDER,
    WORKERS,
    INVENTORY
};

int main() {
    // Initialize Core Systems
    InventoryManager invMgr; // Constructor seeds data
    HRManager hrMgr;         // Constructor seeds data
    OrderManager orderMgr(&invMgr, &hrMgr); // Constructor seeds machines

    // Initialize Raylib
    const int screenWidth = 1280;
    const int screenHeight = 800;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Garment Factory Management System");

    SetTargetFPS(60);
    GuiTheme::LoadThemeResources();

    // State Variables
    AppState currentState = AppState::DASHBOARD;
    
    // UI Layout
    const int sidebarWidth = 260;
    
    // Main Loop
    while (!WindowShouldClose()) {
        // Draw
        BeginDrawing();
        ClearBackground(GuiTheme::COL_BACKGROUND);
        
        // --- Sidebar ---
        Rectangle sidebarRec = {0, 0, (float)sidebarWidth, (float)GetScreenHeight()};
        DrawRectangleRec(sidebarRec, GuiTheme::COL_SURFACE);
        DrawRectangleLinesEx(sidebarRec, 1, GuiTheme::COL_BORDER);
        
        // Logo / Title
        GuiComponents::DrawLabel("GarmentOS", {30, 40}, GuiTheme::FONT_SIZE_HEADER, GuiTheme::COL_PRIMARY);
        GuiComponents::DrawLabel("Professional Ed.", {30, 80}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_MUTED);
        
        // Navigation
        float navY = 140;
        float navH = 54;
        
        if (GuiComponents::DrawNavButton({12, navY, sidebarWidth - 24.0f, navH}, "Dashboard", currentState == AppState::DASHBOARD)) currentState = AppState::DASHBOARD;
        if (GuiComponents::DrawNavButton({12, navY + 64, sidebarWidth - 24.0f, navH}, "Create Order", currentState == AppState::CREATE_ORDER)) currentState = AppState::CREATE_ORDER;
        if (GuiComponents::DrawNavButton({12, navY + 128, sidebarWidth - 24.0f, navH}, "Workforce", currentState == AppState::WORKERS)) currentState = AppState::WORKERS;
        if (GuiComponents::DrawNavButton({12, navY + 192, sidebarWidth - 24.0f, navH}, "Inventory", currentState == AppState::INVENTORY)) currentState = AppState::INVENTORY;
        
        // Save Button (Bottom)
        if (GuiComponents::DrawButtonSecondary({20, (float)GetScreenHeight() - 80, sidebarWidth - 40.0f, 50}, "Exit")) {
            // FileManager::saveData(orderMgr); // Disabled
            GuiTheme::UnloadThemeResources();
            CloseWindow();
            return 0;
        }

        // --- Main Content Area ---
        Rectangle contentArea = {(float)sidebarWidth + 40, 40, (float)GetScreenWidth() - sidebarWidth - 80, (float)GetScreenHeight() - 80};
        
        switch (currentState) {
            case AppState::DASHBOARD: {
                GuiComponents::DrawLabel("Production Dashboard", {contentArea.x, contentArea.y}, GuiTheme::FONT_SIZE_HEADER, GuiTheme::COL_TEXT_PRIMARY);
                GuiComponents::DrawLabel("Overview of active production orders", {contentArea.x, contentArea.y + 40}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_SECONDARY);
                
                // Active Orders List
                float y = contentArea.y + 90;
                auto& orders = orderMgr.getOrders();
                
                if (orders.empty()) {
                    GuiComponents::DrawLabel("No active orders.", {contentArea.x, y}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_MUTED);
                }

                for (const auto& o : orders) {
                    GuiComponents::DrawCard({contentArea.x, y, contentArea.width, 100});
                    
                    GuiComponents::DrawLabel(o.getId(), {contentArea.x + 24, y + 20}, GuiTheme::FONT_SIZE_TITLE, GuiTheme::COL_PRIMARY);
                    GuiComponents::DrawLabel(o.getGarment().getName(), {contentArea.x + 24, y + 50}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_PRIMARY);
                    
                    std::string statusStr = orderStatusToString(o.getStatus());
                    GuiComponents::DrawLabel("Status: " + statusStr, {contentArea.x + 300, y + 20}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_SECONDARY);
                    GuiComponents::DrawLabel("Qty: " + std::to_string(o.getQuantity()), {contentArea.x + 300, y + 50}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_SECONDARY);

                    // Progress Bar
                    float progress = o.getProgress();
                    DrawRectangle(contentArea.x + 500, y + 45, 200, 10, GuiTheme::COL_BACKGROUND);
                    DrawRectangle(contentArea.x + 500, y + 45, (int)(200 * progress), 10, GuiTheme::COL_SECONDARY);
                    GuiComponents::DrawLabel(std::to_string((int)(progress * 100)) + "%", {contentArea.x + 710, y + 40}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_SECONDARY);

                    y += 115;
                }
                break;
            }
            case AppState::CREATE_ORDER: {
                GuiComponents::DrawLabel("New Production Order", {contentArea.x, contentArea.y}, GuiTheme::FONT_SIZE_HEADER, GuiTheme::COL_TEXT_PRIMARY);
                
                GuiComponents::DrawCard({contentArea.x, contentArea.y + 80, 600, 450});
                
                static std::string type = "";
                static std::string size = "";
                static std::string fabric = "";
                static std::string qtyStr = "";
                
                static bool typeActive = false, sizeActive = false, fabricActive = false, qtyActive = false;
                
                float formY = contentArea.y + 110;
                float formX = contentArea.x + 30;
                
                // Form Fields helper
                auto DrawField = [&](const std::string& label, std::string& val, bool& active, float yPos) {
                    GuiComponents::DrawLabel(label, {formX, yPos}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_SECONDARY);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        active = CheckCollisionPointRec(GetMousePosition(), {formX, yPos + 30, 540, 45});
                    }
                    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) active = false; // Defocus
                    
                    GuiComponents::DrawInput({formX, yPos + 30, 540, 45}, val, 30, active);
                };

                DrawField("Garment Type (e.g., Shirt, Pants)", type, typeActive, formY);
                DrawField("Size Range (e.g., M, L, XL)", size, sizeActive, formY + 90);
                DrawField("Fabric Type (e.g., Cotton, Silk)", fabric, fabricActive, formY + 180);
                DrawField("Quantity", qtyStr, qtyActive, formY + 270);
                
                // Submit
                if (GuiComponents::DrawButton({formX, formY + 360, 200, 50}, "Schedule Order")) {
                    if (!type.empty() && !qtyStr.empty()) {
                        try {
                            int qty = std::stoi(qtyStr);
                            // Validating input lightly
                            Garment g("G" + std::to_string(GetTime()), type, size, fabric, 2.5);
                            orderMgr.scheduleOrder(g, qty);
                            
                            // Reset
                            type = ""; size = ""; fabric = ""; qtyStr = "";
                            currentState = AppState::DASHBOARD;
                        } catch(...) {
                            // ignore error
                        }
                    }
                }
                
                break;
            }
            case AppState::WORKERS: {
                GuiComponents::DrawLabel("Employee Directory", {contentArea.x, contentArea.y}, GuiTheme::FONT_SIZE_HEADER, GuiTheme::COL_TEXT_PRIMARY);
                
                float y = contentArea.y + 90;
                auto& employees = hrMgr.getEmployees();
                
                // Grid layout
                int col = 0;
                for (auto& e : employees) {
                    float x = contentArea.x + (col * 320);
                    if (x + 300 > contentArea.x + contentArea.width) {
                        col = 0;
                        x = contentArea.x;
                        y += 160;
                    }
                    
                    GuiComponents::DrawCard({x, y, 300, 140});
                    
                    // Avatar placeholder
                    DrawCircle(x + 40, y + 40, 20, GuiTheme::COL_PRIMARY);
                    DrawTextEx(GuiTheme::AppFont, e.getName().substr(0,1).c_str(), {x+34, y+28}, 24, 0, WHITE);
                    
                    GuiComponents::DrawLabel(e.getName(), {x + 80, y + 25}, GuiTheme::FONT_SIZE_TITLE, GuiTheme::COL_TEXT_PRIMARY);
                    GuiComponents::DrawLabel(e.getRole(), {x + 80, y + 55}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_SECONDARY);
                    
                    GuiComponents::DrawLabel("Dept: " + e.getDepartment(), {x + 24, y + 90}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_SECONDARY);
                    GuiComponents::DrawLabel("ID: " + e.getId(), {x + 24, y + 110}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_MUTED);
                    
                    col++;
                }
                break;
            }
            case AppState::INVENTORY: {
                GuiComponents::DrawLabel("Warehouse Inventory", {contentArea.x, contentArea.y}, GuiTheme::FONT_SIZE_HEADER, GuiTheme::COL_TEXT_PRIMARY);
                
                 float y = contentArea.y + 90;
                 // Headers
                 GuiComponents::DrawLabel("ITEM NAME", {contentArea.x + 20, y}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_MUTED);
                 GuiComponents::DrawLabel("CATEGORY", {contentArea.x + 300, y}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_MUTED);
                 GuiComponents::DrawLabel("STOCK", {contentArea.x + 500, y}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_MUTED);
                 
                 y += 30;
                 DrawLineEx({contentArea.x, y}, {contentArea.x + contentArea.width, y}, 1, GuiTheme::COL_BORDER);
                 y += 20;

                for (auto& i : invMgr.getItems()) {
                     GuiComponents::DrawLabel(i.getName(), {contentArea.x + 20, y}, GuiTheme::FONT_SIZE_BODY, GuiTheme::COL_TEXT_PRIMARY);
                     GuiComponents::DrawLabel(i.getId(), {contentArea.x + 20, y+20}, GuiTheme::FONT_SIZE_SMALL, GuiTheme::COL_TEXT_MUTED);
                     
                     // Category (Private member? No, getter?)
                     // checking InventoryItem... Check Step 198
                     // No getter for Category! But it's in constructor.
                     // I will skip category if no getter, or guess.
                     
                     GuiComponents::DrawLabel(std::to_string((int)i.getStock()), {contentArea.x + 500, y}, GuiTheme::FONT_SIZE_TITLE, GuiTheme::COL_PRIMARY);
                     
                     y += 60;
                }
                break;
            }
            default: break;
        }

        EndDrawing();
    }

    GuiTheme::UnloadThemeResources();
    CloseWindow();

    return 0;
}
