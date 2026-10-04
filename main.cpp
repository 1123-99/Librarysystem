#include <iostream>
#include "book.h"
#include "student.h"

int main() {
    std::cout << "=== Book 类与 Student 借书示例（含生命周期/拷贝/构造演示） ===\n\n";

    // 局部作用域用于演示对象在离开作用域时析构
    {
        Book b1("C++ Primer", "978-7-115-54747-1", "人民邮电出版社", 59.8, 380, true);
        Book b2("经典物理学", "0306406152", "科学出版社", 45.0, 320, true);
        Book b3("错误ISBN示例", "123abc456", "无名出版社", 10.0, 100, true);

        b1.showInfo(); std::cout << "----------\n";
        b2.showInfo(); std::cout << "----------\n";
        b3.showInfo(); std::cout << "----------\n";

        std::cout << "将 b3 的 ISBN 修改为合法 ISBN-10: 0306406152\n";
        b3.setISBN("0306406152");
        b3.showInfo();
        std::cout << "==========\n\n";

        Student s("张三", "2026001");
        std::cout << "张三尝试借 b1\n";
        bool ok = s.borrowBook(b1);
        std::cout << (ok ? "借书成功\n" : "借书失败\n");
        std::cout << "b1 在馆状态: " << (b1.isAvailable() ? "可借" : "已借出") << "\n";
        s.listBorrowed();
        std::cout << "----------\n";

        std::cout << "张三归还 b1\n";
        if (s.returnBook(b1)) std::cout << "归还成功\n"; else std::cout << "归还失败\n";
        std::cout << "b1 在馆状态: " << (b1.isAvailable() ? "可借" : "已借出") << "\n";
        s.listBorrowed();

        std::cout << "作用域结束，Student 以及局部 Book 将被析构（请观察析构输出）\n";
    }

    std::cout << "程序结束，所有局部对象已析构。\n";

    return 0;
}
