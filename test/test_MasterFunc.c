#include "unity.h"
#include "MasterFunc.h"
#include "mock_mockFunc.h"


void setUp(void){}
void tearDown(void){}

void test_UART_Receive_Buffer_uart_receive_position_reset(void)
{
  uart_receive_position = BUFFER_SIZE-1;
  uart_receive[0] = 1;
  uart_receive[1] = MODULE_Self;
  uart_receive[2] = 1;
  uart_receive[3] = ACTION_Open;

  UART_Receive_Buffer();
  TEST_ASSERT_EQUAL(uart_receive_position,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].board,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].module,MODULE_Self);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].size,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].data,ACTION_Open);
}

void test_UART_Receive_Buffer_uart_receive_position_increment(void)
{
  uart_receive_position = 0;
  uart_receive[0] = 1;
  uart_receive[1] = MODULE_Led;
  uart_receive[2] = 1;
  uart_receive[3] = ACTION_Close;

  UART_Receive_Buffer();
  TEST_ASSERT_EQUAL(uart_receive_position,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].board,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].module,MODULE_Led);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].size,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[0].data,ACTION_Close);
}

void test_UART_Receive_Buffer_uart_receive_position_increment_agn(void)
{
  uart_receive[0] = 1;
  uart_receive[1] = MODULE_Buzzer;
  uart_receive[2] = 1;
  uart_receive[3] = ACTION_Close;

  UART_Receive_Buffer();
  TEST_ASSERT_EQUAL(uart_receive_position,2);
  TEST_ASSERT_EQUAL(uart_receive_buffer[1].board,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[1].module,MODULE_Buzzer);
  TEST_ASSERT_EQUAL(uart_receive_buffer[1].size,1);
  TEST_ASSERT_EQUAL(uart_receive_buffer[1].data,ACTION_Close);
}

void test_Init_Func(void){
  dataReceive[2] = REPLY_Here;
  int record = 0;
  for(int i= 0; i< MAX_SLAVE; i++){
    Slave_Enable_Expect(i);
    SPI_SendReceive_Expect((uint8_t*)&datasend,(uint8_t*)&dataReceive);
    Slave_Disable_Expect(i);
    record = record | (1<<i);
  }
  Init_Func();
  TEST_ASSERT_EQUAL(record, slave_record );
}

void test_Idle_Func(){
  uart_use_position = 0;
  uart_receive_position = 1;
  Slave_Enable_Expect(uart_receive_buffer[0].board);
  SPI_SendReceive_Expect((uint8_t*)&uart_receive_buffer[0].module,(uint8_t*)&dataReceive);
  Slave_Disable_Expect(uart_receive_buffer[0].board);
  Idle_Func();
  TEST_ASSERT_EQUAL(uart_use_position, 1);
}

void test_Idle_Func_not_running(){
  uart_use_position = uart_receive_position = 1;
  Idle_Func();
  TEST_ASSERT_EQUAL(uart_use_position, 1);
}
