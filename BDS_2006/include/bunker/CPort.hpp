// Borland C++ Builder
// Copyright (c) 1995, 2005 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Cport.pas' rev: 10.00

#ifndef CportHPP
#define CportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Sysutils.hpp>	// Pascal unit
#include <Inifiles.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cport
{
//-- type declarations -------------------------------------------------------
typedef AnsiString TPort;

#pragma option push -b-
enum TBaudRate { brCustom, br110, br300, br600, br1200, br2400, br4800, br9600, br14400, br19200, br38400, br56000, br57600, br115200, br128000, br256000 };
#pragma option pop

#pragma option push -b-
enum TStopBits { sbOneStopBit, sbOne5StopBits, sbTwoStopBits };
#pragma option pop

#pragma option push -b-
enum TDataBits { dbFive, dbSix, dbSeven, dbEight };
#pragma option pop

#pragma option push -b-
enum TParityBits { prNone, prOdd, prEven, prMark, prSpace };
#pragma option pop

#pragma option push -b-
enum TDTRFlowControl { dtrDisable, dtrEnable, dtrHandshake };
#pragma option pop

#pragma option push -b-
enum TRTSFlowControl { rtsDisable, rtsEnable, rtsHandshake, rtsToggle };
#pragma option pop

#pragma option push -b-
enum TFlowControl { fcHardware, fcSoftware, fcNone, fcCustom };
#pragma option pop

#pragma option push -b-
enum TComEvent { evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full };
#pragma option pop

typedef Set<TComEvent, evRxChar, evRx80Full>  TComEvents;

#pragma option push -b-
enum TComSignal { csCTS, csDSR, csRing, csRLSD };
#pragma option pop

typedef Set<TComSignal, csCTS, csRLSD>  TComSignals;

#pragma option push -b-
enum TComError { ceFrame, ceRxParity, ceOverrun, ceBreak, ceIO, ceMode, ceRxOver, ceTxFull };
#pragma option pop

typedef Set<TComError, ceFrame, ceTxFull>  TComErrors;

#pragma option push -b-
enum TSyncMethod { smThreadSync, smWindowSync, smNone };
#pragma option pop

#pragma option push -b-
enum TStoreType { stRegistry, stIniFile };
#pragma option pop

#pragma option push -b-
enum TStoredProp { spBasic, spFlowControl, spBuffer, spTimeouts, spParity, spOthers };
#pragma option pop

typedef Set<TStoredProp, spBasic, spOthers>  TStoredProps;

#pragma option push -b-
enum TComLinkEvent { leConn, leCTS, leDSR, leRLSD, leRing, leRx, leTx, leTxEmpty, leRxFlag };
#pragma option pop

typedef void __fastcall (__closure *TRxCharEvent)(System::TObject* Sender, int Count);

typedef void __fastcall (__closure *TRxBufEvent)(System::TObject* Sender, const void *Buffer, int Count);

typedef void __fastcall (__closure *TComErrorEvent)(System::TObject* Sender, TComErrors Errors);

typedef void __fastcall (__closure *TComSignalEvent)(System::TObject* Sender, bool OnOff);

#pragma option push -b-
enum TOperationKind { okWrite, okRead };
#pragma option pop

struct TAsync
{
	
public:
	_OVERLAPPED Overlapped;
	TOperationKind Kind;
	void *Data;
	int Size;
} ;

typedef TAsync *PAsync;

class DELPHICLASS TComLink;
class PASCALIMPLEMENTATION TComLink : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	TComSignalEvent FOnConn;
	TRxBufEvent FOnRxBuf;
	TRxBufEvent FOnTxBuf;
	Classes::TNotifyEvent FOnTxEmpty;
	Classes::TNotifyEvent FOnRxFlag;
	TComSignalEvent FOnCTSChange;
	TComSignalEvent FOnDSRChange;
	TComSignalEvent FOnRLSDChange;
	Classes::TNotifyEvent FOnRing;
	TComSignalEvent FOnTx;
	TComSignalEvent FOnRx;
	
public:
	__property TComSignalEvent OnConn = {read=FOnConn, write=FOnConn};
	__property TRxBufEvent OnRxBuf = {read=FOnRxBuf, write=FOnRxBuf};
	__property TRxBufEvent OnTxBuf = {read=FOnTxBuf, write=FOnTxBuf};
	__property Classes::TNotifyEvent OnTxEmpty = {read=FOnTxEmpty, write=FOnTxEmpty};
	__property Classes::TNotifyEvent OnRxFlag = {read=FOnRxFlag, write=FOnRxFlag};
	__property TComSignalEvent OnCTSChange = {read=FOnCTSChange, write=FOnCTSChange};
	__property TComSignalEvent OnDSRChange = {read=FOnDSRChange, write=FOnDSRChange};
	__property TComSignalEvent OnRLSDChange = {read=FOnRLSDChange, write=FOnRLSDChange};
	__property Classes::TNotifyEvent OnRing = {read=FOnRing, write=FOnRing};
	__property TComSignalEvent OnTx = {read=FOnTx, write=FOnTx};
	__property TComSignalEvent OnRx = {read=FOnRx, write=FOnRx};
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TComLink(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TComLink(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComThread;
class DELPHICLASS TCustomComPort;
class DELPHICLASS TComBuffer;
class PASCALIMPLEMENTATION TComBuffer : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TCustomComPort* FComPort;
	int FInputSize;
	int FOutputSize;
	void __fastcall SetComPort(const TCustomComPort* AComPort);
	void __fastcall SetInputSize(const int Value);
	void __fastcall SetOutputSize(const int Value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	
public:
	__fastcall TComBuffer(void);
	__property TCustomComPort* ComPort = {read=FComPort};
	
__published:
	__property int InputSize = {read=FInputSize, write=SetInputSize, default=1024};
	__property int OutputSize = {read=FOutputSize, write=SetOutputSize, default=1024};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TComBuffer(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComParity;
class PASCALIMPLEMENTATION TComParity : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TCustomComPort* FComPort;
	TParityBits FBits;
	bool FCheck;
	bool FReplace;
	char FReplaceChar;
	void __fastcall SetComPort(const TCustomComPort* AComPort);
	void __fastcall SetBits(const TParityBits Value);
	void __fastcall SetCheck(const bool Value);
	void __fastcall SetReplace(const bool Value);
	void __fastcall SetReplaceChar(const char Value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	
public:
	__fastcall TComParity(void);
	__property TCustomComPort* ComPort = {read=FComPort};
	
__published:
	__property TParityBits Bits = {read=FBits, write=SetBits, nodefault};
	__property bool Check = {read=FCheck, write=SetCheck, default=0};
	__property bool Replace = {read=FReplace, write=SetReplace, default=0};
	__property char ReplaceChar = {read=FReplaceChar, write=SetReplaceChar, default=0};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TComParity(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComTimeouts;
class PASCALIMPLEMENTATION TComTimeouts : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TCustomComPort* FComPort;
	int FReadInterval;
	int FReadTotalM;
	int FReadTotalC;
	int FWriteTotalM;
	int FWriteTotalC;
	void __fastcall SetComPort(const TCustomComPort* AComPort);
	void __fastcall SetReadInterval(const int Value);
	void __fastcall SetReadTotalM(const int Value);
	void __fastcall SetReadTotalC(const int Value);
	void __fastcall SetWriteTotalM(const int Value);
	void __fastcall SetWriteTotalC(const int Value);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	
public:
	__fastcall TComTimeouts(void);
	__property TCustomComPort* ComPort = {read=FComPort};
	
__published:
	__property int ReadInterval = {read=FReadInterval, write=SetReadInterval, default=-1};
	__property int ReadTotalMultiplier = {read=FReadTotalM, write=SetReadTotalM, default=0};
	__property int ReadTotalConstant = {read=FReadTotalC, write=SetReadTotalC, default=0};
	__property int WriteTotalMultiplier = {read=FWriteTotalM, write=SetWriteTotalM, default=100};
	__property int WriteTotalConstant = {read=FWriteTotalC, write=SetWriteTotalC, default=1000};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TComTimeouts(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComFlowControl;
class PASCALIMPLEMENTATION TComFlowControl : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TCustomComPort* FComPort;
	bool FOutCTSFlow;
	bool FOutDSRFlow;
	TDTRFlowControl FControlDTR;
	TRTSFlowControl FControlRTS;
	bool FXonXoffOut;
	bool FXonXoffIn;
	bool FDSRSensitivity;
	bool FTxContinueOnXoff;
	char FXonChar;
	char FXoffChar;
	void __fastcall SetComPort(const TCustomComPort* AComPort);
	void __fastcall SetOutCTSFlow(const bool Value);
	void __fastcall SetOutDSRFlow(const bool Value);
	void __fastcall SetControlDTR(const TDTRFlowControl Value);
	void __fastcall SetControlRTS(const TRTSFlowControl Value);
	void __fastcall SetXonXoffOut(const bool Value);
	void __fastcall SetXonXoffIn(const bool Value);
	void __fastcall SetDSRSensitivity(const bool Value);
	void __fastcall SetTxContinueOnXoff(const bool Value);
	void __fastcall SetXonChar(const char Value);
	void __fastcall SetXoffChar(const char Value);
	void __fastcall SetFlowControl(const TFlowControl Value);
	TFlowControl __fastcall GetFlowControl(void);
	
protected:
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	
public:
	__fastcall TComFlowControl(void);
	__property TCustomComPort* ComPort = {read=FComPort};
	
__published:
	__property TFlowControl FlowControl = {read=GetFlowControl, write=SetFlowControl, stored=false, nodefault};
	__property bool OutCTSFlow = {read=FOutCTSFlow, write=SetOutCTSFlow, nodefault};
	__property bool OutDSRFlow = {read=FOutDSRFlow, write=SetOutDSRFlow, nodefault};
	__property TDTRFlowControl ControlDTR = {read=FControlDTR, write=SetControlDTR, nodefault};
	__property TRTSFlowControl ControlRTS = {read=FControlRTS, write=SetControlRTS, nodefault};
	__property bool XonXoffOut = {read=FXonXoffOut, write=SetXonXoffOut, nodefault};
	__property bool XonXoffIn = {read=FXonXoffIn, write=SetXonXoffIn, nodefault};
	__property bool DSRSensitivity = {read=FDSRSensitivity, write=SetDSRSensitivity, default=0};
	__property bool TxContinueOnXoff = {read=FTxContinueOnXoff, write=SetTxContinueOnXoff, default=0};
	__property char XonChar = {read=FXonChar, write=SetXonChar, default=17};
	__property char XoffChar = {read=FXoffChar, write=SetXoffChar, default=19};
public:
	#pragma option push -w-inl
	/* TPersistent.Destroy */ inline __fastcall virtual ~TComFlowControl(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TCustomComPort : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TComThread* FEventThread;
	bool FThreadCreated;
	unsigned FHandle;
	unsigned FWindow;
	int FUpdateCount;
	Classes::TList* FLinks;
	bool FTriggersOnRxChar;
	Classes::TThreadPriority FEventThreadPriority;
	bool FHasLink;
	bool FConnected;
	TBaudRate FBaudRate;
	int FCustomBaudRate;
	TStopBits FStopBits;
	TDataBits FDataBits;
	bool FDiscardNull;
	char FEventChar;
	TComEvents FEvents;
	TComBuffer* FBuffer;
	TComParity* FParity;
	TComTimeouts* FTimeouts;
	TComFlowControl* FFlowControl;
	TSyncMethod FSyncMethod;
	TStoredProps FStoredProps;
	TRxCharEvent FOnRxChar;
	TRxBufEvent FOnRxBuf;
	Classes::TNotifyEvent FOnTxEmpty;
	Classes::TNotifyEvent FOnBreak;
	Classes::TNotifyEvent FOnRing;
	TComSignalEvent FOnCTSChange;
	TComSignalEvent FOnDSRChange;
	TComSignalEvent FOnRLSDChange;
	TComErrorEvent FOnError;
	Classes::TNotifyEvent FOnRxFlag;
	Classes::TNotifyEvent FOnAfterOpen;
	Classes::TNotifyEvent FOnAfterClose;
	Classes::TNotifyEvent FOnBeforeOpen;
	Classes::TNotifyEvent FOnBeforeClose;
	Classes::TNotifyEvent FOnRx80Full;
	bool __fastcall GetTriggersOnRxChar(void);
	void __fastcall SetTriggersOnRxChar(const bool Value);
	void __fastcall SetConnected(const bool Value);
	void __fastcall SetBaudRate(const TBaudRate Value);
	void __fastcall SetCustomBaudRate(const int Value);
	void __fastcall SetStopBits(const TStopBits Value);
	void __fastcall SetDataBits(const TDataBits Value);
	void __fastcall SetDiscardNull(const bool Value);
	void __fastcall SetEventChar(const char Value);
	void __fastcall SetSyncMethod(const TSyncMethod Value);
	void __fastcall SetEventThreadPriority(const Classes::TThreadPriority Value);
	void __fastcall SetParity(const TComParity* Value);
	void __fastcall SetTimeouts(const TComTimeouts* Value);
	void __fastcall SetBuffer(const TComBuffer* Value);
	void __fastcall SetFlowControl(const TComFlowControl* Value);
	bool __fastcall HasLink(void);
	void __fastcall TxNotifyLink(const void *Buffer, int Count);
	void __fastcall NotifyLink(TComLinkEvent FLinkEvent);
	void __fastcall SendSignalToLink(TComLinkEvent Signal, bool OnOff);
	void __fastcall CheckSignals(bool Open);
	void __fastcall WindowMethod(Messages::TMessage &Message);
	void __fastcall CallAfterOpen(void);
	void __fastcall CallAfterClose(void);
	void __fastcall CallBeforeOpen(void);
	void __fastcall CallBeforeClose(void);
	void __fastcall CallRxChar(void);
	void __fastcall CallTxEmpty(void);
	void __fastcall CallBreak(void);
	void __fastcall CallRing(void);
	void __fastcall CallRxFlag(void);
	void __fastcall CallCTSChange(void);
	void __fastcall CallDSRChange(void);
	void __fastcall CallError(void);
	void __fastcall CallRLSDChange(void);
	void __fastcall CallRx80Full(void);
	
protected:
	virtual void __fastcall Loaded(void);
	DYNAMIC void __fastcall DoAfterClose(void);
	DYNAMIC void __fastcall DoAfterOpen(void);
	DYNAMIC void __fastcall DoBeforeClose(void);
	DYNAMIC void __fastcall DoBeforeOpen(void);
	DYNAMIC void __fastcall DoRxChar(int Count);
	DYNAMIC void __fastcall DoRxBuf(const void *Buffer, int Count);
	DYNAMIC void __fastcall DoTxEmpty(void);
	DYNAMIC void __fastcall DoBreak(void);
	DYNAMIC void __fastcall DoRing(void);
	DYNAMIC void __fastcall DoRxFlag(void);
	DYNAMIC void __fastcall DoCTSChange(bool OnOff);
	DYNAMIC void __fastcall DoDSRChange(bool OnOff);
	DYNAMIC void __fastcall DoError(TComErrors Errors);
	DYNAMIC void __fastcall DoRLSDChange(bool OnOff);
	DYNAMIC void __fastcall DoRx80Full(void);
	virtual void __fastcall StoreRegistry(Registry::TRegistry* Reg);
	virtual void __fastcall StoreIniFile(Inifiles::TIniFile* IniFile);
	virtual void __fastcall LoadRegistry(Registry::TRegistry* Reg);
	virtual void __fastcall LoadIniFile(Inifiles::TIniFile* IniFile);
	virtual void __fastcall CreateHandle(void);
	virtual void __fastcall DestroyHandle(void);
	DYNAMIC void __fastcall ApplyDCB(void);
	DYNAMIC void __fastcall ApplyTimeouts(void);
	DYNAMIC void __fastcall ApplyBuffer(void);
	virtual void __fastcall SetupComPort(void);
	
public:
	AnsiString FPort;
	__fastcall virtual TCustomComPort(Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomComPort(void);
	void __fastcall SetPort(const AnsiString Value);
	void __fastcall BeginUpdate(void);
	void __fastcall EndUpdate(void);
	void __fastcall StoreSettings(TStoreType StoreType, AnsiString StoreTo);
	void __fastcall LoadSettings(TStoreType StoreType, AnsiString LoadFrom);
	void __fastcall Open(void);
	void __fastcall Close(void);
	void __fastcall ShowSetupDialog(void);
	int __fastcall InputCount(void);
	int __fastcall OutputCount(void);
	TComSignals __fastcall Signals(void);
	Windows::TComStateFlags __fastcall StateFlags(void);
	void __fastcall SetDTR(bool OnOff);
	void __fastcall SetRTS(bool OnOff);
	void __fastcall SetXonXoff(bool OnOff);
	void __fastcall SetBreak(bool OnOff);
	void __fastcall ClearBuffer(bool Input, bool Output);
	TComErrors __fastcall LastErrors(void);
	int __fastcall Write(const void *Buffer, int Count);
	int __fastcall WriteStr(const AnsiString Str);
	int __fastcall Read(void *Buffer, int Count);
	int __fastcall ReadStr(AnsiString &Str, int Count);
	int __fastcall WriteAsync(const void *Buffer, int Count, PAsync &AsyncPtr);
	int __fastcall WriteStrAsync(const AnsiString Str, PAsync &AsyncPtr);
	int __fastcall ReadAsync(void *Buffer, int Count, PAsync &AsyncPtr);
	int __fastcall ReadStrAsync(AnsiString &Str, int Count, PAsync &AsyncPtr);
	int __fastcall WaitForAsync(PAsync &AsyncPtr);
	bool __fastcall IsAsyncCompleted(PAsync AsyncPtr);
	void __fastcall WaitForEvent(TComEvents &Events, unsigned StopEvent, int Timeout);
	void __fastcall AbortAllAsync(void);
	void __fastcall TransmitChar(char Ch);
	void __fastcall RegisterLink(TComLink* AComLink);
	void __fastcall UnRegisterLink(TComLink* AComLink);
	__property unsigned Handle = {read=FHandle, nodefault};
	__property bool TriggersOnRxChar = {read=GetTriggersOnRxChar, write=SetTriggersOnRxChar, nodefault};
	__property Classes::TThreadPriority EventThreadPriority = {read=FEventThreadPriority, write=SetEventThreadPriority, nodefault};
	__property TStoredProps StoredProps = {read=FStoredProps, write=FStoredProps, nodefault};
	__property bool Connected = {read=FConnected, write=SetConnected, default=0};
	__property TBaudRate BaudRate = {read=FBaudRate, write=SetBaudRate, nodefault};
	__property int CustomBaudRate = {read=FCustomBaudRate, write=SetCustomBaudRate, nodefault};
	__property AnsiString Port = {read=FPort, write=SetPort};
	__property TComParity* Parity = {read=FParity, write=SetParity};
	__property TStopBits StopBits = {read=FStopBits, write=SetStopBits, nodefault};
	__property TDataBits DataBits = {read=FDataBits, write=SetDataBits, nodefault};
	__property bool DiscardNull = {read=FDiscardNull, write=SetDiscardNull, default=0};
	__property char EventChar = {read=FEventChar, write=SetEventChar, default=0};
	__property TComEvents Events = {read=FEvents, write=FEvents, nodefault};
	__property TComBuffer* Buffer = {read=FBuffer, write=SetBuffer};
	__property TComFlowControl* FlowControl = {read=FFlowControl, write=SetFlowControl};
	__property TComTimeouts* Timeouts = {read=FTimeouts, write=SetTimeouts};
	__property TSyncMethod SyncMethod = {read=FSyncMethod, write=SetSyncMethod, default=0};
	__property Classes::TNotifyEvent OnAfterOpen = {read=FOnAfterOpen, write=FOnAfterOpen};
	__property Classes::TNotifyEvent OnAfterClose = {read=FOnAfterClose, write=FOnAfterClose};
	__property Classes::TNotifyEvent OnBeforeOpen = {read=FOnBeforeOpen, write=FOnBeforeOpen};
	__property Classes::TNotifyEvent OnBeforeClose = {read=FOnBeforeClose, write=FOnBeforeClose};
	__property TRxCharEvent OnRxChar = {read=FOnRxChar, write=FOnRxChar};
	__property TRxBufEvent OnRxBuf = {read=FOnRxBuf, write=FOnRxBuf};
	__property Classes::TNotifyEvent OnTxEmpty = {read=FOnTxEmpty, write=FOnTxEmpty};
	__property Classes::TNotifyEvent OnBreak = {read=FOnBreak, write=FOnBreak};
	__property Classes::TNotifyEvent OnRing = {read=FOnRing, write=FOnRing};
	__property TComSignalEvent OnCTSChange = {read=FOnCTSChange, write=FOnCTSChange};
	__property TComSignalEvent OnDSRChange = {read=FOnDSRChange, write=FOnDSRChange};
	__property TComSignalEvent OnRLSDChange = {read=FOnRLSDChange, write=FOnRLSDChange};
	__property Classes::TNotifyEvent OnRxFlag = {read=FOnRxFlag, write=FOnRxFlag};
	__property TComErrorEvent OnError = {read=FOnError, write=FOnError};
	__property Classes::TNotifyEvent OnRx80Full = {read=FOnRx80Full, write=FOnRx80Full};
};


class PASCALIMPLEMENTATION TComThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	TCustomComPort* FComPort;
	unsigned FStopEvent;
	TComEvents FEvents;
	
protected:
	void __fastcall DispatchComMsg(void);
	void __fastcall DoEvents(void);
	virtual void __fastcall Execute(void);
	void __fastcall SendEvents(void);
	void __fastcall Stop(void);
	
public:
	__fastcall TComThread(TCustomComPort* AComPort);
	__fastcall virtual ~TComThread(void);
};


class DELPHICLASS TComPort;
class PASCALIMPLEMENTATION TComPort : public TCustomComPort 
{
	typedef TCustomComPort inherited;
	
__published:
	__property Connected  = {default=0};
	__property BaudRate ;
	__property Port ;
	__property Parity ;
	__property StopBits ;
	__property DataBits ;
	__property DiscardNull  = {default=0};
	__property EventChar  = {default=0};
	__property Events ;
	__property Buffer ;
	__property FlowControl ;
	__property Timeouts ;
	__property SyncMethod  = {default=0};
	__property OnAfterOpen ;
	__property OnAfterClose ;
	__property OnBeforeOpen ;
	__property OnBeforeClose ;
	__property OnRxChar ;
	__property OnRxBuf ;
	__property OnTxEmpty ;
	__property OnBreak ;
	__property OnRing ;
	__property OnCTSChange ;
	__property OnDSRChange ;
	__property OnRLSDChange ;
	__property OnRxFlag ;
	__property OnError ;
	__property OnRx80Full ;
public:
	#pragma option push -w-inl
	/* TCustomComPort.Create */ inline __fastcall virtual TComPort(Classes::TComponent* AOwner) : TCustomComPort(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomComPort.Destroy */ inline __fastcall virtual ~TComPort(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TComStrEvent)(System::TObject* Sender, const AnsiString Str);

typedef void __fastcall (__closure *TCustPacketEvent)(System::TObject* Sender, const AnsiString Str, int &Pos);

class DELPHICLASS TComDataPacket;
class PASCALIMPLEMENTATION TComDataPacket : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	TComLink* FComLink;
	TCustomComPort* FComPort;
	AnsiString FStartString;
	AnsiString FStopString;
	int FMaxBufferSize;
	int FSize;
	bool FIncludeStrings;
	bool FCaseInsensitive;
	bool FInPacket;
	AnsiString FBuffer;
	TComStrEvent FOnPacket;
	TComStrEvent FOnDiscard;
	TCustPacketEvent FOnCustomStart;
	TCustPacketEvent FOnCustomStop;
	void __fastcall SetComPort(const TCustomComPort* Value);
	void __fastcall SetCaseInsensitive(const bool Value);
	void __fastcall SetSize(const int Value);
	void __fastcall SetStartString(const AnsiString Value);
	void __fastcall SetStopString(const AnsiString Value);
	void __fastcall RxBuf(System::TObject* Sender, const void *Buffer, int Count);
	void __fastcall CheckIncludeStrings(AnsiString &Str);
	AnsiString __fastcall Upper(const AnsiString Str);
	void __fastcall EmptyBuffer(void);
	bool __fastcall ValidStop(void);
	
protected:
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	DYNAMIC void __fastcall DoDiscard(const AnsiString Str);
	DYNAMIC void __fastcall DoPacket(const AnsiString Str);
	DYNAMIC void __fastcall DoCustomStart(const AnsiString Str, int &Pos);
	DYNAMIC void __fastcall DoCustomStop(const AnsiString Str, int &Pos);
	virtual void __fastcall HandleBuffer(void);
	__property AnsiString Buffer = {read=FBuffer, write=FBuffer};
	
public:
	__fastcall virtual TComDataPacket(Classes::TComponent* AOwner);
	__fastcall virtual ~TComDataPacket(void);
	void __fastcall AddData(const AnsiString Str);
	
__published:
	__property TCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property bool CaseInsensitive = {read=FCaseInsensitive, write=SetCaseInsensitive, default=0};
	__property bool IncludeStrings = {read=FIncludeStrings, write=FIncludeStrings, default=0};
	__property int MaxBufferSize = {read=FMaxBufferSize, write=FMaxBufferSize, default=1024};
	__property AnsiString StartString = {read=FStartString, write=SetStartString};
	__property AnsiString StopString = {read=FStopString, write=SetStopString};
	__property int Size = {read=FSize, write=SetSize, default=0};
	__property TComStrEvent OnDiscard = {read=FOnDiscard, write=FOnDiscard};
	__property TComStrEvent OnPacket = {read=FOnPacket, write=FOnPacket};
	__property TCustPacketEvent OnCustomStart = {read=FOnCustomStart, write=FOnCustomStart};
	__property TCustPacketEvent OnCustomStop = {read=FOnCustomStop, write=FOnCustomStop};
};


class DELPHICLASS TComStream;
class PASCALIMPLEMENTATION TComStream : public Classes::TStream 
{
	typedef Classes::TStream inherited;
	
private:
	TCustomComPort* FComPort;
	
public:
	__fastcall TComStream(TCustomComPort* AComPort);
	virtual int __fastcall Read(void *Buffer, int Count);
	virtual int __fastcall Write(const void *Buffer, int Count);
	virtual int __fastcall Seek(int Offset, Word Origin)/* overload */;
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TComStream(void) { }
	#pragma option pop
	
	
/* Hoisted overloads: */
	
public:
	inline __int64 __fastcall  Seek(const __int64 Offset, Classes::TSeekOrigin Origin){ return TStream::Seek(Offset, Origin); }
	
};


class DELPHICLASS EComPort;
class PASCALIMPLEMENTATION EComPort : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
private:
	int FWinCode;
	int FCode;
	
public:
	__fastcall EComPort(int ACode, int AWinCode);
	__fastcall EComPort(int ACode);
	__property int WinCode = {read=FWinCode, write=FWinCode, nodefault};
	__property int Code = {read=FCode, write=FCode, nodefault};
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EComPort(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
//	/* Exception.CreateRes */ inline __fastcall EComPort(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EComPort(int Ident, System::TVarRec const * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EComPort(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EComPort(const AnsiString Msg, System::TVarRec const * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
//	/* Exception.CreateResHelp */ inline __fastcall EComPort(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EComPort(System::PResStringRec ResStringRec, System::TVarRec const * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EComPort(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
static const int WaitInfinite = -1;
static const Shortint CError_OpenFailed = 0x1;
static const Shortint CError_WriteFailed = 0x2;
static const Shortint CError_ReadFailed = 0x3;
static const Shortint CError_InvalidAsync = 0x4;
static const Shortint CError_PurgeFailed = 0x5;
static const Shortint CError_AsyncCheck = 0x6;
static const Shortint CError_SetStateFailed = 0x7;
static const Shortint CError_TimeoutsFailed = 0x8;
static const Shortint CError_SetupComFailed = 0x9;
static const Shortint CError_ClearComFailed = 0xa;
static const Shortint CError_ModemStatFailed = 0xb;
static const Shortint CError_EscapeComFailed = 0xc;
static const Shortint CError_TransmitFailed = 0xd;
static const Shortint CError_ConnChangeProp = 0xe;
static const Shortint CError_EnumPortsFailed = 0xf;
static const Shortint CError_StoreFailed = 0x10;
static const Shortint CError_LoadFailed = 0x11;
static const Shortint CError_RegFailed = 0x12;
static const Shortint CError_LedStateFailed = 0x13;
static const Shortint CError_ThreadCreated = 0x14;
static const Shortint CError_WaitFailed = 0x15;
static const Shortint CError_HasLink = 0x16;
static const Shortint CError_RegError = 0x17;
extern PACKAGE void __fastcall InitAsync(PAsync &AsyncPtr);
extern PACKAGE void __fastcall DoneAsync(PAsync &AsyncPtr);
extern PACKAGE void __fastcall EnumComPorts(Classes::TStrings* Ports);
extern PACKAGE TBaudRate __fastcall StrToBaudRate(AnsiString Str);
extern PACKAGE TStopBits __fastcall StrToStopBits(AnsiString Str);
extern PACKAGE TDataBits __fastcall StrToDataBits(AnsiString Str);
extern PACKAGE TParityBits __fastcall StrToParity(AnsiString Str);
extern PACKAGE TFlowControl __fastcall StrToFlowControl(AnsiString Str);
extern PACKAGE AnsiString __fastcall BaudRateToStr(TBaudRate BaudRate);
extern PACKAGE AnsiString __fastcall StopBitsToStr(TStopBits StopBits);
extern PACKAGE AnsiString __fastcall DataBitsToStr(TDataBits DataBits);
extern PACKAGE AnsiString __fastcall ParityToStr(TParityBits Parity);
extern PACKAGE AnsiString __fastcall FlowControlToStr(TFlowControl FlowControl);

}	/* namespace Cport */
using namespace Cport;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Cport
