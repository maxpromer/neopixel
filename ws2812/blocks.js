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

Blockly.Blocks["neopixel_set_pixel"] = {
	init: function() {
		this.jsonInit({
			"type": "",
			"message0": "NeoPixel set pixel  %1 color %2",
			"args0": [{
				"type": "input_value",
				"name": "n"
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

Blockly.Blocks["neopixel_show"] = {
	init: function() {
		this.jsonInit({
			"type": "",
			"message0": "NeoPixel show",
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
			"message0": "NeoPixel clear",
			"inputsInline": true,
			"previousStatement": null,
			"nextStatement": null,
			"colour": 75,
			"tooltip": "",
			"helpUrl": ""
		});
	}
};


