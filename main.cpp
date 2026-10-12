#include <iostream>
#include <string>
#include <limits>
#include "library.h"
#include "resource.h"

// Derived resource types
class BookRes : public Resource {
private:
    std::string author_;
    std::string isbn_;
    int pages_;
public:
    BookRes(int id, const std::string& title, int count, const std::string& author, const std::string& isbn, int pages)
    : Resource(id, title, count), author_(author), isbn_(isbn), pages_(pages) {}

    void displayInfo(std::ostream& os = std::cout) const override {
        os << "[Book] ID: " << id_ << " | Title: " << title_ << " | Author: " << author_ << " | ISBN: " << isbn_
           << " | Pages: " << pages_ << " | Count: " << count_ << std::endl;
    }
};

class MagazineRes : public Resource {
private:
    int issue_;
    std::string period_;
public:
    MagazineRes(int id, const std::string& title, int count, int issue, const std::string& period)
    : Resource(id, title, count), issue_(issue), period_(period) {}

    void displayInfo(std::ostream& os = std::cout) const override {
        os << "[Magazine] ID: " << id_ << " | Title: " << title_ << " | Issue: " << issue_ << " | Period: " << period_
           << " | Count: " << count_ << std::endl;
    }
};

class ElectronicRes : public Resource {
private:
    std::string format_;
    std::string url_;
public:
    ElectronicRes(int id, const std::string& title, int count, const std::string& format, const std::string& url)
    : Resource(id, title, count), format_(format), url_(url) {}

    void displayInfo(std::ostream& os = std::cout) const override {
        os << "[Electronic] ID: " << id_ << " | Title: " << title_ << " | Format: " << format_ << " | URL: " << url_
           << " | Count: " << count_ << std::endl;
    }
};

// Helper to read line
static void readLine(std::string &out) {
    std::getline(std::cin, out);
}

int main() {
    Library lib;
    int nextId = 1; // simple id generator

    while (true) {
        std::cout << "\n=== 图书资源管理系统 ===\n";
        std::cout << "1. 增加新的图书或资源\n";
        std::cout << "2. 增加已有图书或资源的数量\n";
        std::cout << "3. 显示某一图书或资源情况\n";
        std::cout << "4. 显示所有图书或资源情况\n";
        std::cout << "5. 减少已有图书或资源的数量\n";
        std::cout << "6. 删除某一图书或资源\n";
        std::cout << "7. 学生借阅图书或资源\n";
        std::cout << "8. 学生归还图书或资源\n";
        std::cout << "9. 退出\n";
        std::cout << "选择操作(1-9): ";
        int choice = 0;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "输入无效，请输入数字。" << std::endl;
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "选择资源类型：1=Book 2=Magazine 3=Electronic: ";
            int t; std::cin >> t; std::cin.ignore();
            std::string title; int count;
            std::cout << "输入标题: "; std::getline(std::cin, title);
            std::cout << "输入数量: "; std::cin >> count; std::cin.ignore();
            if (t == 1) {
                std::string author, isbn; int pages;
                std::cout << "作者: "; std::getline(std::cin, author);
                std::cout << "ISBN: "; std::getline(std::cin, isbn);
                std::cout << "页数: "; std::cin >> pages; std::cin.ignore();
                Resource* r = new BookRes(nextId++, title, count, author, isbn, pages);
                lib.addResource(r);
                std::cout << "添加 Book 成功，ID=" << r->getId() << std::endl;
            } else if (t == 2) {
                int issue; std::string period;
                std::cout << "期号: "; std::cin >> issue; std::cin.ignore();
                std::cout << "发行周期: "; std::getline(std::cin, period);
                Resource* r = new MagazineRes(nextId++, title, count, issue, period);
                lib.addResource(r);
                std::cout << "添加 Magazine 成功，ID=" << r->getId() << std::endl;
            } else if (t == 3) {
                std::string format, url;
                std::cout << "格式 (PDF/EPUB/...): "; std::getline(std::cin, format);
                std::cout << "URL: "; std::getline(std::cin, url);
                Resource* r = new ElectronicRes(nextId++, title, count, format, url);
                lib.addResource(r);
                std::cout << "添加 Electronic 成功，ID=" << r->getId() << std::endl;
            } else {
                std::cout << "未知类型" << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "输入资源ID: "; int id; std::cin >> id; std::cin.ignore();
            std::cout << "增加数量: "; int n; std::cin >> n; std::cin.ignore();
            if (lib.increaseResource(id, n)) std::cout << "增加成功" << std::endl; else std::cout << "增加失败" << std::endl;
        } else if (choice == 3) {
            std::cout << "输入资源ID: "; int id; std::cin >> id; std::cin.ignore();
            lib.displayResource(id);
        } else if (choice == 4) {
            lib.displayAll();
        } else if (choice == 5) {
            std::cout << "输入资源ID: "; int id; std::cin >> id; std::cin.ignore();
            std::cout << "减少数量: "; int n; std::cin >> n; std::cin.ignore();
            if (lib.decreaseResource(id, n)) std::cout << "减少成功" << std::endl; else std::cout << "减少失败" << std::endl;
        } else if (choice == 6) {
            std::cout << "输入资源ID: "; int id; std::cin >> id; std::cin.ignore();
            if (lib.deleteResource(id)) std::cout << "删除成功" << std::endl; else std::cout << "删除失败" << std::endl;
        } else if (choice == 7) {
            std::string sid; int id;
            std::cout << "学生ID: "; std::getline(std::cin, sid);
            std::cout << "资源ID: "; std::cin >> id; std::cin.ignore();
            lib.borrowResource(sid, id);
        } else if (choice == 8) {
            std::string sid; int id;
            std::cout << "学生ID: "; std::getline(std::cin, sid);
            std::cout << "资源ID: "; std::cin >> id; std::cin.ignore();
            lib.returnResource(sid, id);
        } else if (choice == 9) {
            std::cout << "退出系统。" << std::endl;
            break;
        } else {
            std::cout << "无效选项" << std::endl;
        }
    }

    return 0;
}
