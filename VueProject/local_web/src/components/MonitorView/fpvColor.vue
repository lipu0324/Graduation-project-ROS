<template>
      <!-- elenmentUI包裹的图片 -->
      <el-image
          style="width: 100%; height: 100%;"
          src="http://localhost:8080/stream?topic=/camera/rgb/image_rect_color"
          fit="contain"
      ></el-image>
</template>

<script>
export default {
  name: 'FpvColor',
  // Your component options go here
}
</script>

<style scoped>
/* Your component styles go here */
</style>
