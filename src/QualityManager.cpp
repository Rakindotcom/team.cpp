#include <bits/stdc++.h>
using namespace std;

struct QualityCheck
{
    string checkId;
    string orderId;
    string inspectorId;
    string date;
    int totalPieces;
    int passedPieces;
    int failedPieces;
    string overallStatus;

    double calculatePassRate()
    {
        if (totalPieces == 0) return 0.0;
        return (double)passedPieces / totalPieces * 100.0;
    }
};

struct DefectLog
{
    string defectId;
    string checkId;
    string severity;
    string description;
};

class QualityManager
{
private:
    vector<QualityCheck> inspections;
    vector<DefectLog> defectLogs;

public:
    void monitorQuality() {}

    void performInspection(string orderId, int total, int passed)
    {
        QualityCheck qc;
        qc.checkId = "QC-" + to_string(inspections.size());
        qc.orderId = orderId;
        qc.totalPieces = total;
        qc.passedPieces = passed;
        qc.failedPieces = total - passed;
        if (qc.calculatePassRate() > 90.0)
            qc.overallStatus = "PASS";
        else
            qc.overallStatus = "FAIL";
        inspections.push_back(qc);
    }

    vector<QualityCheck>& getInspections() { return inspections; }

    string generateQualityReport()
    {
        int passed = 0;
        for (int i = 0; i < inspections.size(); i++)
        {
            if (inspections[i].overallStatus == "PASS") passed++;
        }
        return "Quality Report: " + to_string(passed) + "/" + to_string(inspections.size()) + " Passed.";
    }

    void analyzeDefectTrends()
    {
        // could analyze defectLogs here
    }
};
