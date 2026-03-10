#pragma once

#include "DataTypes.cpp"

namespace GarmentFactory {

class Order {
private:
    std::string orderId;
    Item item;
    int quantity;
    OrderStatus status;
    std::string assignedWorkerId;
    DateTime timestamp;
    DateTime lastUpdated;
    float progress;      // 0.0 to 1.0
    float totalDuration; // Seconds to complete

    static int orderCounter;

public:
    // Constructors
    Order() 
        : orderId(""), item(), quantity(0), status(OrderStatus::PENDING),
          assignedWorkerId(""), timestamp(), lastUpdated(), progress(0.0f), totalDuration(0.0f) {}

    Order(const Item& item, int quantity)
        : orderId(generateOrderId()), item(item), quantity(quantity),
          status(OrderStatus::PENDING), assignedWorkerId(""),
          timestamp(DateTime::now()), lastUpdated(DateTime::now()), progress(0.0f), totalDuration(5.0f * quantity) {} // 5 seconds per unit default

    Order(const std::string& id, const Item& item, int quantity,
          OrderStatus status, const std::string& workerId,
          std::time_t created, std::time_t updated)
        : orderId(id), item(item), quantity(quantity), status(status),
          assignedWorkerId(workerId), timestamp(DateTime::fromTimestamp(created)),
          lastUpdated(DateTime::fromTimestamp(updated)) {}

    // Getters
    std::string getOrderId() const { return orderId; }
    Item getItem() const { return item; }
    int getQuantity() const { return quantity; }
    OrderStatus getStatus() const { return status; }
    std::string getStatusString() const { return orderStatusToString(status); }
    std::string getAssignedWorkerId() const { return assignedWorkerId; }
    DateTime getTimestamp() const { return timestamp; }
    DateTime getLastUpdated() const { return lastUpdated; }
    float getProgress() const { return progress; }

    // Simulation Step
    // Returns true if completed in this step
    bool updateProgress(float dt) {
        if (status == OrderStatus::IN_PROGRESS) {
            progress += dt / totalDuration;
            if (progress >= 1.0f) {
                progress = 1.0f;
                return true;
            }
        }
        return false;
    }

    // Setters
    void setQuantity(int qty) {
        if (qty > 0) {
            quantity = qty;
            lastUpdated = DateTime::now();
        }
    }

    void setStatus(OrderStatus newStatus) {
        status = newStatus;
        lastUpdated = DateTime::now();
    }

    // Assign order to a worker
    void assignTo(const std::string& workerId) {
        assignedWorkerId = workerId;
        if (status == OrderStatus::PENDING) {
            status = OrderStatus::IN_PROGRESS;
        }
        lastUpdated = DateTime::now();
    }

    // Unassign order from worker
    void unassign() {
        assignedWorkerId = "";
        if (status == OrderStatus::IN_PROGRESS) {
            status = OrderStatus::PENDING;
        }
        lastUpdated = DateTime::now();
    }

    // Get formatted order details
    std::string getDetails() const {
        std::ostringstream oss;
        oss << "ID: " << orderId << " | Item: " << item.name 
            << " | Qty: " << quantity << " | Status: " << getStatusString();
        if (!assignedWorkerId.empty()) {
            oss << " | Worker: " << assignedWorkerId;
        }
        return oss.str();
    }

    // Calculate required materials
    MaterialQuantityMap getRequiredMaterials() const {
        MaterialQuantityMap materials;
        for (const auto& pair : item.recipe) {
            materials[pair.first] = pair.second * quantity;
        }
        return materials;
    }

    bool isAssigned() const { return !assignedWorkerId.empty(); }
    bool isActive() const { return status == OrderStatus::PENDING || status == OrderStatus::IN_PROGRESS; }
    bool isCompleted() const { return status == OrderStatus::COMPLETED; }

    static std::string generateOrderId() {
        std::ostringstream oss;
        oss << "ORD-" << std::setfill('0') << std::setw(5) << orderCounter++;
        return oss.str();
    }

    static void setOrderCounter(int count) { orderCounter = count; }
};

int Order::orderCounter = 1;

} // namespace GarmentFactory
