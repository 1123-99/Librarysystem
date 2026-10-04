# Librarysystem — 图书管理系统（教学 / 实验）

说明：本仓库用于课程实验，演示 Book 类的封装、ISBN 校验，以及 Student 借书的组合/依赖关系实现。仓库已从仅包含实验一扩展为同时包含实验二的代码。

主要文件
- book.h / book.cpp — Book 类（字段：书名、ISBN、出版社、价格、页数、在馆状态），包含 ISBN-10/ISBN-13 校验。
- student.h / student.cpp — Student 类，演示借书（依赖 Book&）与学生内部保存已借图书集合（组合 has-a）。
- main.cpp — 简单的演示程序，展示类的使用。
- CMakeLists.txt — 跨平台构建支持（可使用 CMake 生成项目或直接用 g++ 编译）。
- .gitignore — 忽略生成产物与 IDE 文件。

如何编译（推荐，跨平台）
1. 使用 CMake（Linux/macOS/Windows + MinGW/MSYS2）
   mkdir build && cd build
   cmake ..
   cmake --build .

2. 直接用 g++（简单项目）
   g++ -std=c++17 main.cpp book.cpp student.cpp -o library

注意
- 本仓库建议使用 UTF-8 编码保存源文件，否则控制台中文可能显示为乱码。

功能
- Book::isValidISBN 支持 ISBN-10（含末位 X）与 ISBN-13 校验。
- Student::borrowBook(Book&) 体现依赖（借书函数接收 Book 引用并修改其在馆状态）。
- Student 内部保存已借图书副本（组合 has-a）：当 Student 对象销毁，其内部副本也随之销毁。
