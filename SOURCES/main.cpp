
#include <stdio.h>
#include <string.h>
#include "sd_cpp.h"
#include "mik32fat_cpp.h"

extern "C" void xsprintf(char* buff, const char* fmt, ...);
extern void print(char *text);

/*
    Данный пример показывает работу драйвера карт SD и
    файловой системы, совместимой с файловой системой FAT32
*/

#define  READ_EXAMPLE
#define  WRITE_EXAMPLE

#define  READ_BUFFER_LENGTH  20

MIK32_SPI_SD::SD_Descriptor_t sd;
MIK32FAT::FAT_Descriptor_t fs;

MIK32FAT MIK32FAT_;

static bool SD_FS_Config();

int main_()
{
    char sb[1024];
    xsprintf(sb, "\n\n*** Start ***\n"); print(sb);

    if ( ! SD_FS_Config() ) return 3 ;

    MIK32FAT::FAT_Status_t res;

#ifdef  READ_EXAMPLE
    xsprintf(sb, "\nReading file example\n"); print(sb);
    MIK32FAT::FAT_File_t read_file;
    res = MIK32FAT_.FileOpen(&read_file, &fs, (char*)"TESTS/READ.TXT", 'R');
    xsprintf(sb, "TESTS/READ.TXT file open status: %d\n", int(res)); print(sb);
    if (res != MIK32FAT::FAT_OK)
    {
        xsprintf(sb, "Error occured with file TESTS/READ.TXT, status %u\n", int(res)); print(sb);
        return 1;
    }
    static char read_buffer[READ_BUFFER_LENGTH];
    uint8_t i = read_file.len / (READ_BUFFER_LENGTH-1);
    if (read_file.len % (READ_BUFFER_LENGTH-1) != 0) i += 1;
    uint32_t bytes_read;
    xsprintf(sb, "Text:\n"); print(sb);
    while (i > 0)
    {
        bytes_read = MIK32FAT_.ReadFile(&read_file, read_buffer, READ_BUFFER_LENGTH-1);
        if (bytes_read == 0)
        {
            xsprintf(sb, "Error occured while file reading, stop.\n"); print(sb);
            break;
        }
        else
        {
            /* Вставить символ \0 для корректной печати */
            read_buffer[bytes_read] = '\0';
            xsprintf(sb, read_buffer); print(sb);
        }
        i -= 1;
    }
#endif
#ifdef  WRITE_EXAMPLE
    xsprintf(sb, "\nWriting file example\n"); print(sb);
    MIK32FAT::FAT_File_t write_file;
    res = MIK32FAT_.FileOpen(&write_file, &fs, (char*)"TESTS/WRITE1.TXT", 'W');
    xsprintf(sb, "TESTS/WRITE1.TXT file open status: %d\n", int(res)); print(sb);
    if (res != MIK32FAT::FAT_OK)
    {
        xsprintf(sb, "Error occured with file TESTS/WRITE1.TXT, status %u\n", unsigned(res)); print(sb);
        return 2;
    }
    char str[] = "Writing string to file\n";
    xsprintf(sb, "Wrote bytes: %d\n", MIK32FAT_.WriteFile(&write_file, str, strlen(str)-1)); print(sb);
    xsprintf(sb, "Close status: %d\n", MIK32FAT_.FileClose(&write_file)); print(sb);
#endif
}

static bool SD_FS_Config()
{
    char sb[1024];
    MIK32_SPI_SD::SD_Status_t res;
    res = MIK32_SPI_SD::SD_Init(&sd, NULL, NULL, 0);
    xsprintf(sb, "SD card: %s\n", res==MIK32_SPI_SD::SD_OK ? "found" : "not found");
    print(sb);
    if (res != MIK32_SPI_SD::SD_OK)
    {
        return false;
    }
    xsprintf(sb, "Type: "); print(sb);
    switch (sd.type)
    {
        case MIK32_SPI_SD::SDv1: xsprintf(sb, "SDv1"); break;
        case MIK32_SPI_SD::SDv2: xsprintf(sb, "SDv2"); break;
        case MIK32_SPI_SD::SDHC: xsprintf(sb, "SDHC"); break;
        case MIK32_SPI_SD::MMC:  xsprintf(sb, "MMC");  break;
        default:                 xsprintf(sb, "Unknown");
    }
    print(sb);

    /* Инициализация */
    MIK32FAT::FAT_Status_t fs_res;
    fs_res = MIK32FAT_.Init(&fs, &sd);
    xsprintf(sb, "FS initialization: %s", fs_res==MIK32FAT::FAT_OK ? "ok\n" : "FS initialization: failed, ");
    print(sb);
    if (fs_res != MIK32FAT::FAT_OK)
    {
        switch (fs_res)
        {
            case MIK32FAT::FAT_DiskError: xsprintf(sb, "disk error"); break;
            case MIK32FAT::FAT_DiskNForm: xsprintf(sb, "disk not mount"); break;
            default: xsprintf(sb, "unknown error"); break;
        }
        print(sb);
        return false;
    }
    print(sb);
    xsprintf(sb, "FS startaddr: %u\n", unsigned(fs.fs_begin)); print(sb);
    xsprintf(sb, "First FAT1 startaddr: %u\n", unsigned(fs.fat1_begin)); print(sb);
    xsprintf(sb, "First FAT2 startaddr: %u\n", unsigned(fs.fat2_begin)); print(sb);
    xsprintf(sb, "First data cluster: %u\n", unsigned(fs.data_region_begin)); print(sb);
    xsprintf(sb, "FAT length: %u\n", unsigned(fs.param.fat_length)); print(sb);
    xsprintf(sb, "Num of FATs: %u\n", unsigned(fs.param.num_of_fats)); print(sb);
    xsprintf(sb, "Sectors per cluster: %u\n", unsigned(fs.param.sec_per_clust)); print(sb);
    return true;
}
