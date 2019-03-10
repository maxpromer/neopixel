#ifndef __WS2812_CPP__
#define __WS2812_CPP__

#include "ws2812.h"

static void IRAM_ATTR u8_to_rmt(const void* src, rmt_item32_t* dest, size_t src_size, size_t wanted_num, size_t* translated_size, size_t* item_num) {
	if(src == NULL || dest == NULL) {
		*translated_size = 0;
		*item_num = 0;
		return;
	}
    
	/*
	const rmt_item32_t bit0 = {{{ 28, 1, 72, 0 }}};  //Logical 0
	const rmt_item32_t bit1 = {{{ 56, 1, 44, 0 }}};  //Logical 1
	*/
	const rmt_item32_t bit0 = {{{ 28, 0, 72, 1 }}};  //Logical 0
	const rmt_item32_t bit1 = {{{ 56, 0, 44, 1 }}};  //Logical 1
	
	size_t size = 0;
	size_t num = 0;
	uint8_t *psrc = (uint8_t *)src;
	rmt_item32_t* pdest = dest;
	while (size < src_size && num < wanted_num) {
		for(int i = 0; i < 8; i++) {
			if(*psrc & (0x1 << i)) {
				pdest->val =  bit1.val;
				// pdest->val =  bit0.val; 
			} else {
				pdest->val =  bit0.val;
				// pdest->val =  bit1.val;
			}
			num++;
			pdest++;
		}
		size++;
		psrc++;
	}
	*translated_size = size;
	*item_num = num;
}

WS2812::WS2812() { }

void WS2812::init(void) { 
	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
	
	esp_log_level_set("*", ESP_LOG_INFO); 
}

int WS2812::prop_count(void) {
	return 0;
}

bool WS2812::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool WS2812::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool WS2812::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool WS2812::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool WS2812::prop_write(int index, char *value) {
	// not supported
	return false;
}

void WS2812::process(Driver *drv) { }


void WS2812::init(int pin, int length) {
	this->pin = pin;
	this->length = length;
	
	gpio_pad_select_gpio((gpio_num_t)pin);
    gpio_set_direction((gpio_num_t)pin, GPIO_MODE_OUTPUT);
	
	if (this->colorBlock) {
		free(this->colorBlock);
	}
	
	this->colorBlock = (uint8_t*)malloc(length * 3);
	memset(this->colorBlock, 0, length * 3);
	
	// Set up RMT
	rmt_config_t config;
    config.rmt_mode = RMT_MODE_TX;
    config.channel = RMT_CHANNEL_7;
    config.gpio_num = (gpio_num_t)pin;
    config.mem_block_num = 1;
    config.tx_config.loop_en = 0;
	
    config.tx_config.idle_output_en = 1;
    config.tx_config.idle_level = RMT_IDLE_LEVEL_HIGH;
	
	config.tx_config.carrier_en = 0;
    config.tx_config.carrier_duty_percent = 0;
    config.tx_config.carrier_freq_hz = 0;
    config.tx_config.carrier_level = RMT_CARRIER_LEVEL_LOW;
	
	// ABP use 80MHz per 1 clock and 2 clock ABP for 1 clock RMT so clk_div = 1 is 40MHz
    config.clk_div = 1;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
    ESP_ERROR_CHECK(rmt_translator_init(config.channel, u8_to_rmt));
	ESP_ERROR_CHECK(rmt_set_source_clk(config.channel, RMT_BASECLK_APB)); // 80MHz
	
	this->clear();
}

void WS2812::setPixel(int n, uint32_t color) {
	this->setPixel(n, (color>>16)&0xFF, (color>>8)&0xFF, color&0xFF);
}

void WS2812::setPixel(int n, uint8_t r, uint8_t g, uint8_t b) {
	if (n >= this->length) return;
	
	int inx = n * 3;
	this->colorBlock[inx + 0] = g;
	this->colorBlock[inx + 1] = r;
	this->colorBlock[inx + 2] = b;
}

void WS2812::show() {
	ESP_ERROR_CHECK(rmt_write_sample(RMT_CHANNEL_7, colorBlock, length * 3, true));
	
	rmt_wait_tx_done(RMT_CHANNEL_7, portMAX_DELAY);
}

void WS2812::clear() {
	memset(this->colorBlock, 0, this->length * 3);
	
	this->show();
}

#endif
