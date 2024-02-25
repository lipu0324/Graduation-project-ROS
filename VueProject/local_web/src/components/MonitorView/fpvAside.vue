<template>
    <el-menu default-active="1" class="fpv-aside">
      <RouterLink to = "/monitor/color" class="custom-link">
      <el-menu-item index="1">
        RGB监视
      </el-menu-item>
    </RouterLink>
    <router-link to = "/monitor/deep" class="custom-link">
      <el-menu-item index="2">
        深度监视
      </el-menu-item>
    </router-link>
    </el-menu>
</template>

<script>
import { ElAside, ElMenu, ElMenuItem } from 'element-plus'
export default {
  name: 'fpvAside',
  // Add your component logic here
}
</script>

<style scoped>
.fpv-aside {
  width: 100%x;
  height: 100%;
  background-color: #545c64;

}
.custom-link {
    text-decoration: none;
    /* 去掉下划线 */
    /* 继承父元素的样式 */
    color: inherit;
    font-size: inherit;
    line-height: inherit;
    font-weight: inherit;
    font-family: inherit;
    text-indent: inherit;
    text-transform: inherit;
    letter-spacing: inherit;
    word-spacing: inherit;
    white-space: inherit;
    text-decoration: inherit;
    /* 左对齐 */
    text-align: left;
}
</style>
