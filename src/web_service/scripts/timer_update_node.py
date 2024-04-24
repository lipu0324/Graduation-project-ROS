import string
from rospy import *
import schedule,time,json,requests
#############################变量区域#############################
msg_data = {}  # 全局json变量
rate = Rate(1)
############################加载配置文件##########################

settings_file_path = '../../settings.json'
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
    msg_data["location"] = "定时上传"

###########################定时数据上传函数########################

def data_update():
    url = server_url + '/dataupdate/'
    # data_dict = json.loads(data)
    # json_data = json.dumps(data_dict)
    response = requests.post(url, json=msg_data,headers={'Content-Type': 'application/json'})
    print (response.status_code)
    print (response.text)




schedule.every(interval_minutes).minutes.do(data_update)




def timer_update_node():
    init_node('timer_update_node')
    Subscriber('spg30_sensor',string,callback)
    while not is_shutdown():
        schedule.run_pending()
        rate.sleep()

if __name__ == '__main__':
    timer_update_node()