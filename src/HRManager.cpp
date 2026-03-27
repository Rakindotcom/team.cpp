#include "Employee.cpp"
#include <bits/stdc++.h>
using namespace std;

class HRManager
{
private:
    vector<Employee> employees;

    void loadWorkforce()
    {
        ifstream file("workforce.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, name, dept, design;
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, dept, '|');
            getline(ss, design, '|');

            employees.push_back(Employee(id, name, dept, design));
        }
        file.close();
    }

    void saveWorkforce()
    {
        ofstream file("workforce.txt");
        if (!file.is_open()) return;

        for (int i = 0; i < employees.size(); i++) {
            file << employees[i].getId() << "|"
                 << employees[i].getName() << "|"
                 << employees[i].getDepartment() << "|"
                 << employees[i].getRole() << "\n";
        }
        file.close();
    }

public:
    HRManager()
    {
        loadWorkforce();
    }

    vector<Employee>& getEmployees() { return employees; }

    void addEmployee(Employee e)
    {
        employees.push_back(e);
        saveWorkforce();
    }

    void removeEmployee(string id)
    {
        int oldSize = employees.size();
        removeEntityById(employees, id);
        if (employees.size() < oldSize) saveWorkforce();
    }
};
