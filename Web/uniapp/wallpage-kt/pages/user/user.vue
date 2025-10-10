<template>
	<view class="userLayout pageBg">
		<view class="userInfo">
			<view class="avatar">
				<image src="/static/images/xxmLogo.png" mode="aspectFill"></image>
			</view>
			<view class="ip">127.0.0.1</view>
			<view class="address">来自于：未知</view>
		</view>

		 <view class="section">
			<view class="list">
				<template v-for="(item, index) in list1" :key="index">
					<view class="row" v-if="item.text === '联系客服'">
						<view class="left">
							<uni-icons :type="item.icon" size="20"></uni-icons>
							<view class="text">{{ item.text }}</view>
						</view>
						<view class="right">
							<view class="text"></view>
							<uni-icons type="right" size="15" color="#aaa"></uni-icons>
						</view>
						<button open-type="contact"></button>
						<button @click="clickContact"></button>
						</view>

					<view class="row" v-else @click="navigateToPage(item)">
						<view class="left">
							<uni-icons :type="item.icon" size="20"></uni-icons>
							<view class="text">{{ item.text }}</view>
						</view>
						<view class="right">
							<view class="text">{{ item.rightText }}</view>
							<uni-icons type="right" size="15" color="#aaa"></uni-icons>
						</view>
					</view>
				</template>
			</view>
		</view>
		 
		 <view class="section">
			 <view class="list">
				 <view class="row" v-for="(item, index) in list2" :key="index" @click="navigateToPage(item)">
					 <view class="left">
						 <uni-icons :type="item.icon" size="20"></uni-icons>
						 <view class="text">{{ item.text }}</view>
					 </view>
					 <view class="right">
						 <view class="text">{{ item.rightText }}</view>
						 <uni-icons type="right" size="15" color="#aaa"></uni-icons>
					 </view>
				 </view>
			 </view>
		 </view>
	</view>
</template>

<script setup>
import { ref } from "vue";

// 【修改点 2】: 在数据中为需要跳转的项添加 url 属性
const list1 = ref([
  { id: 1, icon: 'download-filled', text: '我的下载', rightText: '3', url: '/pages/index/index' },
  { id: 2, icon: 'star-filled', text: '我的评分', rightText: '5', url: '/pages/classlist/classlist' },
  { id: 3, icon: 'chatboxes-filled', text: '联系客服', rightText: '' } // 此项没有url，因为它使用特殊逻辑
]);

// (为了完整性，也为 list2 的项添加了示例 url)
const list2 = ref([
  { id: 4, icon: 'notification-filled', text: '订阅更新', rightText: 'v1.2', url: '/pages/classlist/classlist' },
  { id: 5, icon: 'help-filled', text: '常见问题', rightText: '', url: '/pages/classlist/classlist' }
]);

// “联系客服”的邮件功能保持不变
const clickContact = () => {
	window.location.href = 'mailto:hyastar@qq.com';
};

// 【修改点 3】: 新增一个方法，用于处理页面跳转
const navigateToPage = (item) => {
	// 检查 item 对象中是否存在 url 属性
	if (item.url) {
		// 如果存在，则使用 uni-app 的 API 进行跳转
		uni.navigateTo({
			url: item.url
		});
	}
	// 如果没有 url，则点击事件不执行任何操作
};

</script>

<style lang="scss" scoped>
/* 样式部分完全不变 */
.userLayout {
	.userInfo {
		display: flex;
		align-items: center;
		justify-content: center;
		flex-direction: column;
		padding: 50rpx 0;
		.avatar {
			width: 160rpx;
			height: 160rpx;
			border-radius: 50%;
			overflow: hidden;
			image {
				width: 100%;
				height: 100%;
			}
		}
		.ip {
			font-size: 44rpx;
			color: #333;
			padding: 20rpx 0 5rpx;
		}
		.address {
			font-size: 28rpx;
			color: #aaa;
		}
	}

	.section {
		width: 690rpx;
		margin: 50rpx auto;
		border: 1px solid #eee;
		border-radius: 10rpx;
		box-shadow: 0 0 30rpx rgba(0, 0, 0, 0.05);
		.list {
			.row {
				display: flex;
				justify-content: space-between;
				align-items: center;
				padding: 0 30rpx;
				height: 100rpx;
				border-bottom: 1px solid #eee;
				position: relative;
				background-color: #fff;
				&:last-child {
					border-bottom: 0;
				}
				.left {
					display: flex;
					align-items: center;
					:deep(){
					.uni-icons{
						color: $brand-theme-color !important;				
						}
					}
					.text {
						padding-left: 20rpx;
						color: #666;
					}
				}
				.right {
					display: flex;
					align-items: center;
					.text {
						font-size: 28rpx;
						color: #aaa;
						padding-right: 10rpx;
					}
				}
				button {
					position: absolute;
					top: 0;
					left: 0;
					height: 100rpx;
					width: 100%;
					opacity: 0;
				}
			}
		}
	}
}
</style>