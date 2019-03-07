Blockly.JavaScript['neopixel_init'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var number_len = block.getFieldValue('len');
	var code = 'DEV_IO.WS2812().init(' + dropdown_pin + ', ' + number_len + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_set_pixel'] = function(block) {
	var value_n = Blockly.JavaScript.valueToCode(block, 'n', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var colour_hex = block.getFieldValue('hex').replace('#', '0x');
	var code = 'DEV_IO.WS2812().setPixel(' + value_n + ', ' + colour_hex + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_show'] = function(block) {
	var code = 'DEV_IO.WS2812().show();\n';
	return code;
};

Blockly.JavaScript['neopixel_clear'] = function(block) {
	var code = 'DEV_IO.WS2812().clear();\n';
	return code;
};
