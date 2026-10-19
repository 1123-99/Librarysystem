#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "resource.h"

class Library {
private:
    std::vector<std::unique_ptr<Resource>> resources_; // owns resources
    int nextId_;
    // student id -> list of borrowed resource ids
    std::unordered_map<std::string, std::vector<int>> borrowed_;

    Resource* findById(int id) const;
public:
    Library();
    ~Library();

    int addResource(std::unique_ptr<Resource> res); // returns assigned id
    bool increaseResource(int id, int n);
    bool decreaseResource(int id, int n);
    bool deleteResource(int id);
    void displayResource(int id) const;
    void displayAll() const;

    bool borrowResource(const std::string& studentId, int id);
    bool returnResource(const std::string& studentId, int id);

    // persistence
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);

    void clear();
};

#endif // LIBRARY_H
