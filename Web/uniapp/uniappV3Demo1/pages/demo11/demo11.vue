<template>
	<view class="out">
		<input type="text" v-model="firstName" placeholder="请输入名"/>
		<input type="text" v-model="lastName" placeholder="请输入姓"/>
		
		<view>全称：{{fullName}}</view>
	</view>
</template>

<script setup>
import {ref, watch, watchEffect} from "vue";
const firstName = ref("迈克尔");
const lastName = ref("乔丹");

const fullName = ref("")

// watch([firstName, lastName], ([NfirstName, NlastName],[ofirstName, OlastName])=>{
// 	console.log(NfirstName,NlastName);
// })
watchEffect(()=>{
	console.log(firstName.value, lastName.value);
})

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
