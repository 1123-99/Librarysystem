#include "electronicres.h"
#include <sstream>

ElectronicRes::ElectronicRes(int id, const std::string& title, int count, const std::string& format, const std::string& url)
    : Resource(id, title, count), format_(format), url_(url) {}

ElectronicRes::~ElectronicRes() {}

void ElectronicRes::displayInfo(std::ostream& os) const {
    os << "[Electronic] ID:" << id_ << " Title:" << title_ << " Format:" << format_
       << " URL:" << url_ << " Count:" << count_ << std::endl;
}

std::string ElectronicRes::serialize() const {
    std::ostringstream oss;
    oss << "ELECTRONIC|" << id_ << "|" << title_ << "|" << count_ << "|" << format_ << "|" << url_;
    return oss.str();
}
