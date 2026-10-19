#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>
#include <memory>

// Base class for all resources
class Resource {
protected:
    int id_;
    std::string title_;
    int count_;
public:
    Resource(int id, const std::string& title, int count);
    virtual ~Resource();

    int getId() const;
    const std::string& getTitle() const;
    int getCount() const;

    void addCount(int n);
    bool reduceCount(int n);

    virtual void displayInfo(std::ostream& os = std::cout) const = 0;

    // Serialization: write a single-line representation (type|fields...)
    virtual std::string serialize() const = 0;

    // Factory: parse a line and return a resource instance
    // Implemented in resource.cpp
    static std::unique_ptr<Resource> deserialize(const std::string& line);
};

#endif // RESOURCE_H
