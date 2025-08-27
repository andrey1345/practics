#include "WorkshopMaster.h"
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

WorkshopMaster::WorkshopMaster(string name) : name_master_(name) {}

WorkshopMaster::~WorkshopMaster() {
    if (GetDetails().empty()) {
        return;
    }
    else {
        map<string, vector<PartBatch*>*>::iterator it;
        for (it = details_.begin(); it != details_.end(); ++it) {
            delete it->second;
        }
    }
}

void WorkshopMaster::AddDetails(PartBatch* detail) {
    string name = detail->GetName();
    vector<PartBatch*>* v;
    if (details_.find(name) != details_.end()) {
        v = details_[name];
    }
    else {
        details_.emplace(name, v = new vector<PartBatch*>());
    }
    v->push_back(detail);
}

string WorkshopMaster::GetName() const {
    return name_master_;
}

map<string, vector <PartBatch*>*>& WorkshopMaster::GetDetails() {
    return details_;
}

int CmpPartBatch(PartBatch* a, PartBatch* b) {
    return a->GetTimeSpent() < b->GetTimeSpent();
}

void WorkshopMaster::SortVectors() {
    for (map <string, vector<PartBatch*>*>::iterator it = details_.begin(); it != details_.end(); ++it) {
        sort(it->second->begin(), it->second->end(), CmpPartBatch);
    }
}
