#include <bits/stdc++.h>
using namespace std;

class Garment
{
private:
    string garmentId;
    string garmentType;
    string sizeRange;
    string fabricType;
    double baseFabricRequirement;

public:
    Garment() {}

    Garment(string id, string type, string size, string fabric, double baseReq)
    {
        garmentId = id;
        garmentType = type;
        sizeRange = size;
        fabricType = fabric;
        baseFabricRequirement = baseReq;
    }

    string getName() const { return garmentType + " (" + sizeRange + ")"; }
    string getId() const { return garmentId; }
    string getType() const { return garmentType; }
    string getSize() const { return sizeRange; }
    string getFabric() const { return fabricType; }
    double getBaseReq() const { return baseFabricRequirement; }
};
