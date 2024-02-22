<template>
        <!-- elenmentUI包裹的图片 -->
        <el-image
            style="width: 100%; height: 100%;"
            src='http://localhost:8080/stream?topic=/camera/depth/image'
            fit="contain"
        ></el-image>
</template>

<script>
import { ref } from 'vue';
import { ElImage } from 'element-plus';
export default {
    name: 'FpvDeep',
};

</script>

<style scoped>
/* Your component styles here */
</style>
