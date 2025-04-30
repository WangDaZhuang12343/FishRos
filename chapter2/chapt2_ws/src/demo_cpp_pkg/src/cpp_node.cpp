#include "rclcpp/rclcpp.hpp"
 
int main(int argc,char** argv)
{
    rclcpp::init(argc,argv);//初始化
     auto node = std::make_shared<rclcpp::Node>("cpp_node");
     RCLCPP_INFO(node->get_logger(),"C++节点");
     rclcpp::spin(node);
     rclcpp::shutdown();
    return 0;
}