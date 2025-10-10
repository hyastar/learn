/**
 * HEX字符串转ArrayBuffer
 */
export function hexStringToArrayBuffer(hexStr) {
	let str = hexStr.replace(/\s+/g, '');
	if (str.length % 2 !== 0) throw new Error('HEX字符串长度必须为偶数');
	let buffer = new ArrayBuffer(str.length / 2);
	let dataView = new DataView(buffer);
	for (let i = 0; i < str.length; i += 2) {
		const byte = parseInt(str.substring(i, i + 2), 16);
		if (isNaN(byte)) throw new Error('包含无效的HEX字符');
		dataView.setUint8(i / 2, byte);
	}
	return buffer;
}

/**
 * UTF-8字符串转ArrayBuffer
 */
export function utf8StringToArrayBuffer(str) {
	let buffer = [];
	for (let i = 0; i < str.length; i++) {
		let charcode = str.charCodeAt(i);
		if (charcode < 0x80) buffer.push(charcode);
		else if (charcode < 0x800) {
			buffer.push(0xc0 | (charcode >> 6), 0x80 | (charcode & 0x3f));
		} else if (charcode < 0xd800 || charcode >= 0xe000) {
			buffer.push(0xe0 | (charcode >> 12), 0x80 | ((charcode >> 6) & 0x3f), 0x80 | (charcode & 0x3f));
		}
	}
	return new Uint8Array(buffer).buffer;
}

/**
 * ASCII字符串转ArrayBuffer
 */
export function asciiStringToArrayBuffer(str) {
	for(let i = 0; i < str.length; i++) {
		if(str.charCodeAt(i) > 127) throw new Error("包含非ASCII字符");
	}
	return utf8StringToArrayBuffer(str); 
}

/**
 * ArrayBuffer转HEX字符串
 */
export function arrayBufferToHexString(buffer) {
	if (!buffer) return '无';
	return Array.prototype.map.call(new Uint8Array(buffer), x => ('00' + x.toString(16)).slice(-2)).join(' ').toUpperCase();
}

/**
 * ArrayBuffer转UTF-8字符串
 */
export function arrayBufferToUtf8String(buffer) {
	if (!buffer) return '';
	let out = "";
	let i = 0;
	const bytes = new Uint8Array(buffer);
	while (i < bytes.length) {
		let c = bytes[i++];
		if (c > 127) {
			if (c > 191 && c < 224) {
				if (i >= bytes.length) break;
				c = ((c & 31) << 6) | (bytes[i++] & 63);
			} else {
				if (i + 1 >= bytes.length) break;
				c = ((c & 15) << 12) | (((bytes[i++]) & 63) << 6) | ((bytes[i++]) & 63);
			}
		}
		out += String.fromCharCode(c);
	}
	return out;
}

/**
 * ArrayBuffer转ASCII字符串
 */
export function arrayBufferToAsciiString(buffer) {
    if (!buffer) return '';
    return String.fromCharCode.apply(null, new Uint8Array(buffer));
}
