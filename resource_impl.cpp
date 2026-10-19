#include "resource.h"
#include "bookres.h"
#include "magazineres.h"
#include "electronicres.h"

#include <sstream>

// Helper: split by '|'
static std::vector<std::string> split(const std::string& s, char delim) {
    std::vector<std::string> out;
    std::string token;
    std::istringstream iss(s);
    while (std::getline(iss, token, delim)) out.push_back(token);
    return out;
}

std::unique_ptr<Resource> Resource::deserialize(const std::string& line) {
    auto fields = split(line, '|');
    if (fields.empty()) return nullptr;
    const std::string &type = fields[0];
    try {
        if (type == "BOOK") {
            // BOOK|id|title|count|author|isbn|pages
            if (fields.size() < 7) return nullptr;
            int id = std::stoi(fields[1]);
            std::string title = fields[2];
            int count = std::stoi(fields[3]);
            std::string author = fields[4];
            std::string isbn = fields[5];
            int pages = std::stoi(fields[6]);
            return std::make_unique<BookRes>(id, title, count, author, isbn, pages);
        } else if (type == "MAGAZINE") {
            // MAGAZINE|id|title|count|issue|period
            if (fields.size() < 6) return nullptr;
            int id = std::stoi(fields[1]);
            std::string title = fields[2];
            int count = std::stoi(fields[3]);
            int issue = std::stoi(fields[4]);
            std::string period = fields[5];
            return std::make_unique<MagazineRes>(id, title, count, issue, period);
        } else if (type == "ELECTRONIC") {
            // ELECTRONIC|id|title|count|format|url
            if (fields.size() < 6) return nullptr;
            int id = std::stoi(fields[1]);
            std::string title = fields[2];
            int count = std::stoi(fields[3]);
            std::string format = fields[4];
            std::string url = fields[5];
            return std::make_unique<ElectronicRes>(id, title, count, format, url);
        }
    } catch (...) {
        return nullptr;
    }
    return nullptr;
}
