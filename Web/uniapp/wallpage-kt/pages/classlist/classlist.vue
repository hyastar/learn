<template>
	<view class="classlist">
		<view class="loadingLayout" v-if="!classList.length && !noData">
			<uni-load-more status="loading"></uni-load-more>
		</view>
		<view class="content">
			<navigator class="item" :url="'/pages/preview/preview?id='+item._id" v-for="item in classList" :key="item._id">
				<image :src="item.smallPicurl" mode="aspectFill"></image>
			</navigator>
		</view>
		<view class="loadingLayout" v-if="classList.length || noData">
			<uni-load-more :status="noData?'noMore':'loading'"></uni-load-more>
		</view>
		<view class="safe-area-inset-bottom"></view>
	</view>
</template>

<script setup>
import {ref} from 'vue';
import {onLoad,onReachBottom} from "@dcloudio/uni-app";
import {apiGetClassList} from '@/api/apis.js';

const classList = ref([]);
const noData = ref(false);
const queryParams = ref({
	pageNum:1,
	pageSize:12,
	classid: null
});

onLoad((e)=>{
	let {id=null,name=null} = e;
	queryParams.value.classid = id;	
	
	uni.setNavigationBarTitle({
		title:name
	})
	getClassList();
})

// 触底加载更多
onReachBottom(()=>{
	if(noData.value) return;
	queryParams.value.pageNum++;
	getClassList();
})

const getClassList = async()=>{
		let res = await apiGetClassList(queryParams.value);
		classList.value = [...classList.value, ...res.data];
		if(queryParams.value.pageSize > res.data.length) noData.value = true;
		uni.setStorageSync("storgClassList",classList.value);
		console.log(res);
}
</script>
<style lang="scss" scoped>
.classlist{
	.content{
		display: grid;
		grid-template-columns: repeat(3,1fr);
		gap: 5rpx;
		padding: 5rpx;
		.item{
			height: 440rpx;
			image{
				width: 100%;
				height: 100%;
			}
		}
	}
}
</style>
