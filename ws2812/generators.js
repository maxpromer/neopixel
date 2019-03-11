Blockly.JavaScript['neopixel_init'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var number_len = block.getFieldValue('len');
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').init(' + number_len + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_set_pixel'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_n = Blockly.JavaScript.valueToCode(block, 'n', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var colour_hex = block.getFieldValue('hex').replace('#', '0x');
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').setPixel(' + value_n + ', ' + colour_hex + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_show'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').show();\n';
	return code;
};

Blockly.JavaScript['neopixel_clear'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').clear();\n';
	return code;
};
