#include <bits/stdc++.h>
using namespace std;

class Machine
{
private:
    string machineId;
    string machineType;
    string model;
    string status;
    string lastMaintenance;
    int dailyCapacity;

public:
    Machine() {}

    Machine(string id, string type, string mod, int capacity)
    {
        machineId = id;
        machineType = type;
        model = mod;
        status = "Operational";
        dailyCapacity = capacity;
    }

    bool isOperational() const { return status == "Operational"; }

    void scheduleMaintenance(string date)
    {
        status = "Maintenance";
        lastMaintenance = date;
    }

    void updateStatus(string newStatus) { status = newStatus; }

    string getDetails() const { return machineType + " - " + status; }
    string getId() const { return machineId; }
};
