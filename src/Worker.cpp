#pragma once

#include "DataTypes.cpp"
#include <algorithm>
#include <iostream>

namespace GarmentFactory {

class Worker {
private:
    std::string workerId;
    std::string name;
    int activeLoad;     
    int maxLoad;        
    std::vector<std::string> assignedOrderIds;

    static int workerCounter;

public:
    // Constructors
    Worker() : workerId(""), name(""), activeLoad(0), maxLoad(5) {}

    Worker(const std::string& name, int maxLoad = 5)
        : workerId(generateWorkerId()), name(name), activeLoad(0), 
          maxLoad(maxLoad > 0 ? maxLoad : 5) {}

    Worker(const std::string& id, const std::string& name, int activeLoad,
           int maxLoad, const std::vector<std::string>& orderIds)
        : workerId(id), name(name), activeLoad(activeLoad), maxLoad(maxLoad),
          assignedOrderIds(orderIds) {}

    // Getters
    std::string getWorkerId() const { return workerId; }
    std::string getName() const { return name; }
    int getActiveLoad() const { return activeLoad; }
    int getMaxLoad() const { return maxLoad; }
    std::vector<std::string> getAssignedOrderIds() const { return assignedOrderIds; }

    // Setters
    void setName(const std::string& newName) { if (!newName.empty()) name = newName; }
    void setMaxLoad(int max) { if (max > 0) maxLoad = max; }

    // Core methods
    void updateLoad(int amount) {
        activeLoad += amount;
        if (activeLoad < 0) activeLoad = 0;
        if (activeLoad > maxLoad) activeLoad = maxLoad;
    }

    bool isAvailable() const { return activeLoad < maxLoad; }
    int getAvailableCapacity() const { return maxLoad - activeLoad; }
    
    float getWorkloadPercentage() const {
        if (maxLoad == 0) return 0.0f;
        return (static_cast<float>(activeLoad) / static_cast<float>(maxLoad)) * 100.0f;
    }

    // Order assignment
    bool assignOrder(const std::string& orderId) {
        if (!isAvailable()) return false;
        if (hasOrder(orderId)) return false;

        assignedOrderIds.push_back(orderId);
        activeLoad++;
        return true;
    }

    bool unassignOrder(const std::string& orderId) {
        auto it = std::find(assignedOrderIds.begin(), assignedOrderIds.end(), orderId);
        if (it == assignedOrderIds.end()) return false;

        assignedOrderIds.erase(it);
        activeLoad--;
        if (activeLoad < 0) activeLoad = 0;
        return true;
    }

    bool hasOrder(const std::string& orderId) const {
        return std::find(assignedOrderIds.begin(), assignedOrderIds.end(), orderId) 
               != assignedOrderIds.end();
    }

    // Utility
    std::string getDetails() const {
        std::ostringstream oss;
        oss << "ID: " << workerId << " | Name: " << name 
            << " | Load: " << activeLoad << "/" << maxLoad 
            << " (" << std::fixed << std::setprecision(1) << getWorkloadPercentage() << "%)";
        return oss.str();
    }

    static std::string generateWorkerId() {
        std::ostringstream oss;
        oss << "WRK-" << std::setfill('0') << std::setw(4) << workerCounter++;
        return oss.str();
    }

    static void setWorkerCounter(int count) { workerCounter = count; }
};

int Worker::workerCounter = 1;

} // namespace GarmentFactory
