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
#define CYCLES_400_T0H  (F_CPU / 2000000) // 0.5uS
#define CYCLES_400_T1H  (F_CPU /  833333) // 1.2us
#define CYCLES_400      (F_CPU /  400000) // 2.5us per bit
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
	
	colorBlock = (Color888**)malloc(length * sizeof(Color888));
	for (int i=0;i<length;i++)
		colorBlock[i] = (Color888*)malloc(sizeof(Color888));
	
	this->clear();
	
}

void WS2812::setPixel(int n, uint32_t color) {
	this->setPixel(n, (color>>16)&0xFF, (color>>8)&0xFF, color&0xFF);
}

void WS2812::setPixel(int n, uint8_t r, uint8_t g, uint8_t b) {
	if (n >= length) return;
	
	colorBlock[n]->r = r;
	colorBlock[n]->g = g;
	colorBlock[n]->b = b;
}

void WS2812::show() {
	vTaskSuspendAll();
	for (int i=0;i<length;i++) {
		this->espShow(this->pin, (uint8_t*)colorBlock[i], 3);
	}
	xTaskResumeAll();
}

void WS2812::clear() {
	for (int i=0;i<length;i++) {
		colorBlock[i]->r = 0;
		colorBlock[i]->g = 0;
		colorBlock[i]->b = 0;
	}
	
	this->show();
}

#endif
