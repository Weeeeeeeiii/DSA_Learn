#include "List.h"
#include <iostream>

int main()
{
    // List 初始化
    List<int> lst_a{1, 2, 3, 4, 5};
    if (!(lst_a.empty())) std::cout << "lst_a 初始化后为非空" << std::endl;
    std::cout << "lst_a 的初始值：" << std::endl;
    for (auto &i : lst_a) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    // 这两个 for 等价
    std::cout << "lst_a 的初始值：" << std::endl;
    for (auto iter = lst_a.begin(); iter != lst_a.end(); ++iter) {
        std::cout << *iter << "\t";
    }
    std::cout << std::endl;

    // push 测试
    List<int> lst_b;
    if (lst_b.empty()) std::cout << "lst_b 初始化后为空" << std::endl;
    std::cout << "lst_b 从后 push 进 1 到 10 后：" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        lst_b.push_back(i);
    }

    for (auto &i : lst_b) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    std::cout << "lst_b 再从前 push 进 1 到 10 后：" << std::endl;
    for (int i = 1; i <= 10; ++i) {
        lst_b.push_front(i);
    }
    for (auto &i : lst_b) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
    
    // 拷贝构造函数
    List<int> lst_c = lst_b;
    std::cout << "lst_c 从 lst_b 拷贝过来：" << std::endl;
    for (auto &i : lst_c) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    // 输出 List 大小
    std::cout << "lst_c 此时的大小为：" << lst_c.size() << "\t";
    std::cout << std::endl;

    // pop 测试
    for (int i = 1; i<= 5; ++i) {
        lst_b.pop_back();
    }
    std::cout << "lst_b 从后 pop 出 5 个元素：" << std::endl; 
    for (auto &i : lst_b) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    for (int i = 1; i<= 10; ++i) {
        lst_c.pop_front();
    }
    std::cout << "lst_c 从前 pop 出 5 个元素：" << std::endl;
    for (auto &i : lst_c) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;

    // 自增自减和动态迭代器测试
    std::cout << "lst_a 全部元素改为 10086：" << std::endl;
    for (auto iter = lst_a.begin(); iter != lst_a.end(); ++iter) {
        *iter = 10086;
    }
    for (auto &i : lst_a) {
        std::cout << i << "\t";
    }
    std::cout << std::endl;
    auto iter = lst_c.begin();
    std::cout << "iter 指向 lst_c 的 begin(), 依次输出 iter++, ++iter, iter--, --iter 指向的值" << std::endl;
    std::cout << *(iter++) << '\t' << *(++iter) << '\t';
    std::cout << *(iter--) << '\t' << *(--iter) << std::endl;

    return 0;
}
