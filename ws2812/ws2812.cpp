#ifndef __WS2812_CPP__
#define __WS2812_CPP__

#include "ws2812.h"

static uint32_t _getCycleCount(void) __attribute__((always_inline));
static inline uint32_t _getCycleCount(void) {
  uint32_t ccount;
  __asm__ __volatile__("rsr %0,ccount":"=a" (ccount));
  return ccount;
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

// Code from Adafruit : https://github.com/adafruit/Adafruit_NeoPixel Thank you so much !
#define F_CPU 240000000L
#define CYCLES_800_T0H  (F_CPU / 2500000) // 0.4us
#define CYCLES_800_T1H  (F_CPU / 1250000) // 0.8us
#define CYCLES_800      (F_CPU /  800000) // 1.25us per bit

void WS2812::espShow(uint8_t pin, uint8_t *pixels, uint32_t numBytes) {
	uint8_t *p, *end, pix, mask;
	uint32_t t, time0, time1, period, c, startTime;

	p         =  pixels;
	end       =  p + numBytes;
	pix       = *p++;
	mask      = 0x80;
	startTime = 0;
	
	time0  = CYCLES_800_T0H;
	time1  = CYCLES_800_T1H;
	period = CYCLES_800;

	for(t = time0;; t = time0) {
		if(pix & mask) t = time1;                             // Bit high duration
		while(((c = _getCycleCount()) - startTime) < period); // Wait for bit start

		// gpio_set_level(pin, 1);
		gpio_set_level((gpio_num_t)pin, 0);

		startTime = c;                                        // Save start time
		while(((c = _getCycleCount()) - startTime) < t);      // Wait high duration

		// gpio_set_level(pin, 0);
		gpio_set_level((gpio_num_t)pin, 1);

		if(!(mask >>= 1)) {                                   // Next bit/byte
			if(p >= end) break;
			pix  = *p++;
			mask = 0x80;
		}
	}
	while((_getCycleCount() - startTime) < period); // Wait for last bit
}

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
    config.channel = RMT_TX_CHANNEL;
    config.gpio_num = RMT_TX_GPIO;
    config.mem_block_num = 3;
    config.tx_config.loop_en = 0;
	
	
    config.tx_config.idle_output_en = 1;
    config.tx_config.idle_level = 1;
	
	config.tx_config.carrier_en = 0;
    config.tx_config.carrier_duty_percent = 0;
    config.tx_config.carrier_freq_hz = 0;
    config.tx_config.carrier_level = 0;
	
	// ABP use 80MHz and NeoPixel use 800kHz so 80MHz / 100 = 800kHz
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
	
}

void WS2812::clear() {
	memset(this->colorBlock, 0, this->length * 3);
	
	this->show();
}

#endif
