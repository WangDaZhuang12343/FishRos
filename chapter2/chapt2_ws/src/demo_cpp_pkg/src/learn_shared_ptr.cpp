#include <iostream>
#include <memory>

int main()
{

    auto p1 = std :: make_shared<std::string>("This is a str"); //std :: make_shared<数据类型/类(参数)；返回值，对应类的共享指针> std::shared_ptr<std::string> 写成 auto
    std::cout<< "p1的引用计数:"<< p1.use_count() << ",指向内存地址:"<<p1.get() << std::endl;
    
    auto p2 = p1;
    std::cout<< "p1的引用计数:"<< p1.use_count() << ",指向内存地址:"<<p1.get() << std::endl;
    std::cout<< "p2的引用计数:"<< p2.use_count() << ",指向内存地址:"<<p2.get() << std::endl;
    
    p1.reset();//释放引用,不指向"This is a str" 所在内存
    std::cout<< "p1的引用计数:"<< p1.use_count() << ",指向内存地址:"<<p1.get() << std::endl;
    std::cout<< "p2的引用计数:"<< p2.use_count() << ",指向内存地址:"<<p2.get() << std::endl;
    
  
    std::cout<< "p2的指向内存地址数据:"<< p2->c_str() << std::endl; //",指向内存地址:"<<p2.get() << std::endl;
    
    return 0;
}