#pragma once
#include <string>

namespace GarmentFactory {

class Machine {
private:
    std::string machineId;
    std::string machineType; // "Sewing", "Cutting", "Embroidery"
    std::string model;
    std::string status; // "Operational", "Maintenance", "Broken"
    std::string lastMaintenance;
    int dailyCapacity;

public:
    Machine() {}
    Machine(std::string id, std::string type, std::string mod, int capacity)
        : machineId(id), machineType(type), model(mod), status("Operational"), dailyCapacity(capacity) {}

    bool isOperational() const { return status == "Operational"; }

    void scheduleMaintenance(std::string date) {
        status = "Maintenance";
        lastMaintenance = date;
    }

    void updateStatus(std::string newStatus) {
        status = newStatus;
    }

    // Getters
    std::string getDetails() const {
        return machineType + " - " + status;
    }
    std::string getId() const { return machineId; }
};

} // namespace GarmentFactory
