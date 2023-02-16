
/*
 * GeraçãoPWM.c
 *
 *  Created on: Fev 16, 2023
 *  Copyright Owner 2023 <Stephanie Cardoso Guimarães> 
 *      Author: steph
 */

/*
 * Disciplina: Tópicos de Engenharia Mecatrônica
 * Professor: Jones
 * Aluna: Stephanie Cardoso Guimarães
 * 
 * Trabalho 1: Geração de PWM
 * Objetivo deste arquivo é gerar um sinal PWM capaz de variar a intensidade da luminosidade de um LED 
 * durante determinado intervalo de tempo.
 * Para seu funcionamento são necessários um board esp32, um resistor, um LED, cabo USB e jumpers.
 */
// ========================================================================================

/*
	1 - Teste este programa.
	2 - Modifique o código para piscar um led 
	externo a cada 1 segundo.
	3 - Crie uma função de PWM, para variar
	a intensidade do brilho, aumentando e diminuindo
	de forma suave. 
	4 - Busque na documentação como utilizar pinos 
	digitais como entradas. Crie uma variável que conta
	quantas vezes a entrada foi acionada, imprimindo
	na tela cada incremento desse contador.



#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIN 4

void app_main(void)
{
    esp_rom_gpio_pad_select_gpio(PIN);
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);

    int estado = 0;
		
    gpio_set_level(PIN, estado);
}
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/ledc.h"
#include "esp_err.h"

#define PIN 4
#define FADE_TIME 2000
#define MAX_RESOLUTION 1023  //  Resolução para o sinal PWM

void app_main(void) {
  int delay_time = FADE_TIME;
  //  trutura do timer que altera a frequência e dutcycle do PWM
  ledc_timer_config_t ledc_timer = {
      .duty_resolution = LEDC_TIMER_10_BIT,
        .freq_hz = 5000,
      .speed_mode = LEDC_HIGH_SPEED_MODE,
      .timer_num = LEDC_TIMER_0,
      .clk_cfg = LEDC_AUTO_CLK,
  };

  //  configurações do timer
  ledc_timer_config(&ledc_timer);

  // Relacao entre o timer com o canal de GPIO para gerar o PWM
  ledc_channel_config_t ledc_channel = {
      .channel = LEDC_CHANNEL_0,
      .duty = 0,
      .gpio_num = PIN,
      .speed_mode = LEDC_HIGH_SPEED_MODE,
      .hpoint = 0,
      .timer_sel = LEDC_TIMER_0,
      .flags.output_invert = 0
    };

  // Uso de fading para transicionar entre dutycycles
  ledc_fade_func_install(0);
  // Configurações do canal
  ledc_channel_config(&ledc_channel);

  while (true) {
    ledc_set_fade_with_time(ledc_channel.speed_mode,
                            ledc_channel.channel, MAX_RESOLUTION, FADE_TIME);
    ledc_fade_start(ledc_channel.speed_mode,
                    ledc_channel.channel, LEDC_FADE_NO_WAIT);
    vTaskDelay(delay_time / portTICK_PERIOD_MS);
    ledc_set_fade_with_time(ledc_channel.speed_mode,
                            ledc_channel.channel, 0, FADE_TIME);
    ledc_fade_start(ledc_channel.speed_mode,
                    ledc_channel.channel, LEDC_FADE_NO_WAIT);
    vTaskDelay(delay_time / portTICK_PERIOD_MS);
  }
}
