#include "WorkshopMaster.h"
#include "PartBatch.h"
#pragma once
#include <vector>
#include <map>

class ProductionDepartment {
private:
    vector<WorkshopMaster*> name_master_;

public:
    struct WorkerResult {
        int tabNumber;
        string name;
        double defectPercent;
        double penaltyHours;
        int coefficient;
    };

    vector<WorkshopMaster*> AnalyzeMasters();
    double CalculateGeneralBrak();
    void AddMaster(WorkshopMaster* master);
    void Svodka(int& summ_details, int& summ_defect_details, double& summ_avg_deffect_procent, int& late_count);
    const vector< WorkshopMaster*>& GetNameMaster();
    vector<WorkerResult> CalculateWorkerResults();
};
