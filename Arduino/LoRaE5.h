/* DATA: 08/2023
 * AUTOR: Caio Teraoka de Menezes Câmara
 * VERSÃO 1.0
 * DESCRIÇÃO: Biblioteca desenvolvida para facilitar o uso dos comandos AT em projetos utilizando o módulo LoRa WIO-E5
 * REQUISITOS de HARDWARE: Módulo WIO-E5, Microcontrolador com comunicação serial
 * REQUISITOS DE SOFTWARE: ArduinoIDE
 */

#ifndef LORAE5_H
#define LORAE5_H

#include <string>
#include <Arduino.h>
#include <HardwareSerial.h>

class WIO_E5 {
private:
    char DevAddr[12];
    char DevEui[24];
    char AppEui[24];
    HardwareSerial *_serial;

public:
    void init(HardwareSerial*);
    void reset();
    char *get_DevAddr();
    char *get_DevEui();
    char *get_AppEui();
    char *get_Band();
    int set_DevAddr(char *DevAddr);
    int set_DevEui(char *DevEui);
    int set_AppEui(char *AppEui);
    int set_Band(char *Band);
    int set_Mode(char *Mode);
    int set_Appkey(char *Appkey);
    int set_Channel(char *Channel);
    int send_String(char *String);
    int send_Hex(char *Hex);
    int lora_Join();
};

#endif // E5MODULE_H


