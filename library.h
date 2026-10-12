#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "resource.h"

class Library {
private:
    std::vector<Resource*> resources_; // owner of resources
    int nextId_;
    // map student id -> vector of borrowed Resource* (duplicates allowed)
    std::unordered_map<std::string, std::vector<Resource*>> borrowed_;

    Resource* findById(int id) const;
public:
    Library();
    ~Library();

    // add a new resource (caller transfers ownership)
    int addResource(Resource* res);
    bool increaseResource(int id, int n);
    bool decreaseResource(int id, int n);
    bool deleteResource(int id);
    void displayResource(int id) const;
    void displayAll() const;

    bool borrowResource(const std::string& studentId, int id);
    bool returnResource(const std::string& studentId, int id);
};

#endif // LIBRARY_H
