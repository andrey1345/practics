#include "ProductionDepartment.h"
#include <vector>
#include <fstream>
#include <map>

using namespace std;

void ProductionDepartment::AddMaster(WorkshopMaster* master) {
    name_master_.push_back(master);
}

vector<WorkshopMaster*> ProductionDepartment::AnalyzeMasters() {
    vector<WorkshopMaster*> bad_masters;
    map<string, vector<PartBatch*>*>::iterator it;
    for (auto* master : GetNameMaster()) {
        bool has_narush = false;
        for (it = master->GetDetails().begin(); it != master->GetDetails().end(); ++it) {
            for (PartBatch* part : *(it->second)) {
                if (part->IsBrak() || part->IsLate()) {
                    has_narush = true;
                    break;
                }
            }
        }
        if (has_narush) {
            bad_masters.push_back(master);
        }
    }
    return bad_masters;
}

double ProductionDepartment::CalculateGeneralBrak() {
    double summa_fines = 0.0;
    map<string, vector<PartBatch*>*>::iterator it;
    for (WorkshopMaster* master : GetNameMaster()) {
        for (it = master->GetDetails().begin(); it != master->GetDetails().end(); ++it) {
            for (PartBatch* part : *(it->second)) {
                summa_fines += part->CalculateFine();
            }
        }
    }
    return summa_fines;
}

void ProductionDepartment::Svodka(int& summ_details, int& summ_defect_details, double& summ_avg_deffect_procent, int& late_count) {
    summ_details = 0;
    summ_defect_details = 0;
    late_count = 0;
    map<string, vector<PartBatch*>*>::iterator it;
    for (WorkshopMaster* master : GetNameMaster()) {
        for (it = master->GetDetails().begin(); it != master->GetDetails().end(); ++it) {
            for (PartBatch* part : *(it->second)) {
                summ_details += part->GetNormParts() + part->GetBadParts();
                summ_defect_details += part->GetBadParts();
                if (part->IsLate()) {
                    late_count++;
                }
            }
        }
    }

    if (summ_details > 0) {
        summ_avg_deffect_procent = (static_cast<double>(summ_defect_details) / summ_details) * 100.0;
    }
    else {
        summ_avg_deffect_procent = 0.0;
    }
}

const vector< WorkshopMaster*>& ProductionDepartment::GetNameMaster() {
    return name_master_;
}

vector<ProductionDepartment::WorkerResult> ProductionDepartment::CalculateWorkerResults() {
    map<int, WorkerResult> workerResults;

    for (auto master : name_master_) {
        for (auto& detail : master->GetDetails()) {
            for (auto batch : *detail.second) {
                int tabNumber = batch->GetTabNumber();

                if (workerResults.find(tabNumber) == workerResults.end()) {
                    workerResults[tabNumber] = WorkerResult{
                        tabNumber,
                        batch->GetWorkerName(),
                        0.0,
                        0.0,
                        0
                    };
                }

                auto& result = workerResults[tabNumber];
                result.defectPercent += batch->GetBadParts();
                result.penaltyHours += batch->GetPenaltyTime() ;
            }
        }
    }

    vector<WorkerResult> results;
    for (auto& pair : workerResults) {
        auto& result = pair.second;
        double totalParts = 0;
        double totalDefects = 0;

        for (auto master : name_master_) {
            for (auto& detail : master->GetDetails()) {
                for (auto batch : *detail.second) {
                    if (batch->GetTabNumber() == result.tabNumber) {
                        totalParts += batch->GetTotal();
                        totalDefects += batch->GetBadParts();
                    }
                }
            }
        }

        if (totalParts > 0) {
            result.defectPercent = (totalDefects / totalParts) * 100.0;
        }

        result.coefficient = static_cast<int>(100 - result.defectPercent - result.penaltyHours + 0.5);
        if (result.coefficient < 0) result.coefficient = 0;

        results.push_back(result);
    }

    return results;
}
