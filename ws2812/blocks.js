Blockly.Blocks["neopixel_init"] = {
	init: function() {
		this.jsonInit({
			"message0": "NeoPixel initialize pin %1 length %2",
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "18", "18" ],
					[ "19", "19" ], 
					[ "23", "23" ]
				]
			}, {
				"type": "field_number",
				"name": "len",
				"value": 0,
				"min": 0,
				"precision": 1
			}],
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};

Blockly.Blocks["neopixel_set_brightness"] = {
	init: function() {
		this.jsonInit({
			"message0": "NeoPixel pin %1 set brightness %2",
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "18", "18" ],
					[ "19", "19" ], 
					[ "23", "23" ]
				]
			}, {
				"type": "input_value",
				"name": "brightness",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};

Blockly.Blocks["neopixel_set_pixel"] = {
	init: function() {
		this.jsonInit({
			"message0": "NeoPixel pin %1 set pixel %2 color %3",
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "18", "18" ],
					[ "19", "19" ], 
					[ "23", "23" ]
				]
			}, {
				"type": "input_value",
				"name": "n",
				"check": "Number"
			}, {
				"type": "field_colour",
				"name": "hex",
				"colour": "#ff0000"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};

Blockly.Blocks["neopixel_set_pixel_rgb"] = {
	init: function() {
		this.jsonInit({
			"message0": "NeoPixel pin %1 set pixel %2 color rgb( %3 , %4 , %5 )",
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "18", "18" ],
					[ "19", "19" ], 
					[ "23", "23" ]
				]
			}, {
				"type": "input_value",
				"name": "n",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "red",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "green",
				"check": "Number"
			}, {
				"type": "input_value",
				"name": "blue",
				"check": "Number"
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};

Blockly.Blocks["neopixel_show"] = {
	init: function() {
		this.jsonInit({
			"message0": "NeoPixel pin %1 show",
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "18", "18" ],
					[ "19", "19" ], 
					[ "23", "23" ]
				]
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};

Blockly.Blocks["neopixel_clear"] = {
	init: function() {
		this.jsonInit({
			"message0": "NeoPixel pin %1 clear",
			"args0": [{
				"type": "field_dropdown",
				"name": "pin",
				"options": [
					[ "OUT1", "26" ],
					[ "OUT2", "27" ],
					[ "18", "18" ],
					[ "19", "19" ], 
					[ "23", "23" ]
				]
			}],
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};


