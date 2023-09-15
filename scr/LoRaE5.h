/* DATA: 08/2023
 * AUTOR: Caio Teraoka de Menezes Câmara
 * VERSÃO 1.0
 * DESCRIÇÃO: Biblioteca desenvolvida para facilitar o uso dos comandos AT em projetos utilizando o módulo LoRa WIO-E5
 * REQUISITOS de HARDWARE: Módulo WIO-E5, Microcontrolador com comunicação serial
 * REQUISITOS DE SOFTWARE: CubeIDE
 */

#ifndef LORA_E5_H
#define LORA_E5_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stm32f4xx_hal.h>


struct ID{
    char DevAddr[12];
    char DevEui[24];
    char AppEui[24];
};

void E5_init(UART_HandleTypeDef uart);
struct ID *get_ID();
char *get_DevAddr();
char *get_DevEui();
char *get_AppEui();
char *get_Band();
int set_DevAddr(char *DevAddr);
int set_DevEui(char *DevEui);
int set_AppEui(char *AppEui);
int set_Band(char *Band);
int set_Mode(char *Mode);
int send_String(char *String);
int send_Hex(char *Hex);
int lora_Join();

#endif
