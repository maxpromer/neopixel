/* RMT transmit example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"

static const char *RMT_TX_TAG = "RMT Tx";

#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define RMT_TX_GPIO 26

//Convert uint8_t type of data to rmt format data.
static void IRAM_ATTR u8_to_rmt(const void* src, rmt_item32_t* dest, size_t src_size, 
                         size_t wanted_num, size_t* translated_size, size_t* item_num)
{
    if(src == NULL || dest == NULL) {
        *translated_size = 0;
        *item_num = 0;
        return;
    }
    // const rmt_item32_t bit0 = {{{ 32767, 1, 15000, 0 }}}; //Logical 0
    // const rmt_item32_t bit1 = {{{ 32767, 1, 32767, 0 }}}; //Logical 1
	
	const rmt_item32_t bit0 = {{{ 28, 1, 72, 0 }}};  //Logical 0
    const rmt_item32_t bit1 = {{{ 56, 1, 44, 0 }}}; //Logical 1
	
    size_t size = 0;
    size_t num = 0;
    uint8_t *psrc = (uint8_t *)src;
    rmt_item32_t* pdest = dest;
    while (size < src_size && num < wanted_num) {
        for(int i = 0; i < 8; i++) {
            if(*psrc & (0x1 << i)) {
                // pdest->val =  bit1.val;
				pdest->val =  bit0.val; 
            } else {
                // pdest->val =  bit0.val;
				pdest->val =  bit1.val;
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

/*
 * Initialize the RMT Tx channel
 */
static void rmt_tx_int()
{
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
}

uint8_t color[3 * 12];

void writeNeoPixel(int n, uint8_t r, uint8_t g, uint8_t b) {
	int inx = n * 3;
	color[inx + 0] = g;
	color[inx + 1] = r;
	color[inx + 2] = b;
}

void show() {
	ESP_ERROR_CHECK(rmt_write_sample(RMT_TX_CHANNEL, color, sizeof color, true));
    // ESP_LOGI(RMT_TX_TAG, "Sample transmission complete");
}

void app_main(void *ignore)
{
    ESP_LOGI(RMT_TX_TAG, "Configuring transmitter");
    rmt_tx_int();

    while (1) {
		writeNeoPixel(0, 255, 0, 0);
		show();
        vTaskDelay(300 / portTICK_PERIOD_MS);
		writeNeoPixel(1, 0, 255, 0);
		show();
		vTaskDelay(300 / portTICK_PERIOD_MS);
		writeNeoPixel(2, 0, 0, 255);
		show();
		vTaskDelay(300 / portTICK_PERIOD_MS);
		memset(color, 0, sizeof color);
		show();
		vTaskDelay(300 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
