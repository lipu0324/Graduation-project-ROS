<template>

  
</template>

<script setup>
import { onMounted } from 'vue';
import element from '@/plugins/element';
import fpvAside from '@/components/MonitorView/fpvAside.vue';
// 引入roslib
import ROSLIB from 'roslib';

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
