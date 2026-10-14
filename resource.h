#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include <iostream>

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

    // 显示资源特定信息
    virtual void displayInfo(std::ostream& os = std::cout) const = 0;
};

#endif // RESOURCE_H
