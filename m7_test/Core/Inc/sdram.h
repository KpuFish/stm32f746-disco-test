#ifndef __SDRAM_H__
#define __SDRAM_H__


//----------------------------------------
// Enum
//----------------------------------------
/* Exported types ------------------------------------------------------------*/
typedef enum {PASSED = 0, FAILED = !PASSED} TestStatus_t;


//----------------------------------------
// Define
//----------------------------------------
/* Exported constants --------------------------------------------------------*/
#define SDRAM_BANK_ADDR                 ((uint32_t)0xC0000000)

/* #define SDRAM_MEMORY_WIDTH            FMC_SDRAM_MEM_BUS_WIDTH_8  */
#define SDRAM_MEMORY_WIDTH               FMC_SDRAM_MEM_BUS_WIDTH_16

#define SDCLOCK_PERIOD                   FMC_SDRAM_CLOCK_PERIOD_2
/* #define SDCLOCK_PERIOD                FMC_SDRAM_CLOCK_PERIOD_3 */

#define SDRAM_TIMEOUT     ((uint32_t)0xFFFF)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)



//----------------------------------------
// Function
//----------------------------------------
void sdram_init(void);

void BSP_SDRAM_Initialization_Sequence(SDRAM_HandleTypeDef *hsdram, FMC_SDRAM_CommandTypeDef *Command);


#endif /*  __SDRAM_H__  */
