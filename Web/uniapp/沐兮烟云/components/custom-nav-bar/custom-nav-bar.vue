<template>
	<view class="layout">
		<view class="navbar">
			<view class="statusBar" :style="{height:getstatusBarHeight() +'px'}"></view>
			<view class="titleBar" :style="{height:getTitleBarHeight() + 'px'}">
				<view class="title">{{title}}</view>
				<view class="search">
					<uni-icons class="icon" type="search" color="#888" size="18"></uni-icons>
					<text class="text">搜索</text>
				</view>
			</view>
			
		</view>
		<view class="fill" :style="{height:getNavBarHeight()+'px'}">
			
		</view>
		
	</view>
</template>

<script setup>
import {ref} from 'vue';
import {getstatusBarHeight,getTitleBarHeight,getNavBarHeight} from "@/utils/system.js"

defineProps({
	title:{
		type:String,
		default:"加藤惠"
	}
})

</script>

<style lang="scss" scoped>
.layout{
	.navbar{
		position: fixed;
		top: 0;
		left: 0;
		width: 100%;
		z-index: 10;
	    background: 
		linear-gradient(to bottom,transparent,#fff 400rpx),
		linear-gradient(to right,#beecd8 20%,#F4E2D8);
		.statusBar{
			height: var(--status-bar-height);
		}
		.titleBar{
			display: flex;
			height: 88rpx;
			align-items: center;
			padding: 0 30rpx;
			.title{
				font-size: 44rpx;
				font-weight: 700;
				color: #000;
			}
			.search{
				width: 220rpx;
				height: 56rpx;
				border-radius: 60rpx;
				background: rgba(255,255,255,0.4);
				border: 1px solid #fff;
				margin-left: 30rpx;
				color: #999;
				font-size: 28rpx;
				display: flex;
				align-items: center;
				.icon{
					margin-left: 5rpx;
				}
				.text{
					padding-left: 10rpx;
				}
			}
		}
	}
	.fill{
		
	}
}
</style>