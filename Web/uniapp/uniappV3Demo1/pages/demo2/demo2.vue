<template>
	<view>{{ num1 }}</view>
	<view>{{ num2 }}</view>
	<view>{{ test }}</view>
	<view>{{ arr }}</view>
	<view>{{ obj }}</view>
</template>

<script setup>
import {ref} from "vue";

let num1 = 6;
// setInterval(()=>{
// 	num1++;
// 	console.log(num1);
// }, 1000)

let num2 = ref(10);
console.log(num1);
console.log(num2.value);
setInterval(()=>{
	num2.value++;
	console.log(num2.value);
}, 10000)

let test = ref("100");

let arr = ref([1, 2, 3, 4]);

let obj = ref({name:"王五", age: 18})
obj.value.name = "李四";


</script>

<style>
	       
</style>
