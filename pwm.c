/*
 * ATENÇÃO: Este código pode ser utilizado para controlar um servomotor ou um LED no GPIO 12.
 * Se for rodar em um Raspberry Pi Pico real, NÃO conecte o servomotor diretamente ao GPIO 22 
 * sem um circuito de interface adequado, pois isso pode danificar a placa.
 * Para testes seguros, utilize a simulação no Wokwi ou ative o modo LED descomentando #define USE_LED.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

// -------------------------------------------------------------
// ATENÇÃO: Se estiver usando hardware real, ative o modo LED descomentando a linha abaixo 
// para evitar danos ao Raspberry Pi Pico. 
//
// Configuração para alternar entre o motor (GPIO 22) e o LED (GPIO 12).
// -> COMENTE a linha abaixo para ativar o modo MOTOR (GPIO 22).
// -> DESCOMENTE a linha abaixo para ativar o modo LED (GPIO 12), recomendável para testes seguros.
// -------------------------------------------------------------

//#define USE_LED // Descomente para usar o LED (GPIO12) e Comente para ativar o motor (GPIO22)

#ifdef USE_LED
#define PWM_PIN 12      // Pino do LED
#else
#define PWM_PIN 22       // Pino do motor no simulador
#endif

// Valores de duty cycle em microssegundos conforme especificação
#define DUTY_CYCLE_0   500   // 0 graus (2.5%)
#define DUTY_CYCLE_90  1470  // 90 graus (7.35%)
#define DUTY_CYCLE_180 2400  // 180 graus (12%)

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