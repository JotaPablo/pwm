#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Configuração para alternar entre motor e LED
#define USE_LED // Descomente para usar o LED na BitDogLab (GPIO12)

#ifdef USE_LED
#define PWM_PIN 12      // Pino do LED
#else
#define PWM_PIN 22       // Pino do motor no simulador
#endif

// Valores de duty cycle em microssegundos conforme especificação
#define DUTY_CYCLE_0   500   // 0 graus (0.025%)
#define DUTY_CYCLE_90  1470  // 90 graus (0.0735%)
#define DUTY_CYCLE_180 2400  // 180 graus (0.12%)

// Parâmetros de controle
#define WRAP_PERIOD 20000 // 20ms para 50Hz
#define PWM_DIVISER 125.0 // Ajustado para 50Hz
#define STEP 5      // Incremento de pulso (μs)

void pwm_setup() {
    gpio_set_function(PWM_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(PWM_PIN);
    pwm_set_clkdiv(slice, PWM_DIVISER); // Divisor para 50Hz (20000 ciclos)
    pwm_set_wrap(slice, WRAP_PERIOD);
    pwm_set_enabled(slice, true);
}

void set_servo_position(uint16_t pulse_width) {

    pwm_set_gpio_level(PWM_PIN, pulse_width);
}



int main() {
    stdio_init_all();
    pwm_setup();

    // Executa a sequência inicial
    pwm_set_gpio_level(PWM_PIN, DUTY_CYCLE_180);
    sleep_ms(5000);
    pwm_set_gpio_level(PWM_PIN, DUTY_CYCLE_90);
    sleep_ms(5000);
    pwm_set_gpio_level(PWM_PIN, DUTY_CYCLE_0);
    sleep_ms(5000);

    // Variáveis para movimento contínuo
    uint16_t duty_nivel = DUTY_CYCLE_0;
    bool up = true;

    // Loop de movimento contínuo
    while(true) {
        pwm_set_gpio_level(PWM_PIN, duty_nivel);

        sleep_ms(10);

        if(up) {
            duty_nivel += STEP;
            if(duty_nivel >= DUTY_CYCLE_180) up = false;
        } else {
            duty_nivel -= STEP;
            if(duty_nivel <= DUTY_CYCLE_0) up  = true;
        }
    }
}