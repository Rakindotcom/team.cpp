#pragma once
#include <string>
#include <vector>
#include <map>

namespace GarmentFactory {

class PatternPiece {
private:
    std::string pieceId;
    std::string pieceName; // "Sleeve", "Collar"
    std::string garmentType;
    double length;
    double width;
    std::string fabricType;

public:
    PatternPiece(std::string name, double l, double w, std::string fabric)
        : pieceName(name), length(l), width(w), fabricType(fabric) {}

    double calculateArea() const { return length * width; }
    bool validateDimensions() const { return length > 0 && width > 0; }
};

class Garment {
private:
    std::string garmentId;
    std::string garmentType; // "Shirt", "Trousers"
    std::string sizeRange;   // "S-XL"
    std::string fabricType;
    double baseFabricRequirement;
    std::vector<PatternPiece> contains;

public:
    Garment() {}
    Garment(std::string id, std::string type, std::string size, std::string fabric, double baseReq)
        : garmentId(id), garmentType(type), sizeRange(size), fabricType(fabric), baseFabricRequirement(baseReq) {}

    void addPatternPiece(const PatternPiece& piece) {
        contains.push_back(piece);
    }

    // Returns generic Map<MaterialName, Quantity>
    std::map<std::string, double> calculateMaterial() const {
        std::map<std::string, double> mats;
        mats[fabricType] = baseFabricRequirement;
        return mats;
    }

    double estimateCost() const {
        // Simplified
        return baseFabricRequirement * 10.0; 
    }
    
    std::string getName() const { return garmentType + " (" + sizeRange + ")"; }
};

} // namespace GarmentFactory
