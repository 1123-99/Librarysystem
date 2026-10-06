#include "student.h"
#include <algorithm>

Student::Student() : name_(""), id_("") {
    std::cout << "Student default ctor" << std::endl;
}

Student::Student(const std::string& name, const std::string& id) : name_(name), id_(id) {
    std::cout << "Student ctor: " << name_ << std::endl;
}

Student::~Student() {
    std::cout << "Destructing Student: " << name_ << std::endl;
}

const std::string& Student::getName() const { return name_; }
const std::string& Student::getId() const { return id_; }

bool Student::borrowBook(Book& book) {
    if (!book.isAvailable()) return false;
    book.setAvailable(false);
    // 保存一份副本到学生内部（组合）
    borrowed_.push_back(&book);
    std::cout << "Book copied into Student (composition): " << book.getTitle() << std::endl;
    return true;
}

bool Student::returnBook(Book& book) {
    const std::string& isbn = book.getISBN();
    auto it = std::find_if(borrowed_.begin(), borrowed_.end(),
        [&isbn](const Book* b){ return b->getISBN() == isbn; });
    if (it == borrowed_.end()) return false;
    book.setAvailable(true);
    borrowed_.erase(it);
    std::cout << "Book returned and removed from Student: " << book.getTitle() << std::endl;
    return true;
}

void Student::listBorrowed(std::ostream& os) const {
    os << "学生：" << name_ << " (学号: " << id_ << ")\n";
    os << "已借图书数量: " << borrowed_.size() << "\n";
    for (size_t i = 0; i < borrowed_.size(); ++i) {
        os << "---- 图书" << (i+1) << " ----\n";
        borrowed_[i]->showInfo(os);
    }
    if (borrowed_.empty()) os << "（无）\n";
}

bool Student::hasBorrowedISBN(const std::string& isbn) const {
    return std::any_of(borrowed_.begin(), borrowed_.end(),
        [&isbn](const Book* b){ return b->getISBN() == isbn; });
}
