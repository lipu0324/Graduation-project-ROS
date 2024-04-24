import string
from rospy import *
import time,json,requests
#############################变量区域#############################
msg_data = {}  # 全局json变量
############################加载配置文件##########################

settings_file_path = '../../settings.json'
with open(settings_file_path) as f:
    settings = json.load(f)
    server_url = settings['Server_URL']
    car_id = settings['car_id']
    car_ip = settings['car_ip']

###########################订阅话题回调函数########################

def callback(data):
    # 将data解析成json格式
    global msg_data
    msg_data = json.loads(data.data)
    msg_data["car_id"] = car_id
    msg_data["car_ip"] = car_ip
    msg_data["location"] = "手动上传"

###########################定时数据上传函数########################

def data_update(data):
    url = server_url + '/dataupdate/'
    # data_dict = json.loads(data)
    # json_data = json.dumps(data_dict)
    response = requests.post(url, json=msg_data,headers={'Content-Type': 'application/json'})
    print (response.status_code)
    print (response.text)







def manual_update_node():
    init_node('manual_update_node')
    Subscriber('spg30_sensor',string,callback)
    Subscriber('updateControl',bool,data_update)
    while not is_shutdown():
        spin()

if __name__ == '__main__':
    manual_update_node()