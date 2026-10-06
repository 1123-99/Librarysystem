Librarysystem — 图书馆借阅管理系统。

主要内容
* book.h / book.cpp：Book 类定义与实现，包含ISBN校验。
* student.h / student.cpp：Student 类定义与实现，包含借书与还书功能。
* main.cpp：程序入口及测试代码。
* book_1.sln / book_1.vcxproj：Visual Studio 工程文件。

运行环境
* Visual Studio 2022（需在项目属性 C/C++ 命令行中添加 `/utf-8` 解决中文乱码）
* 也可使用 CMake 或 g++ 编译（参考 CMakeLists.txt）

功能简述
* 图书信息管理（书名、ISBN、作者等）
* ISBN-10 / ISBN-13 合法性校验
* 学生借书、还书
* 演示组合关系与依赖关系，以及对象的构造/析构顺序
