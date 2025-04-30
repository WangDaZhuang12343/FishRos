import rclpy
from rclpy.node import Node
from chapt4_interfaces.srv import FaceDetector
import face_recognition
import cv2
from ament_index_python.packages import get_package_share_directory #获取功能包share目录绝对路径
import os
from cv_bridge import CvBridge
import time

class FaceDetectNode(Node):
    def __init__(self):
        super.__init__('face_detect_node')
        self.servoce = self.create_service(FaceDetector,'face_detect',self.detect_face_callback)
        self.bridge = CvBridge()
        self.number_of_times_to_upsample = 1
        self.nodel = 'hog'
        self.default_image_path = os.path.join(get_package_share_directory
        ('demo_python_service'),'resource/default.jpg')
        self.get_logger().info("人脸检测服务")

    def detect_face_callback(self, request, response):
        if request.image.data:
            cv_image = self.bridge.imgmsg_to_cv2(request.image)

        else:
            cv_image = cv2.imread(self.default_image_path)
            self.get_logger().info(f"传入图像为空")
            
        #cv_image 
        start_time = time.time()
        self.get_logger().info(f"加载完成图像，开始识别")
        #检测人脸
        face_locations = face_recognition.face_locations(cv_image,
        number_of_times_to_upsample=self.number_of_times_to_upsample,model='hog')
        response.use_time = time.time() - start_time
        response.number = len(face_locations)
        for top,right,bottom,left in face_locations:
            response.top.append(top)
            response.right.append(right)
            response.bottom.append(bottom)
            response.left.append(left)

        return response  #必须response
    

def main():
    rclpy.init()
    node = FaceDetectNode
    rclpy.spin(node)
    rclpy.shutdown()