<template>
  <!-- 引入fpvAside.vue模块 -->
  <el-container style="height: 100%;
  border: 1px solid #eee;
  margin-left: 0;">
    <!-- 路由模块 -->
    <el-main>
      <router-view></router-view>
    </el-main>
  </el-container>
</template>

<script>
import { onMounted } from 'vue';
import element from '@/plugins/element';
import fpvAside from '@/components/MonitorView/fpvAside.vue';
// 引入roslib
import ROSLIB from 'roslib';
export default {
  name: 'MonitorView',
  components: {
    fpvAside
  },
  setup() {
    let hostname = window.location.hostname;
      // 创建ros对象
      let ros = new ROSLIB.Ros({
        url: 'ws://' + hostname + ':9090'
      });
      console.log(hostname);

    let boolArray = [false, false, false, false, false, false];//用于存储按键状态,分别对应QWEASD，其中WASD为前后左右平移，QE为左右转动
    document.addEventListener('keydown',(Event)=>
    {
      // 判断是否是QWEASD中的一个并在boolArray中标记
      if (Event.key == 'q') {
        boolArray[0] = true;
      }
      if (Event.key == 'w') {
        boolArray[1] = true;
      }
      if (Event.key == 'e') {
        boolArray[2] = true;
      }
      if (Event.key == 'a') {
        boolArray[3] = true;
      }
      if (Event.key == 's') {
        boolArray[4] = true;
      }
      if (Event.key == 'd') {
        boolArray[5] = true;
      }
    })
    // 包含水平轴和左右的运动数组
    let moveArray = [0, 0, 0];
    document.addEventListener('keyup',(Event)=>
    {
      // 判断是否是QWEASD中的一个并在boolArray中标记
      if (Event.key == 'q') {
        boolArray[0] = false;
      }
      if (Event.key == 'w') {
        boolArray[1] = false;
      }
      if (Event.key == 'e') {
        boolArray[2] = false;
      }
      if (Event.key == 'a') {
        boolArray[3] = false;
      }
      if (Event.key == 's') {
        boolArray[4] = false;
      }
      if (Event.key == 'd') {
        boolArray[5] = false;
      }
      console.log(boolArray);
    })
    var cmdvel = new ROSLIB.Topic({
        ros: ros,
        name: '/cmd_vel',
        messageType: 'geometry_msgs/Twist'
      });
    // 创建一个定时器，每隔100ms检测一次boolArray数组
    setInterval(() => {
      //跟据boolArray数组的值来发布cmd_vel话题
      moveArray[0] = boolArray[1] ? 1 : boolArray[4] ? -1 : 0;
      moveArray[1] = boolArray[5] ? -0.5 : boolArray[3] ? 0.5 : 0;
      moveArray[2] = boolArray[0] ? 1 : boolArray[2] ? -1 : 0;
      cmdvel.publish({linear: {x: moveArray[0], y: moveArray[1], z: 0}, angular: {x: 0, y: 0, z: moveArray[2]}});
    }, 100);

  },
}
</script>

<style scoped>
/* Your CSS styles here */
</style>
