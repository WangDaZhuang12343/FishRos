#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

using namespace std::chrono_literals;

class TurtleCircleNode: public rclcpp::Node // 定义一个继承自 rclcpp::Node 的类
{   
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; // 发布者智能指针，用于发布速度消息
        rclcpp::TimerBase::SharedPtr timer_; // 定时器智能指针，用于定时触发事件
        geometry_msgs::msg::Twist msg_; // 消息对象，用于存储速度指令

    public:
        explicit TurtleCircleNode(const std::string& node_name) : Node("node_name") // 构造函数，初始化节点
        {
            // 创建一个发布者，发布到话题 "/turtle1/cmd_vel"，队列大小为 10
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            
            // 创建一个定时器，定时触发回调函数
            timer_ = this->create_wall_timer(1000ms,std::bind(&TurtleCircleNode::timer_callback, this));
        }
    
    void timer_callback() // 定时器回调函数
    {
        auto msg = geometry_msgs::msg::Twist(); // 创建一个速度消息对象
        msg.linear.x = 1.0; // 设置线速度为 1.0
        msg.angular.z = 0.5; // 设置角速度为 0.5
        publisher_->publish(msg); // 发布速度消息
    }
};

int main(int argc,char* argv[]) // 主函数
{
    rclcpp::init(argc,argv); // 初始化 ROS 2
    auto node = std::make_shared<TurtleCircleNode>("turtle_circle_control"); // 创建节点对象
    rclcpp::spin(node); // 进入循环，等待回调函数触发
    rclcpp::shutdown(); // 关闭 ROS 2
    return 0; // 返回 0，表示程序正常结束
}