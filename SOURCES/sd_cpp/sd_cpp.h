
#ifndef  _SD_H_
#define  _SD_H_

#include <stdint.h>

typedef  void  SPI_HandleTypeDef;
typedef  void  SPI_TypeDef;

extern void HAL_SPI_CS_Enable(SPI_HandleTypeDef* hspi, uint32_t CS_M), HAL_SPI_CS_Disable(SPI_HandleTypeDef* hspi),
            HAL_SPI_Exchange(SPI_HandleTypeDef* hspi, uint8_t TransmitBytes[], uint8_t ReceiveBytes[], uint32_t Size, uint32_t Timeout),
            HAL_DelayMs(uint32_t ms);

class MIK32_SPI_SD
{
    private:
        enum
        {
            /* R1 response */
                SD_R1_IDLE_STATE_S      = 0,
                SD_R1_IDLE_STATE_M      = (1 << SD_R1_IDLE_STATE_S),
                SD_R1_ERASE_RESET_S     = 1,
                SD_R1_ERASE_RESET_M     = (1 << SD_R1_ERASE_RESET_S),
                SD_R1_ILLEGAL_COMMAND_S = 2,
                SD_R1_ILLEGAL_COMMAND_M = (1 << SD_R1_ILLEGAL_COMMAND_S),
                SD_R1_CRC_ERROR_S       = 3,
                SD_R1_CRC_ERROR_M       = (1 << SD_R1_CRC_ERROR_S),
                SD_R1_ERASE_SEQ_ERROR_S = 4,
                SD_R1_ERASE_SEQ_ERROR_M = (1 << SD_R1_ERASE_SEQ_ERROR_S),
                SD_R1_ADDRESS_ERROR_S   = 5,
                SD_R1_ADDRESS_ERROR_M   = (1 << SD_R1_ADDRESS_ERROR_S),
                SD_R1_PARAMETER_ERROR_S = 6,
                SD_R1_PARAMETER_ERROR_M = (1 << SD_R1_PARAMETER_ERROR_S),
            /* R2 response */
                SD_R2_CARD_IS_LOCKED_S  = 0,
                SD_R2_CARD_IS_LOCKED_M  = (1 << SD_R2_CARD_IS_LOCKED_S),
                SD_R2_WP_ERASE_SKIP_S   = 1,
                SD_R2_WP_ERASE_SKIP_M   = (1 << SD_R2_WP_ERASE_SKIP_S),
                SD_R2_ERROR_S           = 2,
                SD_R2_ERROR_M           = (1 << SD_R2_ERROR_S),
                SD_R2_CC_ERROR_S        = 3,
                SD_R2_CC_ERROR_M        = (1 << SD_R2_CC_ERROR_S),
                SD_R2_CARD_ECC_FAILED_S = 4,
                SD_R2_CARD_ECC_FAILED_M = (1 << SD_R2_CARD_ECC_FAILED_S),
                SD_R2_WP_VIOLATION_S    = 5,
                SD_R2_WP_VIOLATION_M    = (1 << SD_R2_WP_VIOLATION_S),
                SD_R2_ERASE_PARAM_S     = 6,
                SD_R2_ERASE_PARAM_M     = (1 << SD_R2_ERASE_PARAM_S),
                SD_R2_OUT_OF_RANGE_S    = 7,
                SD_R2_OUT_OF_RANGE_M    = (1 << SD_R2_OUT_OF_RANGE_S),

                SD_SREAD_START_TOKEN              = 0xFE,
                SD_SREAD_WAIT_ATTEMPTS            = 10000,
                SD_SREAD_ERR_TOKEN_ERROR_S        = 0,
                SD_SREAD_ERR_TOKEN_ERROR_M        = (1 << SD_SREAD_ERR_TOKEN_ERROR_S),
                SD_SREAD_ERR_TOKEN_CC_ERROR_S     = 1,
                SD_SREAD_ERR_TOKEN_CC_ERROR_M     = (1 << SD_SREAD_ERR_TOKEN_CC_ERROR_S),
                SD_SREAD_ERR_TOKEN_ECC_FAILED_S   = 2,
                SD_SREAD_ERR_TOKEN_ECC_FAILED_M   = (1 << SD_SREAD_ERR_TOKEN_ECC_FAILED_S),
                SD_SREAD_ERR_TOKEN_OUT_OF_RANGE_S = 3,
                SD_SREAD_ERR_TOKEN_OUT_OF_RANGE_M = (1 << SD_SREAD_ERR_TOKEN_OUT_OF_RANGE_S),
        } ;
        typedef enum
        {
            CMD0   = 0x40 +  0,
            CMD1   = 0x40 +  1,
            CMD6   = 0x40 +  6,
            CMD8   = 0x40 +  8,
            CMD9   = 0x40 +  9,
            CMD10  = 0x40 + 10,
            CMD12  = 0x40 + 12,
            CMD13  = 0x40 + 13,
            CMD16  = 0x40 + 16,
            CMD17  = 0x40 + 17,
            CMD18  = 0x40 + 18,
            CMD24  = 0x40 + 24,
            CMD25  = 0x40 + 25,
            CMD27  = 0x40 + 27,
            CMD28  = 0x40 + 28,
            CMD29  = 0x40 + 29,
            CMD30  = 0x40 + 30,
            CMD32  = 0x40 + 32,
            CMD33  = 0x40 + 33,
            CMD38  = 0x40 + 38,
            CMD42  = 0x40 + 42,
            CMD55  = 0x40 + 55,
            CMD56  = 0x40 + 56,
            CMD58  = 0x40 + 58,
            CMD59  = 0x40 + 59,
            ACMD41 = 0x40 + 41,
        } SD_Commands_enum ;
    public:
        typedef enum
        {
            SDv1    = 0,
            SDv2    = 1,
            SDHC    = 2,
            MMC     = 3,
            Unknown = 4,
        } SD_CardType_enum ;
        typedef enum
        {
            SD_Voltage_from_1_6_to_1_7 = 1 <<  4,
            SD_Voltage_from_1_7_to_1_8 = 1 <<  5,
            SD_Voltage_from_1_8_to_1_9 = 1 <<  6,
            SD_Voltage_from_1_9_to_2_0 = 1 <<  7,
            SD_Voltage_from_2_0_to_2_1 = 1 <<  8,
            SD_Voltage_from_2_1_to_2_2 = 1 <<  9,
            SD_Voltage_from_2_2_to_2_3 = 1 << 10,
            SD_Voltage_from_2_3_to_2_4 = 1 << 11,
            SD_Voltage_from_2_4_to_2_5 = 1 << 12,
            SD_Voltage_from_2_5_to_2_6 = 1 << 13,
            SD_Voltage_from_2_6_to_2_7 = 1 << 14,
            SD_Voltage_from_2_7_to_2_8 = 1 << 15,
            SD_Voltage_from_2_8_to_2_9 = 1 << 16,
            SD_Voltage_from_2_9_to_3_0 = 1 << 17,
            SD_Voltage_from_3_0_to_3_1 = 1 << 18,
            SD_Voltage_from_3_1_to_3_2 = 1 << 19,
            SD_Voltage_from_3_2_to_3_3 = 1 << 20,
            SD_Voltage_from_3_3_to_3_4 = 1 << 21,
            SD_Voltage_from_3_4_to_3_5 = 1 << 22,
            SD_Voltage_from_3_5_to_3_6 = 1 << 23,
        } SD_Voltage_enum ;
        typedef enum
        {
            SD_OK                 =   0,
            SD_IncorrectVoltage   = 128,
            SD_UnknownCard        = 129,
            SD_TimeoutError       = 130,
            SD_CommunicationError = 131,
            SD_OperationError     = 132,
        } SD_Status_t ;
        typedef struct sd
        {
            SPI_HandleTypeDef* spi;
            SD_CardType_enum type;
            SD_Voltage_enum voltage;
        } SD_Descriptor_t ;
    private:
        static SD_Status_t SD_SendCommand(SD_Descriptor_t* local, SD_Commands_enum command, uint32_t operand, uint8_t crc, uint8_t* resp);
    public:
        static SD_Status_t SD_Init(SD_Descriptor_t* local, SPI_HandleTypeDef* hspi, SPI_TypeDef* instance, uint8_t cs);
        static SD_Status_t SD_SingleRead (SD_Descriptor_t* local, uint32_t address, uint8_t* buffer);
        static SD_Status_t SD_SingleWrite(SD_Descriptor_t* local, uint32_t address, uint8_t* buffer);
        static SD_Status_t SD_SingleErase(SD_Descriptor_t* local, uint32_t address);
} ;

#endif /* _SD_H_ */

