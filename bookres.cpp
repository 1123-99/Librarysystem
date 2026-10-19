#include "bookres.h"
#include <sstream>

BookRes::BookRes(int id, const std::string& title, int count,
                 const std::string& author, const std::string& isbn, int pages)
    : Resource(id, title, count), author_(author), isbn_(isbn), pages_(pages) {}

BookRes::~BookRes() {}

void BookRes::displayInfo(std::ostream& os) const {
    os << "[Book] ID:" << id_ << " Title:" << title_ << " Author:" << author_
       << " ISBN:" << isbn_ << " Pages:" << pages_ << " Count:" << count_ << std::endl;
}

std::string BookRes::serialize() const {
    std::ostringstream oss;
    oss << "BOOK|" << id_ << "|" << title_ << "|" << count_ << "|" << author_ << "|" << isbn_ << "|" << pages_;
    return oss.str();
}
