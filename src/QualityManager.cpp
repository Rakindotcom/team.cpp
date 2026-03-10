#pragma once
#include "ProductionOrder.cpp"
#include <vector>

namespace GarmentFactory {

struct QualityCheck {
    std::string checkId;
    std::string orderId;
    std::string inspectorId;
    std::string date; // "YYYY-MM-DD"
    int totalPieces;
    int passedPieces;
    int failedPieces;
    std::string overallStatus; // "PASS", "FAIL"

    double calculatePassRate() {
        if(totalPieces == 0) return 0.0;
        return (double)passedPieces / totalPieces * 100.0;
    }
};

struct DefectLog {
    std::string defectId;
    std::string checkId;
    std::string severity; // "Minor", "Critical"
    std::string description;
};

class QualityManager {
private:
    std::vector<QualityCheck> inspections;
    std::vector<DefectLog> defectLogs;

public:
    void monitorQuality() {}
    
    void performInspection(std::string orderId, int total, int passed) {
        QualityCheck qc;
        qc.checkId = "QC-" + std::to_string(inspections.size());
        qc.orderId = orderId;
        qc.totalPieces = total;
        qc.passedPieces = passed;
        qc.failedPieces = total - passed;
        qc.overallStatus = (qc.calculatePassRate() > 90.0) ? "PASS" : "FAIL";
        inspections.push_back(qc);
    }

    std::vector<QualityCheck>& getInspections() { return inspections; }

    // Analytics
    std::string generateQualityReport() {
        int passed = 0;
        for(const auto& qc : inspections) { if(qc.overallStatus == "PASS") passed++; }
        return "Quality Report: " + std::to_string(passed) + "/" + std::to_string(inspections.size()) + " Passed.";
    }

    void analyzeDefectTrends() {
        // Stub for advanced analytics
        // Could analyze defectLogs vector
    }
};

} // namespace GarmentFactory
