#include "student.h"
#include <algorithm>

Student::Student() : name_(""), id_("") {}
Student::Student(const std::string& name, const std::string& id) : name_(name), id_(id) {}

const std::string& Student::getName() const { return name_; }
const std::string& Student::getId() const { return id_; }

bool Student::borrowBook(Book& book) {
    if (!book.isAvailable()) return false;
    book.setAvailable(false);
    borrowed_.push_back(book);
    return true;
}

bool Student::returnBook(Book& book) {
    const std::string& isbn = book.getISBN();
    auto it = std::find_if(borrowed_.begin(), borrowed_.end(),
        [&isbn](const Book& b){ return b.getISBN() == isbn; });
    if (it == borrowed_.end()) return false;
    book.setAvailable(true);
    borrowed_.erase(it);
    return true;
}

void Student::listBorrowed(std::ostream& os) const {
    os << "学生：" << name_ << " (学号: " << id_ << ")\n";
    os << "已借图书数量: " << borrowed_.size() << "\n";
    for (size_t i = 0; i < borrowed_.size(); ++i) {
        os << "---- 图书" << (i+1) << " ----\n";
        borrowed_[i].showInfo(os);
    }
    if (borrowed_.empty()) os << "（无）\n";
}

bool Student::hasBorrowedISBN(const std::string& isbn) const {
    return std::any_of(borrowed_.begin(), borrowed_.end(),
        [&isbn](const Book& b){ return b.getISBN() == isbn; });
}
