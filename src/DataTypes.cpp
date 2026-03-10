#pragma once

#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>

namespace GarmentFactory {

// --- Enumerations ---

enum class OrderStatus {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
};

inline std::string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::PENDING:     return "Pending";
        case OrderStatus::IN_PROGRESS: return "In Progress";
        case OrderStatus::COMPLETED:   return "Completed";
        case OrderStatus::CANCELLED:   return "Cancelled";
        default:                       return "Unknown";
    }
}

inline OrderStatus stringToOrderStatus(const std::string& str) {
    if (str == "Pending")     return OrderStatus::PENDING;
    if (str == "In Progress") return OrderStatus::IN_PROGRESS;
    if (str == "Completed")   return OrderStatus::COMPLETED;
    if (str == "Cancelled")   return OrderStatus::CANCELLED;
    return OrderStatus::PENDING; 
}

// --- Structs ---

struct Item {
    std::string itemId;
    std::string name;
    std::string description;
    std::map<std::string, int> recipe; // materialId -> quantity needed

    Item() : itemId(""), name(""), description("") {}
    
    Item(const std::string& id, const std::string& n, const std::string& desc, const std::map<std::string, int>& rec = {})
        : itemId(id), name(n), description(desc), recipe(rec) {}

    bool operator<(const Item& other) const { return itemId < other.itemId; }
    bool operator==(const Item& other) const { return itemId == other.itemId; }
};

struct Material {
    std::string materialId;
    std::string name;
    std::string unit; 

    Material() : materialId(""), name(""), unit("units") {}
    
    Material(const std::string& id, const std::string& n, const std::string& u = "units")
        : materialId(id), name(n), unit(u) {}

    bool operator<(const Material& other) const { return materialId < other.materialId; }
    bool operator==(const Material& other) const { return materialId == other.materialId; }
};

struct DateTime {
    std::time_t timestamp;

    DateTime() : timestamp(std::time(nullptr)) {}
    
    DateTime(std::time_t t) : timestamp(t) {}

    std::string toString() const {
        char buffer[80];
        struct tm* timeinfo = std::localtime(&timestamp);
        if (timeinfo) {
            std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
            return std::string(buffer);
        }
        return "Unknown Time";
    }

    static DateTime now() { return DateTime(std::time(nullptr)); }
    static DateTime fromTimestamp(std::time_t t) { return DateTime(t); }
};

using MaterialQuantityMap = std::map<std::string, int>;

} // namespace GarmentFactory
