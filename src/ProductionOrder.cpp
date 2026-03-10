#pragma once

#include "Garment.cpp"
#include "Machine.cpp"
#include "Employee.cpp"
#include "DataTypes.cpp" // Reuse status enum

namespace GarmentFactory {

class ProductionOrder {
private:
    std::string orderId;
    Garment garment;
    int quantity;
    std::string orderDate; // String for simplicity
    std::string deadline;
    OrderStatus status;
    std::string priority; // "High", "Normal"
    
    // assignments
    std::string assignedMachineId;
    std::string assignedOperatorId;

    std::vector<std::string> productionSteps;
    
    float progress; // 0.0 - 1.0 (Simulation aspect)

public:
    ProductionOrder() {}
    ProductionOrder(std::string id, Garment g, int qty, std::string dline)
        : orderId(id), garment(g), quantity(qty), deadline(dline), 
          status(OrderStatus::PENDING), priority("Normal"), progress(0.0f) {
              orderDate = DateTime::now().toString();
          }

    // UML Methods
    void createOrder() { status = OrderStatus::PENDING; }
    
    bool validateOrder() { return quantity > 0; }
    
    void updateStatus(OrderStatus newStatus) { status = newStatus; }
    
    void assignResources(std::string machineId, std::string empId) {
        assignedMachineId = machineId;
        assignedOperatorId = empId;
        status = OrderStatus::IN_PROGRESS;
    }
    
    // Simulation
    bool updateProgress(float dt) {
        if(status == OrderStatus::IN_PROGRESS) {
            progress += dt * 0.1f; // Arbitrary speed
            if(progress >= 1.0f) {
                progress = 1.0f;
                return true;
            }
        }
        return false;
    }

    // Getters
    std::string getId() const { return orderId; }
    Garment getGarment() const { return garment; }
    int getQuantity() const { return quantity; }
    OrderStatus getStatus() const { return status; }
    float getProgress() const { return progress; }
    std::string getOperatorId() const { return assignedOperatorId; }
};

} // namespace GarmentFactory
