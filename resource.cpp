#include "resource.h"

Resource::Resource(int id, const std::string& title, int count)
    : id_(id), title_(title), count_(count) {}

Resource::~Resource() {}

int Resource::getId() const { return id_; }
const std::string& Resource::getTitle() const { return title_; }
int Resource::getCount() const { return count_; }

void Resource::addCount(int n) { if (n > 0) count_ += n; }

bool Resource::reduceCount(int n) {
    if (n <= 0) return false;
    if (count_ < n) return false;
    count_ -= n;
    return true;
}
