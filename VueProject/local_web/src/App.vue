<template>
  <link rel="stylesheet" href="https://unpkg.com/element-ui/lib/theme-chalk/index.css">
  <div class="app">
    <!-- 头部 -->
    <myHeader></myHeader>
    <el-container style="height: 100vh;
      border:0px soild #eee;
      margin: 0;
      padding: 0;
      border:0;">
      <!-- 侧边栏 -->
      <el-aside width="15%">
        <asideNav></asideNav>
      </el-aside>
      <!-- 主体内容 -->
        <router-view></router-view>
    </el-container>
  </div>
</template>

<script>
import myHeader from './components/myHeader.vue'
import asideNav from './components/asideNav.vue'

export default {
  name: 'App',
  components: {
    myHeader,
    asideNav
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
