<template>
	<view class="">
		<view v-if="shop">京东</view>
		<view v-else>淘宝网</view>
		
		<view v-if="day==1">星期一</view>
		<view v-else-if="day == 2">星期二</view>
		<view v-else-if="day == 3">星期三</view>
		<view v-else-if="day == 4">星期四</view>
		<view v-else-if="day == 5">星期五</view>
		<view v-else-if="day == 6">星期六</view>
		<view v-else-if="day == 7">星期日</view>
		<view v-else>格式错误</view>
		
		
	</view>
</template>

<script setup>
import {ref} from "vue";
const shop = ref(true);
const day = ref(3);
</script>

<style lang="scss" scoped>

</style>
