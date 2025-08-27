#include "PartBatch.h"
#include <fstream>

PartBatch::PartBatch(int norm_parts, int bad_parts, double porog, double fine,
    long timeSpent, long norm_time, string name_detail,
    int tabNumber, string name_worker, double costPerItem, int type)
    : norm_parts_(norm_parts), bad_parts_(bad_parts), porog_(porog), fine_(fine),
    timeSpent_(timeSpent), norm_time_(norm_time),
    name_detail_(name_detail), tabNumber_(tabNumber),
    name_worker_(name_worker), costPerItem_(costPerItem), type_(type) {
}

double PartBatch::AnalyzeBraka() {
    int total = GetTotal();
    if (total == 0) return 0.0;
    return (static_cast<double>(GetBadParts()) / total) * 100.0;
}

bool PartBatch::IsBrak() {
    return AnalyzeBraka() > porog_;
}

double PartBatch::CalculateFine() {
    return GetBadParts() * fine_;
}

int PartBatch::GetTotal() {
    return norm_parts_ + bad_parts_;
}

long PartBatch::GetPenaltyTime() {
    long penalty = timeSpent_ - (GetTotal() * norm_time_);
    return penalty > 0 ? penalty : 0;
}

StandardPartBatch::StandardPartBatch(int norm_parts, int bad_parts,
    long timeSpent, long norm_time, string name_detail,
    int tabNumber, string name_worker, double costPerItem)
    : PartBatch(norm_parts, bad_parts, 5.0, 100000.0,
        timeSpent, norm_time, name_detail,
        tabNumber, name_worker, costPerItem, 0) {
}

bool StandardPartBatch::IsBrak() {
    return PartBatch::IsBrak();
}

double StandardPartBatch::CalculateFine() {
    return PartBatch::CalculateFine();
}

CriticalPartBatch::CriticalPartBatch(int norm_parts, int bad_parts,
    long timeSpent, long norm_time, string name_detail,
    int tabNumber, string name_worker, double costPerItem)
    : PartBatch(norm_parts, bad_parts, 2.0, 500000.0,
        timeSpent, norm_time, name_detail,
        tabNumber, name_worker, costPerItem, 1) {
}

bool CriticalPartBatch::IsBrak() {
    return PartBatch::IsBrak();
}

double CriticalPartBatch::CalculateFine() {
    return PartBatch::CalculateFine();
}

int PartBatch::GetNormParts() {
    return norm_parts_;
}

int PartBatch::GetBadParts() {
    return bad_parts_;
}

bool PartBatch::IsLate() {
    return timeSpent_ > (GetTotal() * norm_time_);
}

string PartBatch::GetName() {
    return name_detail_;
}

long PartBatch::GetTimeSpent() {
    return timeSpent_;
}

long PartBatch::GetNormTime() {
    return norm_time_;
}

int PartBatch::GetTabNumber() {
    return tabNumber_;
}

string PartBatch::GetWorkerName() {
    return name_worker_;
}

PartBatch::~PartBatch() {}
StandardPartBatch::~StandardPartBatch() {}
CriticalPartBatch::~CriticalPartBatch() {}
