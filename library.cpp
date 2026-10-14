#include "library.h"
#include <iostream>

Library::Library() : nextId_(1) {}

Library::~Library() {
    for (Resource* r : resources_) delete r;
    resources_.clear();
}

Resource* Library::findById(int id) const {
    for (Resource* r : resources_) if (r->getId() == id) return r;
    return nullptr;
}

int Library::addResource(Resource* res) {
    if (!res) return -1;
    
    if (res->getId() <= 0) {

    }
    bool idConflict = false;
    for (const Resource* r : resources_) {
        if (r->getId() == res->getId()) {
            idConflict = true;
            break;
        }
    }

    if (idConflict) {
        std::cerr << "Error: Duplicate resource ID" << res->getId() << ".Cannot add." << std::endl;
        delete res;
        return -1;
    }
    
    
    resources_.push_back(res);
    return res->getId();
}

bool Library::increaseResource(int id, int n) {
    Resource* r = findById(id);
    if (!r) return false;
    if (n <= 0) return false;
    r->addCount(n);
    return true;
}

bool Library::decreaseResource(int id, int n) {
    Resource* r = findById(id);
    if (!r) return false;
    if (n <= 0) return false;
    return r->reduceCount(n);
}

bool Library::deleteResource(int id) {
    Resource* r = findById(id);
    if (!r) return false;
    // check borrowed records
    for (const auto& kv : borrowed_) {
        for (Resource* br : kv.second) {
            if (br == r) {
                std::cerr << "Cannot delete resource id " << id << " because it is borrowed by students." << std::endl;
                return false;
            }
        }
    }
    // remove from vector and delete
    auto it = std::find(resources_.begin(), resources_.end(), r);
    if (it != resources_.end()) {
        resources_.erase(it);
        delete r;
        return true;
    }
    return false;
}

void Library::displayResource(int id) const {
    Resource* r = findById(id);
    if (!r) {
        std::cout << "Resource id " << id << " not found." << std::endl;
        return;
    }
    r->displayInfo();
}

void Library::displayAll() const {
    if (resources_.empty()) {
        std::cout << "No resources in library." << std::endl;
        return;
    }
    for (const Resource* r : resources_) {
        r->displayInfo();
        std::cout << "-----------------------" << std::endl;
    }
}

bool Library::borrowResource(const std::string& studentId, int id) {
    Resource* r = findById(id);
    if (!r) {
        std::cout << "Resource not found." << std::endl;
        return false;
    }
    if (!r->reduceCount(1)) {
        std::cout << "No available copies to borrow." << std::endl;
        return false;
    }
    borrowed_[studentId].push_back(r);
    std::cout << "Borrowed resource id " << id << " for student " << studentId << std::endl;
    return true;
}

bool Library::returnResource(const std::string& studentId, int id) {
    auto it = borrowed_.find(studentId);
    if (it == borrowed_.end()) {
        std::cout << "Student has no borrowed resources." << std::endl;
        return false;
    }
    auto &vec = it->second;
    for (auto vit = vec.begin(); vit != vec.end(); ++vit) {
        if ((*vit)->getId() == id) {
            // return
            (*vit)->addCount(1);
            vec.erase(vit);
            std::cout << "Returned resource id " << id << " for student " << studentId << std::endl;
            return true;
        }
    }
    std::cout << "Student did not borrow resource id " << id << std::endl;
    return false;
}
