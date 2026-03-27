#include "raylib.h"
#include "GuiTheme.h"
#include "GuiComponents.h"

// include all modules
#include "User.cpp"
#include "OrderManager.cpp"

using namespace std;

// global state
User currentUser;
bool isLoggedIn = false;

InventoryManager invMgr;
HRManager hrMgr;
QualityManager qcMgr;
OrderManager orderMgr(&invMgr, &hrMgr);

enum Screen {
    LOGIN,
    DASHBOARD,
    HR,
    PRODUCTION,
    INVENTORY,
    QUALITY
};

Screen currentScreen = LOGIN;

// input buffers
string loginUser = "";
string loginPass = "";
bool userActive = false;
bool passActive = false;

string orderItemInput = "";
string orderQtyInput = "";

// --- screen drawing functions ---

void DrawLogin() {
    int w = 400;
    int h = 350;

    Rectangle panel = { (float)GetScreenWidth()/2 - w/2, (float)GetScreenHeight()/2 - h/2, (float)w, (float)h };
    DrawCard(panel);

    DrawText("System Login", panel.x + 20, panel.y + 20, 32, COL_PRIMARY);

    DrawLabel("Username", {panel.x + 20, panel.y + 80}, 20, GRAY);
    if(DrawInput({panel.x + 20, panel.y + 105, 360, 40}, loginUser, 20, userActive)) {
        userActive = true; passActive = false;
    }

    DrawLabel("Password", {panel.x + 20, panel.y + 160}, 20, GRAY);
    if(DrawInput({panel.x + 20, panel.y + 185, 360, 40}, loginPass, 20, passActive)) {
        passActive = true; userActive = false;
    }

    if(DrawButton({panel.x + 20, panel.y + 260, 360, 50}, "Login")) {
        if(loginUser == "admin" && loginPass == "admin") {
            currentUser = User("U01", "Admin", "admin", "Admin", "admin@factory.com");
            isLoggedIn = true;
            currentScreen = DASHBOARD;
        }
    }

    DrawLabel("Hint: admin / admin", {panel.x + 20, panel.y + 320}, 14, DARKGRAY);
}

void DrawSidebar() {
    int w = 220;
    DrawRectangle(0, 0, w, GetScreenHeight(), COL_SURFACE);

    DrawText("FactoryOS", 40, 40, 32, COL_PRIMARY);

    int y = 120;
    if(DrawNavButton({10, (float)y, 200, 45}, "Dashboard", currentScreen == DASHBOARD, ICON_HOME)) currentScreen = DASHBOARD;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "Production", currentScreen == PRODUCTION, ICON_USER)) currentScreen = PRODUCTION;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "HR & Shifts", currentScreen == HR, ICON_USER)) currentScreen = HR;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "Inventory", currentScreen == INVENTORY, ICON_SETTINGS)) currentScreen = INVENTORY;
    y += 55;
    if(DrawNavButton({10, (float)y, 200, 45}, "Quality", currentScreen == QUALITY, ICON_SETTINGS)) currentScreen = QUALITY;

    // user info
    DrawLabel(currentUser.getUsername(), {20, (float)GetScreenHeight() - 60}, 20, WHITE);
    DrawLabel(currentUser.getRole(), {20, (float)GetScreenHeight() - 40}, 14, GRAY);

    if(DrawButtonSecondary({140, (float)GetScreenHeight() - 50, 60, 30}, "Exit")) {
        currentScreen = LOGIN;
        isLoggedIn = false;
        loginPass = "";
    }
}

void DrawProduction() {
    DrawHeader("Production Management");

    DrawCard({260, 100, 200, 100});
    DrawLabel("Active Batches", {280, 120}, 20, GRAY);
    DrawLabel(to_string(orderMgr.getOrders().size()), {280, 150}, 40, COL_PRIMARY);

    DrawCard({480, 100, 200, 100});
    DrawLabel("Machines Active", {500, 120}, 20, GRAY);
    DrawLabel(to_string(orderMgr.getMachines().size()), {500, 150}, 40, COL_SECONDARY);

    // create order
    static bool itemActive=false;
    static bool qtyActive=false;
    DrawLabel("New Batch:", {260, 240}, 20, WHITE);

    DrawInput({260, 270, 200, 40}, orderItemInput, 20, itemActive);
    DrawInput({480, 270, 100, 40}, orderQtyInput, 10, qtyActive);

    if(DrawButton({600, 270, 100, 40}, "Schedule")) {
        if(!orderItemInput.empty()) {
            Garment g("G01", orderItemInput, "L", "Cotton", 2.0);
            try {
                int q = stoi(orderQtyInput);
                orderMgr.scheduleOrder(g, q);
            } catch(...) {}
        }
    }
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if(CheckCollisionPointRec(GetMousePosition(), {260,270,200,40})) itemActive=true; else itemActive=false;
        if(CheckCollisionPointRec(GetMousePosition(), {480,270,100,40})) qtyActive=true; else qtyActive=false;
    }

    // list orders
    int y = 350;
    DrawLabel("#  Garment  Qty  Status  Progress", {270, (float)y-30}, 16, GRAY);
    auto& orders = orderMgr.getOrders();
    for(int i = 0; i < orders.size(); i++) {
        DrawRectangleRounded({260, (float)y, 800, 50}, 0.2, 4, COL_SURFACE);

        DrawLabel(orders[i].getId(), {280, (float)y+15}, 16, WHITE);
        DrawLabel(orders[i].getGarment().getName(), {350, (float)y+15}, 16, WHITE);
        DrawLabel(to_string(orders[i].getQuantity()), {500, (float)y+15}, 16, WHITE);

        // progress bar
        DrawRectangle(600, y+20, 100, 10, BLACK);
        DrawRectangle(600, y+20, 100 * orders[i].getProgress(), 10, COL_PRIMARY);

        y += 60;
    }
}

void DrawHR() {
    DrawHeader("Human Resources");

    int y = 100;
    int x = 260;
    auto& employees = hrMgr.getEmployees();
    for(int i = 0; i < employees.size(); i++) {
        DrawCard({(float)x, (float)y, 250, 150});
        DrawLabel(employees[i].getName(), {(float)x+20, (float)y+20}, 20, COL_PRIMARY);
        DrawLabel(employees[i].getRole(), {(float)x+20, (float)y+50}, 16, GRAY);
        DrawLabel(employees[i].getId(), {(float)x+20, (float)y+80}, 14, DARKGRAY);
        DrawLabel("Load: " + to_string(employees[i].getLoad()) + "%", {(float)x+20, (float)y+110}, 16, WHITE);

        x += 270;
        if(x > 1000) { x = 260; y += 170; }
    }
}

void DrawInventoryScreen() {
    DrawHeader("Inventory");
    // would show inventory items here
    DrawLabel("Inventory view coming soon.", {280, 120}, 20, GRAY);
}

void DrawQualityScreen() {
    DrawHeader("Quality Control");
    // would show QC reports here
    DrawLabel("Quality reports coming soon.", {280, 120}, 20, GRAY);
}

void DrawMain() {
    switch(currentScreen) {
        case DASHBOARD:
            DrawHeader("Executive Dashboard");
            DrawCard({260,100,400,200});
            DrawLabel("Welcome back,", {280, 130}, 24, GRAY);
            DrawLabel(currentUser.getUsername(), {280, 170}, 40, COL_PRIMARY);
            break;
        case PRODUCTION: DrawProduction(); break;
        case HR: DrawHR(); break;
        case INVENTORY: DrawInventoryScreen(); break;
        case QUALITY: DrawQualityScreen(); break;
        default: break;
    }
}

int main() {
    InitWindow(1280, 720, "FactoryOS (UML v2)");
    SetTargetFPS(60);

    LoadThemeResources();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if(isLoggedIn) {
            orderMgr.trackProgress(dt);
            orderMgr.assignResources();
        }

        BeginDrawing();
        ClearBackground(COL_BACKGROUND);

        if(!isLoggedIn) {
            DrawLogin();
        } else {
            DrawSidebar();
            DrawMain();
        }

        EndDrawing();
    }

    UnloadThemeResources();
    CloseWindow();
    return 0;
}
