import rospy,platform,socket,json 
from std_msgs.msg import String


datajson={}
msg_data = {}

# 定义发布者
def callback(data):
    # 将data解析成json格式
    global msg_data
    msg_data = json.loads(data.data)

publisher = rospy.Publisher('/host_data', String, queue_size=2)
subscriber = rospy.Subscriber('callback', String, callback)


def main():
    rospy.init_node('home_data_node')
    global datajson
    rate = rospy.Rate(1)
    while not rospy.is_shutdown():
        datajson['hostname'] = socket.gethostname()
        datajson['platform'] = platform.platform()
        datajson['hostip'] = socket.gethostbyname(socket.gethostname())
        if msg_data != {}:
            datajson['air_quality'] = msg_data
        else:
            datajson['air_quality'] = {}
            datajson['air_quality']['co2'] = 0
            datajson['air_quality']['tvoc'] = 0
        publisher.publish(json.dumps(datajson))
        print(json.dumps(datajson))
        rate.sleep()

if __name__ == '__main__':
    main()