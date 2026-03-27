#include "raylib.h"
#include "GuiComponents.cpp"
#include "GuiTheme.cpp"
#include <iostream>
#include <string>
#include <vector>

// include modules
#include "OrderManager.cpp"

using namespace std;

// Custom Exception Handling
class InvalidInputException : public exception {
public:
    const char* what() const throw() {
        return "Quantity must be greater than zero!";
    }
};

// app states
enum AppState {
    DASHBOARD,
    CREATE_ORDER,
    WORKERS,
    INVENTORY
};

int main() {
    // initialize core systems
    InventoryManager invMgr;
    HRManager hrMgr;
    OrderManager orderMgr(&invMgr, &hrMgr);

    // initialize raylib
    int screenWidth = 1280;
    int screenHeight = 800;
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Garment Factory Management System");

    SetTargetFPS(60);
    LoadThemeResources();

    // state
    AppState currentState = DASHBOARD;

    // layout
    int sidebarWidth = 260;

    // form helpers
    auto DrawField = [](float formX, float yPos, string label, string& val, bool& active, int width = 540) {
        DrawLabel(label, {formX, yPos}, FONT_SIZE_BODY, COL_TEXT_SECONDARY);
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            active = CheckCollisionPointRec(GetMousePosition(), {formX, yPos + 30, (float)width, 45});
        }
        DrawInput({formX, yPos + 30, (float)width, 45}, val, 30, active);
    };

    // main loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(COL_BACKGROUND);

        // sidebar
        Rectangle sidebarRec = {0, 0, (float)sidebarWidth, (float)GetScreenHeight()};
        DrawRectangleRec(sidebarRec, COL_SURFACE);
        DrawRectangleLinesEx(sidebarRec, 1, COL_BORDER);

        // logo
        DrawLabel("GarmentOS", {30, 40}, FONT_SIZE_HEADER, COL_PRIMARY);
        DrawLabel("Professional Ed.", {30, 80}, FONT_SIZE_SMALL, COL_TEXT_MUTED);

        // navigation
        float navY = 140;
        float navH = 54;

        if (DrawNavButton({12, navY, sidebarWidth - 24.0f, navH}, "Dashboard", currentState == DASHBOARD)) currentState = DASHBOARD;
        if (DrawNavButton({12, navY + 64, sidebarWidth - 24.0f, navH}, "Create Order", currentState == CREATE_ORDER)) currentState = CREATE_ORDER;
        if (DrawNavButton({12, navY + 128, sidebarWidth - 24.0f, navH}, "Workforce", currentState == WORKERS)) currentState = WORKERS;
        if (DrawNavButton({12, navY + 192, sidebarWidth - 24.0f, navH}, "Inventory", currentState == INVENTORY)) currentState = INVENTORY;

        // exit button
        if (DrawButtonSecondary({20, (float)GetScreenHeight() - 80, sidebarWidth - 40.0f, 50}, "Exit")) {
            UnloadThemeResources();
            CloseWindow();
            return 0;
        }

        // main content area
        Rectangle contentArea = {(float)sidebarWidth + 40, 40, (float)GetScreenWidth() - sidebarWidth - 80, (float)GetScreenHeight() - 80};

        switch (currentState) {
            case DASHBOARD: {
                DrawLabel("Production Dashboard", {contentArea.x, contentArea.y}, FONT_SIZE_HEADER, COL_TEXT_PRIMARY);
                DrawLabel("Overview of active production orders", {contentArea.x, contentArea.y + 40}, FONT_SIZE_BODY, COL_TEXT_SECONDARY);

                float y = contentArea.y + 90;
                auto& orders = orderMgr.getOrders();

                if (orders.empty()) {
                    DrawLabel("No active orders.", {contentArea.x, y}, FONT_SIZE_BODY, COL_TEXT_MUTED);
                }

                for (int i = 0; i < orders.size(); i++) {
                    DrawCard({contentArea.x, y, contentArea.width, 100});

                    DrawLabel(orders[i].getId(), {contentArea.x + 24, y + 20}, FONT_SIZE_TITLE, COL_PRIMARY);
                    DrawLabel(orders[i].getGarment().getName(), {contentArea.x + 24, y + 50}, FONT_SIZE_BODY, COL_TEXT_PRIMARY);

                    string statusStr = orders[i].getStatus();

                    if (DrawButtonSecondary({contentArea.x + 300, y + 15, 160, 30}, "Status: " + statusStr)) {
                        orderMgr.advanceOrderStatus(i);
                    }

                    DrawLabel("Qty: " + to_string(orders[i].getQuantity()), {contentArea.x + 300, y + 55}, FONT_SIZE_BODY, COL_TEXT_SECONDARY);

                    // progress bar
                    float progress = orders[i].getProgress();
                    DrawRectangle(contentArea.x + 500, y + 45, 200, 10, COL_BACKGROUND);
                    DrawRectangle(contentArea.x + 500, y + 45, (int)(200 * progress), 10, COL_SECONDARY);
                    DrawLabel(to_string((int)(progress * 100)) + "%", {contentArea.x + 710, y + 40}, FONT_SIZE_SMALL, COL_TEXT_SECONDARY);

                    y += 115;
                }
                break;
            }
            case CREATE_ORDER: {
                DrawLabel("New Production Order", {contentArea.x, contentArea.y}, FONT_SIZE_HEADER, COL_TEXT_PRIMARY);

                DrawCard({contentArea.x, contentArea.y + 80, 600, 450});

                static string type = "";
                static string size = "";
                static string fabric = "";
                static string qtyStr = "";

                static bool typeActive = false, sizeActive = false, fabricActive = false, qtyActive = false;

                float formY = contentArea.y + 110;
                float formX = contentArea.x + 30;

                DrawField(formX, formY, "Garment Type (e.g., Shirt, Pants)", type, typeActive);
                DrawField(formX, formY + 90, "Size Range (e.g., M, L, XL)", size, sizeActive);
                DrawField(formX, formY + 180, "Fabric Type (e.g., Cotton, Silk)", fabric, fabricActive);
                DrawField(formX, formY + 270, "Quantity", qtyStr, qtyActive);

                // submit
                if (DrawButton({formX, formY + 360, 200, 50}, "Schedule Order")) {
                    if (!type.empty() && !qtyStr.empty()) {
                        try {
                            int qty = stoi(qtyStr);
                            
                            // Throw Custom Exception
                            if (qty <= 0) throw InvalidInputException();

                            Garment g("G" + to_string(GetTime()), type, size, fabric, 2.5);
                            orderMgr.scheduleOrder(g, qty);

                            // reset
                            type = ""; size = ""; fabric = ""; qtyStr = "";
                            currentState = DASHBOARD;
                        } catch (const InvalidInputException& e) {
                            cout << "Exception Caught: " << e.what() << endl;
                        } catch(...) {
                            // ignore error
                        }
                    }
                }

                break;
            }
            case WORKERS: {
                DrawLabel("Employee Directory", {contentArea.x, contentArea.y}, FONT_SIZE_HEADER, COL_TEXT_PRIMARY);

                // Add Employee Form
                float formY = contentArea.y + 60;
                static string empName = "";
                static string empRole = "";
                static string empDept = "";
                static bool nActive = false, rActive = false, dActive = false;

                DrawCard({contentArea.x, formY, contentArea.width, 100});
                DrawField(contentArea.x + 20, formY + 15, "Name", empName, nActive, 200);
                DrawField(contentArea.x + 240, formY + 15, "Role", empRole, rActive, 150);
                DrawField(contentArea.x + 410, formY + 15, "Department", empDept, dActive, 150);

                if (DrawButton({contentArea.x + 580, formY + 35, 120, 45}, "Add Worker")) {
                    if(!empName.empty() && !empRole.empty() && !empDept.empty()) {
                        string newId = "E00" + to_string(hrMgr.getEmployees().size() + 1);
                        hrMgr.addEmployee(Employee(newId, empName, empDept, empRole));
                        empName = ""; empRole = ""; empDept = "";
                    }
                }

                float y = formY + 120;
                auto& employees = hrMgr.getEmployees();

                // grid layout
                int col = 0;
                for (int i = 0; i < employees.size(); i++) {
                    float x = contentArea.x + (col * 320);
                    if (x + 300 > contentArea.x + contentArea.width) {
                        col = 0;
                        x = contentArea.x;
                        y += 160;
                    }

                    DrawCard({x, y, 300, 140});

                    // avatar circle
                    DrawCircle(x + 40, y + 40, 20, COL_PRIMARY);
                    DrawTextEx(AppFont, employees[i].getName().substr(0,1).c_str(), {x+34, y+28}, 24, 0, WHITE);

                    DrawLabel(employees[i].getName(), {x + 80, y + 25}, FONT_SIZE_TITLE, COL_TEXT_PRIMARY);
                    DrawLabel(employees[i].getRole(), {x + 80, y + 55}, FONT_SIZE_BODY, COL_SECONDARY);

                    DrawLabel("Dept: " + employees[i].getDepartment(), {x + 24, y + 90}, FONT_SIZE_SMALL, COL_TEXT_SECONDARY);
                    DrawLabel("ID: " + employees[i].getId(), {x + 24, y + 110}, FONT_SIZE_SMALL, COL_TEXT_MUTED);

                    if (DrawButtonSecondary({x + 200, y + 95, 80, 25}, "Remove")) {
                        hrMgr.removeEmployee(employees[i].getId());
                        break;
                    }

                    col++;
                }
                break;
            }
            case INVENTORY: {
                DrawLabel("Warehouse Inventory", {contentArea.x, contentArea.y}, FONT_SIZE_HEADER, COL_TEXT_PRIMARY);

                // Add Item Form
                float formY = contentArea.y + 60;
                static string iName = "";
                static string iCat = "";
                static string iStock = "";
                static bool inActive = false, icActive = false, isActive = false;

                DrawCard({contentArea.x, formY, contentArea.width, 100});
                DrawField(contentArea.x + 20, formY + 15, "Item Name", iName, inActive, 200);
                DrawField(contentArea.x + 240, formY + 15, "Category", iCat, icActive, 150);
                DrawField(contentArea.x + 410, formY + 15, "Initial Stock", iStock, isActive, 150);

                if (DrawButton({contentArea.x + 580, formY + 35, 120, 45}, "Add Item")) {
                    if(!iName.empty() && !iStock.empty()) {
                        try {
                            double qty = stod(iStock);
                            string newId = "I00" + to_string(invMgr.getItems().size() + 1);
                            invMgr.addItem(InventoryItem(newId, iName, iCat, qty, "units"));
                            iName = ""; iCat = ""; iStock = "";
                        } catch(...) {}
                    }
                }

                float y = formY + 130;
                // headers
                DrawLabel("ITEM NAME", {contentArea.x + 20, y}, FONT_SIZE_SMALL, COL_TEXT_MUTED);
                DrawLabel("CATEGORY", {contentArea.x + 300, y}, FONT_SIZE_SMALL, COL_TEXT_MUTED);
                DrawLabel("STOCK", {contentArea.x + 500, y}, FONT_SIZE_SMALL, COL_TEXT_MUTED);

                y += 30;
                DrawLineEx({contentArea.x, y}, {contentArea.x + contentArea.width, y}, 1, COL_BORDER);
                y += 20;

                auto& items = invMgr.getItems();
                for (int i = 0; i < items.size(); i++) {
                    DrawLabel(items[i].getName(), {contentArea.x + 20, y}, FONT_SIZE_BODY, COL_TEXT_PRIMARY);
                    DrawLabel(items[i].getId(), {contentArea.x + 20, y+20}, FONT_SIZE_SMALL, COL_TEXT_MUTED);
                    
                    DrawLabel(items[i].getCategory(), {contentArea.x + 300, y+10}, FONT_SIZE_BODY, COL_TEXT_SECONDARY);

                    DrawLabel(to_string((int)items[i].getStock()) + " " + items[i].getUnit(), {contentArea.x + 500, y+10}, FONT_SIZE_TITLE, COL_PRIMARY);

                    if (DrawButtonSecondary({contentArea.x + 750, y + 5, 80, 25}, "Remove")) {
                        invMgr.removeItem(items[i].getId());
                        break;
                    }

                    y += 60;
                }
                break;
            }
            default: break;
        }

        EndDrawing();
    }

    UnloadThemeResources();
    CloseWindow();

    return 0;
}
