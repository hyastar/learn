<template>
	<view class="control-page" v-if="deviceInfo.deviceId">
		<common-title>
			<template #name>{{ deviceInfo.name || '未知设备' }}</template>
		</common-title>
		
		<view class="info-panel">
			<text>状态: {{ connectionStatus }}</text>
		</view>

		<common-title>
			<template #name>快捷指令</template>
		</common-title>
		<view class="control-panel">
			<view class="led-control">
				<text>LED 0</text>
				<switch :checked="led0Status" @change="controlLed(0, $event)" color="#FFCC33"/>
			</view>
			<view class="led-control">
				<text>LED 1</text>
				<switch :checked="led1Status" @change="controlLed(1, $event)" color="#FFCC33"/>
			</view>
		</view>

		<common-title>
			<template #name>自定义数据发送</template>
		</common-title>
		<view class="send-panel">
			<view class="encoding-picker">
				<picker @change="bindSendEncodingChange" :value="sendEncodingIndex" :range="encodingOptions">
					<view class="picker-content">
						{{ encodingOptions[sendEncodingIndex] }}
						<uni-icons type="bottom" size="14" color="#666"></uni-icons>
					</view>
				</picker>
			</view>
			<input class="input-box" v-model="customData" :placeholder="inputPlaceholder" />
			<button class="send-btn" @click="sendCustomData" :disabled="!isReady">发送</button>
		</view>

		<common-title>
			<template #name>数据接收区</template>
		</common-title>
		<view class="data-display">
			<view class="receive-settings">
				<text class="label">接收格式:</text>
				<picker @change="bindReceiveEncodingChange" :value="receiveEncodingIndex" :range="encodingOptions.slice(0, 3)">
					<view class="picker-content receive-picker">
						{{ encodingOptions[receiveEncodingIndex] }}
						<uni-icons type="bottom" size="14" color="#666"></uni-icons>
					</view>
				</picker>
			</view>
			<view class="data-item">
				<text class="label">温度:</text>
				<text class="value">{{ temperature }} °C</text>
			</view>
			<view class="data-item">
				<text class="label">湿度:</text>
				<text class="value">{{ humidity }} %</text>
			</view>
			<view class="data-item raw-data">
				<text class="label">原始HEX:</text>
				<text class="value">{{ receivedHexData }}</text>
			</view>
			<view class="data-item raw-data">
				<text class="label">解码文本:</text>
				<text class="value decoded-text">{{ decodedText }}</text>
			</view>
		</view>
		
		<view class="footer-actions">
			<button class="disconnect-btn" @click="disconnect">断开连接</button>
		</view>
	</view>
	<view class="placeholder" v-else>
		<text>请先在“连接”页面连接设备</text>
	</view>
</template>

<script setup>
import { ref, reactive, computed } from 'vue';
import { onShow, onHide } from '@dcloudio/uni-app';
import commonTitle from '@/components/common-title/common-title.vue';

// 导入所有工具函数
import { encodegbk } from '@/utils/urlEncodeGBK.js';
import { GBKHexstrToString2 } from '@/utils/Decoder.js';
import { 
	hexStringToArrayBuffer, 
	utf8StringToArrayBuffer, 
	asciiStringToArrayBuffer,
	arrayBufferToHexString, 
	arrayBufferToUtf8String, 
	arrayBufferToAsciiString 
} from '@/utils/bleUtils.js';

const deviceInfo = reactive({ deviceId: null, name: null });
const connectionStatus = ref('未连接');
const isReady = ref(false);

// 分别记录服务和读写特征的ID
const serviceId = ref('');
const writeCharacteristicId = ref('');
const notifyCharacteristicId = ref('');


const led0Status = ref(false);
const led1Status = ref(false);
const temperature = ref('--');
const humidity = ref('--');
const receivedHexData = ref('无');
const customData = ref('');
let receivedBuffer = ref(null);

let mockDataInterval = null;

// --- 编码格式处理 ---
const encodingOptions = ref(['HEX', 'UTF-8', 'GBK', 'ASCII']);
const sendEncodingIndex = ref(0);
const selectedSendEncoding = computed(() => encodingOptions.value[sendEncodingIndex.value]);
const inputPlaceholder = computed(() => {
	if (selectedSendEncoding.value === 'HEX') return '请输入十六进制, 如 B2 E2 C8 D4';
	return '请输入字符串';
});
const receiveEncodingIndex = ref(0);
const selectedReceiveEncoding = computed(() => encodingOptions.value[receiveEncodingIndex.value]);

function bindSendEncodingChange(e) {
	sendEncodingIndex.value = e.detail.value;
}
function bindReceiveEncodingChange(e) {
	receiveEncodingIndex.value = e.detail.value;
}
const decodedText = computed(() => {
	if (!receivedBuffer.value) return '无';
	const hexStr = arrayBufferToHexString(receivedBuffer.value).replace(/\s/g, '');
	switch (selectedReceiveEncoding.value) {
		case 'HEX':
			return arrayBufferToHexString(receivedBuffer.value);
		case 'UTF-8':
			return arrayBufferToUtf8String(receivedBuffer.value);
		case 'GBK':
			return GBKHexstrToString2(hexStr);
		case 'ASCII':
			return arrayBufferToAsciiString(receivedBuffer.value);
		default:
			return '请选择解码格式';
	}
});


onShow(() => {
	const storedDevice = uni.getStorageSync('connectedDevice');
	if (storedDevice && storedDevice.deviceId) {
		deviceInfo.deviceId = storedDevice.deviceId;
		deviceInfo.name = storedDevice.name;

		// #ifndef H5
		connectionStatus.value = '已连接，正在发现服务...';
		setTimeout(discoverServices, 500); // 增加延时，提高稳定性
		// #endif

		// #ifdef H5
		connectionStatus.value = 'H5 模拟模式';
		isReady.value = true;
		startMockData();
		// #endif
	} else {
		Object.assign(deviceInfo, { deviceId: null, name: null });
	}
});

onHide(() => {
	// #ifndef H5
	if (deviceInfo.deviceId && notifyCharacteristicId.value) {
		uni.offBLECharacteristicValueChange(handleDataReceived);
	}
	// #endif
	// #ifdef H5
	stopMockData();
	// #endif
	isReady.value = false;
	connectionStatus.value = '未连接';
});

function startMockData() {
	if (mockDataInterval) clearInterval(mockDataInterval);
	mockDataInterval = setInterval(() => {
		const mockString = `温度:25,湿度:60`;
		const hexStr = encodegbk(mockString).replace(/%/g, '');
		const buffer = hexStringToArrayBuffer(hexStr);
		handleDataReceived({ value: buffer });
	}, 2000);
}
function stopMockData() {
	if (mockDataInterval) clearInterval(mockDataInterval);
}

// #ifndef H5
function discoverServices() {
	uni.getBLEDeviceServices({
		deviceId: deviceInfo.deviceId,
		success: (res) => {
			connectionStatus.value = '已发现服务，正在查找特征...';
			discoverCharacteristics(res.services);
		},
		fail: () => {
			connectionStatus.value = '服务发现失败';
		}
	});
}

// 【重要】重构特征查找逻辑
async function discoverCharacteristics(services) {
    for (let service of services) {
        const res = await uni.getBLEDeviceCharacteristics({
            deviceId: deviceInfo.deviceId,
            serviceId: service.uuid
        }).catch(() => null);

        if (res && res.characteristics) {
            for (let char of res.characteristics) {
                // 如果还没找到可写特征，并且当前特征可写
                if (!writeCharacteristicId.value && char.properties.write) {
                    serviceId.value = service.uuid; // 记录服务ID
                    writeCharacteristicId.value = char.uuid;
                }
                // 如果还没找到可通知特征，并且当前特征可通知
                if (!notifyCharacteristicId.value && char.properties.notify) {
                    serviceId.value = service.uuid; // 记录服务ID
                    notifyCharacteristicId.value = char.uuid;
                }
            }
        }
    }

    // 查找结束后，根据找到的特征更新状态
    if (writeCharacteristicId.value && notifyCharacteristicId.value) {
        connectionStatus.value = '设备就绪，可以通信';
        isReady.value = true;
        enableNotifications();
    } else if (writeCharacteristicId.value) {
        connectionStatus.value = '仅找到发送通道，无法接收数据';
		isReady.value = true;
    } else if (notifyCharacteristicId.value) {
        connectionStatus.value = '仅找到接收通道，无法发送数据';
		isReady.value = false;
		enableNotifications();
    } else {
        connectionStatus.value = '未找到可用的读写特征';
		isReady.value = false;
    }
}

function enableNotifications() {
	if (!notifyCharacteristicId.value) return; // 如果没有找到通知特征，则不执行
	uni.notifyBLECharacteristicValueChange({
		deviceId: deviceInfo.deviceId,
		serviceId: serviceId.value,
		characteristicId: notifyCharacteristicId.value,
		state: true,
		success: () => {
			uni.onBLECharacteristicValueChange(handleDataReceived)
			console.log('通知已启用');
		},
		fail: () => {
			connectionStatus.value = '通知启用失败';
		}
	});
}
// #endif

function handleDataReceived(res) {
	receivedBuffer.value = res.value; 
	receivedHexData.value = arrayBufferToHexString(res.value);
	const tempStr = arrayBufferToUtf8String(res.value);
	if (tempStr.includes('T:') && tempStr.includes('H:')) {
		const tempMatch = tempStr.match(/T:(\d+\.?\d*)/);
		const humMatch = tempStr.match(/H:(\d+\.?\d*)/);
		if (tempMatch) temperature.value = tempMatch[1];
		if (humMatch) humidity.value = humMatch[1];
	}
}

function sendBuffer(buffer) {
	if (!isReady.value || !writeCharacteristicId.value) {
		uni.showToast({ title: '设备未就绪或无发送通道', icon: 'none' });
		return;
	}
	// #ifndef H5
	uni.writeBLECharacteristicValue({
		deviceId: deviceInfo.deviceId,
		serviceId: serviceId.value,
		characteristicId: writeCharacteristicId.value, // 使用找到的可写特征ID
		value: buffer,
		fail: (err) => uni.showToast({ title: '发送失败: ' + JSON.stringify(err), icon: 'none' })
	});
	// #endif
}

function controlLed(index, event) {
	const status = event.detail.value;
	let command = '';
	if (index === 0) {
		led0Status.value = status;
		command = status ? 'LED0_ON' : 'LED0_OFF';
	} else {
		led1Status.value = status;
		command = status ? 'LED1_ON' : 'LED1_OFF';
	}
	const buffer = utf8StringToArrayBuffer(command);
	sendBuffer(buffer);
	// #ifdef H5
	console.log(`H5模拟发送 (UTF-8): ${command}`);
	// #endif
}

function sendCustomData() {
	if (!customData.value) {
		uni.showToast({ title: '请输入内容', icon: 'none' });
		return;
	}
	let buffer;
	try {
		switch (selectedSendEncoding.value) {
			case 'HEX':
				buffer = hexStringToArrayBuffer(customData.value);
				break;
			case 'UTF-8':
				buffer = utf8StringToArrayBuffer(customData.value);
				break;
			case 'GBK':
				const hexStr = encodegbk(customData.value).replace(/%/g, '');
				buffer = hexStringToArrayBuffer(hexStr);
				break;
			case 'ASCII':
				buffer = asciiStringToArrayBuffer(customData.value);
				break;
			default:
				buffer = utf8StringToArrayBuffer(customData.value);
		}
		if (!buffer) throw new Error('输入格式无效');
		sendBuffer(buffer);
		// #ifdef H5
		console.log(`H5模拟发送 (${selectedSendEncoding.value}): ${customData.value}`);
		uni.showToast({ title: `模拟发送(${selectedSendEncoding.value})`, icon: 'none' });
		// #endif
	} catch (e) {
		uni.showToast({ title: e.message || '输入格式错误', icon: 'none' });
	}
}

function disconnect() {
	// #ifndef H5
	if (deviceInfo.deviceId) {
		uni.closeBLEConnection({ deviceId: deviceInfo.deviceId });
	}
	// #endif
	uni.removeStorageSync('connectedDevice');
	Object.assign(deviceInfo, { deviceId: null, name: null });
	isReady.value = false;
	uni.showToast({ title: '已断开连接' });
	uni.switchTab({ url: '/pages/connect/connect' });
}
</script>

<style lang="scss" scoped>
.control-page {
	padding: 20rpx;
	padding-bottom: 50rpx;
}
.info-panel {
	padding: 15rpx 20rpx;
	background-color: #f0f8ff;
	color: #4682b4;
	border-radius: 12rpx;
	margin-bottom: 20rpx;
	font-size: 26rpx;
	text-align: center;
}
.control-panel, .data-display {
	background-color: #fff;
	border-radius: 16rpx;
	padding: 30rpx;
	margin-bottom: 30rpx;
	box-shadow: 0 4rpx 12rpx rgba(0,0,0,0.05);
}
.led-control {
	display: flex;
	justify-content: space-between;
	align-items: center;
	font-size: 32rpx;
	&:not(:last-child) {
		margin-bottom: 30rpx;
	}
}
.send-panel {
	display: flex;
	align-items: center;
	gap: 10rpx;
	background-color: #fff;
	border-radius: 16rpx;
	padding: 30rpx;
	margin-bottom: 30rpx;
	box-shadow: 0 4rpx 12rpx rgba(0,0,0,0.05);

	.encoding-picker {
		background-color: #f5f5f5;
		border-radius: 12rpx;
		padding: 16rpx 20rpx;
		border: 1px solid $border-color-light;
		.picker-content {
			display: flex;
			align-items: center;
			font-size: 28rpx;
			color: #333;
		}
	}

	.input-box {
		flex: 1;
		border: 1px solid $border-color-light;
		border-radius: 12rpx;
		padding: 16rpx;
		font-size: 28rpx;
		height: 82rpx;
		box-sizing: border-box;
	}
	.send-btn {
		background-color: $brand-theme-color;
		color: white;
		margin: 0;
		height: 82rpx;
		line-height: 82rpx;
	}
}
.data-display {
	font-size: 30rpx;
	.receive-settings {
		display: flex;
		justify-content: flex-end;
		align-items: center;
		margin-bottom: 20rpx;
		padding-bottom: 20rpx;
		border-bottom: 1px solid $border-color-light;
		.label {
			font-size: 28rpx;
			color: $text-font-color-2;
		}
		.receive-picker {
			background-color: #f5f5f5;
			border-radius: 8rpx;
			padding: 8rpx 16rpx;
			border: 1px solid $border-color-light;
			margin-left: 10rpx;
		}
	}
	.data-item {
		display: flex;
		justify-content: space-between;
		padding: 15rpx 0;
		.label {
			color: $text-font-color-2;
			flex-shrink: 0;
			margin-right: 20rpx;
		}
		.value {
			font-weight: bold;
			font-family: monospace;
			word-break: break-all;
			text-align: right;
		}
		.decoded-text {
			color: $brand-theme-color;
		}
	}
}
.footer-actions {
	margin-top: 50rpx;
	.disconnect-btn {
		background-color: #f44336;
		color: white;
	}
}
.placeholder{
	display: flex;
	height: 100vh;
	justify-content: center;
	align-items: center;
	color: $text-font-color-3;
}
</style>

