#ifndef __WS2812_H__
#define __WS2812_H__

#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_intr_alloc.h"
#include "esp_log.h"
#include "kidbright32.h"
#include "driver.h"
#include "device.h"

typedef struct {
	uint8_t g;
	uint8_t r;
	uint8_t b;
} Color888;

class WS2812 : public Device {
	private:
		Color888 **colorBlock;
		
		int pin, length;
		
		void espShow(uint8_t pin, uint8_t *pixels, uint32_t numBytes) ;

	public:
		// constructor
		WS2812();
		
		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);
		
		// method
		void init(int pin, int length) ;
		void setPixel(int n, uint32_t color) ;
		void setPixel(int n, uint8_t r, uint8_t g, uint8_t b) ;
		void show() ;
		void clear() ;
		
};

#endif
