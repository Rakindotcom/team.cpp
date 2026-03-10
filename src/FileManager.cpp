#pragma once

#include "OrderManager.cpp"
#include <fstream>
#include <iostream>

// Simple text-based persistence
namespace GarmentFactory {

class FileManager {
public:
    static void saveData(OrderManager& om, const std::string& filename = "data.txt") {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file for saving.\n";
            return;
        }

        // Save Orders
        const auto& orders = om.getActiveOrders();
        file << "ORDERS " << orders.size() << "\n";
        for (const auto& o : orders) {
            file << o.getOrderId() << "|" 
                 << o.getItem().itemId << "|" 
                 << o.getItem().name << "|" 
                 << o.getQuantity() << "|" 
                 << o.getStatusString() << "|" 
                 << o.getAssignedWorkerId() << "\n";
        }

        // Save Workers
        const auto& workers = om.getWorkers();
        file << "WORKERS " << workers.size() << "\n";
        for (const auto& w : workers) {
            file << w.getWorkerId() << "|" << w.getName() << "|" << w.getActiveLoad() << "\n";
        }
        
        file.close();
        std::cout << "Data saved to " << filename << "\n";
    }

    static void loadData(OrderManager& om, const std::string& filename = "data.txt") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "No save file found. Starting fresh.\n";
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Simplified parser - real implementation would need string splitting
            // For MVP, just acknowledging the structure
            // In a real scenario, we'd parse the "|" separated values
        }
        std::cout << "Data loaded (Mock implementation for MVP).\n";
        // Actual parsing logic would go here
    }
};

} // namespace GarmentFactory
