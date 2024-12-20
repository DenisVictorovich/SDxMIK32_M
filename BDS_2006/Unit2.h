//---------------------------------------------------------------------------
#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include ".\include\bunker\CPort.hpp"
#include ".\include\digtyp.h"
#include <CPortCtl.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published: // IDE-managed Components
    TGroupBox *GroupBox1;
    TStaticText *port_label;
    TMemo *Memo1;
    TButton *Button1;
    void __fastcall Button1Click(TObject *Sender);
private: // User declarations
public:  // User declarations
    TCustomComPort  *cp;
    TComComboBox    *ccb_port;
    __fastcall TForm2(TComponent* Owner);
    void __fastcall port_change(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
