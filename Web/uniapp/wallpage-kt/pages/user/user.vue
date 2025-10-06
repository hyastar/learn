<template>
	<view class="userLayout">
		<!-- 我已经把您的用户信息部分加回来了 -->
		<view class="userInfo">
			<view class="avatar">
				<!-- 请确保您的/static/images/目录下有这张图片 -->
				<image src="/static/images/xxmLogo.png" mode="aspectFill"></image>
			</view>
			<view class="ip">127.0.0.1</view>
			<view class="address">来自于：未知</view>
		</view>

		 <!-- 第一个列表区域 -->
		<view class="section">
			<view class="list">
				<!-- 使用 <template> 标签进行循环，以便内部可以使用 v-if/v-else -->
				<template v-for="(item, index) in list1" :key="index">
					<!-- 判断：如果这一项是“联系客服” -->
					<view class="row" v-if="item.text === '联系客服'">
						<view class="left">
							<uni-icons :type="item.icon" size="20" color="#2B9939"></uni-icons>
							<view class="text">{{ item.text }}</view>
						</view>
						<view class="right">
							<view class="text"></view>
							<uni-icons type="right" size="15" color="#aaa"></uni-icons>
						</view>
						<!-- 这里是老师的特殊按钮布局 -->
						<!-- #ifdef MP -->
						<button open-type="contact">联系客服</button>
						<!-- #endif -->
						<!-- #ifndef MP -->
						<button @click="clickContact">拨打电话</button>
						<!-- #endif -->
					</view>

					<!-- 否则（对于其他普通项） -->
					<view class="row" v-else>
						<view class="left">
							<uni-icons :type="item.icon" size="20" color="#2B9939"></uni-icons>
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
		 
		 <!-- 第二个列表区域 -->
		 <view class="section">
			 <view class="list">
				 <!-- 使用 v-for 遍历 list2 数组 -->
				 <view class="row" v-for="(item, index) in list2" :key="index">
					 <view class="left">
						 <!-- 动态绑定图标和文字 -->
						 <uni-icons :type="item.icon" size="20" color="#2B9939"></uni-icons>
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
// 使用 <script setup> 语法，代码更简洁
// 修复：从 'vue' 中手动导入 ref，确保其始终可用
import { ref } from "vue";

// 定义第一个列表的数据
const list1 = ref([
  { id: 1, icon: 'download-filled', text: '我的下载', rightText: '3' },
  { id: 2, icon: 'star-filled', text: '我的评分', rightText: '5' },
  { id: 3, icon: 'chatboxes-filled', text: '联系客服', rightText: '' } // 保持数据结构不变
]);

// 定义第二个列表的数据
const list2 = ref([
  { id: 4, icon: 'notification-filled', text: '订阅更新', rightText: 'v1.2' },
  { id: 5, icon: 'help-filled', text: '常见问题', rightText: '' }
]);

// 老师的“拨打电话”功能，需要在这里定义
const clickContact = () => {
	uni.makePhoneCall({
		phoneNumber: "114" // 这里可以替换成您的客服电话
	});
};
</script>

<style lang="scss" scoped>
// 样式部分无需修改，老师的样式已包含透明按钮的样式
.userLayout {
	// 我已经把用户信息部分的样式也加回来了
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
				background: #fff;
				&:last-child {
					border-bottom: 0;
				}
				.left {
					display: flex;
					align-items: center;
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
				// 老师的透明按钮样式，这里已经有了
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

