#ifndef __FLASH_MAP_H__
#define __FLASH_MAP_H__


//---------------------
// Enum List
//---------------------
typedef union {
    uint8_t  u8_data;
    uint16_t u16_data;
    uint32_t u32_data;
} data_type_t;


//---------------------
// STM32F7 Flash Addres
//---------------------
#define ADDR_FLASH_SECTOR_0         ((uint32_t)0x08000000) /* Base @ of Sector 0, 32 Kbyte */
#define ADDR_FLASH_SECTOR_1         ((uint32_t)0x08008000) /* Base @ of Sector 1, 32 Kbyte */
#define ADDR_FLASH_SECTOR_2         ((uint32_t)0x08010000) /* Base @ of Sector 2, 32 Kbyte */
#define ADDR_FLASH_SECTOR_3         ((uint32_t)0x08018000) /* Base @ of Sector 3, 32 Kbyte */
#define ADDR_FLASH_SECTOR_4         ((uint32_t)0x08020000) /* Base @ of Sector 4, 128 Kbyte */
#define ADDR_FLASH_SECTOR_5         ((uint32_t)0x08040000) /* Base @ of Sector 5, 256 Kbyte */
#define ADDR_FLASH_SECTOR_6         ((uint32_t)0x08080000) /* Base @ of Sector 6, 256 Kbyte */
#define ADDR_FLASH_SECTOR_7         ((uint32_t)0x080C0000) /* Base @ of Sector 7, 256 Kbyte */
#define ADDR_FLASH_SECTOR_8         ((uint32_t)0x08100000) /* Base @ of Sector 8, 256 Kbyte */
#define ADDR_FLASH_SECTOR_9         ((uint32_t)0x08140000) /* Base @ of Sector 9, 256 Kbyte */
#define ADDR_FLASH_SECTOR_10        ((uint32_t)0x08180000) /* Base @ of Sector 10, 256 Kbyte */
#define ADDR_FLASH_SECTOR_11        ((uint32_t)0x08C00000) /* Base @ of Sector 11, 256 Kbyte */
#define ADDR_FLASH_END              ((uint32_t)0x080FFFFF)


#endif /*  __FLASH_MAP_H__  */
