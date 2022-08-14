#include "usart.h"
#include "cli_interface.h"
#include "utill.h"
#include "flash_map.h"
#include "file_system.h"
#include "config.h"


#if _USE_RTOS_ == 1
#include "cmsis_os.h"

#define CLI_TASK_SIGNAL                 (0x01U)

osThreadId cli_TaskHandle;

void cli_task(void const * argument);
#endif


//-------------------------------------------
// str list
//-------------------------------------------
uart_buffer_t user;

//-------------------------------------------
// CallBack List
//-------------------------------------------
int cbf_test(int argc, char *argv[]);
int cbf_help(int argc, char *argv[]);
int cbf_info(int argc, char *argv[]);
int cbf_flash_dump(int argc, char *argv[]);
int cbf_fs_mount(int argc, char *argv[]);
int cbf_fs_open(int argc, char *argv[]);
int cbf_fs_close(int argc, char *argv[]);
int cbf_fs_write(int argc, char *argv[]);
int cbf_fs_read(int argc, char *argv[]);
int cbf_fs_get_info(int argc, char *argv[]);
int cbf_fs_read_dir(int argc, char *argv[]);

//-------------------------------------------
// CLI Def
//-------------------------------------------
typedef int (*CBF)(int argc, char *argv[]);
typedef struct 
{
    char *name;
    CBF   func;
} CMD_LIST;


//-------------------------------------------
// CLI LIST
//-------------------------------------------
const CMD_LIST cmd_list[] =
{
    {"help"             ,           cbf_help            },
    {"test"             ,           cbf_test            },
    {"info"             ,           cbf_info            },
    {"dump"             ,           cbf_flash_dump      },

    //----------------------------------------------------
    // File System Command
    //----------------------------------------------------
    {"fs_mount"         ,           cbf_fs_mount        },
    {"fs_open"          ,           cbf_fs_open         },
    {"fs_close"         ,           cbf_fs_close        },
    {"fs_write"         ,           cbf_fs_write        },
    {"fs_read"          ,           cbf_fs_read         },
    {"fs_get_info"      ,           cbf_fs_get_info     },
    {"fs_read_dir"      ,           cbf_fs_read_dir     },
    //----------------------------------------------------

    {(char*)NULL        ,           (CBF)NULL           }
};

#if _USE_STM32F_SERIES_
//----------------------------------------------------------------------------------
// STM32F Series Uart Callback of HAL Lib
// Can be replaced in another mcu uart lib for this cli module
//----------------------------------------------------------------------------------
/**
  * @brief  Tx Transfer completed callback
  * @param  UartHandle: UART handle. 
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
 
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  /* Set transmission flag: transfer complete */
  if (UartHandle->Instance == USART6) {
      
      if ((user.rx_dummy == CLI_CR) ||
          (user.rx_dummy == CLI_LF)) {
          #if _USE_RTOS_ == 1
          //osSignalSet(cli_TaskHandle, CLI_TASK_SIGNAL);
          #endif
          user.rx_done  = kCLI_SET;
          user.rx_index = kCLI_RESET;
      } else {
          if (user.rx_index < MAX_SIZE) {
              user.rx_buffer[user.rx_index++] = user.rx_dummy; //USART6->RDR;
          } else {
              user.rx_index = kCLI_RESET;
          }
      }    
      
      HAL_UART_Receive_IT(&huart6, &user.rx_dummy, 1);
  }
}
//----------------------------------------------------------------------------------
#endif

void app_cli_init(void)
{
#if _USE_RTOS_ == 1
    osThreadDef(cli_tasks_name, cli_task, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
    cli_TaskHandle = osThreadCreate(osThread(cli_tasks_name), NULL);
#endif

#if _USE_STM32F_SERIES_
    HAL_UART_Receive_IT(&huart6, &user.rx_dummy, 1);
#else
    // other mcu interrupt enable api can be called in here
#endif
}

#if _USE_RTOS_ == 1
void cli_task(void const * argument)
{
    //osEvent evt;
    for(;;)
    {
        //evt = osSignalWait (CLI_TASK_SIGNAL, osWaitForever);
        //if (evt.status == osEventSignal) 
        if (user.rx_done == 1) {
            user.rx_done = 0;
            parser((char*)&user.rx_buffer[0]);
            memset(user.rx_buffer, 0x0, MAX_SIZE);
        }
        osDelay(CLI_SYSTEM_DELAY);
    }
}
#else
void app_cli(void)
{
    if (user.rx_done == 1) {
        user.rx_done = 0;
        parser((char*)&user.rx_buffer[0]);
        memset(user.rx_buffer, 0x0, MAX_SIZE);
    }
}
#endif

/* CLI PARSER */
int parser(char *cmd)
{
    int    argc = kCLI_RESET;
    char  *argv[NUMBER_OF_DELIMITER_VALUE];
       
    argv[argc++] = strtok(cmd, CLI_DELIMITER);
	
	//----------------------------------------
    // SPLIT THE UART RX STRING
    //----------------------------------------
    while (1) {
        argv[argc] = strtok(NULL, CLI_DELIMITER);
        
        if (argv[argc] == NULL) {
            break;
        }
        argc++;
    }

    //----------------------------------------
    // FIND THE MATCHED STRING
    //----------------------------------------
    for (int cnt = 0; cmd_list[cnt].name != NULL; cnt++) {
        if (strcmp(cmd_list[cnt].name, argv[0]) == CLI_MATCH) {
            return cmd_list[cnt].func(argc, argv);
        }
    }
    printf("fish@cli#");
    return CLI_NOT_FOUND;
}

/**
  * @brief  call back function
  * @retval int
  */
int cbf_test(int argc, char *argv[])
{
    if (argv[0] != NULL) {
        printf("argv : %s \r\n", argv[0]);
    }
    
    if (argv[1] != NULL) {
        printf("argc : %d , argv : %s \r\n", argc, argv[1]);
    }
    
	return kCLI_OK;
}

int cbf_help(int argc, char *argv[])
{
    printf("cmd list ---------------------------------\r");
    for (uint8_t cnt = 0; cmd_list[cnt].name != NULL; cnt++) {
        printf("%s\r", cmd_list[cnt].name);
    }
    printf("------------------------------------------\r");
    return kCLI_OK;
}

#define MCU_INFO        "STM32F746NGH6"
#define BD_INFO         "STM32F746NG-DISCOVERY BOARD"
#define FIRMWARE_INFO   "V0.1"
int cbf_info(int argc, char *argv[])
{
    printf("Board InFo ---------------------------------\r");
    printf("MCU : %s\r", MCU_INFO);
    printf("H/D : %s\r", BD_INFO);
    printf("F/W : %s\r", FIRMWARE_INFO);
    printf("------------------------------------------\r");
    return kCLI_OK;
}

int cbf_flash_dump(int argc, char *argv[])
{
    //------------------------------------------------
    // Memory Dump Command
    // dump size address -> dump 64 08000000
    //------------------------------------------------
    const uint16_t DATA_ALLINGMENT_SIZE = 16;
    const uint32_t DEFAULT_DUMP_SIZE    = 64U;
    data_type_t read_data;

    uint32_t size    = atoi(argv[1]);
    uint32_t address = atoh((int8_t *)argv[2]);

    if (size <= 0) {
        size = DEFAULT_DUMP_SIZE;
        //return kCLI_NAK;
    }

    if ((address < ADDR_FLASH_SECTOR_0) || 
        (address > ADDR_FLASH_END)) {
        return kCLI_NAK;
    }

    volatile uint8_t *p_flash_addr = (uint8_t*)address;

    printf("//-------------------------------------------\r");
    printf("// Flash Dump \r");
    printf("//-------------------------------------------\r");

    for(uint32_t cnt = 0; cnt < size; cnt++, p_flash_addr++) {
        
        // Address Print
        if (cnt % DATA_ALLINGMENT_SIZE == 0) {
            printf("\r");
            printf("0x%04X : ", p_flash_addr);
        }

        // Data print
        read_data.u32_data = *p_flash_addr;
        printf("%02X ", read_data.u8_data);
        
    }
    printf("\r");
    printf("//-------------------------------------------\r");
    return kCLI_OK;
}

int cbf_fs_mount(int argc, char *argv[])
{
    fs_mount();
    return kCLI_OK;
}

int cbf_fs_open(int argc, char *argv[])
{
    fs_open("/");
    return kCLI_OK;
}

int cbf_fs_close(int argc, char *argv[])
{
    fs_close();
    return kCLI_OK;
}

int cbf_fs_write(int argc, char *argv[])
{
    fs_write(argv[1], strlen(argv[1]));
    return kCLI_OK;
}

int cbf_fs_read(int argc, char *argv[])
{
    uint32_t *get_str;
    char *get_data_buffer;
    uint32_t rx_byte = atoi(argv[1]);
    fs_read(get_data_buffer, rx_byte, get_str);
    return kCLI_OK;
}

int cbf_fs_get_info(int argc, char *argv[])
{
    fs_get_info(&hsd1);
    return kCLI_OK;
}

int cbf_fs_read_dir(int argc, char *argv[])
{
    if (fs_is_sdcard_detected() != FR_OK) {
        return kCLI_NAK;
    }

    fatfsScanFiles(ROOT);
    return kCLI_OK;
}
