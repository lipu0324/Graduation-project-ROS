<template>

  
</template>

<script setup>
import { onMounted } from 'vue';
import element from '@/plugins/element';
import { ElMessage } from 'element-plus';
import fpvAside from '@/components/MonitorView/fpvAside.vue';
// 引入roslib
import ROSLIB from '@/../../node_modules/roslib/build/roslib';
let hostname = window.location.hostname;
var ros = new ROSLIB.Ros({
  url: 'ws://' + hostname + ':9090'
});
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
</script>

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
</style>
