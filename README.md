# SDxMIK32_M
Переделка библиотеки *github.com/Barsy-Barsevich/SDxMIK32* в стиле ООП (C++) | 
Изначально, настоящая библиотека доступа к данным SD-карты для микроконтроллеров без SDIO была разработана на языке C. | 
Организованы отдельные классы для файловой системы (*MIK32FAT*) и для взаимодействия с SD-картой через одноразрядный SPI (*MIK32_SPI_SD*) | 
Все необходимые макроопределения, переменные и функции (методы) сейчас помещены в соответствующие классы и не валяются отдельно. | 
В качестве руководства пользования можно использовать *INI_README.md* (Barsy-Barsevich) | 
Испытание данной версии библиотеки проводилось посредством Borland Developer Studio 2006 и микросхемы FT232RL, непосредственно подключенной к отформатированной (FAT32) SD-карте на 8Гб.
```cpp
/*
    #### #### ###
    #    #  #  #
    #### ####  #
       # #     #
    #### #    ###

    TXD (FT232RL . #1) ---------------------------> ~DS  (micro-SD . #2)
    DTR (FT232RL . #2) ---------------------------> MOSI (micro-SD . #3)
    RTS (FT232RL . #3) ---> DSR (FT232RL . #9) ---> SCLK (micro-SD . #5)
    CTS (FT232RL . #11) --------------------------> MISO (micro-SD . #7)
*/
    #define  FT232RL  Form2->cp
    void DeviceSelect(bool c) { FT232RL->SetBreak(c); }
    void SCLK(bool c)
    {
        FT232RL->SetRTS(!c);
        while ( FT232RL->Signals().Contains(csDSR) == c ) ;
    }
    void MOSI(bool c) { FT232RL->SetDTR(!c); }
    bool MISO() { return ! FT232RL->Signals().Contains(csCTS); }
```
