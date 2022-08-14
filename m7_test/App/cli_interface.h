#ifndef __CLI_INTERFACE_H__
#define __CLI_INTERFACE_H__


//----------------------------------------------------------
// Include
//----------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>    // strtok 함수가 선언된 헤더 파일
#include <stdint.h>
//#include <ctype.h>     // isdigit


//----------------------------------------------------------
// Define
//----------------------------------------------------------
// CMSIS RTOS or FreeRTOS
#define CLI_SYSTEM_DELAY                    1

#define CLI_NOT_FOUND                       1
                    
#define CLI_END                             0
                    
#define CLI_MATCH                           0

#define CLI_CR                              '\r'

#define CLI_LF                              '\n'
                    
#define CLI_DELIMITER                       " "

#define NUMBER_OF_DELIMITER_VALUE           20

#define MAX_SIZE                            128


//----------------------------------------------------------
// Structure
//----------------------------------------------------------
typedef enum {
    kCLI_RESET      =   0U,
    kCLI_SET        =   1U,
    kCLI_OK         = kCLI_SET,
    kCLI_NAK        = kCLI_RESET,
} CLI_Set_define_e;


//----------------------------------------------------------
// Structure
//----------------------------------------------------------
typedef struct {
    uint8_t rx_buffer[MAX_SIZE];
    uint8_t rx_done;
    uint8_t rx_dummy;
    uint16_t rx_index;
} uart_buffer_t;


//----------------------------------------------------------
// Function
//----------------------------------------------------------
int parser(char *cmd);

void app_cli(void);

void app_cli_init(void);


#endif /* __CLI_INTERFACE_H__ */
