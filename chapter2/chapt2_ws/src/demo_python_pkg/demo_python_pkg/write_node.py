from demo_python_pkg.person_node import PersonNode


class WriteNode(PersonNode):
    def __init__(self,node:str,name:str,age:int,book:str) -> None:
        print('WriteNode __init__方法被调用了,添加了两个属性')
        super().__init__(node,name,age) #手动调用下父类 __init__
        self.book = book


def main():
        node = WriteNode("张三",18,'ROS2开发')
        node.eat('鱼香肉丝1')
