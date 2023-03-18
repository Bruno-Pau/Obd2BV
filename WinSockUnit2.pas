unit WinSockUnit2;
//---------------------------------------------------------------------------
//    Utilisation des Win Sockets:
//
//    Permet de communiquer en UDP ou en TCP
//    Dans le cas du TCP: option client ou serveur
//
//    Version avec Thread sur reception
//
//    Appel de
//       - WSAStartup()
//       - socket()       UDP ou TCP
//       - bind ()        UDP
//       - recvfrom()     UDP ou TCP
//       - sendto()       UDP ou TCP
//       - recv()         TCP
//       - send()         TCP
//       - closesocket()  UDP ou TCP
//                                                    B.Vannier dec 2011
//---------------------------------------------------------------------------
interface

uses
  WinSock, SysUtils, StdCtrls, Classes;

type
  // Format de la procedure a declarer dans votre unité
  // Cette procédure dont l'adresse est passée en paramètre lors de l'ouverture
  // du socket sera appelé à chaque réception de données
  //
  // procedure OnRecvFrom(var buf; nb: integer); // declaration
  //
  // Ouverture socket:
  //	cr := sock.OpenUdp(portLoc, OnRecvFrom);  
  //
  TPostRoutine = procedure (var buf; nb: integer) of object; // pour Pointer sur Post-routine

  TwinSockBV = class;         // cette classe est déclarée plus bas
  //PTwinSockBV = ^TwinSockBV;
//------------------------------------------------------------------------------
// TThreadSock : Thread de reception
//------------------------------------------------------------------------------
  TThreadSock = class(TThread)
  private
    pSock : TwinSockBV;     // lien vers l'objet propriétaire
    //sockCli : TSocket;    // le socket client si le socket pricipal est serveur
    si_cli : TSockAddrIn;   // si le socket pricipal est serveur
    buf_in: array[0..511] of char;   // buffer de reception
    lgRecv : integer;                // taille du dernier message reçu
  protected
    procedure Execute; override;
  public
    fFuncRecv : TPostRoutine; // Post-routine a lancer sur reception
    constructor Create(var pSock_ : TwinSockBV);
  end;

  PThreadSock = ^TThreadSock;

//------------------------------------------------------------------------------
// TwinSockBV
//------------------------------------------------------------------------------
  TwinSockBV = class

  private
    mysock : TSocket;     // le socket principal
    sockCli : TSocket;    // le socket client si le socket pricipal est serveur
    typeSock : integer;   // 0: non ouvert: 1: UDP; 2: client TCP; 3 : serveur TCP
    mon_port_loc, port_dist : integer; // no de ports reception
    si_receiv, si_sendto, si_cli : TSockAddrIn;
    thread1 : TThreadSock;
//---------------------------

  public
    constructor Create();
    destructor Destruct;
    function OpenUdp(noPort: integer):integer;  overload;
    function OpenUdp(noPort: integer; fPost : TPostRoutine):integer;  overload;
    function OpenTcpCli(adIp: string; noPortDist: integer):integer;  overload;
    function OpenTcpCli(adIp: string; noPortDist: integer; noPortLoc: integer):integer;  overload;
    function OpenTcpCli(adIp: string; noPortDist: integer; noPortLoc: integer; fPost : TPostRoutine):integer;  overload;
    function OpenTcpServ(noPortLoc: integer):integer;   overload;
    function OpenTcpServ(noPortLoc: integer; fPost : TPostRoutine):integer;  overload;
    function Accept_():integer;
    function Close():integer;
    function Send_To(var buf; nb: Longint; adIp: string; noPortDist: integer):integer;
    function Send_(var buf; nb: integer):integer;
    function Recv_from(var buf ; var nb: integer):integer; overload;
    function Recv_(var buf ; var nb: integer):integer;
    function noSock(): integer;
    function StrErrMsg(cr : integer): string;
  end;
//------------------------------------------------------------------------------

implementation
//------------------------------------------------------------------------------
//  TThreadSock.Create
//------------------------------------------------------------------------------
constructor TThreadSock.Create(var pSock_ : TwinSockBV);
begin
  pSock := pSock_;
  inherited Create(false);
end;
//------------------------------------------------------------------------------
//  TThreadSock.Execute
//------------------------------------------------------------------------------
procedure TThreadSock.Execute;
var saLen : integer;
begin
  // si TCP Serveur seulement, attente sur accept
  saLen := sizeof(si_cli);
  if pSock.typeSock = 3 then begin
    pSock.sockCli := accept(pSock.mysock, addr(si_cli), addr(saLen));
    if pSock.sockCli = INVALID_SOCKET then  begin
      lgRecv := -15;
      exit
    end
    else lgRecv := 0;
  end;

  repeat
    saLen := sizeof(pSock.si_receiv);
    case pSock.typeSock of
      1: lgRecv := recvfrom( pSock.mySock, buf_in, 511, 0, pSock.si_receiv, saLen );

      2: lgRecv := recv( pSock.mysock , buf_in, 511, 0 );

      3: lgRecv := recv( pSock.sockCli , buf_in, 511, 0 );
    end;

    if Assigned(fFuncRecv) then
      fFuncRecv(buf_in, lgRecv);  // appel de la Post Routine dans Form1

    // si Erreur -1 : fermeture socket...
    if lgRecv = -1 then begin
      if pSock.typeSock = 3 then closesocket(pSock.sockCli);
      closesocket(pSock.mysock);
      pSock.mysock := 0;
      pSock.typeSock := 0;
      Terminate;          // et terminer ce thread...
    end;
  until (terminated);
end;

//------------------------------------------------------------------------------
// TwinSockBV
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//  Create()
//------------------------------------------------------------------------------
constructor TwinSockBV.Create();
var cr : integer;
    wsaData1 : TWSAData;
begin
  mysock := 0;
  typeSock := 0;
  cr := WSAStartup($202, wsaData1); // Charger Winsock version 2.2
end;
//------------------------------------------------------------------------------
//  Destruct : Ce destructeur ferme le socket
//------------------------------------------------------------------------------
destructor TwinSockBV.Destruct;
begin
  if (mysock <> 0) then begin
     closesocket(mysock);     // fermeture socket
  end;
end;

//------------------------------------------------------------------------------
// OpenUDP()
//------------------------------------------------------------------------------
function TwinSockBV.OpenUdp(noPort: integer):integer;
var fPost_ : TPostRoutine;
begin
  fPost_ := nil;
  OpenUdp := OpenUdp(noPort, fPost_);
end;

function TwinSockBV.OpenUdp(noPort: integer; fPost : TPostRoutine):integer;
var
   cr: integer;
begin
  mysock := socket( AF_INET, SOCK_DGRAM, PF_UNSPEC );
  if mysock = INVALID_SOCKET then begin
    OpenUdp := -2;
    exit;
  end else begin
    typeSock := 1;
  end;

  // Bind our port number
  mon_port_loc := noPort;

	si_receiv.sin_family      := AF_INET;
	si_receiv.sin_addr.s_addr := htonl(INADDR_ANY);    // INADDR_ANY : de toute adresse
	si_receiv.sin_port        := htons(mon_port_loc);  // n° de port spécifié

	cr := bind ( mysock, TSOCKADDR (si_receiv), sizeof (si_receiv) );
	if cr = SOCKET_ERROR then OpenUdp := -12
  else begin
    OpenUdp := 0;
    thread1 := TThreadSock.Create(self); // creation du thread sur reception
    thread1.fFuncRecv := fPost;
  end;

end;
//------------------------------------------------------------------------------
// OpenTcpCli()
//------------------------------------------------------------------------------
function TwinSockBV.OpenTcpCli(adIp: string; noPortDist: integer):integer;

begin
  OpenTcpCli := OpenTcpCli(adIp, noPortDist, 0);
end;
//------------------------------------------------------------------------------
// OpenTcpCli()
//------------------------------------------------------------------------------
function TwinSockBV.OpenTcpCli(adIp: string; noPortDist: integer; noPortLoc: integer; fPost : TPostRoutine):integer;
var cr: integer;
begin
  cr := OpenTcpCli(adIp, noPortDist, noPortLoc);
  if cr = 0 then begin
    thread1 := TThreadSock.Create(self); // creation du thread sur reception
    thread1.fFuncRecv := fPost;
    typeSock := 2;
  end;
  Result := cr;
end;
//------------------------------------------------------------------------------
// OpenTcpCli()
//------------------------------------------------------------------------------
function TwinSockBV.OpenTcpCli(adIp: string; noPortDist: integer; noPortLoc: integer):integer;

var szAd : array[0..100] of char;
    cr: integer;
begin
  mysock := socket( AF_INET, SOCK_STREAM, PF_UNSPEC );

  if mysock = INVALID_SOCKET then  begin
    OpenTcpCli := -3;
    exit;
  end;
  typeSock := 2;

  // Bind our port number
  mon_port_loc := noPortLoc;

	si_receiv.sin_family      := AF_INET;
	si_receiv.sin_addr.s_addr := htonl(INADDR_ANY);    // INADDR_ANY : de toute adresse
	si_receiv.sin_port        := htons(mon_port_loc);  // n° de port spécifié

	cr := bind ( mysock, TSOCKADDR (si_receiv), sizeof (si_receiv) );
	if cr = SOCKET_ERROR then begin
    OpenTcpCli := -12;
    exit;
  end;

  StrPCopy(addr(szAd), adIp);  // recopie la chaine d'adresse IP
  // preparation champ d'adresse distante
  si_sendto.sin_family      := AF_INET;
  si_sendto.sin_addr.s_addr := inet_addr(szAd);
  si_sendto.sin_port        := htons(noPortDist);  //  ordre des bytes au standard TCP/IP

  // connect to the server
  cr := connect(mysock, si_sendto, sizeof(si_sendto));
  if cr = SOCKET_ERROR then  OpenTcpCli := -13
  else OpenTcpCli := 0;
end;
//------------------------------------------------------------------------------
//  Close()
//------------------------------------------------------------------------------
function TwinSockBV.Close():integer;
begin
  closesocket(mysock);
  mysock := 0;
  typeSock := 0;
  Close := 0;
  if thread1 <> nil then thread1.Terminate;
end;
//------------------------------------------------------------------------------
// OpenTcpServ()
//------------------------------------------------------------------------------
function TwinSockBV.OpenTcpServ(noPortLoc: integer; fPost:TPostRoutine):integer;
var cr: integer;
begin
  cr := OpenTcpServ(noPortLoc);
  if cr = 0 then begin
    thread1 := TThreadSock.Create(self); // creation du thread sur reception
    thread1.fFuncRecv := fPost;
    typeSock := 3;
  end;
  OpenTcpServ := cr;
end;
//------------------------------------------------------------------------------
// OpenTcpServ()
//------------------------------------------------------------------------------
function TwinSockBV.OpenTcpServ(noPortLoc: integer):integer;
var cr: integer;
begin
  mysock := socket( AF_INET, SOCK_STREAM, PF_UNSPEC );

  if mysock = INVALID_SOCKET then  begin
    OpenTcpServ := -3;
    exit;
  end;
  typeSock := 3;

  // Bind our port number
  mon_port_loc := noPortLoc;

	si_receiv.sin_family      := AF_INET;
	si_receiv.sin_addr.s_addr := INADDR_ANY;    // INADDR_ANY : de toute adresse
	si_receiv.sin_port        := htons(mon_port_loc);  // n° de port spécifié

	cr := bind ( mysock, TSOCKADDR (si_receiv), sizeof (si_receiv) );
	if cr = SOCKET_ERROR then begin
    OpenTcpServ := -12;
    exit;
  end;

  // prepare the connexion
  cr := listen(mysock, 1); //  nombre de connexions attendues : 1
  if cr = SOCKET_ERROR then  OpenTcpServ := -14
  else OpenTcpServ := 0;
end;

//------------------------------------------------------------------------------
// Accept_()
//------------------------------------------------------------------------------
function TwinSockBV.Accept_():integer;
var saLen : integer;
begin
  saLen := sizeof(si_cli);
  sockCli := accept(mysock, addr(si_cli), addr(saLen));
  if sockCli = INVALID_SOCKET then  Accept_ := -15
  else Accept_ := 0;
end;
//------------------------------------------------------------------------------
// Send_()
//------------------------------------------------------------------------------
function TwinSockBV.Send_(var buf; nb: integer):integer;
var cr : integer;
begin
  if typeSock < 2 then begin   // impossible en UDP
    Send_ := -32;
    exit;
  end;
  if typeSock = 3 then cr := send(sockCli, buf, nb,0)
  else cr := send(mysock, buf, nb,0);
  if cr = SOCKET_ERROR then Send_ := -31
  else Send_ := cr;
end;

//------------------------------------------------------------------------------
//  Send_To()
//------------------------------------------------------------------------------
function TwinSockBV.Send_To(var buf; nb: integer; adIp: string; noPortDist: integer):integer;
var szad : array[0..100] of char;
    cr : integer;
begin
  StrPCopy(addr(szad), adIp);  // recopie la chaine d'adresse IP
  // Fill in the server's address
	si_sendto.sin_family      := AF_INET;
  si_sendto.sin_addr.s_addr := inet_addr(szad);
	si_sendto.sin_port        := htons(noPortDist);
  // Send it to the server
  if typeSock = 3 then cr := sendto(sockCli, buf, nb, 0, si_sendto, sizeof(si_sendto) )
  else cr := sendto(mysock, buf, nb, 0, si_sendto, sizeof(si_sendto) );
  if cr = SOCKET_ERROR then Send_to := -30
  else Send_to := cr;
end;

//------------------------------------------------------------------------------
//  Recv_from()    Ne pas appeler si Post-Routine
//------------------------------------------------------------------------------
function TwinSockBV.Recv_from(var buf ; var nb: integer):integer;
var cr, saLen : integer;
begin
  saLen := sizeof(si_receiv);
  if typeSock = 3 then cr := recvfrom( sockCli, buf, nb, 0,si_receiv, saLen )
  else cr := recvfrom( mysock, buf, nb, 0,si_receiv, saLen );
  if cr < 0 then Recv_from := -20
  else Recv_from := cr;
end;
//------------------------------------------------------------------------------
//  Recv_()       Ne pas appeler si Post-Routine
//------------------------------------------------------------------------------
function TwinSockBV.Recv_(var buf; var nb: integer):integer;
var cr : integer;
begin
  if typeSock < 2 then begin  // impossible en UDP
    Recv_ := -22;
    exit;
  end;
  if typeSock = 3 then cr := recv( sockCli, buf, nb, 0 )
  else cr := recv( mysock, buf, nb, 0 );
  if cr < 0 then Recv_ := -21
  else Recv_ := cr;
end;
//------------------------------------------------------------------------------
// noSock()
//------------------------------------------------------------------------------
function TwinSockBV.noSock(): integer;
begin
  noSock := mySock;
end;
//------------------------------------------------------------------------------
//   StrErrMsg() : renvoi un string correspondant au no d'erreur cr
//------------------------------------------------------------------------------
function TwinSockBV.StrErrMsg(cr : integer): string;
begin
  case cr of
  -1 : StrErrMsg := 'Erreur -1: fermeture Socket ';
  -2 : StrErrMsg := 'Erreur création socket UDP';
  -3 : StrErrMsg := 'Erreur création socket TCP';
  -12 : StrErrMsg := 'Erreur bind() ';
  -13 : StrErrMsg := 'Erreur connect() ';
  -14 : StrErrMsg := 'Erreur listen() ';
  -15 : StrErrMsg := 'Erreur accept() ';
  -20 : StrErrMsg := 'Erreur RecvFrom()';
  -21 : StrErrMsg := 'Erreur Recv()';
  -22 : StrErrMsg := 'Erreur Recv(): appel impossible en UDP';
  -30 : StrErrMsg := 'Erreur sendto()';
  -31 : StrErrMsg := 'Erreur send()';
  -32 : StrErrMsg := 'Erreur send(): appel impossible en UDP';
  end;
end;
end.
 