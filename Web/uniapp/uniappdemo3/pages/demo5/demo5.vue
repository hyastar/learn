<template>
	<view class="layout">
		<view class="row" v-for="item in arrs" :key="item.id">
			<view class="title">{{item.title}}</view>
			<view class="content">{{item.body}}</view>
		</view>
	</view> 
</template>

<script setup>	
//import {ref} from "vue";
let arrs = ref([])

async function request(){
	let res = await uni.request({
		url:"https://jsonplaceholder.typicode.com/posts",
		data:{
			id:5,
			cid:3
		}
	});
	
	// 在这里添加 console.log 即可在控制台看到完整的返回数据
	console.log("网络请求成功，返回数据:", res);
	
	arrs.value = res.data;
}

request();

</script>

<style lang="scss" scoped>
.layout{
	padding:30rpx;
	.row{
		border-bottom:1px solid #cfcfcf;
		padding:20rpx 0;
		.title{
			font-size: 36rpx;
			margin-bottom:10rpx;
		}
		.content{
			font-size: 28rpx;
			color:#666
		}
	}
}
</style>
