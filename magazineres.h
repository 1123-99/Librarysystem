#ifndef MAGAZINERES_H
#define MAGAZINERES_H

#include "resource.h"
#include <string>

class MagazineRes : public Resource {
private:
    int issue_;
    std::string period_;
public:
    MagazineRes(int id, const std::string& title, int count, int issue, const std::string& period);
    ~MagazineRes() override;

    void displayInfo(std::ostream& os = std::cout) const override;
    std::string serialize() const override;
};

#endif // MAGAZINERES_H
