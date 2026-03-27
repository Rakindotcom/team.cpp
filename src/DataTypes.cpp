#include <bits/stdc++.h>
using namespace std;

// basic item info for orders
struct Item
{
    string itemId;
    string name;
    string description;
    map<string, int> recipe;

    Item()
    {
        itemId = "";
        name = "";
        description = "";
    }

    Item(string id, string n, string desc)
    {
        itemId = id;
        name = n;
        description = desc;
    }
};

// material info for inventory
struct FabricMaterial
{
    string materialId;
    string name;
    string unit;

    FabricMaterial()
    {
        materialId = "";
        name = "";
        unit = "units";
    }

    FabricMaterial(string id, string n, string u = "units")
    {
        materialId = id;
        name = n;
        unit = u;
    }
};
