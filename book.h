#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book {
private:
    std::string title_;
    std::string isbn_;
    std::string press_;
    double price_;
    int pages_;
    bool available_;
    bool isbnValid_;

    // 辅助函数实现放在 cpp 中
    static std::string sanitize(const std::string& s);

public:
    Book();
    Book(const std::string& title,
         const std::string& isbn,
         const std::string& press,
         double price,
         int pages,
         bool available = true);

    // 拷贝/移动/析构，用于观察生命周期
    Book(const Book& other);
    Book(Book&& other) noexcept;
    ~Book();

    // setters
    void setTitle(const std::string& title);
    void setISBN(const std::string& isbn);
    void setPress(const std::string& press);
    void setPrice(double price);
    void setPages(int pages);
    void setAvailable(bool available);

    // getters
    const std::string& getTitle() const;
    const std::string& getISBN() const;
    const std::string& getPress() const;
    double getPrice() const;
    int getPages() const;
    bool isAvailable() const;
    bool isISBNValid() const;

    // 输出
    void showInfo(std::ostream& os = std::cout) const;

    // 静态校验函数
    static bool isValidISBN(const std::string& isbn);
};

#endif // BOOK_H
