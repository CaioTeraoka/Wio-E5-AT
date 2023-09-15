/* DATA: 08/2023
 * AUTOR: Caio Teraoka de Menezes Câmara
 * VERSÃO 1.0
 * DESCRIÇÃO: Biblioteca desenvolvida para facilitar o uso dos comandos AT em projetos utilizando o módulo LoRa WIO-E5
 * REQUISITOS de HARDWARE: Módulo WIO-E5, Microcontrolador com comunicação serial
 * REQUISITOS DE SOFTWARE: CubeIDE
 */

#include "LoRaE5.h"

UART_HandleTypeDef huart;

void E5_init(UART_HandleTypeDef uart){
	huart = uart;
}

struct ID *get_ID(){
	char message[7] = "AT+ID\r\n";
	char Buffer[101] = {0};
    struct ID* id = (struct ID*)malloc(sizeof(struct ID));

    HAL_UART_Transmit(&huart, (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart, (uint8_t*)Buffer, sizeof(Buffer), 500);

    strncpy(id->DevAddr, &Buffer[14], 11);
    id->DevAddr[11] = '\0';
    strncpy(id->DevEui, &Buffer[40], 23);
    id->DevEui[23] = '\0';
    strncpy(id->AppEui, &Buffer[78], 23);
    id->AppEui[23] = '\0';

    return id;

}

char *get_DevAddr(){
	char message[15] = "AT+ID=DevAddr\r\n";
	char Buffer[26] = {0};
	char *Addr = (char *)malloc(sizeof(char)*12);

    HAL_UART_Transmit(&huart, (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart, (uint8_t*)Buffer, sizeof(Buffer), 300);

    strncpy(Addr, &Buffer[14], 11);
    Addr[11] = '\0';

    return Addr;
}

char *get_DevEui(){
    char message[15] = "AT+ID=DevEui\r\n";
    char Buffer[39] = {0};
    char *DevEui = (char *)malloc(sizeof(char)*24);

    HAL_UART_Transmit(&huart, (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart, (uint8_t*)Buffer, sizeof(Buffer), 300);

    strncpy(DevEui, &Buffer[13], 23);
    DevEui[23] = '\0';

    return DevEui;
}

char *get_AppEui(){
    char message[15] = "AT+ID=AppEui\r\n";
    char Buffer[39] = {0};
    char *AppEui = (char *)malloc(sizeof(char)*24);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    strncpy(AppEui, &Buffer[13], 23);
    AppEui[23] = '\0';

    return AppEui;
}

char *get_Band(){
    char message[7] = "AT+DR\r\n";
    char Buffer[36] = {0};
    char *Band = (char *)malloc(sizeof(char)*24);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    strncpy(Band, &Buffer[15], 23);
    Band[23] = '\0';

    return Band;
}

int set_DevAddr(char *DevAddr){
    char message[30];
    char Buffer[28];
    char erro[6] = "ERROR";

    sprintf(message, "AT+ID=DevAddr, \"%s\"\r\n", DevAddr);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, erro);
    if(resultado == NULL){
       	return 0;
    }
    else return -1;
}

int set_DevEui(char *DevEui){
    char message[41];
    char Buffer[39] = {0};
    char erro[6] = "ERROR";

    sprintf(message, "AT+ID=DevEui, \"%s\"\r\n", DevEui);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, erro);
    if(resultado == NULL){
       	return 0;
    }
    else return -1;
}

int set_AppEui(char *AppEui){
    char message[41] = {0};
    char Buffer[39] = {0};
    char erro[6] = "ERROR";

    sprintf(message, "AT+ID=AppEui, \"%s\"\r\n", AppEui);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, erro);
    if(resultado == NULL){
       	return 0;
    }
    else return -1;
}

int set_Band(char *Band){
    char message[13] = {0};
    char Buffer[15] = {0};
    char erro[6] = "ERROR";

    sprintf(message, "AT+DR=%s\r\n", Band);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, erro);
    if(resultado == NULL){
    	return 0;
    }
    else return -1;
}

int set_Mode(char *Mode){
    char message[16];
    char Buffer[16] = {0};
    char erro[6] = "ERROR";

    sprintf(message, "AT+MODE=%s\r\n", Mode);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, erro);
    if(resultado == NULL){
   	return 0;
    }
    else return -1;
}

int lora_Join(){
    char message[10] = "AT+JOIN\r\n";
    char Buffer[100] = {0};
    char done[12] = "Join failed";

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 10000);

    char *resultado = strstr(Buffer, done);
    if(resultado == NULL){
       	return 0;
    }
    else return -1;
}

int send_String(char *String){
	char message[50] = {0};
	char Buffer[100] = {0};
	char done[4] = "Done";

    sprintf(message, "AT+MSG=%s\r\n", String);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, done);
    if(resultado == NULL){
    	return -1;
    }
    else return 0;
}

int send_Hex(char *Hex){
	char message[50] = {0};
	char Buffer[100] = {0};
	char done[4] = "Done";

    sprintf(message, "AT+MSGHEX=%s\r\n", Hex);

    HAL_UART_Transmit(&huart,  (uint8_t*)message, sizeof(message), 100);
    HAL_UART_Receive(&huart,  (uint8_t*)Buffer, sizeof(Buffer), 300);

    char *resultado = strstr(Buffer, done);
    if(resultado == NULL){
    	return -1;
    }
    else return 0;
}
