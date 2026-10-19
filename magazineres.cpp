#include "magazineres.h"
#include <sstream>

MagazineRes::MagazineRes(int id, const std::string& title, int count, int issue, const std::string& period)
    : Resource(id, title, count), issue_(issue), period_(period) {}

MagazineRes::~MagazineRes() {}

void MagazineRes::displayInfo(std::ostream& os) const {
    os << "[Magazine] ID:" << id_ << " Title:" << title_ << " Issue:" << issue_
       << " Period:" << period_ << " Count:" << count_ << std::endl;
}

std::string MagazineRes::serialize() const {
    std::ostringstream oss;
    oss << "MAGAZINE|" << id_ << "|" << title_ << "|" << count_ << "|" << issue_ << "|" << period_;
    return oss.str();
}
