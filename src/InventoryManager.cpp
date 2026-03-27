#include <bits/stdc++.h>
using namespace std;

// Template definition
template <typename T>
void removeEntityById(vector<T>& vec, string id) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        if (it->getId() == id) {
            vec.erase(it);
            break;
        }
    }
}

class InventoryItem
{
private:
    string itemId;
    string itemName;
    string category;
    double currentStock;
    string unit;

public:
    InventoryItem(string id, string name, string cat, double stock, string u)
    {
        itemId = id;
        itemName = name;
        category = cat;
        currentStock = stock;
        unit = u;
    }

    void updateStock(double qty) { currentStock += qty; }

    // Operator Overloading
    void operator+=(double qty) {
        currentStock += qty;
    }

    string getName() const { return itemName; }
    double getStock() const { return currentStock; }
    string getId() const { return itemId; }
    string getCategory() const { return category; }
    string getUnit() const { return unit; }
};

class InventoryManager
{
private:
    vector<InventoryItem> allItems;

    void loadInventory()
    {
        ifstream file("inventory.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string id, name, cat, stockStr, unit;
            getline(ss, id, '|');
            getline(ss, name, '|');
            getline(ss, cat, '|');
            getline(ss, stockStr, '|');
            getline(ss, unit, '|');

            try {
                double stock = stod(stockStr);
                allItems.push_back(InventoryItem(id, name, cat, stock, unit));
            } catch (...) {}
        }
        file.close();
    }

    void saveInventory()
    {
        ofstream file("inventory.txt");
        if (!file.is_open()) return;

        for (int i = 0; i < allItems.size(); i++) {
            file << allItems[i].getId() << "|"
                 << allItems[i].getName() << "|"
                 << allItems[i].getCategory() << "|"
                 << allItems[i].getStock() << "|"
                 << allItems[i].getUnit() << "\n";
        }
        file.close();
    }

public:
    InventoryManager()
    {
        loadInventory();
    }

    void addItem(InventoryItem item)
    {
        allItems.push_back(item);
        saveInventory();
    }

    void removeItem(string id)
    {
        int oldSize = allItems.size();
        removeEntityById(allItems, id);
        if (allItems.size() < oldSize) saveInventory();
    }

    vector<InventoryItem>& getItems() { return allItems; }
};
