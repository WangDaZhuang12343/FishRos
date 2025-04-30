import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/mi/FishRos/chapt7/chapt7_ws/install/autopatrol_robot'
