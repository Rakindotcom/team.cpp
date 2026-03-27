#include <bits/stdc++.h>
using namespace std;

class PatternPiece
{
private:
    string pieceId;
    string pieceName;
    string garmentType;
    double length;
    double width;
    string fabricType;

public:
    PatternPiece(string name, double l, double w, string fabric)
        : pieceName(name), length(l), width(w), fabricType(fabric) {}

    double calculateArea() const { return length * width; }
    bool validateDimensions() const { return length > 0 && width > 0; }
};

class Garment
{
private:
    string garmentId;
    string garmentType;
    string sizeRange;
    string fabricType;
    double baseFabricRequirement;
    vector<PatternPiece> contains;

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

    void addPatternPiece(PatternPiece piece)
    {
        contains.push_back(piece);
    }

    map<string, double> calculateMaterial() const
    {
        map<string, double> mats;
        mats[fabricType] = baseFabricRequirement;
        return mats;
    }

    double estimateCost() const
    {
        return baseFabricRequirement * 10.0;
    }

    string getName() const { return garmentType + " (" + sizeRange + ")"; }
    string getId() const { return garmentId; }
    string getType() const { return garmentType; }
    string getSize() const { return sizeRange; }
    string getFabric() const { return fabricType; }
    double getBaseReq() const { return baseFabricRequirement; }
};
