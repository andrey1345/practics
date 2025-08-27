#include "PartBatch.h"
#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

class WorkshopMaster {
private:
    string name_master_;
    map <string, vector<PartBatch*>*> details_;

public:
    string GetName() const;
    WorkshopMaster(string name_master);
    ~WorkshopMaster();
    void AddDetails(PartBatch* details);
    map <string, vector<PartBatch*>*>& GetDetails();
    void SortVectors();
};
