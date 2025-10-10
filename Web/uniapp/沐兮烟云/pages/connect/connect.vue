<template>
	<view class="connect-page">
		<!-- 使用您之前的通用标题组件 -->
		<common-title>
			<template #name>设备连接</template>
		</common-title>

		<!-- 状态信息显示 -->
		<view class="status-bar">
			<view :class="['status-light', { 'connected': isConnected }]"></view>
			<text>{{ statusMessage }}</text>
		</view>

		<!-- 操作按钮 -->
		<view class="button-group">
			<button @click="startScan" :loading="isScanning" class="primary-btn">
				{{ isScanning ? '正在扫描...' : '开始扫描设备' }}
			</button>
			<button @click="stopScan" v-if="isScanning" class="stop-btn">停止扫描</button>
		</view>

		<!-- 设备列表 -->
		<common-title>
			<template #name>可用设备</template>
		</common-title>
		<scroll-view class="device-list" scroll-y>
			<view v-if="devices.length === 0 && !isScanning" class="empty-list">
				<text>暂未发现设备</text>
				<text class="tip">{{ platformTip }}</text>
			</view>
			<view v-for="device in devices" :key="device.deviceId" class="device-item" @click="connectToDevice(device)">
				<view class="device-info">
					<view class="device-name">{{ device.name || '未知设备' }}</view>
					<view class="device-id">{{ device.deviceId }}</view>
				</view>
				<view class="connect-action">
					<text>连接</text>
				</view>
			</view>
			<!-- 扫描加载状态 -->
			<uni-load-more v-if="isScanning" status="loading"></uni-load-more>
		</scroll-view>
	</view>
</template>

<script setup>
import { ref, onMounted } from 'vue';
import { onUnload } from '@dcloudio/uni-app';
import commonTitle from '@/components/common-title/common-title.vue';

// 响应式变量
const devices = ref([]);
const isScanning = ref(false);
const isConnected = ref(false);
const statusMessage = ref('等待初始化...');
const platformTip = ref('请确保设备已开机并在附近');

// 初始化蓝牙
function initBluetooth() {
	// #ifndef H5
	uni.openBluetoothAdapter({
		success: () => {
			statusMessage.value = '蓝牙已初始化';
			listenConnectionState(); // 监听连接状态变化
		},
		fail: (err) => {
			statusMessage.value = '请打开手机蓝牙';
			uni.showToast({ title: '请先开启手机蓝牙', icon: 'none' });
		}
	});
	// #endif
}

// 开始扫描
function startScan() {
	if (isScanning.value) return;
	isScanning.value = true;
	statusMessage.value = '正在扫描设备...';
	devices.value = [];

	// #ifndef H5
	uni.startBluetoothDevicesDiscovery({
		allowDuplicatesKey: false,
		success: () => {
			uni.onBluetoothDeviceFound((res) => {
				res.devices.forEach(device => {
					if (device.name && !devices.value.some(d => d.deviceId === device.deviceId)) {
						devices.value.push(device);
					}
				});
			});
		},
		fail: (err) => {
			isScanning.value = false;
			statusMessage.value = '扫描失败';
			uni.showToast({ title: '扫描设备失败', icon: 'none' });
		}
	});
	// #endif
	
	// #ifdef H5
	// H5 模拟扫描
	console.log('H5模式: 模拟扫描...');
	setTimeout(() => {
		devices.value = [
			{ name: 'JDY-23-MOCK', deviceId: 'H5-MOCK-DEVICE-1' },
			{ name: 'STM32-BLE-MOCK', deviceId: 'H5-MOCK-DEVICE-2' },
			{ name: '未知设备', deviceId: 'H5-MOCK-DEVICE-3' }
		];
		isScanning.value = false;
		statusMessage.value = 'H5模拟扫描完成';
	}, 1500);
	// #endif
}

// 停止扫描
function stopScan() {
	// #ifndef H5
	uni.stopBluetoothDevicesDiscovery({
		success: () => {
			isScanning.value = false;
			statusMessage.value = '已停止扫描';
		}
	});
	// #endif
	
	// #ifdef H5
	isScanning.value = false;
	statusMessage.value = 'H5模拟已停止扫描';
	// #endif
}

// 连接设备
function connectToDevice(device) {
	stopScan();
	statusMessage.value = `正在连接 ${device.name}...`;

	// #ifndef H5
	uni.createBLEConnection({
		deviceId: device.deviceId,
		timeout: 10000,
		success: (res) => {
			isConnected.value = true;
			statusMessage.value = `已连接到 ${device.name}`;
			uni.setStorageSync('connectedDevice', { deviceId: device.deviceId, name: device.name });
			uni.showToast({ title: '连接成功', icon: 'success' });
			uni.switchTab({ url: '/pages/control/control' });
		},
		fail: (err) => {
			isConnected.value = false;
			statusMessage.value = '连接失败';
			uni.showToast({ title: '连接失败，请重试', icon: 'none' });
		}
	});
	// #endif
	
	// #ifdef H5
	// H5 模拟连接
	console.log('H5模式: 模拟连接到', device.name);
	setTimeout(() => {
		isConnected.value = true;
		statusMessage.value = `H5模式: 已连接 ${device.name}`;
		uni.setStorageSync('connectedDevice', { deviceId: device.deviceId, name: device.name });
		uni.showToast({ title: 'H5模拟连接成功', icon: 'success' });
		uni.switchTab({ url: '/pages/control/control' });
	}, 1000);
	// #endif
}

// 监听蓝牙连接状态
function listenConnectionState() {
    // #ifndef H5
    uni.onBLEConnectionStateChange(function (res) {
        if (!res.connected) {
			isConnected.value = false;
			statusMessage.value = '蓝牙连接已断开';
			uni.removeStorageSync('connectedDevice');
			uni.showToast({title:'连接已断开', icon:'none'});
        }
    });
    // #endif
}

onMounted(() => {
	// #ifdef H5
	statusMessage.value = 'H5 模拟环境（无蓝牙功能）';
	platformTip.value = 'H5 环境将显示模拟设备';
	// #endif

	// #ifndef H5
	initBluetooth();
	// #endif
});

onUnload(() => {
	// #ifndef H5
	stopScan();
	// #endif
});
</script>

<style lang="scss" scoped>
.connect-page {
	padding: 20rpx;
	display: flex;
	flex-direction: column;
	height: 100vh;
	box-sizing: border-box;
}
.status-bar {
	display: flex;
	align-items: center;
	padding: 20rpx;
	background-color: #f5f5f5;
	border-radius: 16rpx;
	margin-bottom: 20rpx;
	font-size: 28rpx;
	color: #666;
	.status-light {
		width: 20rpx;
		height: 20rpx;
		border-radius: 50%;
		background-color: #f44336; // 红色，表示未连接
		margin-right: 20rpx;
		transition: background-color 0.3s;
		&.connected {
			background-color: #4caf50; // 绿色，表示已连接
		}
	}
}
.button-group {
	display: flex;
	gap: 20rpx;
	margin-bottom: 30rpx;
	.primary-btn {
		flex: 1;
		background-color: $brand-theme-color;
		color: white;
	}
	.stop-btn {
		flex: 1;
		background-color: #e57373;
		color: white;
	}
}
.device-list {
	flex: 1;
	background-color: #f9f9f9;
	border-radius: 16rpx;
	overflow-y: auto;
	min-height: 400rpx;
	.empty-list {
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
		height: 400rpx;
		color: $text-font-color-3;
		.tip {
			font-size: 24rpx;
			margin-top: 10rpx;
		}
	}
	.device-item {
		display: flex;
		align-items: center;
		padding: 30rpx 20rpx;
		border-bottom: 1px solid $border-color-light;
		background-color: white;
		&:active {
			background-color: #fafafa;
		}
		.device-info {
			flex: 1;
			.device-name {
				font-size: 32rpx;
				font-weight: bold;
				color: $text-font-color-1;
			}
			.device-id {
				font-size: 24rpx;
				color: $text-font-color-3;
				word-break: break-all;
			}
		}
		.connect-action {
			margin-left: 20rpx;
			padding: 10rpx 30rpx;
			background-color: $brand-theme-color;
			color: white;
			border-radius: 40rpx;
			font-size: 28rpx;
		}
	}
}
</style>

