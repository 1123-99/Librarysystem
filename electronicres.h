#ifndef ELECTRONICRES_H
#define ELECTRONICRES_H

#include "resource.h"
#include <string>

class ElectronicRes : public Resource {
private:
    std::string format_;
    std::string url_;
public:
    ElectronicRes(int id, const std::string& title, int count, const std::string& format, const std::string& url);
    ~ElectronicRes() override;

    void displayInfo(std::ostream& os = std::cout) const override;
    std::string serialize() const override;
};

#endif // ELECTRONICRES_H
