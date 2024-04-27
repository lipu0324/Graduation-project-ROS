import string,os
from rospy import *
import time,json,requests
from std_msgs.msg import String
#############################变量区域#############################
msg_data = {}  # 全局json变量
############################加载配置文件##########################
print(os.getcwd())
settings_file_path = '/home/orangepi/catkin_ws/src/settings.json'
with open(settings_file_path) as f:
    settings = json.load(f)
    server_url = settings['Server_URL']
    interval_minutes = settings['interval_minutes']
    car_id = settings['car_id']
    car_ip = settings['car_ip']

###########################订阅话题回调函数########################

def callback(data):
    # 将data解析成json格式
    global msg_data
    msg_data = json.loads(data.data)
    msg_data["car_id"] = car_id
    msg_data["car_ip"] = car_ip

###########################定时数据上传函数########################

def data_update(data):
    global msg_data
    msg_data['location'] = data.data
    url = server_url + '/dataupdate/'
    # data_dict = json.loads(data)
    # json_data = json.dumps(data_dict)
    response = requests.post(url, json=msg_data,headers={'Content-Type': 'application/json'})
    print (response.status_code)
    print (response.text)



def timer_update_node():
    init_node('manual_update_node')
    rate = Rate(10)
    Subscriber('spg30_sensor',String,callback)
    Subscriber('location',String,data_update)
    while not is_shutdown():
        rate.sleep()

if __name__ == '__main__':
    timer_update_node()