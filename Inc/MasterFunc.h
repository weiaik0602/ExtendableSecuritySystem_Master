#ifndef _MASTERFUNC_H
#define _MASTERFUNC_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mockFunc.h"

typedef enum sm_state sm_state;
enum sm_state{
  Init,
  Idle
};

typedef struct spi_data spi_data;
struct spi_data{
  uint8_t module;
  uint8_t size;
  uint8_t data;
};

typedef struct uart_data uart_data;
struct uart_data{
  uint8_t board;
  uint8_t module;
  uint8_t size;
  uint8_t data;
};

//define
#define MAX_SLAVE 2
#define UART_SIZE 4
#define SPI_SIZE 5
#define BUFFER_SIZE 5
//module
#define MODULE_Self 0
#define MODULE_Buzzer 1
#define MODULE_Lock 2
#define MODULE_Led 3
//action
#define ACTION_Open 0xa
#define ACTION_Close 0xb
//reply
#define REPLY_Here 0x7
#define REPLY_NA 0xF

//variables
extern volatile sm_state master_sm_state;
extern volatile uart_data uart_receive_buffer[BUFFER_SIZE],uart_receive_buffer[BUFFER_SIZE];
extern volatile uint8_t uart_receive[UART_SIZE];
extern volatile uint8_t uart_slave_receive[UART_SIZE];
extern volatile uint8_t uart_receive_position, uart_use_position;
extern volatile uint8_t slave_record;
extern volatile uint8_t spi_receive[3];
//temp variables
extern uint8_t datasend[3];
extern uint8_t dataReceive[3];
//Functions
void Master_StateMachine();
void UART_Receive_Buffer();
void Init_Func();
void Idle_Func();


#endif // _MASTERFUNC_H
