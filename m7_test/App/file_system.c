#include "file_system.h"


static FRESULT res;
static FILINFO fno;


void app_fs_init(void)
{
    if (fs_is_sdcard_detected() != FR_OK) {
        printf("SD Card is not mounted \r\n");
        return;
    }

    if (f_mount(&SDFatFS, (TCHAR const *)SDPath, MOUNT_IMMEDIATELY) != FR_OK) {
        printf("FS Mount Failed \r\n");
    }
}


FRESULT fs_mount(void)
{
  return f_mount(&SDFatFS, (TCHAR const *)SDPath, MOUNT_IMMEDIATELY);
}

FRESULT fs_open(char *file_name)
{
  return f_open(&SDFile, file_name, FA_CREATE_ALWAYS | FA_WRITE);
}

FRESULT fs_close(void)
{
    return f_close(&SDFile);
}

FRESULT fs_write(char *write_text, uint32_t bytes_written)
{
    return f_write(&SDFile, write_text, strlen((char *)write_text), (void *)&bytes_written);
}

FRESULT fs_read(void *get_str_buffer, uint32_t number_of_read_byte, uint32_t *pointer_to_byte_read)
{
    return f_read(&SDFile, get_str_buffer, number_of_read_byte, pointer_to_byte_read);
}

FRESULT fs_get_info(SD_HandleTypeDef *hsd)
{
    uint32_t tot_sect = 0, fre_sect = 0, fre_clust = 0;
    FATFS *fs;
    
    res = f_getfree("", (DWORD *)&fre_clust, &fs);

    HAL_SD_CardInfoTypeDef card_info;

    HAL_SD_GetCardInfo(&hsd1, &card_info);

    /* Get total sectors and free sectors */
    tot_sect = (fs->n_fatent - 2) * fs->csize;
    fre_sect = fre_clust * fs->csize;

    //---------------------------------------------------------------------------------------------
    printf("%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", tot_sect / 2, fre_sect / 2);
    //---------------------------------------------------------------------------------------------
    printf("card_type            : %d\r\n", card_info.CardType);
    printf("card_version         : %d\r\n", card_info.CardVersion);
    printf("card_class           : %d\r\n", card_info.Class);
    printf("rel_card_Add         : %d\r\n", card_info.RelCardAdd);
    printf("block_numbers        : %d\r\n", card_info.BlockNbr);
    printf("block_size           : %d\r\n", card_info.BlockSize);
    printf("log_block_numbers    : %d\r\n", card_info.LogBlockNbr);
    printf("log_block_size       : %d\r\n", card_info.LogBlockSize);
    printf("card_size            : %d MB, %d.%d GB\r\n", card_info.BlockSize, card_info.BlockSize/1024, ((card_info.BlockSize * 10)/1024) % 10);
    
    return FR_OK;
}

FRESULT fs_is_sdcard_detected(void)
{
  FRESULT ret = FR_NOT_READY;

  if (IS_SD_CARD_DETECTED == GPIO_PIN_SET) {
    ret = FR_OK;
  }

  return ret;
}

FRESULT fatfsScanFiles(char* path)
{
  DIR dir;

  res = f_opendir(&dir, path);                       /* Open the directory */
  if (res == FR_OK) {
    for (;;) {
      res = f_readdir(&dir, &fno);                   /* Read a directory item */
      if (res != FR_OK || fno.fname[0] == 0) {
             break;                                  /* Break on error or end of dir */
      }

      if (fno.fattrib & AM_DIR) {                    /* It is a directory */
        printf(" %s/%s \r\n", path, fno.fname);
      } else {                                       /* It is a file. */
        printf(" %s/%32s \t%d bytes\r\n", path, fno.fname, (int)fno.fsize);
      }
    }
    f_closedir(&dir);
  }

  return res;
}

#if 0
void HAL_SD_AbortCallback(SD_HandleTypeDef *hsd)
{
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
}

void HAL_SD_RxCpltCallback(SD_HandleTypeDef *hsd)
{
  
}
#endif
