#pragma once
#include <string>
#include <vector>

namespace GarmentFactory {

struct SKUVariant {
    std::string sku;
    std::string color;
    std::string size;
    std::string materialGrade;
    std::string batchNumber;
    std::string expiryDate;

    std::string generateSKU() { return batchNumber + "-" + color + "-" + size; }
    bool validateBatch() { return !batchNumber.empty(); }
};

class InventoryItem {
private:
    std::string itemId;
    std::string itemName;
    std::string category; // "Fabric", "Thread"
    double currentStock;
    double reorderLevel;
    std::string unit;
    double unitPrice;
    std::string lastUpdated;
    
    std::vector<SKUVariant> variants;

public:
    InventoryItem(std::string id, std::string name, std::string cat, double stock, std::string u)
        : itemId(id), itemName(name), category(cat), currentStock(stock), unit(u), reorderLevel(50.0) {}

    void updateStock(double qty) { currentStock += qty; }
    
    bool checkAvailability(double qty) const { return currentStock >= qty; }
    
    void generateReorderAlert() {
        if(currentStock < reorderLevel) {
            // Logic to alert System
        }
    }
    
    // Getters
    std::string getName() const { return itemName; }
    double getStock() const { return currentStock; }
    std::string getId() const { return itemId; }
};

class InventoryManager {
private:
    std::vector<InventoryItem> allItems;

public:
    InventoryManager() {
        // Seeds
        allItems.emplace_back("I001", "Cotton Fabric", "Fabric", 1000.0, "meters");
        allItems.emplace_back("I002", "Red Thread", "Thread", 500.0, "spools");
        allItems.emplace_back("I003", "Buttons", "Accessories", 2000.0, "pcs");
    }

    void trackInventory() {
        // Periodic check
    }

    std::string generateStockReport() {
        std::string report = "Stock Alert:\n";
        for(const auto& item : allItems) {
            if(item.getStock() < 50) report += "- Low Stock: " + item.getName() + "\n";
        }
        return report;
    }

    void processReorder() {
        for(auto& item : allItems) {
            if(item.getStock() < 100) item.updateStock(500); // Auto reorder sim
        }
    }

    InventoryItem* findItem(std::string id) {
        for(auto& i : allItems) if(i.getId() == id) return &i;
        return nullptr;
    }
    
    std::vector<InventoryItem>& getItems() { return allItems; }
};

} // namespace GarmentFactory
