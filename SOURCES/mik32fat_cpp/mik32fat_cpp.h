
/* ПЕРЕВОД НА C++17 ОТ NDV
   ИСТОЧНИК: { github.com/Barsy-Barsevich/SDxMIK32 }
*/

#include "sd_cpp.h"

class MIK32FAT
{
    private:
        enum
        {
            /* Master boot record */
            FAT_MBR_Partition0       = 0x1BE,
            FAT_MBR_Partition1       = 0x1CE,
            FAT_MBR_Partition2       = 0x1DE,
            FAT_MBR_Partition3       = 0x1EE,
            FAT_MBR_Signature        = 0x1FE,
            FAT_MBR_Partition_Length = 16,
            /* Partition */
            FAT_Partition_BootFlag  = 0,
            FAT_Partition_CHS_Begin = 1,
            FAT_Partition_TypeCode  = 4,
            FAT_Partition_CHS_End   = 5,
            FAT_Partition_LBA_Begin = 8,
            FAT_Partition_NumOfSec  = 12,
            /* File system's LBA */
            FAT_BPB_BytsPerSec      = 0x0B,
            FAT_BPB_SecPerClus      = 0x0D,
            FAT_BPB_RsvdSecCnt      = 0x0E,
            FAT_BPB_NumFATs         = 0x10,
            FAT_BPB_FATSz32         = 0x24,
            FAT_BPB_RootClus        = 0x2C,

            FAT_DIR_Name            = 0,
            FAT_DIR_Attr            = 11,
            FAT_DIR_NTRes           = 12,
            FAT_DIR_CrtTimeTenth    = 13,
            FAT_DIR_CrtTime         = 14,
            FAT_DIR_CrtDate         = 16,
            FAT_DIR_LstAccDate      = 18,
            FAT_DIR_FstClusHI       = 20,
            FAT_DIR_WrtTime         = 22,
            FAT_DIR_WrtDate         = 24,
            FAT_DIR_FstClusLO       = 26,
            FAT_DIR_FileSize        = 28,
            FAT_ATTR_READ_ONLY      = 0x01,
            FAT_ATTR_HIDDEN         = 0x02,
            FAT_ATTR_SYSTEM         = 0x04,
            FAT_ATTR_VOLUME_ID      = 0x08,
            FAT_ATTR_DIRECTORY      = 0x10,
            FAT_ATTR_ARCHIVE        = 0x20
        } ;
        typedef struct
        {
            char Name[8];
            char Extention[3];
            uint8_t Attr;
            uint8_t NTRes;
            uint8_t CrtTimeTenth;
            uint16_t CrtTime;
            uint16_t CrtDate;
            uint16_t LstAccDate;
            uint16_t FstClusHI;
            uint16_t WrtTime;
            uint16_t WrtDate;
            uint16_t FstClusLO;
            uint32_t FileSize;
        } FAT_Entire_t;
    public:
        typedef enum
        {
            FAT_OK        = 0,
            FAT_DiskError = 1,
            /* Disk not formatted for FAT32 */
            FAT_DiskNForm   = 2,
            FAT_Error       = 3,
            FAT_NotFound    = 4,
            FAT_NoFreeSpace = 5,
        } FAT_Status_t;
        typedef struct
        {
            /* SD card descriptor */
            MIK32_SPI_SD::SD_Descriptor_t *card;
            /**
             * @brief One-sector buffer
             */
            uint8_t buffer[512];
            /**
             * The file system startaddr
             * It is a pointer to 0th cluster of file system containing information about
             */
            uint32_t fs_begin;
            /**
             * The 1st FAT startaddr
             */
            uint32_t fat1_begin;
            /**
             * The 2nd FAT startaddr
             */
            uint32_t fat2_begin;
            /**
             * The data region startaddr
             */
            uint32_t data_region_begin;
            /**
             * @brief Previously read sector
             */
            uint32_t prev_sector;
            /**
             * @brief File system parameters
             */
            struct __param
            {
                /**
                 * @brief Number of sectors per cluster
                 */
                uint8_t sec_per_clust;
                /**
                 * @brief Number of FATs
                 */
                uint8_t num_of_fats;
                /**
                 * @brief The length of one FAT
                 */
                uint32_t fat_length;
                /**
                 * @brief The length of 1 cluster
                 */
                uint32_t clust_len;
            } param;
            /**
             * @brief Temp object parameters
             */
            struct __temp
            {
                /**
                 * Number of sector of previous directory that contains
                 * file's entire
                 */
                uint32_t dir_sector;
                /**
                 * Number of entire of file in dir's sector
                 */
                uint32_t entire_in_dir_clust;
                /**
                 * Number cluster of temp cluster / subdirectory
                 */
                uint32_t cluster;
                /**
                 * Length of file (always 0 for directories)
                 */
                uint32_t len;
                /**
                 * Status of temp file / subdirectory
                 */
                uint8_t status;
            } temp;
        } FAT_Descriptor_t;
        typedef struct
        {
            /**
             * @brief Указатель на дескриптор файловой системы
             */
            FAT_Descriptor_t *fs;
            /**
             * @brief Если бы файл был единым непрерывным массивом данных,
             * addr - это адрес, с которого начинается запись или чтение
             */
            uint32_t addr;
            /**
             * @brief Номер текущего кластера файла, Значение по адресу addr
             * попадает в текущий кластер
             */
            uint32_t cluster;
            /**
             * @brief Номер сектора директории, в котором лежит дескриптор файла
             */
            uint32_t dir_sector;
            /**
             * @brief Адрес дескриптора файла в секторе директории
             */
            uint32_t entire_in_dir_clust;
            /**
             * @brief Длина файла. При чтении декрементируется, при записи инкрементируется
             */
            uint32_t len;
            /**
             * @brief Статус файла
             */
            uint8_t status;
            /**
             * @brief Модификатор доступа к файлу
             */
            char modificator;
            /**
             * @brief
             */
            bool writing_not_finished;
        } FAT_File_t;
    private:
        FAT_Status_t FindFreeCluster(FAT_Descriptor_t *fs, uint32_t *new_cluster);
        FAT_Status_t DeleteTemp(FAT_Descriptor_t *fs);
    public:
        FAT_Status_t Init(FAT_Descriptor_t *fs, MIK32_SPI_SD::SD_Descriptor_t *sd_card);
        void SetPointerToRoot(FAT_Descriptor_t *local);
        FAT_Status_t FindNextCluster(FAT_Descriptor_t *fs);
        FAT_Status_t FindByName(FAT_Descriptor_t *local, char *name);
        FAT_Status_t FindByPath(FAT_Descriptor_t *fs, char *path);
        FAT_Status_t FindOrCreateByPath(FAT_Descriptor_t *fs, char *path);
        FAT_Status_t TakeFreeCluster(FAT_Descriptor_t *fs, uint32_t clust, uint32_t *new_clust);
        FAT_Status_t FileOpen(FAT_File_t *file, FAT_Descriptor_t *fs, char *name, char modificator);
        FAT_Status_t FileClose(FAT_File_t *file);
        uint32_t ReadFile(FAT_File_t *file, char *buf, uint32_t quan);
        uint32_t WriteFile(FAT_File_t *file, const char *buf, uint32_t quan);
        FAT_Status_t Create(FAT_Descriptor_t *fs, char *name, bool dir);
        FAT_Status_t Delete(FAT_Descriptor_t *fs, char *name);
} ;
