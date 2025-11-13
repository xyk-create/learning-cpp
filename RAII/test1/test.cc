#include <gtest/gtest.h>
#include <iostream>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "shared_ptr.hpp"
#include <memory>
class Tst
{
public:
//private:
    int _a = 7;
    double _f = 8.9;
    std::string _str = "hello shared_ptr";
};

TEST(my_shared_ptr构造函数测试, 类对象示例)
{
    my_ptr::shared_ptr<Tst> t1(new Tst);
    my_ptr::shared_ptr<Tst> t2;
    t2=t1;
    my_ptr::shared_ptr<Tst> t3(t2);
}
TEST(my_shared_ptr运算符测试, 成员访问)
{
    my_ptr::shared_ptr<Tst> t1(new Tst);
    std::cout<<t1->_a<<std::endl;;
    std::cout<<(*t1)._str<<std::endl;

}
int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}