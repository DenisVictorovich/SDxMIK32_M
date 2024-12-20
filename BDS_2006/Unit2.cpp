//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
extern int main_();
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner) : TForm(Owner)
{
    cp = new TCustomComPort(Owner);
    cp->LoadSettings(stRegistry, "HKEY_CURRENT_USER\\Software\\SDxMIK32");
    // port combo
    ccb_port = new TComComboBox(port_label->Owner);
    ccb_port->Parent = port_label->Parent;
    ccb_port->ComPort = cp;
    ccb_port->ComProperty = cpPort;
    ccb_port->Left = port_label->Left + port_label->Width + 2;
    ccb_port->Top  = port_label->Top;
    ccb_port->OnChange = port_change;
    ccb_port->AutoApply=true;
    ccb_port->AutoComplete=true;
    ccb_port->Show();
    // additional settings
    cp->BaudRate                 = br115200;
    cp->DataBits                 = dbEight;
    cp->Parity->Bits             = prNone;
    cp->StopBits                 = sbOneStopBit;
    cp->FlowControl->FlowControl = fcNone;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::port_change(TObject *Sender)
{
    cp->FPort = ccb_port->Text;
    ccb_port->ApplySettings();
    cp->StoreSettings(stRegistry, "HKEY_CURRENT_USER\\Software\\SDxMIK32");
}
//---------------------------------------------------------------------------

void print(char *text)
{
    for(int i = 0; text[i]; i++) if(text[i] == 13 || text[i] == 10) text[i] = ' ';
    Form2->Memo1->Lines->Add(String(text));
}

// ###########################################

void HAL_DelayMs(uint32_t ms);

/*
    #### #### ###
    #    #  #  #
    #### ####  #
       # #     #
    #### #    ###
*/
void DeviceSelect(bool c) { Form2->cp->SetBreak(c); }
void SCLK(bool c)
{
    Form2->cp->SetRTS(!c);
    while ( Form2->cp->Signals().Contains(csDSR) == c ) ;
}
void MOSI(bool c) { Form2->cp->SetDTR(!c); }
bool MISO() { return ! Form2->cp->Signals().Contains(csCTS); }
uint8_t SPI_rw(uint8_t d_wr=255)
{
    uint8_t d_rd = 0;
    for ( uint8_t i = 0; i < 8; i++ )
    {
        MOSI ( (d_wr & (1 << 7)) != 0 ) ;
        SCLK(0); d_rd <<= 1; d_rd |= MISO();
        SCLK(1); d_wr <<= 1;
    }
    MOSI(1);
    return d_rd;
}

// ###########################################

#include "sd_cpp.h"

void HAL_SPI_CS_Enable (SPI_HandleTypeDef* hspi, uint32_t CS_M) { DeviceSelect(true ); }
void HAL_SPI_CS_Disable(SPI_HandleTypeDef* hspi)                { DeviceSelect(false); }
void HAL_SPI_Exchange(SPI_HandleTypeDef* hspi, uint8_t TransmitBytes[], uint8_t ReceiveBytes[], uint32_t Size, uint32_t Timeout)
{
    uint32_t i = 0;
    while ( i < Size )
    {
        ReceiveBytes[i] = SPI_rw(TransmitBytes[i]);
        i++;
    }
}

    long long get_sys_time()
    {
        FILETIME ft; LARGE_INTEGER li;
        GetSystemTimeAsFileTime(&ft);
        // The FILETIME structure is a 64-bit value representing the number of
        // 100-nanosecond intervals since January 1, 1601 (UTC)
        li.LowPart  = ft.dwLowDateTime;
        li.HighPart = ft.dwHighDateTime;
        return li.QuadPart / 10/* in microseconds (µs) */;
    }

void HAL_DelayMs(uint32_t ms)
{
    long long delay = get_sys_time() + ms * 1000/* µs */;
    while(delay - get_sys_time() > 0) ;
}

void __fastcall TForm2::Button1Click(TObject *Sender)
{
    cp->Open();
    main_();
}

//---------------------------------------------------------------------------

