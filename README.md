# Garment Factory Management System

A desktop application built with C++ and Raylib that simulates the internal management operations of a clothing manufacturing plant. The system provides a graphical user interface for managing production orders, workforce, and warehouse inventory.

---

## Project Overview

This project models a real-world garment factory using Object-Oriented Programming principles. It allows users to schedule production orders for clothing items, manage employees across departments, track raw material inventory, and monitor the production pipeline through a visual dashboard. All data is persisted to text files so changes are saved between sessions.

---

## Key Features

| Feature | Description |
|---|---|
| **Production Dashboard** | View all active production orders with live status and progress bars |
| **Order Scheduling** | Create new production batches by specifying garment type, size, fabric, and quantity |
| **Manual Status Control** | Click to advance order status through factory stages: Pending → Cutting → Sewing → QC → Completed |
| **Employee Management** | Add and remove workers with name, role, and department. Displayed in a card grid layout |
| **Inventory Tracking** | Add and remove warehouse items with name, category, and stock quantity |
| **Data Persistence** | All employees, inventory items, and orders are saved to text files automatically |
| **Modern GUI** | Dark-themed professional interface built with Raylib and custom UI components |

---

## Project Structure

```
team.cpp/
├── build.bat                  # Build script (compiles and runs the app)
├── app.exe                    # Compiled executable
├── OBJECTSANSREGULAR.OTF      # Custom font file
├── workforce.txt              # Saved employee data
├── inventory.txt              # Saved inventory data
├── orders.txt                 # Saved production order data
└── src/
    ├── main.cpp               # Entry point, GUI screens, app loop
    ├── Employee.cpp            # Person (abstract) and Employee classes
    ├── Garment.cpp             # Garment class for clothing items
    ├── ProductionOrder.cpp     # ProductionOrder class with status management
    ├── HRManager.cpp           # Employee management with file I/O
    ├── InventoryManager.cpp    # Inventory management with file I/O, template
    ├── OrderManager.cpp        # Order scheduling and persistence
    ├── GuiTheme.h              # Color palette, font sizes, UI constants
    ├── GuiTheme.cpp            # Font loading/unloading
    ├── GuiComponents.h         # UI component function declarations
    └── GuiComponents.cpp       # Button, Card, Input, Label implementations
```

---

## Classes and Their Functions

### Person (Abstract Base Class) — `Employee.cpp`
| Member | Type | Description |
|---|---|---|
| `personId` | protected string | Unique ID for the person |
| `name` | protected string | Full name |
| `getRole()` | pure virtual | Must be implemented by derived classes |
| `getId()` | getter | Returns person ID |
| `getName()` | getter | Returns name |

### Employee (inherits Person) — `Employee.cpp`
| Member | Type | Description |
|---|---|---|
| `department` | string | Department (e.g., Production, Maintenance) |
| `designation` | string | Job title (e.g., Operator, Technician) |
| `currentLoad` | int | Current workload percentage |
| `getRole()` | override | Returns designation (polymorphism) |
| `getDepartment()` | getter | Returns department name |

### Garment — `Garment.cpp`
| Member | Type | Description |
|---|---|---|
| `garmentId` | string | Unique garment identifier |
| `garmentType` | string | Type of clothing (Shirt, Pants, etc.) |
| `sizeRange` | string | Size specification (M, L, XL) |
| `fabricType` | string | Material used (Cotton, Silk, etc.) |
| `baseFabricRequirement` | double | Meters of fabric needed per unit |
| `getName()` | getter | Returns type and size as formatted string |

### ProductionOrder — `ProductionOrder.cpp`
| Member | Type | Description |
|---|---|---|
| `orderId` | string | Unique order ID (e.g., PO-1) |
| `garment` | Garment | The garment being produced |
| `quantity` | int | Number of units to produce |
| `status` | string | Current stage (Pending/Cutting/Sewing/QC/Completed) |
| `progress` | float | Completion percentage (0.0 to 1.0) |
| `advanceStatus()` | method | Moves order to next production stage |

### InventoryItem — `InventoryManager.cpp`
| Member | Type | Description |
|---|---|---|
| `itemId` | string | Unique item identifier |
| `itemName` | string | Name of the inventory item |
| `category` | string | Category (Fabric, Thread, Accessories) |
| `currentStock` | double | Current quantity in warehouse |
| `unit` | string | Unit of measurement (meters, spools, pcs) |
| `updateStock()` | method | Adds quantity to current stock |
| `operator+=` | overload | Adds stock using += operator |

### InventoryManager — `InventoryManager.cpp`
| Member | Type | Description |
|---|---|---|
| `allItems` | vector | List of all inventory items |
| `addItem()` | method | Adds a new item and saves to file |
| `removeItem()` | method | Removes item using template function |
| `loadInventory()` | private | Loads data from inventory.txt |
| `saveInventory()` | private | Saves data to inventory.txt |

### HRManager — `HRManager.cpp`
| Member | Type | Description |
|---|---|---|
| `employees` | vector | List of all employees |
| `addEmployee()` | method | Adds employee and saves to file |
| `removeEmployee()` | method | Removes employee using template function |
| `loadWorkforce()` | private | Loads data from workforce.txt |
| `saveWorkforce()` | private | Saves data to workforce.txt |

### OrderManager — `OrderManager.cpp`
| Member | Type | Description |
|---|---|---|
| `activeOrders` | vector | List of production orders |
| `scheduleOrder()` | method | Creates a new production order and saves |
| `advanceOrderStatus()` | method | Advances a specific order's status and saves |
| `loadOrders()` | private | Loads orders from orders.txt |
| `saveOrders()` | public | Saves orders to orders.txt |

---

## OOP Concepts Used

### 1. Classes and Objects
Every entity in the system (Employee, Garment, ProductionOrder, InventoryItem) is modeled as a class with private attributes and public methods.

### 2. Encapsulation
All class attributes are declared `private` and accessed only through public getter methods.

### 3. Abstract Class
The `Person` class in `Employee.cpp` is abstract — it contains a pure virtual function `getRole()` and cannot be instantiated directly.

```cpp
class Person {
public:
    virtual string getRole() const = 0;  // Pure virtual
};
```

### 4. Inheritance
`Employee` inherits from `Person` using public inheritance, reusing the `personId` and `name` attributes.

```cpp
class Employee : public Person {
    // Inherits getId(), getName() from Person
};
```

### 5. Polymorphism (Virtual Functions)
`Employee` overrides the pure virtual function `getRole()` from `Person`, demonstrating runtime polymorphism.

```cpp
string getRole() const override { return designation; }
```

### 6. Operator Overloading
The `InventoryItem` class overloads the `+=` operator to add stock quantities naturally.

```cpp
void operator+=(double qty) {
    currentStock += qty;
}
```

### 7. Templates (Generic Programming)
A generic `removeEntityById` template function works with any class that has a `getId()` method.

```cpp
template <typename T>
void removeEntityById(vector<T>& vec, string id) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (it->getId() == id) { vec.erase(it); break; }
    }
}
// Used by both HRManager and InventoryManager
```

### 8. Exception Handling
A custom exception class `InvalidInputException` inherits from `std::exception` and is thrown when invalid order quantities are entered.

```cpp
class InvalidInputException : public exception {
public:
    const char* what() const throw() {
        return "Quantity must be greater than zero!";
    }
};

// Usage:
try {
    if (qty <= 0) throw InvalidInputException();
} catch (const InvalidInputException& e) {
    cout << "Exception Caught: " << e.what() << endl;
}
```

### 9. File Handling
Data persistence is implemented using `ifstream` and `ofstream` with pipe-delimited (`|`) text file format for employees, inventory, and orders.

### 10. Composition
Classes use other classes as member variables. For example, `ProductionOrder` contains a `Garment` object, and `OrderManager` holds pointers to `InventoryManager` and `HRManager`.

---

## How to Build and Run

### Requirements
- g++ compiler (MinGW recommended on Windows)
- Raylib 5.5 library installed at `C:\raylib-5.5\build\raylib`

### Build
```bash
# Using the build script
./build.bat

# Or manually
g++ src/main.cpp -o app.exe -O2 -std=c++17 -IC:\raylib-5.5\build\raylib\include -LC:\raylib-5.5\build\raylib -lraylib -lopengl32 -lgdi32 -lwinmm -I src
```

### Run
```bash
app.exe
```

---

## Data File Format

### workforce.txt
```
E001|Rakin|Production|Operator
E002|Abdullah|Production|Operator
```

### inventory.txt
```
I001|Cotton Fabric|Fabric|1000|meters
I002|Red Thread|Thread|500|spools
```

### orders.txt
```
PO-1|G01|Shirt|L|Cotton|2.5|100|2025-12-31|Pending|Normal|0|Mon Mar 27 ...
```

---

## GUI Screens

1. **Dashboard** — Lists all orders with clickable status buttons and progress bars
2. **Create Order** — Form with text input fields for scheduling new production batches
3. **Workforce** — Employee card grid with add/remove functionality
4. **Inventory** — Item list with add/remove functionality and stock tracking

---

## Technologies Used

- **Language:** C++ (C++17 standard)
- **Graphics Library:** Raylib 5.5
- **Font:** Object Sans Regular (custom OTF)
- **Build System:** Batch script with g++ compiler
- **Data Storage:** Plain text files (pipe-delimited format)
