<template>
	<view class="out">
		<input type="text" v-model="firstName" placeholder="请输入名"/>
		<input type="text" v-model="lastName" placeholder="请输入姓"/>
		
		<view>全称：{{fullName()}}</view>
		<view>全称：{{fullName()}}</view>
		<view>全称：{{fullName()}}</view>
	</view>
</template>

<script setup>
import {ref, computed} from "vue";
const firstName = ref("");
const lastName = ref("");

const fullName = function(){
	console.log("方法");
	return firstName.value + "-" + lastName.value;
}
</script>

<style lang="scss" scoped>

</style>
