#ifndef __FILE_SYSTEM_H__
#define __FILE_SYSTEM_H__


//----------------------------
// Include
//----------------------------
#include <stdio.h>
#include <string.h>
#include "fatfs.h"
#include "sdmmc.h"


//----------------------------
// Define
//----------------------------
#define MOUNT_IMMEDIATELY       1

#define ROOT                    "/"

#define SD_CARD                 GPIOC
#define DETECTION_IO            GPIO_PIN_13
#define IS_SD_CARD_DETECTED     HAL_GPIO_ReadPin(SD_CARD, DETECTION_IO)


//----------------------------
// Function
//----------------------------
void app_fs_init(void);
FRESULT fs_mount(void);
FRESULT fs_open(char *file_name);
FRESULT fs_close(void);
FRESULT fs_write(char *wtext, uint32_t byteswritten);
FRESULT fs_read(void *get_str_buffer, uint32_t number_of_read_byte, uint32_t *pointer_to_byte_read);
FRESULT fs_get_info(SD_HandleTypeDef *hsd);
FRESULT fs_is_sdcard_detected(void);
FRESULT fatfsScanFiles(char* path);


#endif /*  __FILE_SYSTEM_H__  */
