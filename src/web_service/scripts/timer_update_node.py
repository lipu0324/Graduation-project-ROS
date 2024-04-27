from std_msgs.msg import String
from rospy import *
import schedule,time,json,requests
#############################变量区域#############################
msg_data = {
    "car_id": "1",
    "car_ip": "ROS",
    "CO2": "0",
    "TVOC": "0",
    "location": "定时上传"
}  # 全局json变量

############################加载配置文件##########################

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
    print("接收到数据")
    global msg_data
    msg_data = json.loads(data.data)
    msg_data["car_id"] = car_id
    msg_data["car_ip"] = car_ip
    msg_data["location"] = "定时上传"

###########################定时数据上传函数########################

def data_update():
    print ("定时上传数据")
    url = server_url + '/dataupdate/'
    print(url)
    # data_dict = json.loads(data)
    # json_data = json.dumps(data_dict)
    print(msg_data)
    response = requests.post(url, json=msg_data,timeout=5)
    print (response.status_code)
    print (response.text)




schedule.every(float(interval_minutes)).minutes.do(data_update)




def timer_update_node():
    init_node('timer_update_node')
    rate = Rate(1)
    Subscriber('spg30_sensor',String,callback)
    while not is_shutdown():
        schedule.run_pending()
        rate.sleep()

if __name__ == '__main__':
    timer_update_node()