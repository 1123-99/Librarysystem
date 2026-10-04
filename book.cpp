#include "book.h"
#include <algorithm>
#include <cctype>

namespace {
    // 去除连字符和空白
    std::string sanitize_local(const std::string& s) {
        std::string out;
        out.reserve(s.size());
        for (char c : s) {
            if (c == '-' || c == ' ' || c == '\t' || c == '\r' || c == '\n') continue;
            out.push_back(c);
        }
        return out;
    }

    bool isDigits(const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::isdigit(c); });
    }

    bool isValidISBN10_local(const std::string& raw) {
        std::string s = sanitize_local(raw);
        if (s.size() != 10) return false;
        for (size_t i = 0; i < 9; ++i) {
            if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
        }
        int sum = 0;
        for (int i = 0; i < 10; ++i) {
            int val = 0;
            if (i == 9) {
                char c = s[i];
                if (c == 'X' || c == 'x') val = 10;
                else if (std::isdigit(static_cast<unsigned char>(c))) val = c - '0';
                else return false;
            } else {
                val = s[i] - '0';
            }
            sum += (10 - i) * val;
        }
        return (sum % 11) == 0;
    }

    bool isValidISBN13_local(const std::string& raw) {
        std::string s = sanitize_local(raw);
        if (s.size() != 13) return false;
        if (!isDigits(s)) return false;
        int sum = 0;
        for (int i = 0; i < 12; ++i) {
            int d = s[i] - '0';
            sum += (i % 2 == 0) ? d : 3 * d;
        }
        int check = (10 - (sum % 10)) % 10;
        int last = s[12] - '0';
        return check == last;
    }
}

std::string Book::sanitize(const std::string& s) {
    return sanitize_local(s);
}

Book::Book()
    : title_("未命名图书"), isbn_(""), press_("未知出版社"), price_(0.0), pages_(0), available_(true), isbnValid_(false) {
    std::cout << "Book ctor: " << title_ << std::endl;
}

Book::Book(const std::string& title,
           const std::string& isbn,
           const std::string& press,
           double price,
           int pages,
           bool available)
    : title_(title), isbn_(""), press_(press), price_(0.0), pages_(0), available_(available), isbnValid_(false) {
    setPrice(price);
    setPages(pages);
    setISBN(isbn);
    std::cout << "Book ctor: " << title_ << std::endl;
}

Book::Book(const Book& other)
    : title_(other.title_), isbn_(other.isbn_), press_(other.press_), price_(other.price_), pages_(other.pages_), available_(other.available_), isbnValid_(other.isbnValid_) {
    std::cout << "Book copy ctor: " << title_ << std::endl;
}

Book::Book(Book&& other) noexcept
    : title_(std::move(other.title_)), isbn_(std::move(other.isbn_)), press_(std::move(other.press_)), price_(other.price_), pages_(other.pages_), available_(other.available_), isbnValid_(other.isbnValid_) {
    std::cout << "Book move ctor: " << title_ << std::endl;
}

Book::~Book() {
    std::cout << "Book destroyed: " << title_ << std::endl;
}

void Book::setTitle(const std::string& title) { title_ = title; }
void Book::setISBN(const std::string& isbn) {
    isbnValid_ = isValidISBN(isbn);
    isbn_ = isbn;
}
void Book::setPress(const std::string& press) { press_ = press; }
void Book::setPrice(double price) {
    if (price >= 0) price_ = price;
    else {
        std::cerr << "[Warning] 价格不能为负，操作被忽略。\n";
    }
}
void Book::setPages(int pages) {
    if (pages >= 0) pages_ = pages;
    else std::cerr << "[Warning] 页数应为非负整数，操作被忽略。\n";
}
void Book::setAvailable(bool available) { available_ = available; }

const std::string& Book::getTitle() const { return title_; }
const std::string& Book::getISBN() const { return isbn_; }
const std::string& Book::getPress() const { return press_; }
double Book::getPrice() const { return price_; }
int Book::getPages() const { return pages_; }
bool Book::isAvailable() const { return available_; }
bool Book::isISBNValid() const { return isbnValid_; }

void Book::showInfo(std::ostream& os) const {
    os << "书名： " << title_ << "\n";
    os << "ISBN： " << isbn_ << "  (" << (isbnValid_ ? "合法" : "不合法") << ")\n";
    os << "出版社： " << press_ << "\n";
    os << "价格： " << price_ << "\n";
    os << "页数： " << pages_ << "\n";
    os << "在馆： " << (available_ ? "可借" : "已借出") << "\n";
}

bool Book::isValidISBN(const std::string& isbn) {
    std::string s = sanitize(isbn);
    if (s.empty()) return false;
    if (s.size() == 10) return isValidISBN10_local(isbn);
    if (s.size() == 13) return isValidISBN13_local(isbn);
    return false;
}
