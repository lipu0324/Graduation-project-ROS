<script setup>
import { onMounted,ref } from 'vue';
import element from '@/plugins/element';
import ElementUI from 'element-plus'
import { ElMessage } from 'element-plus';
import fpvAside from '@/components/MonitorView/fpvAside.vue';
// 引入roslib
import ROSLIB from 'roslib';
let hostname = window.location.hostname
const hostname_car = ref()
const platform = ref()
const co2 = ref()
const tvoc = ref()
const hostip = ref()
var ros = new ROSLIB.Ros({
  url: 'ws://' + "ros" + ':9090'
});
var jsonObject ={}
ros.on('connection', function() {
  console.log('Connected to websocket server.');
  ElMessage({
    message: 'ROS系统连接成功',
    type: 'success'
  })
});
ros.on('error', function(error) {
  console.log('Error connecting to websocket server: ', error);
  ElMessage({
    message: 'ROS系统连接失败',
    type: 'error'
  })
});
ros.on('close', function() {
  console.log('Connection to websocket server closed.');
  ElMessage({
    message: 'ROS系统连接关闭',
    type: 'warning'
  })
});

var topicName = '/host_data'
var messageType  = 'std_msgs/String'
var topic = new ROSLIB.Topic({
  ros:ros,
  name:topicName,
  messageType:messageType
});
topic.subscribe(function(message) {
  console.log('即将开始转换')
  jsonObject = JSON.parse(message.data)
  hostname_car.value = jsonObject.hostname
  platform.value = jsonObject.platform
  co2.value = jsonObject.air_quality.co2
  tvoc.value = jsonObject.air_quality.tvoc
  hostip.value = jsonObject.hostip
})
</script>



<template>
  <el-container>
    <el-descriptions
      class = "el-descriptions"
      title = "ROS系统状态"
      :column = "3"
      :size = "large"
      border
      :span = '3'>
      <scription-item label = "ROS网络地址">
        <template #label>
          <div class = "cell-item">
            <i class = "el-icon el-icon-link"></i>
            ROS网络地址
          </div>
        </template>
        {{ hostip }}
      </scription-item>
    <el-descriptions-item label  = "ROS系统信息">
      <template #label>
        <div class = "cell-item">
          <i class = "el-icon el-icon-info"></i>
          ROS系统信息
        </div>
      </template>
      {{platform}}
    </el-descriptions-item>
    <el-descriptions-item label = "ROS主机名称">
      <template #label>
        <div class = "cell-item">
          <i class="el-icon el-icon-user"></i>
          ROS主机名称
        </div>
        {{hostname_car}}
      </template>
    </el-descriptions-item>
    <el-descriptions-item label="CO2浓度">
      <template #label>
        <div class = "cell-item">
          <i class="el-icon el-icon-s-opportunity"></i>
          CO2浓度
        </div>
      </template>
      {{co2}} ppm
    </el-descriptions-item>
    <el-descriptions-item label="TVOC">
      <template #label>
        <div class = "cell-item">
          <i class="el-icon el-icon-s-opportunity"></i>
          TVOC
        </div>
      </template>
      {{tvoc}} ppm
    </el-descriptions-item>
      
    </el-descriptions>
  </el-container>
</template>




<style scoped>
/* 一个导航栏的外观 */
.home-view {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 100%;
  background-color: #f0f0f0;
}
/* Your component styles here */
.cell-item {
  display: flex;
  align-items: center;
}

 .el-descriptions {
   margin: 20px;
   padding: 20px;
   border: 1px solid #ebeef5; /* 添加边框 */
 }
</style>
