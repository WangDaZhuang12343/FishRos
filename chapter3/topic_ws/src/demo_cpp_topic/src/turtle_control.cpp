#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "chrono"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;

class TurtleControlNode: public rclcpp::Node // 定义一个继承自 rclcpp::Node 的类
{   
    private:
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_; // 发布者智能指针，用于发布速度消息
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;// 订阅者的智能共享指针
        double target_x_{1.0};
        double target_y_{1.0};
        double k_{1.0}; //比例系数
        double max_speed_{3.0}; //最大速度


        // rclcpp::TimerBase::SharedPtr timer_; // 定时器智能指针，用于定时触发事件
        // geometry_msgs::msg::Twist msg_; // 消息对象，用于存储速度指令

    public:
        explicit TurtleControlNode(const std::string& node_name):Node(node_name) // 构造函数，初始化节点
        {
            // 创建一个发布者，发布到话题 "/turtle1/cmd_vel"，队列大小为 10
            publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            subscriber_ = this ->create_subscription<turtlesim::msg::Pose>("/turtle1/pose",10,std::bind(&
            TurtleControlNode::on_pose_received_,this,std::placeholders::_1));

        }
    
        void on_pose_received_(const turtlesim::msg::Pose::SharedPtr pose) //参数  收到数据的共享指针
        {
        //1.获取当前的位置
        auto current_x = pose ->x;
        auto current_y = pose ->y;
        RCLCPP_INFO(get_logger(),"当前:x=%f,y=%f",current_x,current_y);
        
        //2.计算当前海龟位置跟目标位置之间的距离差和角度差
        auto distance = std::sqrt(
            (target_x_-current_x)*(target_x_-current_x)+
            (target_y_-current_y)*(target_y_-current_y)
        );
        auto angle = std::atan2((target_y_-current_y),(target_x_-current_x))-pose->theta;
        
        //3.控制策略
        auto msg = geometry_msgs::msg::Twist();
        if(distance>0.1){
            if(fabs(angle)>0.2){
                msg.angular.z = fabs(angle);

            }else{
                msg.linear.x = k_*distance;
            }
        }
        
        //4.限制线速度最大值
        if(msg.linear.x > max_speed_){
            msg.linear.x = max_speed_;
        }

        publisher_->publish(msg); // 发布速度消息
        }
};

int main(int argc,char* argv[]) // 主函数
{
    rclcpp::init(argc,argv); // 初始化 ROS 2
    auto node = std::make_shared<TurtleControlNode>("turtle_circle_node"); // 创建节点对象
    rclcpp::spin(node); // 进入循环，等待回调函数触发
    rclcpp::shutdown(); // 关闭 ROS 2
    return 0; // 返回 0，表示程序正常结束
}