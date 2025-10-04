<template>
	<view class="">
		个人中心
	</view>
</template>

<script setup>
// 1. 从 uni-app 官方库中导入 onShow 生命周期钩子
import { onShow } from '@dcloudio/uni-app';

// onShow 会在每次页面显示时触发
onShow(()=>{
	console.log("个人中心页面显示");
	
	// 2. 将 loading 逻辑移入 onShow 内部
	uni.showLoading({
		title:"加载中..."
	})

	setTimeout(()=>{
		uni.hideLoading()
	}, 200);
	
	// 原有的 hideTabBarRedDot 逻辑也在这里
	uni.hideTabBarRedDot({
		index: 2
	});
})

</script>

<style lang="scss" scoped>

</style>