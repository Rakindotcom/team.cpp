#include "Garment.cpp"
#include <bits/stdc++.h>
using namespace std;

class ProductionOrder
{
private:
    string orderId;
    Garment garment;
    int quantity;
    string orderDate;
    string deadline;
    string status;
    string priority;

    string assignedMachineId;
    string assignedOperatorId;

    vector<string> productionSteps;
    float progress;

public:
    ProductionOrder() { progress = 0.0; }

    ProductionOrder(string id, Garment g, int qty, string dline)
    {
        orderId = id;
        garment = g;
        quantity = qty;
        deadline = dline;
        status = "Pending";
        priority = "Normal";
        progress = 0.0;
        // set order date to current time
        time_t now = time(0);
        orderDate = string(ctime(&now));
        // clean trailing newline from ctime
        if (!orderDate.empty() && orderDate.back() == '\n') orderDate.pop_back();
    }

    // Constructor for loading from file
    ProductionOrder(string id, Garment g, int qty, string dline, string stat, string prio, float prog, string oDate)
    {
        orderId = id;
        garment = g;
        quantity = qty;
        deadline = dline;
        status = stat;
        priority = prio;
        progress = prog;
        orderDate = oDate;
    }

    void createOrder() { status = "Pending"; }

    bool validateOrder() { return quantity > 0; }

    void updateStatus(string newStatus) { status = newStatus; }

    void assignResources(string machineId, string empId)
    {
        assignedMachineId = machineId;
        assignedOperatorId = empId;
        status = "In Progress";
    }

    void advanceStatus()
    {
        if (status == "Pending")
        {
            status = "Cutting";
            progress = 0.25f;
        }
        else if (status == "Cutting")
        {
            status = "Sewing";
            progress = 0.50f;
        }
        else if (status == "Sewing")
        {
            status = "QC";
            progress = 0.75f;
        }
        else if (status == "QC")
        {
            status = "Completed";
            progress = 1.0f;
        }
        else
        {
            status = "Pending";
            progress = 0.0f;
        }
    }

    // getters
    string getId() const { return orderId; }
    Garment getGarment() const { return garment; }
    int getQuantity() const { return quantity; }
    string getStatus() const { return status; }
    float getProgress() const { return progress; }
    string getOperatorId() const { return assignedOperatorId; }
    string getMachineId() const { return assignedMachineId; }
    string getDeadline() const { return deadline; }
    string getPriority() const { return priority; }
    string getOrderDate() const { return orderDate; }
};
