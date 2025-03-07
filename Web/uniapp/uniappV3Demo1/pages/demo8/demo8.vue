<template>
  <view class="out">
    <input type="text" :value="iptValue" @focus="isActive=true" @blur="isActive=false"
	v-model="iptValue"/>
	<image src="/static/chicken.gif" mode="" class="pic"
	:class="isActive?'active':''"></image>
  </view>
  <view>预览:{{iptValue}}</view>
</template>

<script setup>
import { ref } from "vue";
const iptValue = ref("");
const isActive = ref(false);

// function onFocus(e) {
//   console.log("Focused:", e);
// }
// function onBlur(e) {
//   console.log("Blurred:", e);
// }
</script>

<style lang="scss" scoped>
.out{
	padding: 0 20px;
	margin-top: 40px;
	input{
		border: 1px solid #ccc;
		height: 40px;
		position: relative;
		z-index: 2;
		background: #fff;
	}
	.pic{
		width: 24px;
		height: 24px;
		z-index: 1;
		position: absolute;
		top: 0px;
		left: calc(50% - 12px);
		transition: 0.3s;
	}
	.pic.active{
		top: -24px;
	}
}
</style>
