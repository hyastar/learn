<template>
	<view>
		<image :src="picurl" mode="aspectFill"></image>
		
		<button type="primary" :loading="false" :disabled="false">按钮</button>
	</view>
		<view class="box" :class="{active:isActive}">
			v-bind的指令
		</view>
		
<!-- 		<view class="box" :class="isActive ? 'active' : ''"></view> -->
		
		<view class="box" :style="{width: '300px', height: 260+'px', fontSize: size+'px'}">内联样式</view>
</template>

<script setup>
import {ref} from "vue";
const isActive = ref(false);
const size = ref(30);
const arrs = ref([
	"/static/pic1.png",	
	"/static/pic2.png",
	"/static/pic3.webp",
	"/static/pic4.jpg",
]);
const picurl = ref(arrs.value[0]);

let i =0;
setInterval(()=>{
	i++;
	console.log(i);
	size.value += i%arrs.value.length;
	picurl.value = arrs.value[i%arrs.value.length];
	isActive.value = !isActive.value;
}, 1000)
</script>

<style lang="scss">
.box{
	width: 200px;
	height: 200px;
	background: orange;
	fontsize: 20px;
}
.active{
	background: green;
	color: #fff;
}
</style>
