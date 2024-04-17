#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"

#define LED_GPIO_PIN_1 GPIO_NUM_25
#define LED_GPIO_PIN_2 GPIO_NUM_26
#define LED_GPIO_PIN_3 GPIO_NUM_17
#define LED_GPIO_PIN_4 GPIO_NUM_18


gpio_num_t led_pins[] = { LED_GPIO_PIN_1, LED_GPIO_PIN_2, LED_GPIO_PIN_3, LED_GPIO_PIN_4};





void set_gpios(void){
    gpio_set_direction(LED_GPIO_PIN_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_PIN_2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_PIN_3, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED_GPIO_PIN_4, GPIO_MODE_OUTPUT);
    printf("GPIO SET OUTPUT\n");
}



void leds_off(void){
    gpio_set_level(led_pins[0],0);
    gpio_set_level(led_pins[1],0);
    gpio_set_level(led_pins[2],0);
    gpio_set_level(led_pins[3],0);
}



void move_sequence() {
    int direction = 1; // 1 for forward, -1 for reverse
    int current_led = 0;

    while (1) {
        for (int i = 0; i < 4; i++) {
            leds_off();
            gpio_set_level(led_pins[current_led], 1);
            vTaskDelay(200 / portTICK_PERIOD_MS);
            current_led += direction;
            if (current_led == 0 || current_led == 3) {
                direction *= -1;
                //vTaskDelay(100 / portTICK_PERIOD_MS);
                 printf("forward and reverse done\n");
            }
        }
    }
}



void app_main(void) {
    printf("App main started\n\r");
    vTaskDelay(1500 / portTICK_PERIOD_MS);
    set_gpios();
    while(1) {
        move_sequence();
        //vTaskDelay(200 / portTICK_PERIOD_MS);
       
    }
    printf("app main complete\n");
}
