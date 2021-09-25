#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

#define LED_PIN 25
#define HUMIDITY_SENSOR_PIN 26
#define PUMP_PIN 21
#define PUMP_ON_MS 2000 // 2 Sekunden
#define SLEEP_MS 3000000 // 15 Minuten
#define HUMIDITY_THRESHOLD 2500

int main() {
    gpio_init(PUMP_PIN);
    gpio_set_dir(PUMP_PIN, GPIO_OUT);
    gpio_put(PUMP_PIN, true);

    // Initialize chosen serial port
    stdio_init_all();

    adc_init();
    adc_gpio_init(HUMIDITY_SENSOR_PIN);
    adc_select_input(0);

    // Loop forever
    while (true) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        const float conversion_factor = 3.3f / (1 << 12);
        uint16_t result = adc_read();
        printf("Raw hex value: 0x%03x, raw decimal value %d, voltage: %f V\n", result, result, result * conversion_factor);
        if (result > HUMIDITY_THRESHOLD){
            printf("Pump ON\n");
            //gpio_put(LED_PIN, true);
            gpio_put(PUMP_PIN, false);
            sleep_ms(PUMP_ON_MS);
            printf("Pump OFF\n");
            //gpio_put(LED_PIN, false);
            gpio_put(PUMP_PIN, true);
        }
        sleep_ms(SLEEP_MS);
    }
}