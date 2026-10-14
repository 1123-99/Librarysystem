#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "resource.h"

class Library {
private:
    std::vector<Resource*> resources_; // 资源列表，负责管理所有资源的指针
    int nextId_;
    // 记录每个学生借了哪些资源：key是学生ID，Value是资源指针列表
    std::unordered_map<std::string, std::vector<Resource*>> borrowed_;

    Resource* findById(int id) const;
public:
    Library();
    ~Library();

    // 添加新资源。注意：调用者将资源的所有权交给Library，Library负责释放内存
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
