// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WinSockUnit2.pas' rev: 6.00

#ifndef WinSockUnit2HPP
#define WinSockUnit2HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <WinSock.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Winsockunit2
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TPostRoutine)(void *buf, int nb);

class DELPHICLASS TThreadSock;
class DELPHICLASS TwinSockBV;
class PASCALIMPLEMENTATION TwinSockBV : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	int mysock;
	int sockCli;
	int typeSock;
	int mon_port_loc;
	int port_dist;
	sockaddr_in si_receiv;
	sockaddr_in si_sendto;
	sockaddr_in si_cli;
	TThreadSock* thread1;
	
public:
	__fastcall TwinSockBV(void);
	__fastcall ~TwinSockBV(void);
	int __fastcall OpenUdp(int noPort)/* overload */;
	int __fastcall OpenUdp(int noPort, TPostRoutine fPost)/* overload */;
	int __fastcall OpenTcpCli(AnsiString adIp, int noPortDist)/* overload */;
	int __fastcall OpenTcpCli(AnsiString adIp, int noPortDist, int noPortLoc)/* overload */;
	int __fastcall OpenTcpCli(AnsiString adIp, int noPortDist, int noPortLoc, TPostRoutine fPost)/* overload */;
	int __fastcall OpenTcpServ(int noPortLoc)/* overload */;
	int __fastcall OpenTcpServ(int noPortLoc, TPostRoutine fPost)/* overload */;
	int __fastcall Accept_(void);
	int __fastcall Close(void);
	int __fastcall Send_To(void *buf, int nb, AnsiString adIp, int noPortDist);
	int __fastcall Send_(void *buf, int nb);
	int __fastcall Recv_from(void *buf, int &nb)/* overload */;
	int __fastcall Recv_(void *buf, int &nb);
	int __fastcall noSock(void);
	AnsiString __fastcall StrErrMsg(int cr);
public:
	#pragma option push -w-inl
  // la ligne qui suit est a mettre en commentaire
	// /* TObject.Destroy */ inline __fastcall virtual ~TwinSockBV(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TThreadSock : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
private:
	TwinSockBV* pSock;
	sockaddr_in si_cli;
	char buf_in[512];
	int lgRecv;
	
protected:
	virtual void __fastcall Execute(void);
	
public:
	TPostRoutine fFuncRecv;
	__fastcall TThreadSock(TwinSockBV* &pSock_);
public:
	#pragma option push -w-inl
	/* TThread.Destroy */ inline __fastcall virtual ~TThreadSock(void) { }
	#pragma option pop
	
};


typedef TThreadSock* *PThreadSock;

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Winsockunit2 */
using namespace Winsockunit2;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// WinSockUnit2
