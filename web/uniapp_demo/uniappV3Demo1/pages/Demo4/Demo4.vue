<template>
	<view>
		<view class="box" @click="onclick" :style="{background: color}">
			{{ num }}
		</view>
	</view>
	
	<switch checked @change="onChange"/>
	
	<button type="primary" :loading="isLoading">按钮</button>
</template>

<script setup>
import {ref} from "vue";
const num = ref(1);
const isLoading = ref(false);
const color = ref("#fc359a")
function onclick(){
	num.value++;
	color.value = "#" + String(Math.random()).substring(3, 9);
	console.log(String(Math.random()).substring(3, 9));
}
function onChange(e){
	isLoading.value = !isLoading.value;
	console.log(e.detail);
}
</script>

<style>
.box{
	width: 200px;
	height: 200px;
	background: orange;
}
</style>
