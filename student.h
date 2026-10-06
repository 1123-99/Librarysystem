#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <iostream>
#include "book.h"

class Student {
private:
    std::string name_;
    std::string id_;
    // 组合：学生内部保存已借图书的副本
    std::vector<Book*> borrowed_;

public:
    Student();
    Student(const std::string& name, const std::string& id);
    ~Student();

    // 禁用拷贝以便观察显式拷贝（可按需启用）
    Student(const Student&) = delete;
    Student& operator=(const Student&) = delete;

    const std::string& getName() const;
    const std::string& getId() const;

    // 依赖：借书通过 Book& 传入（外部馆藏对象）
    bool borrowBook(Book& book);
    bool returnBook(Book& book);
    void listBorrowed(std::ostream& os = std::cout) const;
    bool hasBorrowedISBN(const std::string& isbn) const;
};

#endif // STUDENT_H
