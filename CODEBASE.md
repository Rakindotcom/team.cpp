# Garment Factory Management System — Complete Codebase Documentation

This document contains a complete, line-by-line breakdown of every file in the project. Every class, struct, function, variable, constant, enum, and parameter is described in full detail. After reading this document, you will know exactly what every piece of code does without ever opening the source files.

---

## Table of Contents

1. [Employee.cpp](#1-employeecpp)
2. [Garment.cpp](#2-garmentcpp)
3. [ProductionOrder.cpp](#3-productionordercpp)
4. [InventoryManager.cpp](#4-inventorymanagercpp)
5. [HRManager.cpp](#5-hrmanagercpp)
6. [OrderManager.cpp](#6-ordermanagercpp)
7. [GuiTheme.h](#7-guithemeh)
8. [GuiTheme.cpp](#8-guithemecpp)
9. [GuiComponents.h](#9-guicomponentsh)
10. [GuiComponents.cpp](#10-guicomponentscpp)
11. [main.cpp](#11-maincpp)

---

## 1. Employee.cpp

**Purpose:** Defines the `Person` abstract base class and the `Employee` derived class. This file demonstrates **Abstract Classes**, **Inheritance**, and **Polymorphism (Virtual Functions)**.

**Includes:** `<bits/stdc++.h>` (standard library shortcut that imports iostream, string, vector, etc.)

**Included by:** `HRManager.cpp`

---

### Class: `Person` (Abstract Base Class)

This class cannot be instantiated on its own because it contains a pure virtual function. It serves as a base blueprint for any person-type entity in the system.

#### Protected Member Variables

| Variable | Type | Description |
|---|---|---|
| `personId` | `string` | A unique identifier string for the person (e.g., `"E001"`). Declared `protected` so that child classes like `Employee` can access it directly through inheritance, but outside code cannot. |
| `name` | `string` | The full name of the person (e.g., `"Rakin"`). Also `protected` for the same reason. |

#### Constructors

| Constructor | Parameters | Description |
|---|---|---|
| `Person()` | None | Default constructor. Does nothing — exists so that child classes can be default-constructed without errors. |
| `Person(string i, string n)` | `i` = person ID, `n` = name | Parameterized constructor. Uses an **initializer list** (`: personId(i), name(n)`) to directly set both protected fields during object construction, which is more efficient than assignment inside the body. |

#### Destructor

| Destructor | Description |
|---|---|
| `virtual ~Person()` | Virtual destructor. Declared `virtual` so that if a `Person*` pointer points to an `Employee` object and is deleted, the `Employee` destructor runs properly (prevents memory leaks in polymorphic usage). The body is empty `{}` because there is nothing to clean up. |

#### Pure Virtual Function

| Function | Return Type | Description |
|---|---|---|
| `virtual string getRole() const = 0` | `string` | **Pure virtual function** — the `= 0` makes `Person` an abstract class. Any class inheriting from `Person` MUST provide its own implementation of `getRole()`. The `const` keyword means this function promises not to modify any member variables. |

#### Public Getter Methods

| Function | Return Type | Description |
|---|---|---|
| `getId() const` | `string` | Returns the value of `personId`. Marked `const` because it does not modify the object. |
| `getName() const` | `string` | Returns the value of `name`. Marked `const` because it does not modify the object. |

---

### Class: `Employee` (inherits from `Person`)

`Employee` uses **public inheritance** (`class Employee : public Person`), meaning all public members of `Person` remain public in `Employee`. This class represents a single factory worker.

#### Private Member Variables

| Variable | Type | Default | Description |
|---|---|---|---|
| `department` | `string` | Set by constructor | The department the employee belongs to (e.g., `"Production"`, `"Maintenance"`). |
| `designation` | `string` | Set by constructor | The job title or role (e.g., `"Operator"`, `"Technician"`). This is what `getRole()` returns. |
| `employmentStatus` | `string` | `"Active"` | Current employment status. Always set to `"Active"` on construction. |
| `currentLoad` | `int` | `0` | Represents the employee's current workload as a numeric value. Initialized to `0` (no load). |

#### Constructors

| Constructor | Parameters | Description |
|---|---|---|
| `Employee()` | None | Default constructor. Calls `Person()` (the parent default constructor) via the initializer list `: Person()`. Sets `currentLoad` to `0`. Needed so that `vector<Employee>` can resize and create empty objects internally. |
| `Employee(string id, string n, string dept, string desig)` | `id` = employee ID, `n` = name, `dept` = department, `desig` = designation | Main constructor. Calls `Person(id, n)` via the initializer list to set the inherited `personId` and `name` fields. Then sets `department`, `designation`, `employmentStatus` (to `"Active"`), and `currentLoad` (to `0`) inside the body. |

#### Public Methods

| Function | Return Type | Description |
|---|---|---|
| `getRole() const override` | `string` | **Polymorphism in action.** This overrides the pure virtual `getRole()` from `Person`. It returns the `designation` string (e.g., `"Operator"`). The `override` keyword tells the compiler to verify that this actually overrides a base class virtual function — if the signature doesn't match, the compiler will throw an error. |
| `getDepartment() const` | `string` | Returns the `department` string. |
| `getLoad() const` | `int` | Returns the `currentLoad` value. |

---

## 2. Garment.cpp

**Purpose:** Defines the `Garment` class, which represents a type of clothing item that can be manufactured (e.g., a Shirt in size L made of Cotton).

**Includes:** `<bits/stdc++.h>`

**Included by:** `ProductionOrder.cpp`

---

### Class: `Garment`

#### Private Member Variables

| Variable | Type | Description |
|---|---|---|
| `garmentId` | `string` | A unique identifier for this garment definition (e.g., `"G12.345"`). Generated dynamically using `GetTime()` in main.cpp when the user creates a new order. |
| `garmentType` | `string` | The type of clothing being manufactured (e.g., `"Shirt"`, `"Pants"`, `"Jacket"`). Entered by the user in the Create Order form. |
| `sizeRange` | `string` | The target size for the production batch (e.g., `"M"`, `"L"`, `"XL"`). Entered by the user. |
| `fabricType` | `string` | The material required (e.g., `"Cotton"`, `"Silk"`, `"Polyester"`). Entered by the user. |
| `baseFabricRequirement` | `double` | The estimated meters of fabric needed to produce one unit of this garment. Currently hardcoded to `2.5` when created from the UI form. |

#### Constructors

| Constructor | Parameters | Description |
|---|---|---|
| `Garment()` | None | Default constructor with an empty body `{}`. Required because `ProductionOrder` stores a `Garment` as a member variable, and the default `ProductionOrder()` constructor needs to default-construct it. |
| `Garment(string id, string type, string size, string fabric, double baseReq)` | All 5 fields | Main constructor. Sets all five private member variables by simple assignment in the body. |

#### Public Getter Methods

| Function | Return Type | Description |
|---|---|---|
| `getName() const` | `string` | Returns a human-readable formatted string by concatenating `garmentType + " (" + sizeRange + ")"`. For example, if `garmentType` is `"Shirt"` and `sizeRange` is `"L"`, this returns `"Shirt (L)"`. Used in the dashboard to display what the order is for. |
| `getId() const` | `string` | Returns `garmentId`. Used when saving orders to `orders.txt`. |
| `getType() const` | `string` | Returns `garmentType`. Used when saving orders to `orders.txt`. |
| `getSize() const` | `string` | Returns `sizeRange`. Used when saving orders to `orders.txt`. |
| `getFabric() const` | `string` | Returns `fabricType`. Used when saving orders to `orders.txt`. |
| `getBaseReq() const` | `double` | Returns `baseFabricRequirement`. Used when saving orders to `orders.txt`. |

---

## 3. ProductionOrder.cpp

**Purpose:** Defines the `ProductionOrder` class, which represents a single manufacturing job in the factory. Each order tracks a garment, a quantity, a status that advances through production stages, and a progress percentage.

**Includes:** `"Garment.cpp"`, `<bits/stdc++.h>`

**Included by:** `OrderManager.cpp`

---

### Class: `ProductionOrder`

This class uses **Composition** — it contains a `Garment` object as a member variable (not a pointer), meaning each `ProductionOrder` owns its own copy of a garment definition.

#### Private Member Variables

| Variable | Type | Default | Description |
|---|---|---|---|
| `orderId` | `string` | Set by constructor | Unique identifier for this order (e.g., `"PO-1"`, `"PO-2"`). Generated sequentially by `OrderManager::scheduleOrder()`. |
| `garment` | `Garment` | Default-constructed | The garment specification for this production run. This is an example of **Composition** — one class containing another class as a member. |
| `quantity` | `int` | Set by constructor | How many units of the garment to produce in this batch (e.g., `100`). |
| `orderDate` | `string` | Current timestamp | The date and time the order was created. Set using `ctime()` which converts the system clock to a human-readable string like `"Thu Mar 27 14:30:00 2025"`. A trailing newline character from `ctime()` is stripped. |
| `deadline` | `string` | Set by constructor | The target completion date for the order. Currently hardcoded to `"2025-12-31"` by `OrderManager`. |
| `status` | `string` | `"Pending"` | The current production stage. Cycles through: `"Pending"` → `"Cutting"` → `"Sewing"` → `"QC"` → `"Completed"`. After `"Completed"`, clicking again resets to `"Pending"`. |
| `priority` | `string` | `"Normal"` | The urgency level of the order. Always set to `"Normal"`. Stored and persisted but not used in the UI. |
| `progress` | `float` | `0.0` | A decimal from `0.0` to `1.0` representing how far along the order is. Maps directly to status: Pending=`0.0`, Cutting=`0.25`, Sewing=`0.50`, QC=`0.75`, Completed=`1.0`. Displayed as a progress bar in the dashboard. |

#### Constructors

| Constructor | Parameters | Description |
|---|---|---|
| `ProductionOrder()` | None | Default constructor. Only sets `progress = 0.0`. Needed for `vector<ProductionOrder>` internal operations. |
| `ProductionOrder(string id, Garment g, int qty, string dline)` | `id`, `g`, `qty`, `dline` | **New order constructor.** Used when the user creates a brand new order from the UI. Sets `status` to `"Pending"`, `priority` to `"Normal"`, `progress` to `0.0`, and captures the current system time as `orderDate` using `time(0)` and `ctime()`. The trailing `\n` from `ctime()` is removed with `orderDate.pop_back()`. |
| `ProductionOrder(string id, Garment g, int qty, string dline, string stat, string prio, float prog, string oDate)` | All 8 fields | **File-loading constructor.** Used by `OrderManager::loadOrders()` to reconstruct a previously saved order from `orders.txt` with its exact saved state, including its current status, priority, progress, and original order date. |

#### Public Methods

| Function | Return Type | Description |
|---|---|---|
| `advanceStatus()` | `void` | Moves the order to the next production stage. Uses a chain of `if/else if` checks on the current `status` string. Each transition also updates the `progress` float to match. The full cycle is: `Pending(0.0)` → `Cutting(0.25)` → `Sewing(0.50)` → `QC(0.75)` → `Completed(1.0)` → back to `Pending(0.0)`. Called from `OrderManager::advanceOrderStatus()` which is triggered when the user clicks the status button on the dashboard. |

#### Public Getter Methods

| Function | Return Type | Description |
|---|---|---|
| `getId() const` | `string` | Returns `orderId` (e.g., `"PO-1"`). |
| `getGarment() const` | `Garment` | Returns a **copy** of the `garment` object (not a reference). Used to access garment details for display and file saving. |
| `getQuantity() const` | `int` | Returns `quantity`. |
| `getStatus() const` | `string` | Returns `status` (e.g., `"Cutting"`). |
| `getProgress() const` | `float` | Returns `progress` (e.g., `0.5`). |
| `getDeadline() const` | `string` | Returns `deadline`. |
| `getPriority() const` | `string` | Returns `priority`. |
| `getOrderDate() const` | `string` | Returns `orderDate`. |

---

## 4. InventoryManager.cpp

**Purpose:** Defines a generic **Template Function**, the `InventoryItem` class (with **Operator Overloading**), and the `InventoryManager` class which handles warehouse inventory management with **File I/O** persistence to `inventory.txt`.

**Includes:** `<bits/stdc++.h>`

**Included by:** `OrderManager.cpp`

---

### Template Function: `removeEntityById<T>`

```cpp
template <typename T>
void removeEntityById(vector<T>& vec, string id)
```

This is a **generic (template) function** — it works with ANY type `T` as long as that type has a public `getId()` method that returns a `string`. The compiler generates a separate version of this function for each type it is used with.

| Parameter | Type | Description |
|---|---|---|
| `vec` | `vector<T>&` | A reference to a vector of any type `T`. Passed by reference so the original vector is modified (not a copy). |
| `id` | `string` | The ID to search for and remove. |

**How it works:** Iterates through the vector using an iterator (`auto it`). For each element, it calls `it->getId()` and compares the result to the target `id`. If a match is found, it calls `vec.erase(it)` to remove that element from the vector and immediately `break`s out of the loop. Only removes the first match.

**Used by:** `HRManager::removeEmployee()` (with `T = Employee`) and `InventoryManager::removeItem()` (with `T = InventoryItem`). This demonstrates how one template function replaces two separate functions that would otherwise contain identical logic.

---

### Class: `InventoryItem`

Represents a single item stored in the factory warehouse (e.g., "Cotton Fabric", "Red Thread", "Buttons").

#### Private Member Variables

| Variable | Type | Description |
|---|---|---|
| `itemId` | `string` | Unique identifier (e.g., `"I001"`, `"I002"`). |
| `itemName` | `string` | Human-readable name of the item (e.g., `"Cotton Fabric"`). |
| `category` | `string` | Classification group (e.g., `"Fabric"`, `"Thread"`, `"Accessories"`). |
| `currentStock` | `double` | The current quantity of this item in the warehouse (e.g., `1000.0`). Type is `double` to allow fractional quantities (e.g., 2.5 meters of fabric). |
| `unit` | `string` | The unit of measurement for `currentStock` (e.g., `"meters"`, `"spools"`, `"pcs"`, `"units"`). |

#### Constructor

| Constructor | Parameters | Description |
|---|---|---|
| `InventoryItem(string id, string name, string cat, double stock, string u)` | `id`, `name`, `cat`, `stock`, `u` | The only constructor. Sets all five fields via assignment. There is no default constructor, which means you cannot create an `InventoryItem` without providing all five values. |

#### Public Methods

| Function | Return Type | Description |
|---|---|---|
| `updateStock(double qty)` | `void` | Adds `qty` to `currentStock`. Can be positive (restocking) or negative (deducting). Example: `item.updateStock(50)` adds 50 to current stock. |
| `operator+=(double qty)` | `void` | **Operator Overloading.** Overloads the `+=` operator so you can write `item += 500` instead of `item.updateStock(500)`. Internally does the exact same thing: `currentStock += qty`. This demonstrates customizing C++ operators for user-defined types. |

#### Public Getter Methods

| Function | Return Type | Description |
|---|---|---|
| `getName() const` | `string` | Returns `itemName`. |
| `getStock() const` | `double` | Returns `currentStock`. |
| `getId() const` | `string` | Returns `itemId`. Required by the `removeEntityById` template. |
| `getCategory() const` | `string` | Returns `category`. |
| `getUnit() const` | `string` | Returns `unit`. |

---

### Class: `InventoryManager`

Manages the entire warehouse inventory. Loads items from `inventory.txt` on startup and saves back whenever items are added or removed.

#### Private Member Variables

| Variable | Type | Description |
|---|---|---|
| `allItems` | `vector<InventoryItem>` | A dynamic array holding all warehouse items. This is the single source of truth for inventory data in memory. |

#### Private Methods (File I/O)

| Function | Return Type | Description |
|---|---|---|
| `loadInventory()` | `void` | Opens `inventory.txt` for reading using `ifstream`. Reads one line at a time with `getline()`. Skips empty lines. For each line, creates a `stringstream` and splits the line by the pipe `\|` delimiter using `getline(ss, field, '\|')` to extract five fields: `id`, `name`, `cat`, `stockStr`, `unit`. Converts `stockStr` to a `double` using `stod()` inside a `try/catch` block (silently skips malformed lines). Constructs an `InventoryItem` and pushes it to `allItems`. Closes the file at the end. If the file doesn't exist or can't be opened, the function returns immediately and `allItems` stays empty. |
| `saveInventory()` | `void` | Opens `inventory.txt` for writing using `ofstream` (this overwrites the entire file). Iterates through every item in `allItems` and writes one line per item in the format: `id\|name\|category\|stock\|unit\n`. Closes the file at the end. If the file can't be opened, returns immediately without doing anything. |

**File format:** `inventory.txt` — each line is pipe-delimited with 5 fields:
```
I001|Cotton Fabric|Fabric|1000|meters
I002|Red Thread|Thread|500|spools
```

#### Constructor

| Constructor | Description |
|---|---|
| `InventoryManager()` | Calls `loadInventory()` to populate `allItems` from `inventory.txt`. If the file doesn't exist, inventory starts empty. |

#### Public Methods

| Function | Return Type | Description |
|---|---|---|
| `addItem(InventoryItem item)` | `void` | Appends the given `item` to the end of `allItems` using `push_back()`. Then immediately calls `saveInventory()` to persist the change to disk. The item is passed **by value** (a copy is made). |
| `removeItem(string id)` | `void` | Records the current vector size in `oldSize`. Calls the template function `removeEntityById(allItems, id)` to find and erase the item with the matching ID. Then compares the new size to `oldSize` — if the size decreased (meaning something was actually removed), calls `saveInventory()` to persist. This check avoids unnecessary file writes when trying to remove an ID that doesn't exist. |
| `getItems()` | `vector<InventoryItem>&` | Returns a **reference** to `allItems`. This means the caller can read (and technically modify) the items directly without copying the entire vector. Used by `main.cpp` to iterate and display items on the Inventory screen. |

---

## 5. HRManager.cpp

**Purpose:** Manages the workforce (list of employees). Loads from and saves to `workforce.txt`. Uses the `removeEntityById` template function from `InventoryManager.cpp`.

**Includes:** `"Employee.cpp"`, `<bits/stdc++.h>`

**Included by:** `OrderManager.cpp`

**Depends on:** The `removeEntityById<T>` template defined in `InventoryManager.cpp` (which is included earlier in the compilation chain via `OrderManager.cpp`).

---

### Class: `HRManager`

#### Private Member Variables

| Variable | Type | Description |
|---|---|---|
| `employees` | `vector<Employee>` | A dynamic array holding all employees. The single source of truth for workforce data in memory. |

#### Private Methods (File I/O)

| Function | Return Type | Description |
|---|---|---|
| `loadWorkforce()` | `void` | Opens `workforce.txt` for reading using `ifstream`. Reads one line at a time. Skips empty lines. Splits each line by `\|` into four fields: `id`, `name`, `dept`, `design` (designation). Constructs an `Employee(id, name, dept, design)` and pushes it to `employees`. Closes the file. If the file doesn't exist, returns immediately and workforce stays empty. |
| `saveWorkforce()` | `void` | Opens `workforce.txt` for writing using `ofstream` (overwrites the entire file). Writes one line per employee in the format: `id\|name\|department\|role\n`. Uses the getter methods `getId()`, `getName()`, `getDepartment()`, and `getRole()` to extract the values. Closes the file. |

**File format:** `workforce.txt` — each line is pipe-delimited with 4 fields:
```
E001|Rakin|Production|Operator
E002|Abdullah|Production|Operator
```

#### Constructor

| Constructor | Description |
|---|---|
| `HRManager()` | Calls `loadWorkforce()` to populate `employees` from `workforce.txt`. |

#### Public Methods

| Function | Return Type | Description |
|---|---|---|
| `getEmployees()` | `vector<Employee>&` | Returns a reference to `employees`. Used by `main.cpp` to iterate and display employee cards on the Workforce screen. |
| `addEmployee(Employee e)` | `void` | Appends `e` to `employees` via `push_back()`. Then calls `saveWorkforce()` to persist. The parameter is passed by value (copy). |
| `removeEmployee(string id)` | `void` | Records `oldSize`. Calls `removeEntityById(employees, id)`. If the size decreased, calls `saveWorkforce()`. |

---

## 6. OrderManager.cpp

**Purpose:** The top-level manager that coordinates production orders. It ties together `InventoryManager` and `HRManager` via pointer composition, and handles order creation, status advancement, and persistence to `orders.txt`.

**Includes:** `"ProductionOrder.cpp"`, `"InventoryManager.cpp"`, `"HRManager.cpp"`, `<bits/stdc++.h>`

**Included by:** `main.cpp`

**Note:** Because `OrderManager.cpp` includes the other three manager files, including just `OrderManager.cpp` in main.cpp brings the entire backend into scope.

---

### Class: `OrderManager`

#### Private Member Variables

| Variable | Type | Description |
|---|---|---|
| `activeOrders` | `vector<ProductionOrder>` | A dynamic array of all production orders (both active and completed). This is the single source of truth for order data in memory. |
| `invMgr` | `InventoryManager*` | A raw pointer to the `InventoryManager` instance created in `main()`. Stored as a pointer (not a copy) so that `OrderManager` operates on the same inventory data as the rest of the application. |
| `hrMgr` | `HRManager*` | A raw pointer to the `HRManager` instance created in `main()`. Same reasoning as above. |

#### Private Methods (File I/O)

| Function | Return Type | Description |
|---|---|---|
| `loadOrders()` | `void` | Opens `orders.txt` for reading. Reads line by line, splits each line by `\|` into 12 fields: `oId` (order ID), `gId` (garment ID), `gType` (garment type), `gSize` (size), `gFab` (fabric), `gBaseStr` (base fabric requirement as string), `qtyStr` (quantity as string), `dline` (deadline), `stat` (status), `prio` (priority), `progStr` (progress as string), `oDate` (order date). Converts numeric strings using `stod()`, `stoi()`, `stof()` inside a `try/catch` (silently skips bad lines). Reconstructs a `Garment` object and then a `ProductionOrder` using the 8-parameter file-loading constructor. Pushes to `activeOrders`. |

**File format:** `orders.txt` — each line is pipe-delimited with 12 fields:
```
PO-1|G12.345|Shirt|L|Cotton|2.5|100|2025-12-31|Cutting|Normal|0.25|Thu Mar 27 14:30:00 2025
```

#### Constructor

| Constructor | Parameters | Description |
|---|---|---|
| `OrderManager(InventoryManager* i, HRManager* h)` | `i` = pointer to inventory manager, `h` = pointer to HR manager | Stores the two pointers into `invMgr` and `hrMgr`. Then calls `loadOrders()` to populate `activeOrders` from `orders.txt`. |

#### Public Methods

| Function | Return Type | Description |
|---|---|---|
| `saveOrders()` | `void` | Opens `orders.txt` for writing (overwrites). For each order in `activeOrders`, extracts the `Garment` object via `getGarment()`, then writes all 12 fields separated by `\|` on a single line. The fields are: order ID, garment ID, garment type, garment size, garment fabric, base fabric requirement, quantity, deadline, status, priority, progress, order date. Closes the file. |
| `scheduleOrder(Garment garment, int quantity)` | `void` | Creates a new production order. Generates an ID by concatenating `"PO-"` with the next sequential number (`activeOrders.size() + 1`). Creates a `ProductionOrder` with a hardcoded deadline of `"2025-12-31"`. Pushes it to `activeOrders`. Calls `saveOrders()` to persist. |
| `advanceOrderStatus(int index)` | `void` | Validates that `index` is within bounds (`>= 0` and `< activeOrders.size()`). If valid, calls `activeOrders[index].advanceStatus()` to move that order to the next production stage, then calls `saveOrders()` to persist the state change. Called from `main.cpp` when the user clicks a status button on the dashboard. |
| `getOrders()` | `vector<ProductionOrder>&` | Returns a reference to `activeOrders`. Used by `main.cpp` to iterate and display order cards on the Dashboard screen. |

---

## 7. GuiTheme.h

**Purpose:** Header file that declares all visual constants (colors, font sizes, spacing) and the global font variable. Acts as the centralized design system / style sheet for the entire GUI.

**Includes:** `"raylib.h"`

**Included by:** `GuiComponents.h` → `GuiComponents.cpp` → `main.cpp`

**Header Guard:** `#ifndef GUITHEME_H` / `#define GUITHEME_H` / `#endif` — prevents the file from being included multiple times during compilation, which would cause "duplicate definition" errors.

---

### Global Variable Declaration

| Variable | Type | Description |
|---|---|---|
| `extern Font AppFont` | `Font` (Raylib type) | Declares that a `Font` variable named `AppFont` exists somewhere (defined in `GuiTheme.cpp`). The `extern` keyword tells the compiler "this variable is defined in another file, don't create a new one here." Every file that includes this header can use `AppFont` to render text. |

### Function Declarations

| Function | Description |
|---|---|
| `void LoadThemeResources()` | Declared here, defined in `GuiTheme.cpp`. Loads the custom font from disk. |
| `void UnloadThemeResources()` | Declared here, defined in `GuiTheme.cpp`. Frees the font from memory. |

### Color Constants (Background Colors)

All colors use Raylib's `Color` struct `{R, G, B, A}` where each value is 0-255.

| Constant | RGBA Value | Visual | Description |
|---|---|---|---|
| `COL_BACKGROUND` | `{15, 23, 42, 255}` | Very dark navy blue | The main background color of the entire window. Equivalent to Tailwind "Slate 900". |
| `COL_SURFACE` | `{30, 41, 59, 255}` | Slightly lighter dark blue | Used for sidebar and card backgrounds — surfaces that sit "on top of" the background. Tailwind "Slate 800". |
| `COL_SURFACE_HOVER` | `{51, 65, 85, 255}` | Medium dark blue | Used when the mouse hovers over a surface element (button, nav item). Tailwind "Slate 700". |

### Color Constants (Accent Colors)

| Constant | RGBA Value | Visual | Description |
|---|---|---|---|
| `COL_PRIMARY` | `{59, 130, 246, 255}` | Bright blue | The main brand/accent color. Used for primary buttons, active nav indicators, order IDs, stock numbers, and avatar circles. Tailwind "Blue 500". |
| `COL_PRIMARY_HOVER` | `{37, 99, 235, 255}` | Darker blue | Used when the mouse hovers over a primary button. Tailwind "Blue 600". |
| `COL_SECONDARY` | `{16, 185, 129, 255}` | Emerald green | Used for progress bar fills and employee role text. Tailwind "Emerald 500". |
| `COL_ACCENT` | `{239, 68, 68, 255}` | Red | Available for error states or alerts. Tailwind "Red 500". Not currently used in the UI but defined for future use. |

### Color Constants (Text Colors)

| Constant | RGBA Value | Visual | Description |
|---|---|---|---|
| `COL_TEXT_PRIMARY` | `{248, 250, 252, 255}` | Near-white | Used for main headings, item names, employee names — the most important text. Tailwind "Slate 50". |
| `COL_TEXT_SECONDARY` | `{148, 163, 184, 255}` | Light grey-blue | Used for supporting text like subtitles, quantities, department labels. Tailwind "Slate 400". |
| `COL_TEXT_MUTED` | `{71, 85, 105, 255}` | Dark grey | Used for the least important text like IDs, column headers, and "No active orders" messages. Tailwind "Slate 600". |

### Color Constants (UI Elements)

| Constant | RGBA Value | Description |
|---|---|---|
| `COL_BORDER` | `{51, 65, 85, 255}` | Used for card borders, sidebar border, input field borders, and separator lines. Same as Slate 700. |
| `COL_SHADOW` | `{0, 0, 0, 80}` | A semi-transparent black. Used to draw subtle drop shadows behind buttons and cards (the shadow rectangle is drawn 2px below the actual element). Alpha of 80/255 ≈ 31% opacity. |

### Dimension Constants

| Constant | Type | Value | Description |
|---|---|---|---|
| `PADDING` | `int` | `24` | Standard spacing unit in pixels. Currently defined but the UI uses hardcoded pixel values instead of referencing this constant. |
| `BORDER_RADIUS` | `float` | `6.0` | The corner rounding for cards, buttons, and inputs. Passed to Raylib's `DrawRectangleRounded()` as a ratio of `BORDER_RADIUS / elementHeight`. |
| `FONT_SIZE_HEADER` | `int` | `36` | Pixel size for page titles like "Production Dashboard", "Employee Directory". |
| `FONT_SIZE_TITLE` | `int` | `20` | Pixel size for card titles like order IDs, employee names, stock numbers. |
| `FONT_SIZE_BODY` | `int` | `16` | Pixel size for regular body text, form labels, button text, descriptions. |
| `FONT_SIZE_SMALL` | `int` | `13` | Pixel size for small text like column headers, employee IDs, department labels. |

---

## 8. GuiTheme.cpp

**Purpose:** Implementation file for the theme system. Defines the global `AppFont` variable and the functions to load/unload the custom font.

**Includes:** `"GuiTheme.h"`, `<bits/stdc++.h>`

**Included by:** `main.cpp`

---

### Global Variable Definition

| Variable | Type | Initial Value | Description |
|---|---|---|---|
| `AppFont` | `Font` | `{ 0 }` (zero-initialized) | The actual definition of the font variable declared as `extern` in `GuiTheme.h`. Initialized to zero/empty. Gets populated when `LoadThemeResources()` is called. Used by every drawing function in `GuiComponents.cpp` to render text in the custom font. |

### Functions

| Function | Return Type | Description |
|---|---|---|
| `LoadThemeResources()` | `void` | Loads the custom font file `"OBJECTSANSREGULAR.OTF"` from the working directory (next to `app.exe`). Uses Raylib's `LoadFontEx()` with a size of `64` pixels (high resolution for crisp scaling). The last two parameters `0, 0` mean "load all default character glyphs." Then applies `TEXTURE_FILTER_BILINEAR` to the font's texture for smooth anti-aliased rendering at any size. Prints `"GuiTheme: Font Loaded"` to the console as a confirmation message. |
| `UnloadThemeResources()` | `void` | Checks if `AppFont` is valid using Raylib's `IsFontValid()`. If so, calls `UnloadFont(AppFont)` to free the texture and font data from GPU/CPU memory. Called when the user exits the application. |

---

## 9. GuiComponents.h

**Purpose:** Header file declaring all custom UI component functions. These functions abstract away raw Raylib drawing calls into reusable, styled components.

**Includes:** `"raylib.h"`, `"GuiTheme.h"`, `<bits/stdc++.h>`

**Included by:** `GuiComponents.cpp`

**Header Guard:** `#ifndef GUICOMPONENTS_H` / `#define GUICOMPONENTS_H` / `#endif`

---

### Enum: `Icon`

```cpp
enum Icon { ICON_NONE, ICON_HOME, ICON_USER, ICON_SETTINGS };
```

Defines available icon types for navigation buttons. Currently only `ICON_NONE` is used — the others are defined as placeholders. The `DrawNavButton` function accepts an `Icon` parameter with a default of `ICON_NONE`, but the icon is never actually drawn.

### Function Declarations

| Function | Parameters | Return | Description |
|---|---|---|---|
| `DrawButton(Rectangle bounds, string text)` | `bounds` = position/size, `text` = label | `bool` | Draws a primary (blue) action button. Returns `true` on the frame the user clicks it. |
| `DrawButtonSecondary(Rectangle bounds, string text)` | Same | `bool` | Draws a secondary (outlined/subtle) button. Returns `true` on click. |
| `DrawCard(Rectangle bounds)` | `bounds` = position/size | `void` | Draws a card background panel with shadow and border. |
| `DrawInput(Rectangle bounds, string& buffer, int maxLen, bool active)` | `bounds` = position/size, `buffer` = text variable (by ref), `maxLen` = character limit, `active` = has focus | `bool` | Draws a text input field. Handles keyboard input when `active`. Returns `true` if content changed. |
| `DrawNavButton(Rectangle bounds, string text, bool selected, Icon icon)` | `bounds`, `text`, `selected` = is current page, `icon` = unused (default `ICON_NONE`) | `bool` | Draws a sidebar navigation button. Returns `true` on click. |
| `DrawLabel(string text, Vector2 pos, int fontSize, Color color)` | `text`, `pos` = {x,y}, `fontSize`, `color` | `void` | Draws text at a position using the custom font. |
| `DrawHeader(string title)` | `title` = text | `void` | Draws a centered header at the top of the screen. |
| `IsMouseOver(Rectangle bounds)` | `bounds` = area to check | `bool` | Returns `true` if the mouse cursor is inside the given rectangle. |

---

## 10. GuiComponents.cpp

**Purpose:** Implementation of all custom UI components. Each function draws styled Raylib shapes and handles mouse/keyboard interaction. This is the rendering engine for the application's user interface.

**Includes:** `"GuiComponents.h"`

**Included by:** `main.cpp`

---

### Helper Functions

#### `IsMouseOver(Rectangle bounds) → bool`
Calls Raylib's `CheckCollisionPointRec(GetMousePosition(), bounds)` to test if the current mouse position is inside the given rectangular area. Used internally by every interactive component to detect hover states.

#### `DrawTextCentered(string text, Rectangle bounds, int fontSize, Color color) → void`
A private helper (not declared in the header). Measures the text dimensions using `MeasureTextEx(AppFont, ...)`, then calculates the X and Y position needed to center the text both horizontally and vertically within the given `bounds` rectangle. Draws the text at that calculated position. Used by `DrawButton` and `DrawButtonSecondary` to center their labels.

---

### Component Functions

#### `DrawButton(Rectangle bounds, string text) → bool`

Draws a **primary action button** (solid blue background).

**Visual behavior:**
1. Checks if mouse is hovering (sets background to `COL_PRIMARY_HOVER` if yes, `COL_PRIMARY` if no)
2. Draws a shadow rectangle 2px below the button bounds using `DrawRectangleRounded` with `COL_SHADOW`
3. Draws the main rounded rectangle background
4. Draws centered white text on top

**Interaction:** If hovered AND mouse left button is pressed this frame → returns `true`. Otherwise returns `false`.

---

#### `DrawButtonSecondary(Rectangle bounds, string text) → bool`

Draws a **secondary button** (subtle surface background with border outline).

**Visual behavior:**
1. Background is `COL_SURFACE_HOVER` when hovered, `COL_SURFACE` otherwise
2. No shadow (unlike primary button)
3. Draws a rounded rectangle background
4. Draws a rounded rectangle border outline on top using `DrawRectangleRoundedLinesEx` with `COL_BORDER` at 1.5px thickness
5. Text color is `COL_TEXT_PRIMARY` (white) instead of pure white

**Interaction:** Same as `DrawButton` — returns `true` on click frame.

---

#### `DrawCard(Rectangle bounds) → void`

Draws a **card panel** — a container for grouping related content.

**Visual layers (drawn in order):**
1. Shadow: A rounded rectangle 2px below using `COL_SHADOW`
2. Background: A rounded rectangle at exact bounds using `COL_SURFACE`
3. Border: A rounded outline at 1.0px using `COL_BORDER`

No interaction — returns nothing.

---

#### `DrawInput(Rectangle bounds, string& buffer, int maxLen, bool active) → bool`

Draws an **interactive text input field** and handles keyboard typing.

**Visual behavior:**
1. Background is always `COL_BACKGROUND` (darker than surrounding cards to look "inset")
2. Border color is `COL_PRIMARY` (blue, 2px thick) when `active`, `COL_BORDER` (grey, 1px thick) when not
3. Text is drawn left-aligned with 12px horizontal padding, vertically centered
4. When `active`, a blinking cursor (2px wide blue rectangle) is drawn after the text. The blink is achieved by `(int)(GetTime() * 2.0f) % 2 == 0` — the cursor is visible for 0.5 seconds, invisible for 0.5 seconds, repeating

**Keyboard handling (only when `active` is `true`):**
- `GetCharPressed()` is called in a while loop to consume all characters typed this frame. Characters with ASCII codes 32-125 (space through `}`) are appended to `buffer` if `buffer.length() < maxLen`
- `IsKeyPressed(KEY_BACKSPACE)` removes the last character from `buffer` via `pop_back()`

**Returns:** `true` if the buffer contents changed this frame (character added or removed), `false` otherwise.

---

#### `DrawNavButton(Rectangle bounds, string text, bool selected, Icon icon) → bool`

Draws a **sidebar navigation button**.

**Visual behavior:**
- If `selected` (this is the current page): draws a rounded rectangle with `COL_SURFACE_HOVER` background AND a 3px-wide vertical blue accent bar (`COL_PRIMARY`) on the left side, inset 10px from top and bottom
- If just `hovered` (not selected): draws a rounded rectangle with a 50% faded `COL_SURFACE_HOVER` using Raylib's `Fade()` function
- If neither: draws nothing (transparent background)
- Text color is `COL_PRIMARY` (blue) when selected, `COL_TEXT_SECONDARY` (grey) otherwise
- Text is drawn 24px from the left edge of bounds, vertically centered

**Returns:** `true` if hovered and clicked this frame.

The `Icon icon` parameter is accepted but never used in the drawing logic — it exists for potential future icon rendering.

---

#### `DrawLabel(string text, Vector2 pos, int fontSize, Color color) → void`

The simplest component. Draws text at position `pos` using `AppFont` with the specified `fontSize` and `color`. Character spacing is `1.0f`. This is used throughout the entire application for all text rendering.

---

#### `DrawHeader(string title) → void`

Draws a centered page title. Measures the text width, then calculates horizontal center based on a hardcoded screen width of `1280`. Uses `FONT_SIZE_HEADER` and `COL_TEXT_PRIMARY`. Drawn at Y position `20`. Not currently used by `main.cpp` (the main loop uses `DrawLabel` with manual positioning instead).

---

## 11. main.cpp

**Purpose:** The entry point and central controller of the entire application. Contains the `main()` function which initializes all systems, runs the Raylib game loop at 60 FPS, handles user interaction, draws all four screens (Dashboard, Create Order, Workforce, Inventory), and manages application lifecycle.

**Includes:** `"raylib.h"`, `"GuiComponents.cpp"`, `"GuiTheme.cpp"`, `<iostream>`, `<string>`, `<vector>`, `"OrderManager.cpp"`

**Include chain:** Because `main.cpp` includes `OrderManager.cpp`, which includes `ProductionOrder.cpp` + `InventoryManager.cpp` + `HRManager.cpp`, which include `Garment.cpp` + `Employee.cpp` respectively, the entire backend is compiled through this single include chain.

---

### Class: `InvalidInputException`

```cpp
class InvalidInputException : public exception
```

A custom exception class demonstrating **Exception Handling** and **Inheritance** from the standard library's `std::exception` base class.

| Method | Return Type | Description |
|---|---|---|
| `what() const throw()` | `const char*` | Overrides `exception::what()`. Returns the C-string `"Quantity must be greater than zero!"`. The `throw()` specifier is a legacy C++ feature indicating this function itself won't throw exceptions. |

**Usage:** Thrown in the Create Order form when the user enters a quantity ≤ 0. Caught by a specific `catch (const InvalidInputException& e)` block which prints the error message to the console via `cout`.

---

### Enum: `AppState`

```cpp
enum AppState { DASHBOARD, CREATE_ORDER, WORKERS, INVENTORY };
```

Defines the four pages/screens of the application. The integer values are automatically assigned: `DASHBOARD = 0`, `CREATE_ORDER = 1`, `WORKERS = 2`, `INVENTORY = 3`. The `currentState` variable is compared against these to decide which screen to render.

---

### Function: `main()`

The entire application logic is inside `main()`. Here is a complete breakdown:

#### Initialization Phase (runs once at startup)

| Code | Description |
|---|---|
| `InventoryManager invMgr;` | Creates an `InventoryManager` instance. Constructor automatically loads `inventory.txt`. |
| `HRManager hrMgr;` | Creates an `HRManager` instance. Constructor automatically loads `workforce.txt`. |
| `OrderManager orderMgr(&invMgr, &hrMgr);` | Creates an `OrderManager` instance. Passes addresses of `invMgr` and `hrMgr` as pointers. Constructor loads `orders.txt`. |
| `int screenWidth = 1280;` | Initial window width in pixels. |
| `int screenHeight = 800;` | Initial window height in pixels. |
| `SetConfigFlags(FLAG_MSAA_4X_HINT \| FLAG_WINDOW_RESIZABLE);` | Enables 4x multi-sample anti-aliasing for smooth edges AND allows the user to resize the window. |
| `InitWindow(screenWidth, screenHeight, "Garment Factory Management System");` | Creates the Raylib window with the given dimensions and title bar text. |
| `SetTargetFPS(60);` | Caps the rendering loop at 60 frames per second. |
| `LoadThemeResources();` | Loads the custom font from `OBJECTSANSREGULAR.OTF`. |
| `AppState currentState = DASHBOARD;` | The app starts on the Dashboard screen. |
| `int sidebarWidth = 260;` | The left sidebar is 260 pixels wide. |

#### Lambda: `DrawField`

```cpp
auto DrawField = [](float formX, float yPos, string label, string& val, bool& active, int width = 540) { ... };
```

A reusable form field component defined as a lambda (anonymous function). Combines a text label with a text input field below it.

| Parameter | Type | Description |
|---|---|---|
| `formX` | `float` | X position of the field |
| `yPos` | `float` | Y position of the label (input appears 30px below) |
| `label` | `string` | The text label shown above the input |
| `val` | `string&` | Reference to the string variable that stores typed text |
| `active` | `bool&` | Reference to the boolean tracking if this field has focus |
| `width` | `int` | Width of the input box. Default is `540` pixels. |

**Behavior:** Draws the label using `DrawLabel`. Checks if the mouse was clicked inside the input rectangle — if yes, sets `active = true`; if clicked outside, sets `active = false`. Calls `DrawInput` to render the text box and handle keyboard input.

---

#### Main Game Loop

`while (!WindowShouldClose())` — runs every frame (60 times per second) until the user closes the window via the OS close button or presses ESC (Raylib default).

Each frame:
1. `BeginDrawing()` — starts a new frame
2. `ClearBackground(COL_BACKGROUND)` — fills the entire screen with the dark navy background
3. Draws the sidebar (always visible on all pages)
4. Draws the content for the current page via `switch (currentState)`
5. `EndDrawing()` — finalizes and presents the frame

---

#### Sidebar (drawn every frame, all pages)

| Element | Description |
|---|---|
| Sidebar background | A `COL_SURFACE` rectangle spanning the full height of the window, 260px wide, with a 1px `COL_BORDER` outline. |
| Logo text "GarmentOS" | Drawn at (30, 40) in `FONT_SIZE_HEADER` with `COL_PRIMARY` (blue). |
| Subtitle "Professional Ed." | Drawn at (30, 80) in `FONT_SIZE_SMALL` with `COL_TEXT_MUTED` (grey). |
| Navigation buttons | 4 nav buttons stacked vertically starting at Y=140, spaced 64px apart: "Dashboard", "Create Order", "Workforce", "Inventory". Each is 236px wide × 54px tall. Clicking one sets `currentState` to the corresponding `AppState`. The currently active button is visually highlighted. |
| Exit button | A secondary button near the bottom of the sidebar. When clicked: calls `UnloadThemeResources()` to free the font, calls `CloseWindow()` to destroy the Raylib window, and `return 0` to exit the program. |

#### Content area calculation

```cpp
Rectangle contentArea = {sidebarWidth + 40, 40, GetScreenWidth() - sidebarWidth - 80, GetScreenHeight() - 80};
```
This defines the rectangular region to the right of the sidebar where page content is drawn. It has 40px margins on all sides.

---

#### Screen: DASHBOARD (case `DASHBOARD`)

Displays all production orders as a vertical list of cards.

| Element | Description |
|---|---|
| Title | "Production Dashboard" in header font |
| Subtitle | "Overview of active production orders" in body font, grey |
| Empty state | If `orders` vector is empty, shows "No active orders." in muted color |
| Order cards | For each order, draws a 100px-tall card containing: |
| — Order ID | Top-left in title font, blue (e.g., "PO-1") |
| — Garment name | Below the ID in body font (e.g., "Shirt (L)") |
| — Status button | A secondary button showing "Status: Pending" (or current status). Clicking it calls `orderMgr.advanceOrderStatus(i)` which moves the order to the next stage and saves to file. |
| — Quantity | Below the status button (e.g., "Qty: 100") |
| — Progress bar | A 200px-wide bar at the right side. Background is dark (`COL_BACKGROUND`), filled portion is green (`COL_SECONDARY`) proportional to `progress`. Percentage text is shown to the right (e.g., "50%"). |
| Spacing | Cards are spaced 115px apart vertically (100px card + 15px gap). |

---

#### Screen: CREATE_ORDER (case `CREATE_ORDER`)

A form for creating new production orders.

| Element | Description |
|---|---|
| Title | "New Production Order" in header font |
| Form card | A 600×450 card background |
| Static variables | `type`, `size`, `fabric`, `qtyStr` (all `string`) and their `bool active` flags are declared `static` so they persist between frames (normal local variables would reset every frame at 60 FPS). |
| Input fields | Four `DrawField` calls spaced 90px apart vertically: "Garment Type", "Size Range", "Fabric Type", "Quantity" |
| Submit button | "Schedule Order" primary button. On click: |
| — Validation | Checks `type` and `qtyStr` are not empty |
| — Parsing | Converts `qtyStr` to `int` via `stoi()` |
| — Exception | If `qty <= 0`, throws `InvalidInputException`. Caught and printed to console. |
| — Garment creation | Creates a `Garment` with ID `"G" + GetTime()` (Raylib elapsed time as a unique-ish ID), user-entered type/size/fabric, and hardcoded base requirement of `2.5` |
| — Order scheduling | Calls `orderMgr.scheduleOrder(g, qty)` which creates the order and saves to file |
| — Reset | Clears all four input strings to empty and switches to `DASHBOARD` |

---

#### Screen: WORKERS (case `WORKERS`)

Displays employee cards in a grid layout with an add/remove form.

| Element | Description |
|---|---|
| Title | "Employee Directory" in header font |
| Add form | A card spanning the full content width, containing 3 input fields ("Name" 200px, "Role" 150px, "Department" 150px) and an "Add Worker" button. Static variables `empName`, `empRole`, `empDept` and their active flags persist between frames. |
| — Add logic | Generates ID `"E00" + (current count + 1)`. Creates an `Employee` and calls `hrMgr.addEmployee()`. Clears the fields. |
| Employee grid | Cards are 300×140px, laid out in columns. The column index increments with each card. When the next card would exceed the content width, column resets to 0 and Y jumps down 160px (starting a new row). |
| — Avatar | A 20px-radius blue circle with the first letter of the employee's name drawn inside in white at 24px font size. |
| — Name | Employee name in title font, white |
| — Role | Employee designation in body font, green (`COL_SECONDARY`) |
| — Department | "Dept: Production" in small font, grey |
| — ID | "ID: E001" in small font, muted |
| — Remove button | An 80×25 secondary button "Remove". Calls `hrMgr.removeEmployee(id)` and immediately `break`s the loop (to avoid iterating a modified container). The file is saved automatically inside `removeEmployee()`. |

---

#### Screen: INVENTORY (case `INVENTORY`)

Displays warehouse items in a columnar list with an add/remove form.

| Element | Description |
|---|---|
| Title | "Warehouse Inventory" in header font |
| Add form | A card with 3 fields ("Item Name" 200px, "Category" 150px, "Initial Stock" 150px) and an "Add Item" button. Static variables `iName`, `iCat`, `iStock` and active flags persist between frames. |
| — Add logic | Converts stock to `double` via `stod()` in a try/catch. Generates ID `"I00" + (current count + 1)`. Creates an `InventoryItem` with unit `"units"`. Calls `invMgr.addItem()`. Clears fields. |
| Column headers | "ITEM NAME" at X+20, "CATEGORY" at X+300, "STOCK" at X+500, all in small muted font |
| Separator line | A 1px horizontal line in `COL_BORDER` below the headers |
| Item rows | For each item (spaced 60px apart): |
| — Item name | In body font, white |
| — Item ID | Below the name in small muted font |
| — Category | At X+300, body font, grey |
| — Stock | At X+500, title font, blue. Format: `"1000 meters"` (stock integer + unit) |
| — Remove button | An 80×25 "Remove" button at X+750. Calls `invMgr.removeItem(id)` and `break`s the loop. |

---

#### Shutdown Phase (runs once when loop exits)

| Code | Description |
|---|---|
| `UnloadThemeResources();` | Frees the custom font from memory. |
| `CloseWindow();` | Destroys the Raylib window and releases all GPU resources. |
| `return 0;` | Exits the program with success code 0. |

---

## Include / Compilation Chain

The entire project compiles from a single file. Here is the exact include order:

```
main.cpp
├── raylib.h                    (Raylib graphics library)
├── GuiComponents.cpp
│   └── GuiComponents.h
│       ├── raylib.h
│       └── GuiTheme.h          (colors, fonts, constants)
├── GuiTheme.cpp                (font loading implementation)
│   └── GuiTheme.h
├── <iostream>, <string>, <vector>
└── OrderManager.cpp
    ├── ProductionOrder.cpp
    │   ├── Garment.cpp
    │   │   └── <bits/stdc++.h>
    │   └── <bits/stdc++.h>
    ├── InventoryManager.cpp     (also defines removeEntityById template)
    │   └── <bits/stdc++.h>
    ├── HRManager.cpp
    │   ├── Employee.cpp         (Person + Employee classes)
    │   │   └── <bits/stdc++.h>
    │   └── <bits/stdc++.h>
    └── <bits/stdc++.h>
```

The `g++` compiler processes `main.cpp`, which recursively pulls in all other `.cpp` files via `#include` directives. There is no separate compilation or linking of individual object files — everything compiles as one translation unit.
