//---------------------------------------------------------------------------

#ifndef Obd2_v2_0H
#define Obd2_v2_0H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>

#include <mem.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "ListePorts.h"
#include <Mask.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ScktComp.hpp>
#include <vector>
#include <algorithm>

#include "WinSockUnit2.hpp"
#include "PidListCode.h"  // Intitulés des codes PID
#include "default_list.h"
#include <Dialogs.hpp>  // Intitulés des codes Défauts
#include <ShellApi.h>

#include <shlobj.h>  // pour appel SHGetPathFromIDList

#define SD_RECEIVE      0x00   // Winsock2.h
#define SD_SEND         0x01
#define SD_BOTH         0x02

REG Reg;

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
//---------------------------------------------------------------------------
// PID : classe premettant de répertorier les PID supportés
//---------------------------------------------------------------------------
class PID
{
private:
  uchar Tab[10][32];     // [10]: le nb de modes ;[32] PID supportés (32x8=256)
  uchar hexToBin(char car) {
    if ( car <= '9' ) return (car & 15);
    return (car - 'A' + 10);
  }
public:
  PID(){ init(); }                 // constructeur
  void init(){ setmem(Tab, sizeof(Tab), 0); }

  int set(int mode, int groupe, char *chaine){  // initialise les PID valides à partir de chaine "BE3EB811"
    if ((groupe > 9) || (groupe < 1)) return(-2); // no du groupe de PID (1 à 9 / PID 1 à 256)
    int ofset = (groupe-1) << 2;
    int lg = strlen(chaine), i=0;
    setmem(&Tab[mode-1][ofset], 4, 0);  // RAZ anciennes valeurs
    for (i=0; (i<8) && (i<lg); i++) {
      if ((mode < 1) || (mode > 10)) return(-2);
      if ( (chaine[i]<'0') || (chaine[i] >'F') ||( (chaine[i]>'9' ) && (chaine[i]<'A' ) ) ) return(-1);
      if ( i & 1 ) Tab[mode-1][ofset + (i>>1)] |= hexToBin(chaine[i]);    // i impaire
      else Tab[mode-1][ofset + (i>>1)] |= hexToBin(chaine[i]) <<4;    // i paire : poids forts
    }
    return(i);
  }
  bool supporte(int mode, int noPid) { // le PID noPid est il supporté en mode mode ?
    return ( ( Tab[mode-1][(noPid-1) >> 3] >> ( 7-((noPid-1) & 7 ) ) ) & 1) ;
  }
  int nbPid(int mode) { // retourne le nombre de PID dans le mode
    int nb=0;
    for (int i=0; i<32; i++){
      for (int j=0; j<8; j++) {
        if ( ( (Tab[mode-1][i] >> j) & 1) != 0) ++nb;
      }
    }
    return(nb);
  }
};
//---------------------------------------------------------------------------
// MODE: table des modes  -1:non testé 0:invalide 1:Valide
//---------------------------------------------------------------------------
class MODE
{
public:
  MODE(){ init(); }                 // constructeur
  void init(){ setmem(Tab, sizeof(Tab), -1); }
  void set(int mode, char val) { Tab[mode] = val; }
  int test(int mode){ return Tab[mode];}
private:
  char Tab[15]; // table des modes: -1:non testé 0:invalide 1:Valide
};
//---------------------------------------------------------------------------
//  TREPONSE : classe analysant les réponses à une requète
//---------------------------------------------------------------------------
class TREPONSE{
  public:
    int typeRep;    // 0:? , 1:int, 3: Volts, 4: temp, 17:chaine
    int noReq;
    int val;        // valeur entière s'il a été possible de la décoder
    bool repondu;
    char sz1[100];  // chaine réponse sans entète
    char szRep[10][8]; // tableau des réponses
    char sz2[100];  // information éventuellement décodée (VIN, CAL, ...)
    TREPONSE() { init(); }
    void init() {
      typeRep=0; noReq=0; val=0; sz1[0]=0; sz2[0]=0; repondu=false;
      for (int i=0; i<10; i++) szRep[i][0] = 0;
    }
    int analyse1(int noReq_, char *bufRec, int nbr, int cr1, bool headers); // retour entier
    int analyse17(int noReq_, char *bufRec, int nbr, int cr1);// retour chaine
} ;
//---------------------------------------------------------------------------
//  TREQ : utilisé pour le classement des requètes en simulation
//---------------------------------------------------------------------------
class TREQ {  //
  public:
    int no_, nbR, codePID, sousPID;
    bool HeadersOn;       // si les entètes sont activées dans trames retour
    char question[20];    // la requète envoyé à l'ELM
    char reponse[10][150]; // les réponses de l'ELM à cette requète
    int cr[10];           // les codes réponses qui avaient été détectés
    TREQ(int no, char *pQuest) {
      no_ = no; nbR = 0; codePID = 0; sousPID=0; HeadersOn = false;
      strcpy (question, pQuest);
      for (int i=0; i<10; i++) {reponse[i][0]=0; cr[i]=0;}
    }
};
//---------------------------------------------------------------------------
#define TAILLEBUF 512   // nb de car max recu dans ReadFile
//---------------------------------------------------------------------------
#define MAXREQ  10  // nb
char reqElm[MAXREQ][20] = {
  "ATZ\r",        // 0  Reset ALL
  "ATRV\r",         // 1  Read the Voltage
  "ATE0\r",         // 2  Echo OFF
  "ATL0\r",         // 3  Line Feed OFF
  "ATS0\r",         // 4  Space OFF
  "ATSP0\r",        // 5  Set Protocol 0
  "ATH1\r",         // 6  Set Headers ON
  "ATDPN\r",        // 7  Describe the current protocol by nb
  "0100\r",         // 8  Mode 1 PID 0 : Liste PID
  "ATH0\r"          // 9  Set Headers OFF
};
#define MAXDIAG1  11  // nb
char szItemDiag1[MAXDIAG1][40] = {
  "Raté d'allumage",
  "Circuit de carburant",
  "Composant",
  "Catalytique",
  "Catalytique chauffé",
  "Circuit d'évaporation",
  "Circuit secondaire d'air",
  "Refrigerant de climatisation",
  "Sonde a oxygène",
  "Sonde a oxygene chauffée",
  "Circuit EGR"
};

//---------------------------------------------------------------------------
// TthreadListeRequete : lance une série de requètes et traite la réponse
//---------------------------------------------------------------------------
class TthreadListeRequete : public TThread
{
private:
    HANDLE Hport;
    AnsiString szPort;
    int typeListe;
protected:
    void __fastcall Execute();
public:
    __fastcall TthreadListeRequete(bool CreateSuspended, int typeListe_);
};
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// Composants gérés par l'EDI
  TMainMenu *MainMenu1;
  TMenuItem *Fichier_;
  TMenuItem *Quitter_;
  TPageControl *PageControl1;
  TTabSheet *TabConnexion;
  TTabSheet *TabDiag1;
  TTabSheet *TabDiag2;
  TTabSheet *TabPID;
  TLabel *Label1;
  TMemo *Memo1;
  TGroupBox *GroupBox1;
  TRadioButton *R9600;
  TRadioButton *R38400;
  TRadioButton *R115200;
  TButton *BConnect;
  TButton *BDeConnect;
  TStatusBar *StatusBar1;
  TEdit *Edit2;
  TLabel *Label2;
  TComboBox *ComboBox1;
  TButton *Bactualiser;
  TCheckBox *CheckBox1;
  TButton *BlistPID;
  TTimer *Timer1;
  TShape *ShapeConnect;
  TShape *ShapeReqEnCours;
  TTimer *Timer2;
  TButton *BscrutePID;
  TButton *BannuleRequete;
  TButton *Binit;
  TProgressBar *ProgressBar1;
  TButton *BLireDiag1;
  TButton *BeffaceDiag1;
  TMemo *Memo2;
  TImage *ImageMIL1;
  TStringGrid *StringGrid1;
  TImage *ImageMIL0;
  TTabSheet *TabInfo;
  TStringGrid *StringGrid2;
  TButton *BlireM9;
  TMemo *Memo9;
  TStringGrid *StringGrid3;
  TComboBox *ComboBoxMode;
  TLabel *Label4;
  TLabel *Label5;
  TLabel *Label6;
  TMemo *Memo3;
  TButton *BlirePID;
  TButton *BannuleReq;
  TStringGrid *StringGrid4;
  TMenuItem *Simuler;
  TOpenDialog *OpenDialog1;
  TButton *Bsimul;
  TMenuItem *Aide1;
  TMenuItem *Apropos;
  TMenuItem *siteweb1;
  TEdit *EditIP;
  TEdit *EditPortTcp;
  TRadioGroup *RadioGroup1;
  TLabel *Label3;
  TLabel *Label7;
  TTimer *Timer3;
  TComboBox *ComboBoxTo;
  TLabel *Label8;
  TLabel *Label9;
  TImage *ImageMILok;
  TLabel *Label10;
  TLabel *Label11;
  void __fastcall BConnectClick(TObject *Sender);
  void __fastcall BDeConnectClick(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall BactualiserClick(TObject *Sender);
  void __fastcall BlistPIDClick(TObject *Sender);
  void __fastcall Timer1Timer(TObject *Sender);
  void __fastcall Timer2Timer(TObject *Sender);
  void __fastcall BscrutePIDClick(TObject *Sender);
  void __fastcall BannuleRequeteClick(TObject *Sender);
  void __fastcall BinitClick(TObject *Sender);
  void __fastcall BLireDiag1Click(TObject *Sender);
  void __fastcall StringGrid1DrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
  void __fastcall BeffaceDiag1Click(TObject *Sender);
  void __fastcall BlireM9Click(TObject *Sender);
  void __fastcall ComboBoxModeChange(TObject *Sender);
  void __fastcall StringGrid3SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
  void __fastcall PageControl1Change(TObject *Sender);
  void __fastcall BlirePIDClick(TObject *Sender);
  void __fastcall Quitter_Click(TObject *Sender);
  void __fastcall SimulerClick(TObject *Sender);
  void __fastcall AproposClick(TObject *Sender);
  void __fastcall siteweb1Click(TObject *Sender);
  void __fastcall RadioGroup1Click(TObject *Sender);
  void __fastcall Timer3Timer(TObject *Sender);
private:	// Déclarations de l'utilisateur
  int LienElm327(int noReq);
  //void __fastcall Traite_req();
  int nouveauRadioButton(TWinControl* pere, int noReq);
  void __fastcall RadioButtonClick(TObject *Sender);
  int GetPortList();
  char *supresBlanc(char *schaine);
  bool chercheItem(char *schaine, char *sItem);
  char *chercheItem(char *schaine, char *sItem, char *dest);
  char *chercheValAvant(char *schaine, char *sItem, char *dest, int nb);
  char *chercheValApres(char *schaine, char *sItem, char *dest, int nb);
  int chercheValApres3(char *schaine, char *sItem, char *dest);
  char asciiToChar(char *schaine);
  int chercheVolt(char *schaine);
  int chercheTemp(char *buf);
  int decode1Trame (char *buf, int nb);
  int decode2Trame(char *schaine);
  int decode3Trame (int noReq, char *buf, int nb, int cr1, TREPONSE *pReponse);
  int SauveFicLog(AnsiString AsLigne);
  int AfficheEtSauve(AnsiString AsLigne);
  char *ToHexaAscii(int val, char *buf, int nbo);
  int RetourTrameListPID(char *buf, int mode, int pid, int groupe, int typeReq);
  int RetourTrameListPID(char *buf, int requete, int typeReq);
  int Write(char *pReqElm);
  int Read(char *pchaine, TREPONSE *pReponse, int time_out);
  int afficheTableauDiag();
  int afficheTableauDefauts();
  int afficheTableauM9();
  int afficheTableauPid(int mode);
  int CheckSum(char *buf);
  int hexaToInt(char *schaine, uint nbDigit);
  int analyseReponse(char *dst, char *src, int codeReq);
  char *CodeReqToChar(int codeReq, char *chaine);
  char *doubleSlach(char *dest, AnsiString AsChaine);
  int trouver(FILE *fic_, char *chaine);

  int lireFicLog(FILE *fic1);
  int filtrerLog();

  TthreadListeRequete *thListReq;    //  Gère une liste de requète
  AnsiString AffichePID(int mode, AnsiString AsChaine);
  AnsiString AsPort;

  TwinSockBV *winSock1;      // classe de gestion des sockets dans WinSockUnit2.pas
  void __fastcall OnRecv(void *buf, int nb);  // sur reception TCP
  TEvent *Event1;
  int timeOut;

  char* comport_list_strings;// = NULL;
  int* comport_list_numbers; // = NULL;
  int comport_list_size; // = 0;
  TRadioButton *RadioButton[MAXREQ];
  PID pid;  // tableau de validité des PID
  MODE Mode; // tableau de validité des modes
  int iTensionBat, iTemp1;
  AnsiString AsNomFic;
  int noReqEnCours;   // no de requète Elm en cours
  bool reqEnCours;    // indique si une demande est en cours

  int ModeEnCours, PidEncours;
  bool ligneGriseeGrid1[MAXDIAG1+1];
  bool HeadersOn; // indique si les entêtes + Checksum sont activées (commande ATH1)

  FILE *ficSimu; // Fichier log pour simulation
  bool simulation;
  std::vector<TREQ> reqSim; // tableau dynamique de classement des requètes simulées(fichier log)
  TREQ *pReqSimEnCours;
  char szReqEnCours[20];
  int nbReqSim;
  int noRepEnCours;   // no de réponse à la requète
  TREPONSE reponse;

public:		// Déclarations de l'utilisateur
  __fastcall TForm1(TComponent* Owner);
  void __fastcall affiche_erreur_sys(AnsiString AsMsg);
  void __fastcall LanceListeReqInit();   // Lancé par le thread TthreadListeRequete
  void __fastcall LanceListeReqPid();    // Lancé par le thread TthreadListeRequete
  void __fastcall LanceListeReqPid2();   // Lancé par le thread TthreadListeRequete
  void __fastcall LanceListeReqDiag1();  // Lancé par le thread TthreadListeRequete
  void __fastcall LanceListeReqM9();     // Mode 9, Lancé par le thread TthreadListeRequete

  int hexaToInt(char *schaine);
  int chercheValApres2 (char *buf, char *sItem, int nb);
  int chercheValApres2 (char *buf, char *sItem, int nb, int deb);
  int chercheValApres2BCD (char *buf, char *sItem, int nb, int deb);  // 23/01/12
  char *chercheStrApres (char *buf, char *sItem, int nb, int deb, char *dest);
  char *chercheStrApres2 (char *buf, char *sItem, int nb, int deb, char *dest);
//  char *chercheStrApres (char *buf, char *sItem, int nb, char *dest);
  char *chercheStrApres (char *buf, char *sItem, char *dest);

  TStrings *MemoAffi;
  // Déclarations pour la communication série...
  HANDLE Hport;
  char bufTCP[512];
  char bufRec[TAILLEBUF]; // buffer réception
  int nbRecu;             // nb de byte recu en TCP dans bufRec
  int ncara;              // taille de bufRec (TAILLEBUF)

  int noReqElm;   // prochain no de requète Elm
  int iProtocoleOBD;
  int iAdECU;   // adresse du calculateur Moteur
  char szIdVerif[10][8]; // Numéros d'identification de vérificateurs de calibration
  char sz2Vin[40];    // Numéro d'identification du véhicule(chaine finale)
  char sz2Cal[40];    // Numéro d'identification de calibration (chaine finale)
  char sz2CVN[40];    // Numéro de vérification de calibration CVN (chaine finale)
  char sz2IdVerif[40];    // Numéro d'identification de vérificateurs de calibration (chaine finale)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
