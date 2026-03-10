#pragma once

#include "ProductionOrder.cpp"
#include "InventoryManager.cpp"
#include "HRManager.cpp"
#include "Machine.cpp"
#include "QualityManager.cpp" 

// This replaces the old OrderManager but now acts as the central facade for the "Production" domain
// connecting other managers as per UML flow (ProductionOrder references Machine, etc.)

namespace GarmentFactory {

class OrderManager {
private:
    std::vector<ProductionOrder> activeOrders;
    std::vector<Machine> machines;
    
    // Dependencies
    InventoryManager* invMgr;
    HRManager* hrMgr;

public:
    OrderManager(InventoryManager* i, HRManager* h) : invMgr(i), hrMgr(h) {
        // Seed Machines
        machines.emplace_back("MAC-01", "Sewing", "Brother S-7000", 100);
        machines.emplace_back("MAC-02", "Sewing", "Juki DDL-8700", 120);
        machines.emplace_back("CUT-01", "Cutting", "Eastman 629", 500);
    }

    // Updated create logic
    void scheduleOrder(Garment garment, int quantity) {
        // Check inv (Simplified access)
        if(invMgr->getItems().size() > 0) {
            // Deduct? Logic moved to specific implementations if needed
        }
        
        std::string id = "PO-" + std::to_string(activeOrders.size() + 1);
        ProductionOrder po(id, garment, quantity, "2025-12-31");
        po.createOrder();
        activeOrders.push_back(po);
    }

    void assignResources() {
        // Auto assign logic
        for(auto& order : activeOrders) {
            if(order.getStatus() == OrderStatus::PENDING) {
                // Find machine
                std::string mid = machines[0].getId(); // First available
                // Find emp
                std::string eid = hrMgr->getEmployees()[0].getId();
                
                order.assignResources(mid, eid);
            }
        }
    }
    
    void trackProgress(float dt) {
        // Simulation
        for(auto& order : activeOrders) {
            order.updateProgress(dt);
        }
    }

    // Analytics
    std::string generateProductionReport() {
        std::stringstream ss;
        ss << "=== Production Report ===\n";
        ss << "Active Orders: " << activeOrders.size() << "\n";
        int completed = 0;
        for(const auto& o : activeOrders) { if(o.getStatus() == OrderStatus::COMPLETED) completed++; }
        ss << "Completed (Session): " << completed << "\n";
        ss << "Machines Operational: " << machines.size() << "\n";
        return ss.str();
    }

    std::vector<ProductionOrder>& getOrders() { return activeOrders; }
    std::vector<Machine>& getMachines() { return machines; }
};

} // namespace GarmentFactory
