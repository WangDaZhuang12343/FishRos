#include "rclcpp/rclcpp.hpp"

class PersonNode : public rclcpp::Node
{
private:
    std::string name_;
    int age_;

public:
    PersonNode(const std::string &node_name,const std::string & name,const int & age)
    :Node(node_name) /*调用父类的构造函数，等同于python中的uper().__init__()*/
    {
        this->name_ = name;
        this->age_  = age;
    }

    void eat(const std::string & food_name)
    {
            RCLCPP_INFO(this->get_logger(),"我是%s,%d,爱吃%s",this->name_.c_str(),
            this->age_,food_name.c_str());
    };
};


int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);//初始化
     auto node = std::make_shared<PersonNode>("person_node","李四",19);
     RCLCPP_INFO(node->get_logger(),"C++节点");
     node->eat("鱼香ROS");
     rclcpp::spin(node);
     rclcpp::shutdown();
    return 0;
}