<template>
	<view class="container">
		<view class="layout">
			<view class="box" v-for="item in 5">
				<view class="pic">
					<image src="/static/images/xxmLogo.png" mode="widthFix"></image>
				</view>
				<view class="text">@@@@</view>
			</view>
		</view>
	</view>
</template>

<script setup>

</script>

<style lang="scss" scoped>
.container{
	.layout{
		padding:50rpx;
		.box{
			margin-bottom:60rpx;
			box-shadow: 0 10rpx 40rpx rgba(0,0,0,0.2);
			border-radius: 15rpx;
			overflow: hidden;
			.pic{
				image{
					width:100%;
				}
			}
			.text{
				padding:30rpx;
			}
		}
	}
}
</style>
