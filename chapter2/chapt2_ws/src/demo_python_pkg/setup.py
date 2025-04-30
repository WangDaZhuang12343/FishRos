# from setuptools import find_packages, setup

# package_name = 'demo_python_pkg'

# setup(
#     name=package_name,
#     version='0.0.0',
#     packages=find_packages(exclude=['test']),
#     data_files=[
#         ('share/ament_index/resource_index/packages',
#             ['resource/' + package_name]),
#         ('share/' + package_name, ['package.xml']),
#     ],
#     install_requires=['setuptools'],
#     zip_safe=True,
#     maintainer='mi',
#     maintainer_email='mi@todo.todo',
#     description='TODO: Package description',
#     license='Apache-2.0',
#     extras_require=['pytest'],
#     entry_points={
#         'console_scripts': [
#             'python_node = demo_python_pkg.python_node:main'
#         ],
#     },
# )


from setuptools import setup
import os
from glob import glob

package_name = 'demo_python_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('launch/*.launch.py')),
    ],
    install_requires=[
        'setuptools',
    ],
    zip_safe=True,
    maintainer='mi',
    maintainer_email='mi@todo.todo',
    description='TODO: Package description',
    license='Apache License 2.0',
    extras_require={
        'test': ['pytest'],
    },
    entry_points={
        'console_scripts': [
            'python_node = demo_python_pkg.python_node:main',
            'person_node = demo_python_pkg.person_node:main',
            'write_node =  demo_python_pkg.write_node:main',
            'learn_thread = demo_python_pkg.learn_thread:main'
        ],
    },
)