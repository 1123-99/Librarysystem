#include "library.h"
#include "bookres.h"
#include "magazineres.h"
#include "electronicres.h"
#include "resource.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

Library::Library() : nextId_(1) {}
Library::~Library() { clear(); }

Resource* Library::findById(int id) const {
    for (const auto& up : resources_) if (up->getId() == id) return up.get();
    return nullptr;
}

int Library::addResource(std::unique_ptr<Resource> res) {
    if (!res) return -1;
    int id = res->getId();
    if (id <= 0) {
        id = nextId_++;
        // cannot reset id_ (protected), so assume constructors set id properly
    } else {
        if (id >= nextId_) nextId_ = id + 1;
    }
    resources_.push_back(std::move(res));
    return id;
}

bool Library::increaseResource(int id, int n) {
    Resource* r = findById(id);
    if (!r || n <= 0) return false;
    r->addCount(n);
    return true;
}

bool Library::decreaseResource(int id, int n) {
    Resource* r = findById(id);
    if (!r || n <= 0) return false;
    return r->reduceCount(n);
}

bool Library::deleteResource(int id) {
    // check borrowed
    for (const auto& kv : borrowed_) {
        for (int bid : kv.second) if (bid == id) {
            std::cerr << "Cannot delete: resource id " << id << " is borrowed." << std::endl;
            return false;
        }
    }
    auto it = std::find_if(resources_.begin(), resources_.end(), [id](const std::unique_ptr<Resource>& up){ return up->getId() == id; });
    if (it != resources_.end()) {
        resources_.erase(it);
        return true;
    }
    return false;
}

void Library::displayResource(int id) const {
    Resource* r = findById(id);
    if (!r) { std::cout << "Resource id " << id << " not found." << std::endl; return; }
    r->displayInfo();
}

void Library::displayAll() const {
    if (resources_.empty()) { std::cout << "No resources." << std::endl; return; }
    for (const auto& up : resources_) {
        up->displayInfo();
    }
}

bool Library::borrowResource(const std::string& studentId, int id) {
    Resource* r = findById(id);
    if (!r) { std::cout << "Resource not found." << std::endl; return false; }
    if (!r->reduceCount(1)) { std::cout << "No available copies." << std::endl; return false; }
    borrowed_[studentId].push_back(id);
    std::cout << "Student " << studentId << " borrowed resource " << id << std::endl;
    return true;
}

bool Library::returnResource(const std::string& studentId, int id) {
    auto it = borrowed_.find(studentId);
    if (it == borrowed_.end()) { std::cout << "Student has no borrowed resources." << std::endl; return false; }
    auto &vec = it->second;
    auto vit = std::find(vec.begin(), vec.end(), id);
    if (vit == vec.end()) { std::cout << "Student did not borrow this resource." << std::endl; return false; }
    Resource* r = findById(id);
    if (!r) { std::cout << "Resource no longer exists in library." << std::endl; return false; }
    r->addCount(1);
    vec.erase(vit);
    std::cout << "Student " << studentId << " returned resource " << id << std::endl;
    return true;
}

bool Library::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) return false;
    for (const auto& up : resources_) {
        ofs << up->serialize() << "\n";
    }
    return true;
}

bool Library::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) return false;
    clear();
    std::string line;
    while (std::getline(ifs, line)) {
        if (line.empty()) continue;
        auto res = Resource::deserialize(line);
        if (res) {
            if (res->getId() >= nextId_) nextId_ = res->getId() + 1;
            resources_.push_back(std::move(res));
        }
    }
    return true;
}

void Library::clear() {
    resources_.clear();
    borrowed_.clear();
}
