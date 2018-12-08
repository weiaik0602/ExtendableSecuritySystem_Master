#ifndef _MASTERFUNC_H
#define _MASTERFUNC_H

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
#define MAX_SLAVE 5
#define UART_SIZE 10
#define SPI_SIZE 10
#define BUFFER_SIZE 10
//module
#define MODULE_Self 0
#define MODULE_Buzzer 1
#define MODULE_Lock 2
#define MODULE_Led 3
//action
#define ACTION_Open 0
#define ACTION_Close 1
//reply
#define REPLY_Here 0
#define REPLY_NA 0xF

//variables
sm_state master_sm_state;



//Functions



#endif // _MASTERFUNC_H
