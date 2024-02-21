<template>
    <!-- 基于elementUI的侧边栏 -->
    <el-aside width="100%">
        <el-menu default-active="1" class="el-menu-vertical-demo" @open="handleOpen" @close="handleClose"
            background-color="#545c64" text-color="#fff" active-text-color="#ffd04b">
            <RouterLink to="/home" class="custom-link">
                <el-menu-item index="1">
                    <i class="el-icon-menu"></i>
                    主页
                </el-menu-item>
            </RouterLink>
            <RouterLink to="/monitor" class="custom-link">
                <el-menu-item index="2">
                    <i class="el-icon-monitor"></i>
                    监视器
                </el-menu-item>
            </RouterLink>
            <RouterLink to="/settings" class="custom-link">
                <el-menu-item index="3">
                    <i class="el-icon-setting"></i>
                    系统设置
                </el-menu-item>
            </RouterLink>
 
        </el-menu>
    </el-aside>
</template>
  
<script>

export default {
    methods: {
        handleOpen(key, keyPath) {
            console.log(key, keyPath);
        },
        handleClose(key, keyPath) {
            console.log(key, keyPath);
        }
    }
}
</script>
<style>
/* 侧边栏背景延续到底部 */
.el-aside {
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
