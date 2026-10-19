#ifndef BOOKRES_H
#define BOOKRES_H

#include "resource.h"
#include <string>

class BookRes : public Resource {
private:
    std::string author_;
    std::string isbn_;
    int pages_;
public:
    BookRes(int id, const std::string& title, int count,
            const std::string& author, const std::string& isbn, int pages);
    ~BookRes() override;

    void displayInfo(std::ostream& os = std::cout) const override;
    std::string serialize() const override;
};

#endif // BOOKRES_H
