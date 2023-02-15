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
*/

#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define PIN 4

void app_main(void)
{
    gpio_pad_select_gpio(PIN);
    gpio_set_direction(PIN, GPIO_MODE_OUTPUT);

    int estado = 0;
    
    gpio_set_level(PIN, estado);
    
}