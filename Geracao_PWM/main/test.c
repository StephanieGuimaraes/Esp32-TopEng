/*
intro_tasks.c
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
 * Trabalho 3
 */
// ========================================================================================

/*
    Este código mostra a criação de duas Tasks simples, sem parâmetros.
    Cada Task tem um contador e imprime seu valor a cada chamada.
    1 - Teste o código e verifique seu funcionamento.
    2 - Modifique o delay interno de uma das Tasks (de 1000 para 2000, por exemplo)
        e explique o que ocorre.
    3 - Utilizando a função esp_timer_get_time (vista em exemplos anteriores) e 
        com informações da documentação ESP32/FreeRTOS, modifique prioridades das
        Tasks e mostre seu funcionamento.
*/
/*
* 1 - Primeiro o delay interno aumentou o tempo que leva para executar novamente a * função. Basicamente mudou o tempo de escalonamento das tarefas.
* 2 - Quando a tarefa com a maior prioridade começa e o atraso é aplicado, o * microcontrolador não executará nenhuma tarefa. Em vez disso, ele dará prioridade * à próxima tarefa. Em outras palavras, o tempo total necessário será a soma do * tempo de execução da tarefa atual, o tempoo de atraso e a execução da próxima * tarefa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void task1(void * params) {
    int cont1 = 0;
    while (true) {
        int64_t begin = esp_timer_get_time();  // time stamp 1
        printf("Task1 -> %d \n", cont1);
        cont1++;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        int64_t end = esp_timer_get_time();  // time stamp 1
        int64_t temp = (end - begin) / 1000;
        Serial.print("tempo = ");
        Serial.println(temp);
    }
}

void task2(void * params) {
    int cont2 = 0;
    while (true) {
        int64_t begin = esp_timer_get_time();  // time stamp 1
        printf("Task2 -> %d \n", cont2);
        cont2++;
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        int64_t end = esp_timer_get_time();  // time stamp 1
        int64_t temp = (end - begin) / 1000;
        Serial.print("tempo = ");
        Serial.println(temp);
    }
}

void app_main(void) {
    xTaskCreate(
        &task1,     // Ponteiro para a função que implementa a Task
        "cont1",   // Nome da Task
        2048,       // Stack depth - ver documentação
        NULL,       // Parâmetro para a task, neste exemplo sem parâmetros
        1,          // Prioridade da Task
        NULL        // Task handle - ver documentação
    );
    xTaskCreate(&task2, "cont2", 2048, NULL, 2, NULL);
}
