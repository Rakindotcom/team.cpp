#include <bits/stdc++.h>
using namespace std;

struct ShiftSchedule
{
    string shiftId;
    string shiftType;
    string startTime;
    string endTime;
    string date;
    vector<string> assignedEmployees;
};

// Abstract Class & Inheritance
class Person {
protected:
    string personId;
    string name;
public:
    Person() {}
    Person(string i, string n) : personId(i), name(n) {}
    virtual ~Person() {}

    // Pure virtual function -> Abstract Class
    virtual string getRole() const = 0;

    string getId() const { return personId; }
    string getName() const { return name; }
};

class Employee : public Person
{
private:
    string department;
    string designation;
    string contact;
    string joiningDate;
    string employmentStatus;
    vector<string> skills;
    string currentShiftId;
    int currentLoad;

public:
    Employee() : Person() { currentLoad = 0; }

    Employee(string id, string n, string dept, string desig) : Person(id, n)
    {
        department = dept;
        designation = desig;
        employmentStatus = "Active";
        currentLoad = 0;
    }

    void updateProfile(string newContact) { contact = newContact; }
    void addSkill(string skill) { skills.push_back(skill); }

    bool isAvailable() const { return employmentStatus == "Active" && currentLoad < 100; }

    void assignTask()
    {
        currentLoad += 20;
        if (currentLoad > 100) currentLoad = 100;
    }

    void completeTask()
    {
        currentLoad -= 20;
        if (currentLoad < 0) currentLoad = 0;
    }

    // Polymorphism: overriding the pure virtual function
    string getRole() const override { return designation; }
    
    string getDepartment() const { return department; }
    int getLoad() const { return currentLoad; }
};
