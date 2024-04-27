#   2024/4/24 用于扫描二维码并且上传到服务器的节点
#   依赖opencv进行二维码识别
#   二维码的json格式为:
#   {
#       "operation":"", # 操作类型
#       "location":"",
#   }

import rospy,cv2
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
from geometry_msgs.msg import PoseStamped
import schedule,time,json,requests
from std_msgs.msg import String

######################################全局变量######################################
# 转化过的图像
cv_image = None
bridge = CvBridge()
pub = rospy.Publisher('QRcodeResult', String, queue_size=1)





# 收到图像后的回调函数
def QrScanner(msg):
    try:
        global cv_image
        cv_image = bridge.imgmsg_to_cv2(msg, "bgr8")
    except CvBridgeError as e:
        print(e)
    qrDecoder = cv2.QRCodeDetector()
    data,bbox,rectifiedImage = qrDecoder.detectAndDecode(cv_image)
    # 检测扫描结果是否存在
    if len(data)>0:
        print("QR Code data: ", data)
        try:
            # 解析json
            data = json.loads(data)
            if data['operation'] == 'upload':
                pub.publish(data['location'])
                rospy.sleep(30)
        except json.JSONDecodeError:
            print("QR Code data is not json format")
    else:
        print("QR Code not detected")
        





def QRScanner_node():
    rospy.init_node('QR_code_scanner_node')
    rate = rospy.Rate(10)
    image_sub = rospy.Subscriber('/camera/rgb/image_raw', Image, QrScanner)
    while not rospy.is_shutdown():
        rate.sleep()
        print("QR Scanner node is running")


if __name__ == '__main__':
    QRScanner_node()