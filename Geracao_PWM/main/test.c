/*
Sleep.c
 *
 *  Created on: Fev 17, 2023
 *  Copyright Owner 2023 <Stephanie Cardoso Guimarães> 
 *      Author: steph
 */

/*
 * Disciplina: Tópicos de Engenharia Mecatrônica
 * Professor: Jones
 * Aluna: Stephanie Cardoso Guimarães
 * 
 * Trabalho 4
 */
// ========================================================================================

/*
	Exemplo light-sleep.
	Primeira versao.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"
/*
* O código original contém um erro. Na linha 51, a variável "fim" é atribuida
* o valor de "esp_timer_get_time()", mas na linha 53, a expressão "(depois - antes)/1000"
* tenta calcular a diferença de tempo subtraindo "antes" de "depois", que não são variáveis
* definidas. A expressão correta seria "(fim - inicio)/1000". 
*
* A versão corrigida esta comentada logo abaixo do código original.
*/

void app_main()
{
    esp_sleep_enable_timer_wakeup(5000000); // configura o timer

    printf("Iniciando modo sleep... \n"); // mensagem informativa

    int64_t inicio = esp_timer_get_time(); // time stamp 1

    esp_light_sleep_start(); // iniciando modo sleep

    int64_t fim = esp_timer_get_time(); // time stamp 2

    printf("Modo sleep durou %lld milisegundos.\n", (depois - antes) / 1000);
}

/*
void app_main()
{
    esp_sleep_enable_timer_wakeup(5000000); // configura o timer

    printf("Iniciando modo sleep... \n"); // mensagem informativa

    int64_t inicio = esp_timer_get_time(); // time stamp 1

    esp_light_sleep_start(); // iniciando modo sleep

    int64_t fim = esp_timer_get_time(); // time stamp 2

    printf("Modo sleep durou %lld milisegundos.\n", (fim - inicio)/1000);
}
*/