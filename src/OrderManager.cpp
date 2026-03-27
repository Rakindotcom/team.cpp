#include "ProductionOrder.cpp"
#include "InventoryManager.cpp"
#include "HRManager.cpp"
#include "Machine.cpp"
#include "QualityManager.cpp"
#include <bits/stdc++.h>
using namespace std;

class OrderManager
{
private:
    vector<ProductionOrder> activeOrders;
    vector<Machine> machines;

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

        // seed some machines (keeping machines hardcoded for now as per instructions, only orders/inv/hr to text files)
        machines.push_back(Machine("MAC-01", "Sewing", "Brother S-7000", 100));
        machines.push_back(Machine("MAC-02", "Sewing", "Juki DDL-8700", 120));
        machines.push_back(Machine("CUT-01", "Cutting", "Eastman 629", 500));

        loadOrders();
    }

    void scheduleOrder(Garment garment, int quantity)
    {
        // check inventory
        if (invMgr->getItems().size() > 0)
        {
            // deduct logic would go here
        }

        string id = "PO-" + to_string(activeOrders.size() + 1);
        ProductionOrder po(id, garment, quantity, "2025-12-31");
        po.createOrder();
        activeOrders.push_back(po);
        saveOrders();
    }

    void assignResources()
    {
        for (int i = 0; i < activeOrders.size(); i++)
        {
            if (activeOrders[i].getStatus() == "Pending")
            {
                // get first available machine and employee
                string mid = machines[0].getId();
                string eid = hrMgr->getEmployees()[0].getId();
                activeOrders[i].assignResources(mid, eid);
            }
        }
        saveOrders();
    }

    void advanceOrderStatus(int index) {
        if (index >= 0 && index < activeOrders.size()) {
            activeOrders[index].advanceStatus();
            saveOrders();
        }
    }



    string generateProductionReport()
    {
        string report = "=== Production Report ===\n";
        report += "Active Orders: " + to_string(activeOrders.size()) + "\n";
        int completed = 0;
        for (int i = 0; i < activeOrders.size(); i++)
        {
            if (activeOrders[i].getStatus() == "Completed") completed++;
        }
        report += "Completed (Session): " + to_string(completed) + "\n";
        report += "Machines Operational: " + to_string(machines.size()) + "\n";
        return report;
    }

    vector<ProductionOrder>& getOrders() { return activeOrders; }
    vector<Machine>& getMachines() { return machines; }
};
