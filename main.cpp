#include <iostream>
#include <string>
#include <limits>
#include "library.h"
#include "bookres.h"
#include "magazineres.h"
#include "electronicres.h"

static void pause() {
    std::cout << "按回车继续...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Library lib;
    // try load saved data
    lib.loadFromFile("library_db.txt");

    int nextId = 1; // ID generators now handled by constructors; but we will use next id based on lib content when adding
    while (true) {
        std::cout << "\n=== 实验四/五/六：多态图书馆管理系统 ===\n";
        std::cout << "1. 增加新的资源\n";
        std::cout << "2. 增加已有资源数量\n";
        std::cout << "3. 显示某一资源信息\n";
        std::cout << "4. 显示所有资源信息\n";
        std::cout << "5. 减少已有资源数量\n";
        std::cout << "6. 删除某一资源\n";
        std::cout << "7. 学生借阅资源\n";
        std::cout << "8. 学生归还资源\n";
        std::cout << "9. 保存并退出\n";
        std::cout << "选择(1-9): ";
        int choice;
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(1024, '\n'); continue; }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            std::cout << "选择类型：1=Book 2=Magazine 3=Electronic: ";
            int t; std::cin >> t; std::cin.ignore();
            std::string title; int count;
            std::cout << "标题: "; std::getline(std::cin, title);
            std::cout << "数量: "; std::cin >> count; std::cin.ignore();
            if (t == 1) {
                std::string author, isbn; int pages;
                std::cout << "作者: "; std::getline(std::cin, author);
                std::cout << "ISBN: "; std::getline(std::cin, isbn);
                std::cout << "页数: "; std::cin >> pages; std::cin.ignore();
                int id = lib.addResource(std::make_unique<BookRes>(0, title, count, author, isbn, pages));
                std::cout << "添加 Book 成功，ID=" << id << std::endl;
            } else if (t == 2) {
                int issue; std::string period;
                std::cout << "期号: "; std::cin >> issue; std::cin.ignore();
                std::cout << "周期: "; std::getline(std::cin, period);
                int id = lib.addResource(std::make_unique<MagazineRes>(0, title, count, issue, period));
                std::cout << "添加 Magazine 成功，ID=" << id << std::endl;
            } else if (t == 3) {
                std::string format, url;
                std::cout << "格式: "; std::getline(std::cin, format);
                std::cout << "URL: "; std::getline(std::cin, url);
                int id = lib.addResource(std::make_unique<ElectronicRes>(0, title, count, format, url));
                std::cout << "添加 Electronic 成功，ID=" << id << std::endl;
            } else {
                std::cout << "未知类型" << std::endl;
            }
        } else if (choice == 2) {
            std::cout << "资源ID: "; int id; std::cin >> id; std::cin.ignore();
            std::cout << "增加数量: "; int n; std::cin >> n; std::cin.ignore();
            if (lib.increaseResource(id, n)) std::cout << "增加成功" << std::endl; else std::cout << "失败" << std::endl;
        } else if (choice == 3) {
            std::cout << "资源ID: "; int id; std::cin >> id; std::cin.ignore();
            lib.displayResource(id);
            pause();
        } else if (choice == 4) {
            lib.displayAll();
            pause();
        } else if (choice == 5) {
            std::cout << "资源ID: "; int id; std::cin >> id; std::cin.ignore();
            std::cout << "减少数量: "; int n; std::cin >> n; std::cin.ignore();
            if (lib.decreaseResource(id, n)) std::cout << "减少成功" << std::endl; else std::cout << "失败" << std::endl;
        } else if (choice == 6) {
            std::cout << "资源ID: "; int id; std::cin >> id; std::cin.ignore();
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
            lib.saveToFile("library_db.txt");
            std::cout << "已保存，退出。" << std::endl;
            break;
        }
    }

    return 0;
}
