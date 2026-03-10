#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

namespace GarmentFactory {

struct ShiftSchedule {
    std::string shiftId;
    std::string shiftType; // "Morning", "Evening"
    std::string startTime;
    std::string endTime;
    std::string date;
    
    // In a full DB these would be IDs, keeping strings for MVP
    std::vector<std::string> assignedEmployees; 
};

class Employee {
private:
    std::string employeeId;
    std::string name;
    std::string department; // "Production", "Quality", "HR"
    std::string designation; // "Operator", "Supervisor"
    std::string contact;
    std::string joiningDate;
    std::string employmentStatus; // "Active", "OnLeave"
    
    std::vector<std::string> skills;
    // Current Schedule context
    std::string currentShiftId; 
    int currentLoad; // 0-100%

public:
    Employee() {}
    Employee(std::string id, std::string n, std::string dept, std::string desig)
        : employeeId(id), name(n), department(dept), designation(desig), employmentStatus("Active"), currentLoad(0) {}

    void updateProfile(std::string newContact) { contact = newContact; }
    
    void addSkill(std::string skill) { skills.push_back(skill); }

    // Logic from previous 'Worker' class adapted
    bool isAvailable() const { return employmentStatus == "Active" && currentLoad < 100; }
    
    void assignTask() { currentLoad += 20; if(currentLoad > 100) currentLoad = 100; }
    void completeTask() { currentLoad -= 20; if(currentLoad < 0) currentLoad = 0; }

    std::string getId() const { return employeeId; }
    std::string getName() const { return name; }
    std::string getRole() const { return designation; }
    std::string getDepartment() const { return department; }
    int getLoad() const { return currentLoad; }
};

} // namespace GarmentFactory
