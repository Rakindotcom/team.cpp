#pragma once
#include "Employee.cpp"
#include <vector>
#include <algorithm>

namespace GarmentFactory {

class HRManager {
private:
    std::vector<Employee> employees;
    std::vector<ShiftSchedule> schedules;

public:
    HRManager() {
        // Seed Employees
        employees.emplace_back("E001", "Alice Smith", "Production", "Operator");
        employees.emplace_back("E002", "Bob Jones", "Production", "Operator");
        employees.emplace_back("E003", "Charlie Day", "Maintenance", "Technician");
    }

    void manageShifts() {
        // Auto-assign logic could go here
    }

    std::string generateWorkforceReport() {
        int active = 0; 
        for(const auto& e : employees) if(e.getLoad() > 0) active++;
        return "Workforce: " + std::to_string(active) + " active out of " + std::to_string(employees.size());
    }
    
    std::vector<Employee>& getEmployees() { return employees; }
    
    Employee* findEmployee(std::string id) {
        for(auto& e : employees) if(e.getId() == id) return &e;
        return nullptr;
    }
};

} // namespace GarmentFactory
