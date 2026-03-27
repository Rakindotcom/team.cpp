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
        time_t now = time(0);
        orderDate = string(ctime(&now));
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
    string getDeadline() const { return deadline; }
    string getPriority() const { return priority; }
    string getOrderDate() const { return orderDate; }
};
