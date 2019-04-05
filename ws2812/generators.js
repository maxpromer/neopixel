Blockly.JavaScript['neopixel_init'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var number_len = block.getFieldValue('len');
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').init(' + number_len + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_set_brightness'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_brightness = Blockly.JavaScript.valueToCode(block, 'brightness', Blockly.JavaScript.ORDER_ATOMIC);
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').setBrightness(' + value_brightness + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_set_pixel'] = function(block) {
	var dropdown_pin = block.getFieldValue('pin');
	var value_n = Blockly.JavaScript.valueToCode(block, 'n', Blockly.JavaScript.ORDER_ATOMIC) || '0';
	var colour_hex = block.getFieldValue('hex').replace('#', '0x');
	var code = 'DEV_IO.WS2812(' + dropdown_pin + ').setPixel(' + value_n + ', ' + colour_hex + ');\n';
	return code;
};

Blockly.JavaScript['neopixel_set_pixel_rgb'] = function(block) {
  var value_n = Blockly.JavaScript.valueToCode(block, 'n', Blockly.JavaScript.ORDER_ATOMIC);
  var value_red = Blockly.JavaScript.valueToCode(block, 'red', Blockly.JavaScript.ORDER_ATOMIC);
  var value_green = Blockly.JavaScript.valueToCode(block, 'green', Blockly.JavaScript.ORDER_ATOMIC);
  var value_blue = Blockly.JavaScript.valueToCode(block, 'blue', Blockly.JavaScript.ORDER_ATOMIC);
  var code = 'DEV_IO.WS2812(' + dropdown_pin + ').setPixel(' + value_n + ', ' + value_red + ', ' + value_green + ', ' + value_blue + ');\n';
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
