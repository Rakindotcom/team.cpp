#include "raylib.h"
#include "GuiTheme.h"
#include "GuiComponents.h"

// Include All New Modules
#include "User.cpp"
#include "OrderManager.cpp" 
// (OrderManager includes HR, Inventory, Quality, etc via headers or we include them here if needed for direct access)

using namespace GarmentFactory;
using namespace GuiComponents;

// Global State
User currentUser;
bool isLoggedIn = false;

InventoryManager invMgr;
HRManager hrMgr;
QualityManager qcMgr;
OrderManager orderMgr(&invMgr, &hrMgr); // Production Manager

enum class Screen {
    LOGIN,
    DASHBOARD,
    HR,
    PRODUCTION,
    INVENTORY,
    QUALITY
};

Screen currentScreen = Screen::LOGIN;

// Input Buffers
std::string loginUser = "";
std::string loginPass = "";
bool userActive = false;
bool passActive = false;

std::string orderItemInput = "";
std::string orderQtyInput = "";

// --- Screens ---

void DrawLogin() {
    int w = 400;
    int h = 350;
    
    Rectangle panel = { (float)GetScreenWidth()/2 - w/2, (float)GetScreenHeight()/2 - h/2, (float)w, (float)h };
    DrawCard(panel);
    
    DrawText("System Login", panel.x + 20, panel.y + 20, 32, GuiTheme::COL_PRIMARY);
    
    DrawLabel("Username", {panel.x + 20, panel.y + 80}, 20, GRAY);
    if(DrawInput({panel.x + 20, panel.y + 105, 360, 40}, loginUser, 20, userActive)) {
        userActive = true; passActive = false;
    }

    DrawLabel("Password", {panel.x + 20, panel.y + 160}, 20, GRAY);
    if(DrawInput({panel.x + 20, panel.y + 185, 360, 40}, loginPass, 20, passActive)) {
        passActive = true; userActive = false;
    }
    
    if(DrawButton({panel.x + 20, panel.y + 260, 360, 50}, "Login")) {
        // Mock Login
        if(loginUser == "admin" && loginPass == "admin") {
            currentUser = User("U01", "Admin", "admin", "Admin", "admin@factory.com");
            isLoggedIn = true;
            currentScreen = Screen::DASHBOARD;
        }
    }
    
    DrawLabel("Hint: admin / admin", {panel.x + 20, panel.y + 320}, 14, DARKGRAY);
}

void DrawSidebar() {
    int w = 220;
    DrawRectangle(0, 0, w, GetScreenHeight(), GuiTheme::COL_SURFACE);
    
    DrawText("FactoryOS", 40, 40, 32, GuiTheme::COL_PRIMARY);
    
    int y = 120;
    if(DrawNavButton({10, (float)y, 200, 45}, "Dashboard", currentScreen == Screen::DASHBOARD, ICON_HOME)) currentScreen = Screen::DASHBOARD;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "Production", currentScreen == Screen::PRODUCTION, ICON_USER)) currentScreen = Screen::PRODUCTION;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "HR & Shifts", currentScreen == Screen::HR, ICON_USER)) currentScreen = Screen::HR;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "Inventory", currentScreen == Screen::INVENTORY, ICON_SETTINGS)) currentScreen = Screen::INVENTORY;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "Quality", currentScreen == Screen::QUALITY, ICON_SETTINGS)) currentScreen = Screen::QUALITY;
    
    // User Info
    DrawLabel(currentUser.getUsername(), {20, (float)GetScreenHeight() - 60}, 20, WHITE);
    DrawLabel(currentUser.getRole(), {20, (float)GetScreenHeight() - 40}, 14, GRAY);
    
    if(DrawButtonSecondary({140, (float)GetScreenHeight() - 50, 60, 30}, "Exit")) {
        currentScreen = Screen::LOGIN;
        isLoggedIn = false;
        loginPass = "";
    }
}

void DrawProduction() {
    DrawHeader("Production Management");
    
    // Overview
    DrawCard({260, 100, 200, 100});
    DrawLabel("Active Batches", {280, 120}, 20, GRAY);
    DrawLabel(std::to_string(orderMgr.getOrders().size()), {280, 150}, 40, GuiTheme::COL_PRIMARY);
    
    DrawCard({480, 100, 200, 100});
    DrawLabel("Machines Active", {500, 120}, 20, GRAY);
    DrawLabel(std::to_string(orderMgr.getMachines().size()), {500, 150}, 40, GuiTheme::COL_SECONDARY);

    // Create Order
    static bool itemActive=false;
    static bool qtyActive=false;
    DrawLabel("New Batch:", {260, 240}, 20, WHITE);
    
    DrawInput({260, 270, 200, 40}, orderItemInput, 20, itemActive);
    DrawInput({480, 270, 100, 40}, orderQtyInput, 10, qtyActive);
    
    if(DrawButton({600, 270, 100, 40}, "Schedule")) {
        if(!orderItemInput.empty()) {
            Garment g("G01", orderItemInput, "L", "Cotton", 2.0);
            try {
                int q = std::stoi(orderQtyInput);
                orderMgr.scheduleOrder(g, q);
            } catch(...) {}
        }
    }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(GetMousePosition(), {260,270,200,40})) itemActive=true; else itemActive=false;
        if(CheckCollisionPointRec(GetMousePosition(), {480,270,100,40})) qtyActive=true; else qtyActive=false;
    }
    
    // List
    int y = 350;
    DrawLabel("#  Garment  Qty  Status  Progress", {270, (float)y-30}, 16, GRAY);
    for(auto& o : orderMgr.getOrders()) {
        DrawRectangleRounded({260, (float)y, 800, 50}, 0.2, 4, GuiTheme::COL_SURFACE);
        
        DrawLabel(o.getId(), {280, (float)y+15}, 16, WHITE);
        DrawLabel(o.getGarment().getName(), {350, (float)y+15}, 16, WHITE);
        DrawLabel(std::to_string(o.getQuantity()), {500, (float)y+15}, 16, WHITE);
        
        // Progress
        DrawRectangle(600, y+20, 100, 10, BLACK);
        DrawRectangle(600, y+20, 100 * o.getProgress(), 10, GuiTheme::COL_PRIMARY);
        
        y += 60;
    }
}

void DrawHR() {
    DrawHeader("Human Resources");
    
    int y = 100;
    int x = 260;
    for(auto& emp : hrMgr.getEmployees()) {
        DrawCard({(float)x, (float)y, 250, 150});
        DrawLabel(emp.getName(), {(float)x+20, (float)y+20}, 20, GuiTheme::COL_PRIMARY);
        DrawLabel(emp.getRole(), {(float)x+20, (float)y+50}, 16, GRAY);
        DrawLabel(emp.getId(), {(float)x+20, (float)y+80}, 14, DARKGRAY);
        DrawLabel("Load: " + std::to_string(emp.getLoad()) + "%", {(float)x+20, (float)y+110}, 16, WHITE);
        
        x += 270;
        if(x > 1000) { x = 260; y += 170; }
    }
}

void DrawMain() {
    switch(currentScreen) {
        case Screen::DASHBOARD: 
            DrawHeader("Executive Dashboard"); 
            DrawCard({260,100,400,200});
            DrawLabel("Welcome back,", {280, 130}, 24, GRAY);
            DrawLabel(currentUser.getUsername(), {280, 170}, 40, GuiTheme::COL_PRIMARY);
            break;
        case Screen::PRODUCTION: DrawProduction(); break;
        case Screen::HR: DrawHR(); break;
        case Screen::INVENTORY: DrawInventory(); break; 
        case Screen::QUALITY: DrawQuality(); break;
    }
}

int main() {
    InitWindow(1280, 720, "FactoryOS (UML v2)");
    SetTargetFPS(60);
    
    GuiTheme::LoadThemeResources();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if(isLoggedIn) {
            orderMgr.trackProgress(dt);
            orderMgr.assignResources(); // Auto assign daemon
        }

        BeginDrawing();
        ClearBackground(GuiTheme::COL_BACKGROUND);
        
        if(!isLoggedIn) {
            DrawLogin();
        } else {
            DrawSidebar();
            DrawMain();
        }

        EndDrawing();
    }

    GuiTheme::UnloadThemeResources();
    CloseWindow();
    return 0;
}
