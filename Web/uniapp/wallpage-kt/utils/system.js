let SYSTEM_INFO = uni.getSystemInfoSync();
export const getstatusBarHeight = ()=>SYSTEM_INFO.statusBarHeight || 0;

export const getTitleBarHeight = ()=>{
	if(uni.getMenuButtonBoundingClientRect){
		 let {top,height} = uni.getMenuButtonBoundingClientRect();
		 return  height + (top - getstatusBarHeight())*2
	}else{
		return 40
	}
}

export const getNavBarHeight = ()=>getstatusBarHeight() + getTitleBarHeight()