#include "ProductionOrder.cpp"
#include "InventoryManager.cpp"
#include "HRManager.cpp"
#include <bits/stdc++.h>
using namespace std;

class OrderManager
{
private:
    vector<ProductionOrder> activeOrders;

    InventoryManager* invMgr;
    HRManager* hrMgr;

    void loadOrders()
    {
        ifstream file("orders.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string oId, gId, gType, gSize, gFab, gBaseStr, qtyStr, dline, stat, prio, progStr, oDate;
            
            getline(ss, oId, '|');
            getline(ss, gId, '|');
            getline(ss, gType, '|');
            getline(ss, gSize, '|');
            getline(ss, gFab, '|');
            getline(ss, gBaseStr, '|');
            getline(ss, qtyStr, '|');
            getline(ss, dline, '|');
            getline(ss, stat, '|');
            getline(ss, prio, '|');
            getline(ss, progStr, '|');
            getline(ss, oDate, '|');

            try {
                double gBase = stod(gBaseStr);
                int qty = stoi(qtyStr);
                float prog = stof(progStr);
                
                Garment g(gId, gType, gSize, gFab, gBase);
                activeOrders.push_back(ProductionOrder(oId, g, qty, dline, stat, prio, prog, oDate));
            } catch(...) {}
        }
        file.close();
    }

public:
    void saveOrders()
    {
        ofstream file("orders.txt");
        if (!file.is_open()) return;

        for (int i = 0; i < activeOrders.size(); i++) {
            Garment g = activeOrders[i].getGarment();
            file << activeOrders[i].getId() << "|"
                 << g.getId() << "|"
                 << g.getType() << "|"
                 << g.getSize() << "|"
                 << g.getFabric() << "|"
                 << g.getBaseReq() << "|"
                 << activeOrders[i].getQuantity() << "|"
                 << activeOrders[i].getDeadline() << "|"
                 << activeOrders[i].getStatus() << "|"
                 << activeOrders[i].getPriority() << "|"
                 << activeOrders[i].getProgress() << "|"
                 << activeOrders[i].getOrderDate() << "\n";
        }
        file.close();
    }

    OrderManager(InventoryManager* i, HRManager* h)
    {
        invMgr = i;
        hrMgr = h;
        loadOrders();
    }

    void scheduleOrder(Garment garment, int quantity)
    {
        string id = "PO-" + to_string(activeOrders.size() + 1);
        ProductionOrder po(id, garment, quantity, "2025-12-31");
        activeOrders.push_back(po);
        saveOrders();
    }

    void advanceOrderStatus(int index) {
        if (index >= 0 && index < activeOrders.size()) {
            activeOrders[index].advanceStatus();
            saveOrders();
        }
    }

    vector<ProductionOrder>& getOrders() { return activeOrders; }
};
