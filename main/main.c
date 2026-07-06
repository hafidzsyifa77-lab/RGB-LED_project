#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h" 
#include "esp_log.h"
#include "driver/ledc.h"
#include "driver/adc.h"

#define ADC_PIN    ADC1_CHANNEL_0 // GPIO 36
#define PIN_R      21
#define PIN_G      22
#define PIN_B      23

// Fungsi untuk memetakan nilai (map)
int map_value(int x, int in_min, int in_max, int out_min, int out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup_ledc(int pin, ledc_channel_t channel) {
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE, .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = LEDC_TIMER_0, .freq_hz = 5000, .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);
    ledc_channel_config_t ledc_channel = {
        .channel = channel, .duty = 0, .gpio_num = pin,
        .speed_mode = LEDC_LOW_SPEED_MODE, .timer_sel = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);
}

void app_main() {
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC_PIN, ADC_ATTEN_DB_12);
    setup_ledc(PIN_R, LEDC_CHANNEL_0);
    setup_ledc(PIN_G, LEDC_CHANNEL_1);
    setup_ledc(PIN_B, LEDC_CHANNEL_2);

    while (1) {
        int val = adc1_get_raw(ADC_PIN); // 0 - 4095
        int r, g, b;

        if (val < 1365) { 
            // 0-1365: Merah memudar, Hijau naik
            r = map_value(val, 0, 1365, 255, 0);
            g = map_value(val, 0, 1365, 0, 255);
            b = 0;
        } else if (val < 2730) { 
            // 1365-2730: Hijau memudar, Biru naik
            r = 0;
            g = map_value(val, 1365, 2730, 255, 0);
            b = map_value(val, 1365, 2730, 0, 255);
        } else { 
            // 2730-4095: Biru memudar, Merah naik
            r = map_value(val, 2730, 4095, 0, 255);
            g = 0;
            b = map_value(val, 2730, 4095, 255, 0);
            
        }
        printf("ADC: %d \t R: %d \t G: %d \t B: %d\n", val, r, g, b);

        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, r);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, g);
        ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2, b);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1);
        ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_2);
        
        vTaskDelay(pdMS_TO_TICKS(100)); // Delay singkat untuk responsif
    }
}