#include "MasterFunc.h"

#include "main.h"


//global variable
volatile sm_state master_sm_state;
volatile uart_data uart_receive_buffer[BUFFER_SIZE],uart_receive_buffer[BUFFER_SIZE];
volatile uint8_t uart_receive[UART_SIZE];
volatile uint8_t uart_receive_position, uart_use_position;
volatile uint8_t spi_receive[3];
volatile uint8_t slave_record=0;

void Master_StateMachine() {
  switch (master_sm_state){
    case Init:
      Init_Func();
    break;

    case Idle:
      //IDLE_Func();
    break;

    default:
    break;

  }
}


//place inside UART-DMA interrupt
void UART_Receive_Buffer(){
  if(uart_receive_position >= BUFFER_SIZE-1){
    uart_receive_position = 0;
  }
  uart_receive_buffer[uart_receive_position].board = uart_receive[0];
  uart_receive_buffer[uart_receive_position].module = uart_receive[1];
  uart_receive_buffer[uart_receive_position].size = uart_receive[2];
  uart_receive_buffer[uart_receive_position].data = uart_receive[3];
  uart_receive_position++;
}

uint8_t datasend[]={MODULE_Self, 1, ACTION_Open};
uint8_t dataReceive[3];
void Init_Func(){

  for(int i = 0; i < MAX_SLAVE ; i++){
    Slave_Enable(i);
    SPI_SendReceive((uint8_t*)&datasend,(uint8_t*)&dataReceive);
    Slave_Disable(i);
    if(dataReceive[2] == REPLY_Here){
      slave_record = slave_record | (1<<i);
    }
  }
}

void Idle_Func(){
  if(uart_use_position != uart_receive_position){
    Slave_Enable(uart_receive_buffer[uart_use_position].board);
    SPI_SendReceive((uint8_t*)&uart_receive_buffer[uart_use_position].module, dataReceive);
    Slave_Disable(uart_receive_buffer[uart_use_position].board);
    uart_use_position++;
  }
}
