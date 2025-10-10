<template>
	<view class="preview">
		<swiper circular :current="currentIndex" @change="swiperChange">
			<swiper-item v-for="(item,index) in class_list" :key="item._id">
				<image v-if="readImgs.includes(index)" @click="maskChange" :src="item.picurl" mode="aspectFill"></image>
			</swiper-item>
		</swiper>

		<view class="mask" v-if="maskState">
			<view class="goBack" :style="{top:getNavBarHeight() + 'px'}" @click="goBack">
				<uni-icons type="back" color="#fff" size="20"></uni-icons>
			</view>
			<view class="count">{{currentIndex + 1}} / {{class_list.length}}</view>
			<view class="time">
				<uni-dateformat :date="new Date()" format="hh:mm"></uni-dateformat>
			</view>
			<view class="date">
				<uni-dateformat :date="new Date()" format="MM月dd日"></uni-dateformat>
			</view>
			<view class="footer">
				<view class="box" @click="clickInfo">
					<uni-icons type="info" size="28"></uni-icons>
					<view class="text">信息</view>
				</view>
				<view class="box" @click="clickScore">
					<uni-icons type="star" size="28"></uni-icons>
					<view class="text">评分</view>
				</view>
				<view class="box" @click="clickDownload">
					<uni-icons type="download" size="28"></uni-icons>
					<view class="text">下载</view>
				</view>
			</view>
		</view>

		<uni-popup ref="infoPopup" type="bottom">
			<view class="infoPopup">
				<view class="popHeader">
					<view class="title">壁纸信息</view>
					<view class="close" @click="closeInfoPopup">
						<uni-icons type="closeempty" size="18" color="#999"></uni-icons>
					</view>
				</view>
				<scroll-view scroll-y>
					<view class="content">
						<template v-if="currentInfo">
							<view class="row" v-for="item in infoList" :key="item.label">
								<view class="label">{{ item.label }}</view>
								<view class="value roteBox" v-if="item.type === 'rate'">
									<uni-rate readonly :value="item.value" size="16" />
									<text class="score">{{ item.value }}分</text>
								</view>
								<view class="value tabs" v-else-if="item.type === 'tabs'">
									<view class="tab" v-for="tab in item.value" :key="tab">{{ tab }}</view>
								</view>
								<text selectable class="value" v-else>{{ item.value }}</text>
							</view>
						</template>
						<view class="copyright">
							声明：本图片来用户投稿，非商业使用，用于免费学习交流，如侵犯了您的权益，您可以拷贝壁纸ID举报至平台，邮箱513894357@qq.com，管理将删除侵权壁纸，维护您的权益。
						</view>
					</view>
				</scroll-view>
			</view>
		</uni-popup>

		<uni-popup ref="scorePopup" type="center" :is-mask-click="false">
			<view class="scorePopup">
				<view class="popHeader">
					<view></view>
					<view class="title">{{isScore ? '您已评分过了~' : '给壁纸打个分吧'}}</view>
					<view class="close" @click="clickScoreClose">
						<uni-icons type="closeempty" size="18" color="#999"></uni-icons>
					</view>
				</view>

				<view class="content">
					<uni-rate v-model="userScore" allowHalf :disabled="isScore" disabled-color="#FFCA3E" />
					<text class="text">{{userScore}}分</text>
				</view>

				<view class="footer">
					<button @click="submitScore" :disabled="!userScore || isScore" type="primary" size="mini" plain>确认评分</button>
				</view>
			</view>
		</uni-popup>
	</view>
</template>

<script setup>
import {
	ref,
	computed
} from 'vue';
import {
	onLoad
} from "@dcloudio/uni-app"
import {
	getNavBarHeight
} from "@/utils/system.js"

// reactive state
const maskState = ref(true);
const infoPopup = ref(null);
const scorePopup = ref(null);
const userScore = ref(0);
const class_list = ref([]);
const currentId = ref(null);
const currentIndex = ref(0);
const readImgs = ref([]); // 用于预加载的索引数组 [prev, current, next]

// 从缓存初始化图片列表
const storgClassList = uni.getStorageSync("storgClassList") || [];
class_list.value = storgClassList.map(item => {
	return {
		...item,
		// 将缩略图地址替换为高清图地址
		picurl: item.smallPicurl.replace("_small.webp", ".jpg")
	}
});


// =======================================================================
// 核心逻辑：图片预加载、信息获取
// =======================================================================

// 【优化点】创建一个统一的、可复用的函数来更新预加载图片数组
const updateReadImgs = (index) => {
	const listLength = class_list.value.length;
	if (listLength === 0) return; // 避免列表为空时出错

	const prevIndex = (index - 1 + listLength) % listLength;
	const nextIndex = (index + 1) % listLength;

	readImgs.value = [prevIndex, index, nextIndex];

	console.log(`当前索引: ${index}, 预加载索引: [${readImgs.value.join(', ')}]`);
}

// 【优化点】将当前壁纸信息变为计算属性，使其自动根据 currentIndex 变化
const currentInfo = computed(() => {
	if (!class_list.value.length) return null;
	return class_list.value[currentIndex.value];
});

// 【优化点】信息弹窗所需的数据列表也变为计算属性
const infoList = computed(() => {
	if (!currentInfo.value) return [];
	return [{
		label: "壁纸ID：",
		value: currentInfo.value._id
	}, {
		label: "发布者：",
		value: currentInfo.value.nickname
	}, {
		label: "评分：",
		value: currentInfo.value.score,
		type: 'rate'
	}, {
		label: "摘要：",
		value: currentInfo.value.description
	}, {
		label: "标签：",
		value: currentInfo.value.tabs,
		type: 'tabs'
	}];
});

// 页面加载
onLoad((e) => {
	currentId.value = e.id;

	// 如果没有id，默认显示第一张
	let findIndex = class_list.value.findIndex(item => item._id == currentId.value);
	currentIndex.value = findIndex === -1 ? 0 : findIndex;

	// 调用新函数进行初始化
	updateReadImgs(currentIndex.value);
});


// =======================================================================
// 事件处理
// =======================================================================

// Swiper 滑动事件
const swiperChange = (e) => {
	const newIndex = e.detail.current;
	currentIndex.value = newIndex;
	// 调用新函数更新预加载数组
	updateReadImgs(newIndex);
};

// 切换遮罩层
const maskChange = () => {
	maskState.value = !maskState.value;
};

// 返回上一页
const goBack = () => {
	uni.navigateBack();
};

// 下载
const clickDownload = () => {
	// #ifdef H5
	uni.showModal({
		content: "请右键保存壁纸",
		showCancel: false
	})
	// #endif

	// #ifndef H5
	uni.showLoading({
		title: "下载中...",
		mask: true
	});
	uni.getImageInfo({
		src: currentInfo.value.picurl,
		success: (res) => {
			uni.saveImageToPhotosAlbum({
				filePath: res.path,
				success: () => {
					uni.showToast({
						title: "保存成功",
						icon: 'success'
					});
				},
				fail: (err) => {
					// 修正：使用 === 进行严格比较，而不是 = 赋值
					if (err.errMsg === 'saveImageToPhotosAlbum:fail cancel') {
						uni.showToast({
							title: "取消保存",
							icon: "none"
						});
					} else if (err.errMsg === 'saveImageToPhotosAlbum:fail auth deny' || err.errMsg === 'saveImageToPhotosAlbum:fail:auth denied') {
						uni.showModal({
							title: "提示",
							content: "需要授权才能保存到相册",
							success: (modalRes) => {
								if (modalRes.confirm) {
									uni.openSetting({
										success: (setting) => {
											if (setting.authSetting['scope.writePhotosAlbum']) {
												uni.showToast({
													title: "授权成功，请再次点击下载",
													icon: "none"
												});
											} else {
												uni.showToast({
													title: "获取授权失败",
													icon: "none"
												});
											}
										}
									});
								}
							}
						});
					} else {
						uni.showToast({
							title: '保存失败，请稍后重试',
							icon: 'error'
						});
					}
				},
				complete: () => {
					uni.hideLoading();
				}
			});
		},
		fail: (err) => {
			uni.hideLoading();
			uni.showToast({
				title: '图片信息获取失败',
				icon: 'error'
			});
			console.error(err);
		}
	});
	// #endif 
};


// --- 信息弹窗方法 ---
const clickInfo = () => {
	infoPopup.value.open();
};
const closeInfoPopup = () => {
	infoPopup.value.close();
};


// --- 评分弹窗方法 ---
const isScore = ref(false); // 是否已评分的状态

const clickScore = () => {
	// 假设用户评分信息在 'userScore' 字段中
	if (currentInfo.value?.userScore) {
		isScore.value = true;
		userScore.value = currentInfo.value.userScore;
	} else {
		isScore.value = false;
		userScore.value = 0;
	}
	scorePopup.value.open();
}

const clickScoreClose = () => {
	scorePopup.value.close();
	// 关闭时重置临时状态
	userScore.value = 0;
	isScore.value = false;
}

const submitScore = () => {
	uni.showLoading({
		title: "评分提交中..."
	});
	setTimeout(() => {
		uni.hideLoading();
		uni.showToast({
			title: `您评了${userScore.value}分`,
			icon: 'none'
		});
		// 模拟评分成功后，更新当前壁纸信息中的用户评分
		if (currentInfo.value) currentInfo.value.userScore = userScore.value;
		clickScoreClose();
	}, 1000)
}
</script>

<style lang="scss" scoped>
	.preview {
		width: 100%;
		height: 100vh;
		position: relative;

		swiper {
			width: 100%;
			height: 100%;

			image {
				width: 100%;
				height: 100%;
			}
		}

		.mask {
			&>view {
				position: absolute;
				left: 0;
				right: 0;
				margin: auto;
				color: #fff;
				width: fit-content;
			}

			.goBack {
				width: 38px;
				height: 38px;
				background: rgba(0, 0, 0, 0.5);
				left: 30rpx;
				margin-left: 0;
				border-radius: 100px;
				backdrop-filter: blur(10rpx);
				border: 1rpx solid rgba(255, 255, 255, 0.3);
				display: flex;
				align-items: center;
				justify-content: center;
			}

			.count {
				top: 10vh;
				background: rgba(0, 0, 0, 0.3);
				font-size: 28rpx;
				border-radius: 40rpx;
				padding: 8rpx 28rpx;
				backdrop-filter: blur(10rpx);
			}

			.time {
				font-size: 140rpx;
				top: calc(10vh + 80rpx);
				font-weight: 100;
				line-height: 1em;
				text-shadow: 0 4rpx rgba(0, 0, 0, 0.3);
			}

			.date {
				font-size: 34rpx;
				top: calc(10vh + 230rpx);
				text-shadow: 0 4rpx rgba(0, 0, 0, 0.3);
			}

			.footer {
				background: rgba(255, 255, 255, 0.8);
				bottom: 10vh;
				width: 65vw;
				height: 120rpx;
				border-radius: 120rpx;
				color: #000;
				display: flex;
				justify-content: space-around;
				align-items: center;
				box-shadow: 0 2rpx 0 rgba(0, 0, 0, 0.1);
				backdrop-filter: blur(20rpx);

				.box {
					display: flex;
					flex-direction: column;
					align-items: center;
					justify-content: center;
					padding: 2rpx 12rpx;

					.text {
						font-size: 26rpx;
						color: #333;
					}
				}
			}
		}

		.infoPopup {
			background: #fff;
			padding: 30rpx;
			border-radius: 30rpx 30rpx 0 0;
			overflow: hidden;

			.popHeader {
				display: flex;
				justify-content: space-between;
				align-items: center;

				.title {
					color: #666;
					font-size: 26rpx;
				}

				.close {
					padding: 6rpx;
				}
			}

			scroll-view {
				max-height: 60vh;

				.content {
					.row {
						display: flex;
						padding: 16rpx 0;
						font-size: 32rpx;
						line-height: 1.7em;

						.label {
							color: #999;
							width: 140rpx;
							text-align: right;
							font-size: 30rpx;
						}

						.value {
							flex: 1;
							width: 0;
						}

						.roteBox {
							display: flex;
							align-items: center;

							.score {
								font-size: 26rpx;
								color: #666;
								padding-left: 10rpx;
							}
						}

						.tabs {
							display: flex;
							flex-wrap: wrap;

							.tab {
								border: 1px solid #007aff;
								color: #007aff;
								font-size: 22rpx;
								padding: 10rpx 30rpx;
								border-radius: 40rpx;
								line-height: 1em;
								margin: 0 10rpx 10rpx 0;
							}
						}
					}

					.copyright {
						font-size: 28rpx;
						padding: 20rpx;
						background: #F6F6F6;
						color: #666;
						border-radius: 10rpx;
						margin: 20rpx 0;
						line-height: 1.6em;
					}
				}
			}
		}

		.scorePopup {
			background: #fff;
			padding: 30rpx;
			width: 70vw;
			border-radius: 30rpx;

			.popHeader {
				display: flex;
				justify-content: space-between;
				align-items: center;

				.title {
					color: #666;
					font-size: 26rpx;
				}

				.close {
					padding: 6rpx;
				}
			}

			.content {
				padding: 30rpx 0;
				display: flex;
				justify-content: center;
				align-items: center;

				.text {
					color: #FFCA3E;
					padding-left: 10rpx;
					width: 80rpx;
					line-height: 1em;
					text-align: right;
					font-size: 28rpx;
				}
			}

			.footer {
				padding: 10rpx 0;
				display: flex;
				align-items: center;
				justify-content: center;
			}
		}
	}
</style>