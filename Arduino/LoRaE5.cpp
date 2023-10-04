/* DATA: 08/2023
 * AUTOR: Caio Teraoka de Menezes Câmara
 * VERSÃO 1.0
 * DESCRIÇÃO: Biblioteca desenvolvida para facilitar o uso dos comandos AT em projetos utilizando o módulo LoRa WIO-E5
 * REQUISITOS de HARDWARE: Módulo WIO-E5, Microcontrolador com comunicação Serial4
 * REQUISITOS DE SOFTWARE: ArduinoIDE
 */

#include "LoRaE5.h"

void WIO_E5::init(HardwareSerial *p){

    if(nullptr == p){}
    _serial = p;

    //Pega os principais dados da placa
    char message[8] = "AT+ID\r\n";
	String Buffer = "";

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    strncpy(DevAddr, &Buffer[14], 11);
    DevAddr[11] = '\0';
    strncpy(DevEui, &Buffer[40], 23);
    DevEui[23] = '\0';
    strncpy(AppEui, &Buffer[78], 23);
    AppEui[23] = '\0';

} // Construtor

void WIO_E5::reset(){
    char message[11] = "AT+RESET\r\n";
	String Buffer = "";

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();
}

char * WIO_E5::get_DevAddr(){
    return DevAddr;
}

char * WIO_E5::get_DevEui(){
    return DevEui;
}

char * WIO_E5::get_AppEui(){
    return AppEui;
}

char * WIO_E5::get_Band(){
    char message[8] = "AT+DR\r\n";
    String Buffer;
    char *Band = (char *)malloc(sizeof(char)*24);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    strncpy(Band, &Buffer[15], 23);
    Band[23] = '\0';

    return Band;
}

int WIO_E5::set_DevAddr(char *DevAddr){
    char message[30];
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+ID=DevAddr, \"%s\"\r\n", DevAddr);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::set_DevEui(char *DevEui){
    char message[41];
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+ID=DevEui, \"%s\"\r\n", DevEui);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::set_AppEui(char *AppEui){
    char message[41] = {0};
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+ID=AppEui, \"%s\"\r\n", AppEui);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::set_Band(char *Band){
    char message[13] = {0};
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+DR=%s\r\n", Band);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::set_Mode(char *Mode){
    char message[16];
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+MODE=%s\r\n", Mode);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::set_Appkey(char *Appkey){
    char message[35];
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+KEY=APPKEY,\"%s\"\r\n", Appkey);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::set_Channel(char *Channel){
    char message[20];
    String Buffer;
    char erro[6] = "ERROR";

    sprintf(message, "AT+CH=NUM,%s\r\n", Channel);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(erro) != -1){
    	return 0;
    }
    else return -1;
}

int WIO_E5::send_String(char *string){
    char message[50] = {0};
	String Buffer;
	char done[5] = "Done";

    sprintf(message, "AT+MSG=%s\r\n", string);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(done) != -1){
    	return -1;
    }
    else return 0;
}

int WIO_E5::send_Hex(char *Hex){
    char message[50] = {0};
	String Buffer;
	char done[5] = "Done";

    sprintf(message, "AT+MSGHEX=%s\r\n", Hex);

    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(done) != -1){
    	return -1;
    }
    else return 0;
}

int WIO_E5::lora_Join(){
    char message[10] = "AT+JOIN\r\n";
    String Buffer = "";
    char failed[7] = "failed";

    _serial->setTimeout(30000);
    while (_serial->availableForWrite() == 0){}
    _serial->print(message);
    while(_serial->available() == 0) {}
    Buffer = _serial->readString();

    if(Buffer.indexOf(failed) == -1){
    	return 0;
    }
    else return -1;
}
