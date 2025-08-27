#pragma once
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class PartBatch {
protected:
    int norm_parts_;
    int bad_parts_;
    double porog_;
    double fine_;
    long timeSpent_;      
    long norm_time_;      
    string name_detail_;
    int tabNumber_;       
    string name_worker_;  
    double costPerItem_;  
    int type_;            

public:
    PartBatch(int norm_parts, int bad_parts, double porog, double fine,
        long timeSpent, long norm_time, string name_detail,
        int tabNumber, string name_worker, double costPerItem, int type);

    virtual double AnalyzeBraka();
    virtual bool IsBrak();
    virtual double CalculateFine();
    int GetNormParts();
    int GetBadParts();
    virtual ~PartBatch();
    bool IsLate();
    string GetName();
    long GetTimeSpent();
    long GetNormTime();
    int GetTabNumber();
    string GetWorkerName();
    int GetTotal();
    long GetPenaltyTime();
};

class StandardPartBatch : public PartBatch {
public:
    StandardPartBatch(int norm_parts, int bad_parts,
        long timeSpent, long norm_time, string name_detail,
        int tabNumber, string name_worker, double costPerItem);

    bool IsBrak() override;
    double CalculateFine() override;
    ~StandardPartBatch() override;
};

class CriticalPartBatch : public PartBatch {
public:
    CriticalPartBatch(int norm_parts, int bad_parts,
        long timeSpent, long norm_time, string name_detail,
        int tabNumber, string name_worker, double costPerItem);

    bool IsBrak() override;
    double CalculateFine() override;
    ~CriticalPartBatch() override;
};
