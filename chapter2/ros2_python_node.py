import rclpy
from rclpy.node import Node

def main():
    # 初始化 ROS 2 客户端库
    rclpy.init()
    
    # 创建一个节点，名称为 'python_node'
    node = Node('python_node')
    
    node.get_logger().info('正在运行python节点')
    node.get_logger().warn('正在运行python节点')
    # 进入 ROS 2 的事件循环，保持节点运行
    rclpy.spin(node)
    
    # 清理资源并关闭节点
    rclpy.shutdown()

# 当脚本被直接运行时，执行 main 函数
if __name__ == '__main__':
    main()