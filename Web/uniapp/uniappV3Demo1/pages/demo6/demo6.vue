<template>
    <view class="out">
        <view class="box" v-for="(item, index) in 10">box模块-{{index+1}}</view>
		
		<view v-for="item in nba" :key="item.id">
			球星:{{item.name}} - 球衣:{{ item.num }}
		</view>
    </view>
</template>

<script setup>
import { ref } from "vue";
const nba = ref([
	{name: "乔丹", num: 23},
	{name: "詹姆斯", num: 6},
	{name: "科比", num: 24}
]); 
</script>

<style lang="scss" scoped>
.out {
    display: flex;
    flex-wrap: wrap;
}
.box {
    width: 100px;
    height: 100px;
    background: orange;
    margin: 5px;
    display: flex;
    align-items: center;
    justify-content: center;
    font-size: 20px;
    color: white;
}
</style> 
