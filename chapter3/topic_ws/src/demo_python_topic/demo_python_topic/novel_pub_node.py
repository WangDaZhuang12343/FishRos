import rclpy
from rclpy.node import Node
import requests
from example_interfaces.msg import String
from queue import Queue

class NovelPubNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self.get_logger().info(f'{node_name},启动')
        #创建线程
        self.novels_queue_ = Queue()
        self.novel_publisher_ = self.create_publisher(String,'novel',10)
        self.create_timer(5,self.timer_callback)


    
    def timer_callback(self):
        #self.novel_publisher_.publish()
        if self.novels_queue_.qsize()>0:
            line = self.novels_queue_.get()
            msg = String() #组装
            msg.data = line
            self.novel_publisher_.publish(msg)
            self.get_logger().info(f'发布了:{msg}')




    def download(self, url):
        response = requests.get(url)
        response.encoding='utf-8'
        text = response.text
        #text.splitlines()
        self.get_logger().info(f'下载{url}，{len(text)}')
        for line in text.splitlines():
            self.novels_queue_.put(line)

        #self.novel_publisher_.publish()
        #response.text
        
def main():
    rclpy.init()
    node = NovelPubNode('novel_pub')
    node.download('http://127.0.0.1:8000/nove1.txt')
    rclpy.spin(node)
    rclpy.shutdown()