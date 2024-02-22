<template>
  <!-- 引入fpvAside.vue模块 -->
  <el-container style="height: 100%;
  border: 1px solid #eee;
  margin-left: 0;">
    <el-aside width="15%">
      <fpvAside></fpvAside>
    </el-aside>
    <!-- 路由模块 -->
    <el-main>
      <router-view></router-view>
    </el-main>
  </el-container>
</template>

<script>
import element from '@/plugins/element';
import fpvAside from '@/components/MonitorView/fpvAside.vue';
export default {
  name: 'MonitorView',
  components: {
    fpvAside
  },
};
</script>

<style scoped>
/* Your CSS styles here */
</style>
