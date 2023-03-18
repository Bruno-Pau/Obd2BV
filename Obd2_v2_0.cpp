//---------------------------------------------------------------------------
// Projet: OBD2bv                                     BV V2.0.3
// Module: OBD2_v2_0.cpp
// But: Diagnostic moteurs via inferface ELM 327
// Début projet: sept 2010
//---------------------------------------------------------------------------
// Modifs:
// BV 05/11/10: Création d'un répertoire log s'il n'existe pas
// BV 09/11/10: Simulation au lieu de connexion à partir d'un fichier log
// BV 22/01/12: Modif quelques intitulés de défauts dans default_list.h  V1.3.1
// BV Modif 23/01/12: Conversion de la chaine liste défauts recue en considerant que c'est du BCD
// BV Modif 23/01/12: Correction Bug lecture code 3 dans fichier log en simulation 
// BV Modif 12/10/12: V1.3.2 : modif calcul temperature 0x105 0x10F
// BV Modif 26/10/12: V1.3.3 : modif chercheValApres2()
//-----------------------
// BV Modif 02/02/14: V2.0 : Ajout Wi-Fi
// BV Modif 03/02/14: V2.0.1 : correction différents bugs :Requètes PID, Mode 9, etc
// BV Modif 03/02/14: V2.0.2 : les sockets sont gérés avec TwinSockBV
// BV Modif 09/02/14: V2.0.3 : fichier log placé dans "Mes Documents\obd2bv_log\piste-***.txt"
// BV Modif 09/02/14: V2.0.3 : correction bugs analyse codes 900, 902, 904, 906
// BV Modif 10/02/14: V2.0.4 : modif analyse et presentation message defaut (detail)
//---------------------------------------------------------------------------
// Généralités:
// Ce logiciel communique avec le calculateur moteur via une interface OBDII
//  à base de composant ELM327   http://www.elmelectronics.com/DSheets/ELM327DS.pdf
// Liaison RS232 ou USB + drivers de liaison série virtuel (drivers ftdibus et ftdiport)
//
// L'ELM327 communique via:
// - des commandes AT (ATZ...) pour l'initialisation et la config du composant ELM
// - des commandes de PID "0105" ... pour dialoguer avec le calculateur
// L'ELM se charge de transformer ces commande PID en protocole CAN ou autre
//
// Ce logiciel analyse les réponses et tente d'en extraire les infos essentielles
// Chaque véhicule répond à des PID différents aussi il est nécessaire de
//  commencer par scruter les PID par mode "0100" pour mode 1, "020000" pour mode 2 ...
// Ce logiciel permet aussi de faire un Reset des défauts (Mode 4)
//
//---------------------------------------------------------------------------
// AVERTISSEMENTS
// Ce logiciel est destiné à communiquer avec des calculateurs moteurs
// Il est EXPERIMENTAL
// Il n'a actuellement été testé que sur peu de véhicules
// Les auteurs de ce logiciel ne peuvent garantir son bon fonctionnement.
// Les auteurs de ce logiciel ne peuvent être tenus pour responsable de
//  dommages causés aux calculateurs ou au moteurs des véhicules testés
//  à la suite de l'utilisation de ce Logiciel
//---------------------------------------------------------------------------
// Licence GPL V2
// Ce logiciel peut être utilisé et recopié.
// Mais la commercialisation de ce code ou d'une partie de ce code est interdite.
// Voir conditions générale des licences GPL
//---------------------------------------------------------------------------
#define NO_WIN32_LEAN_AND_MEAN  // pour appel SHGetPathFromIDList
#include <vcl.h>
#pragma hdrstop

#include "Obd2_v2_0.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
  : TForm(Owner)
{
  ncara = TAILLEBUF; // taille max buffer réception
  noReqElm = 0;
  noReqEnCours = 0;
  
  comport_list_strings= NULL;  // Interrogation base de registre
  comport_list_numbers = NULL;
  comport_list_size = 0;

  winSock1 = new TwinSockBV();
  Event1 = new TEvent(NULL, true, false, "ReadEvent");  // Reset manuel
}
//---------------------------------------------------------------------------
//  GetPortList(): Interrogation base de registre pour liste Ports RS232
//---------------------------------------------------------------------------
int  TForm1::GetPortList()
{
  int i;
  if (Reg.get_port_names(&comport_list_strings, &comport_list_size) != 0){
     AfficheEtSauve("Could not allocate memory for comport_list_strings.");
     return(-1);
  }

  if (comport_list_size > 0) {
    comport_list_numbers = (int*)malloc(comport_list_size * sizeof(int));
    if (comport_list_numbers == NULL) {
      AfficheEtSauve("GetPortList():Could not allocate memory for comport_list_numbers.");
      return(-1);
    }

    AnsiString AsList;
    for (i = 0; i < comport_list_size; i++) {
      char *lpStrPort = &comport_list_strings [ i * PORT_NAME_BUF_SIZE ];
      AnsiString As2 = lpStrPort ;
      ComboBox1->Items->Add(As2);
      AsList += " " + As2;
      if (i==0) ComboBox1->Text = As2;
    }
    //MemoAffi->Add("Liste ports: " + AsList);
    //RegCloseKey(hKey);
  }
  return(i);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  HeadersOn = false;
  MemoAffi = Memo1->Lines;  // affichage en cours
  Memo1->Clear();
  Memo2->Clear();
  Memo3->Clear();
  Memo9->Clear();

  MemoAffi->Add("OBD2bv: Diagnostic moteurs via inferface ELM 327 BV    ");
  GetPortList();
  //
  // Initialisation de variables
  //
  ModeEnCours=1; PidEncours=0;   // init scrutation auto

  afficheTableauDiag();
  afficheTableauDefauts();
  afficheTableauM9();

  simulation = false;
  pReqSimEnCours = NULL;
  szReqEnCours[0] = 0;
  nbReqSim = 0;
  noRepEnCours = 0;

  sz2Vin[0] = 0;
  sz2Cal[0] = 0;
  sz2CVN[0] = 0;
  sz2IdVerif[0] = 0;
  timeOut = ComboBoxTo->Text.ToIntDef(8);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BactualiserClick(TObject *Sender)
{
  while (ComboBox1->Items->Count > 0) {
    ComboBox1->Items->Delete(0);
  }
  GetPortList();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BConnectClick(TObject *Sender)
{

  //----- ouverture ou création du fichier log
  TDateTime DateTime = Now();
  DateSeparator = '-';
  TimeSeparator = '-';
  AsNomFic = "obd2bv_log\\piste-" + DateTime.DateTimeString() + ".txt";
  //
  // changer le repertoire courant:
  char cBuf[MAX_PATH];
  LPITEMIDLIST pidl;
  if (SHGetSpecialFolderLocation(0, CSIDL_PERSONAL, &pidl) == NOERROR) {
    if (SHGetPathFromIDList(pidl, cBuf) ) {

      bool ok = SetCurrentDirectory(cBuf);
      if (!ok) {
        Memo1->Lines->Add("Erreur SetCurrentDirectory");
      }
    }
  }

  DateSeparator = '/';
  TimeSeparator = ':';

  // Le répertoire log existe-t-il ?
  bool repLogExist = DirectoryExists("obd2bv_log");
  if (!repLogExist) {
    bool ok = CreateDir("obd2bv_log");
    if (ok) {
      MemoAffi->Add("Répertoire ""obd2bv_log"" céé");
    }
    else {
      AfficheEtSauve("Impossible de créer le Répertoire ""obd2bv_log"" ");
      Application->MessageBox("Creation repertoire ""obd2bv_log"" impossible", "Erreur Creation repertoire", MB_OK);
    }
  }
  MemoAffi->Add("Fichier log: " + AnsiString(cBuf) + AnsiString("\\obd2bv_log\\") + AsNomFic);

  FILE *fic1 = fopen(AsNomFic.c_str() ,"r+");
  if (!fic1){
    fic1 = fopen(AsNomFic.c_str(),"a+");   // fichier inexistant, on créé
    if (!fic1){
        Application->MessageBox(AsNomFic.c_str(), "Erreur Ouverture", MB_OK);
        return;
    }
    AnsiString AsLigne = Form1->Caption + DateTime.DateTimeString() + "\n";
    fwrite(AsLigne.c_str() , AsLigne.Length() , 1, fic1);
  }
  fclose(fic1);

  timeOut = ComboBoxTo->Text.ToIntDef(8);

  if (RadioGroup1->ItemIndex == 0) {
    //------ Liaison Wi-Fi
    MemoAffi->Add("tentative de connexion à :" + EditIP->Text + "... ");

    int cr = winSock1->OpenTcpCli(EditIP->Text, EditPortTcp->Text.ToIntDef(35000) , 0, &OnRecv );
    if (cr < 0) {
      AfficheEtSauve("ERREUR ouverture socket " + IntToStr(cr));

      EditIP->Enabled = true;
      EditPortTcp->Enabled = true;
      RadioGroup1->Enabled = true;
      BConnect->Enabled = true;
      BDeConnect->Enabled = false;
      ShapeConnect->Visible = false;
      StatusBar1->Panels[0].Items[0]->Text = AsPort + "Déconnecté";
      noReqElm = 0;
      return;
    }

    AfficheEtSauve("Connecté à :" + EditIP->Text);
    StatusBar1->Panels[0].Items[0]->Text = AsPort + "Connecté à EditIP->Text";
    EditIP->Enabled = false;
    EditPortTcp->Enabled = false;
    RadioGroup1->Enabled = false;
  }
  else {

  //-------------- Ouverture Port COM
    DCB Dcb1;  // structure des paramètres de la liaison série
    COMMTIMEOUTS time_out; // structure de time out
  //
  // Ouverture port série
  //
    AsPort = "\\\\.\\";
    AsPort += ComboBox1->Text; //Edit1->Text;
  
    Hport = CreateFile(
        AsPort.c_str() ,         // chaine indiquant le nom du fichier ou du port à ouvrir
      	GENERIC_READ|GENERIC_WRITE,	// accès (read-write) mode
    	0,	// share mode : non partagé
      	0,	// pointer to security attributes (pour Windows NT)
      	OPEN_EXISTING,	// fichier déjà existant
      	FILE_ATTRIBUTE_NORMAL,	// attributs de fichiers
      	NULL 	// handle to file with attributes to copy
     		);

    if (Hport==INVALID_HANDLE_VALUE)  {
      AfficheEtSauve("Erreur ouverture " + AsPort);
      return;
    }
  
  // ------ Paramètres des liaisons séries
    GetCommState(Hport,&Dcb1);   // recup paramètres par défaut
    Dcb1.ByteSize=8;             // 8 bits
    Dcb1.StopBits=0;             // 1 bit de stop
    if (R9600->Checked) Dcb1.BaudRate=CBR_9600;
    else if (R38400->Checked) Dcb1.BaudRate=CBR_38400;
    else Dcb1.BaudRate=CBR_115200;
  
    Dcb1.Parity=0;     // sans parité
  
    if (CheckBox1->Checked) {
      // suppression du test des signaux de contrôle
      Dcb1.fOutxCtsFlow = 0;        // dévalide le controle du CTS
      Dcb1.fOutxDsrFlow = 0;        // dévalide le controle du DSR
      Dcb1.fDsrSensitivity = 0;     // dévalide le test du DSR
      Dcb1.fDtrControl = DTR_CONTROL_ENABLE	;  // met a 1 le DTR
      Dcb1.fRtsControl = RTS_CONTROL_ENABLE	;  // met a 1 le RTS
      // Rajout du 24 juin
      Dcb1.ErrorChar = '#';
      Dcb1.fAbortOnError = 0;
    }
  
    // controles rajoutés 3 sept 2010
    Dcb1.fOutX = FALSE;
    Dcb1.fInX = FALSE;
    Dcb1.fErrorChar = FALSE;
    Dcb1.fAbortOnError = FALSE;
  
    SetCommState(Hport,&Dcb1);
  
  //------- Gestion des time out
    GetCommTimeouts(Hport,&time_out); // récup structure par défaut
    time_out.ReadIntervalTimeout=30;  // temps entre 2 caractères
    time_out.ReadTotalTimeoutMultiplier=1;
  //  time_out.ReadTotalTimeoutConstant = 0x7FFFFFFF;// temps total: attente infinie si aucun caractère
    time_out.ReadTotalTimeoutConstant = 1000;// temps total: temps max d'attente
    SetCommTimeouts(Hport,&time_out); // rechargement de la struture pour port 1
  
    AfficheEtSauve( "Port " + AsPort + " ouvert " + IntToStr(Dcb1.BaudRate) + " Bauds" );
    StatusBar1->Panels[0].Items[0]->Text = "Connecté via Port " + AsPort;

  //  Lancement traitement des requètes:
  //  thread1 = new TthreadRS232(FALSE, Hport, AsPort.c_str());   // creation Thread lié au port

  }  // fin RS232


  BConnect->Enabled = false;
  BDeConnect->Enabled = true;
  ShapeConnect->Visible = true;
  Binit->Enabled = true;
  RadioGroup1->Enabled = false;
  ComboBoxTo->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BDeConnectClick(TObject *Sender)
{
  if (RadioGroup1->ItemIndex == 0) {
    //ClientSocket1->Active = false;
    winSock1->Close();
    EditIP->Enabled = true;
    EditPortTcp->Enabled = true;
  }
  else {
    //if (thread1!=NULL) thread1->Terminate();
    CloseHandle(Hport);
    Hport = NULL;
  }
  BConnect->Enabled = true;
  BDeConnect->Enabled = false;
  ShapeConnect->Visible = false;
  RadioGroup1->Enabled = true;
  StatusBar1->Panels[0].Items[0]->Text = AsPort + "Déconnecté";
  AfficheEtSauve(AsPort + " Déconnecté");
  noReqElm = 0;
  ComboBoxTo->Enabled = true;
}
//---------------------------------------------------------------------------
// OnRecv() : sur reception TCP...
//---------------------------------------------------------------------------
void __fastcall TForm1::OnRecv(void *buf, int nb)
{
  if (nb < 0) return;
  memcpy(bufTCP, buf, nb);  // copie dans buffer temporaire en local
  nbRecu = nb;
  bufTCP[nb] = 0;
  Event1->SetEvent();
}
//---------------------------------------------------------------------------

int TForm1::LienElm327(int noReq)
{
  unsigned long nbecrit, i;
  if ((Hport == 0) || (Hport == INVALID_HANDLE_VALUE)) {
    AfficheEtSauve("Erreur: Port fermé ou invalide");
    return (-1);
  }
  char *pReqElm = NULL; // pointe sur la requete à envoyer

  if ((noReq >= MAXREQ) && (noReq < 0x100)){
    AfficheEtSauve("Erreur: n° requète interdit 0x" + IntToHex(noReq,8) + "  " + IntToStr(noReq));
    return (-2);
  }

  char szReq[20]="";
  if (noReq < MAXREQ) pReqElm = reqElm[noReq];  // prendre dans le tableau
  else  {                           // sinon, construire la chaine requète
    ToHexaAscii(noReq, szReq, 4);
    strcat(szReq, "\r");
    pReqElm = szReq;
  }
  WriteFile(
            Hport,
            pReqElm,
            strlen(pReqElm),
            &nbecrit,
            NULL);

 // -- préparation de AsChaine contenant les caractères ascii à afficher dans Memo1
  AnsiString AsChaine = "  1: ";

  for (i=0; i < nbecrit; i++ ){     // chaque octet
    if ( (pReqElm[i] > 0x20) && (pReqElm[i] < 0x7F) ){
      AsChaine = AsChaine + pReqElm[i];  // ASCII
    }
    else {
      switch ( pReqElm[i] ) {
        case 0x20: AsChaine = AsChaine + "_";  break; // Space
        case 0x0D: AsChaine = AsChaine + "\\r";  break; // CR
        case 0x0A: AsChaine = AsChaine + "\\n";  break; // LF
        default:AsChaine = AsChaine +"\\"+ IntToHex((pReqElm[i]), 2) + " "; // Hexa
      }
    }
  }
  if (nbecrit > 0)  Form1->AfficheEtSauve(AsChaine); // réactualisation de l'affichage

  Timer1->Enabled = false;    // Armement du Time-out
  Timer1->Enabled = true;    // Armement du Time-out
  return (0);
}
//---------------------------------------------------------------------------
// supprime les ' ' de la chaine
//---------------------------------------------------------------------------
char *TForm1::supresBlanc(char *schaine)
{
  unsigned int i,j;
  char s2[512];
  for (i=0, j=0; i <= strlen(schaine); i++) {
    if (schaine[i] != ' ') s2[j++] = schaine[i];
  }
  strcpy (schaine, s2);
  return (schaine);
}
//---------------------------------------------------------------------------
// chercheVolt : Detecte un chaine sItem ("V"...) et recupere la valeur qui précède
//---------------------------------------------------------------------------
int TForm1::chercheVolt(char *schaine)
{
  int i,j;
  int chiffreDetect = 0;
  for (i=strlen(schaine); i>=0; i--) {
    if (schaine[i] == 'V') {
      if ( (i>0) && ( schaine[i-1] >='0') && ( schaine[i-1] <='9')) { // un chiffre précède
        ++chiffreDetect;
        break;
      }
      else chiffreDetect = 0;
    }
    else chiffreDetect = 0;
  }

  if ( chiffreDetect <= 0) return (-1); // aucun chiffre  détecté ?

  char s2[10]="   ";
  //strncpy(s2, &schaine[i-4], 4);   // 4 chiffres recopiés ex: "13.7"
  s2[0] = schaine[i-4];
  s2[1] = schaine[i-3];
  s2[2] = schaine[i-1];
  int iValeur;
  int cr = sscanf(s2,"%d", &iValeur);   // conversion  en 1/10 de volts
  if (cr == 1){
    return(iValeur);
  }
  return (-1);
}
//---------------------------------------------------------------------------
// chercheValAvant : Detecte un chaine sItem ("41_00_"...) et recupere les nb octets qui précedent
//---------------------------------------------------------------------------
char *TForm1::chercheValAvant(char *schaine, char *sItem, char *dest, int nb)
{
  char *ptS1 = strstr(schaine, sItem);  // recherche sItem dans schaine
  if (ptS1 == NULL) return (NULL);
  char *ptSdeb = ptS1 - nb;  // pointe avant le début de la chaine trouvee
  int lg = strlen(ptSdeb);

  int i, j;            // recopie du morceau contenant la valeur hexa codée ASCII
  for (i=0, j=0; (i<nb) && (j<lg); j++) {
    char car = ptSdeb[j];
    if ((car < '0') || (car > 'F') ||( (car > '9') && (car < 'A') ) ) continue;
    dest[i++] = car;
  }
  dest[i] = 0;
  return (dest);
}
//---------------------------------------------------------------------------
// chercheValApres : Detecte un chaine sItem ("41_00_"...) et recupere les nb octets qui suivent
//---------------------------------------------------------------------------
char *TForm1::chercheValApres(char *schaine, char *sItem, char *dest, int nb)
{
  char *ptS1 = strstr(schaine, sItem);  // recherche sItem dans schaine
  if (ptS1 == NULL) return (NULL);
  char *ptSdeb = ptS1 + strlen(sItem);  // pointe apres la fin de chaine trouvee
  int lg = strlen(ptSdeb);

  int i, j;            // recopie du morceau contenant la valeur hexa codée ASCII
  for (i=0, j=0; (i<nb) && (j<lg); j++) {
    char car = ptSdeb[j];
    if ((car < '0') || (car > 'F') ||( (car > '9') && (car < 'A') ) ) continue;
    dest[i++] = car;
  }
  dest[i] = 0;
  return (dest);
}
//---------------------------------------------------------------------------
// chercheValApres3 : Detecte un chaine sItem (" cr="...)
//   et recupere le nombre puis les octets qui suivent
//   spécifique pour traitement en simulation (lecture fichier log)
//   exemple: " cr=256 A5**>" retourne 256 et "A5**>" dans dest
//---------------------------------------------------------------------------
int TForm1::chercheValApres3(char *schaine, char *sItem, char *dest)
{
  char *ptS1 = strstr(schaine, sItem);  // recherche sItem dans schaine
  if (ptS1 == NULL) return (-1);
  char *ptSdeb = ptS1 + strlen(sItem);  // pointe apres la fin de chaine trouvee
  int lg = strlen(ptSdeb);

  int cr = 0;
  if ( sscanf(ptSdeb, "%d", &cr) < 1){
    return (-2); // nombre qui suit sItem non trouvé
  }
  int i, j;
  for (i = 1; i < lg; i++) {
    if ( ptSdeb[i] == ' ' ) break;   // aller jusqu'au 1er blanc
  }
  if ( i == lg ) {
    dest[0] = 0;  // la chaine qui suit est vide
    return (cr);
  }
  for (j=i+1; j<lg; j++) {
    if (ptSdeb[j] != ' ') { // début de chaine trouvé
      strcpy (dest, &ptSdeb[j]);
      return (cr);
    }
  }
  dest[0] = 0;  // la chaine qui suit est vide
  return (cr);
}
//---------------------------------------------------------------------------
// chercheValApres2 : Detecte un chaine sItem ("A"...) et recupere le nombre qui suit
//---------------------------------------------------------------------------
int TForm1::chercheValApres2 (char *buf, char *sItem, int nb)
{
  char *pChaine = strstr( buf, sItem);
  if (pChaine == NULL) return (-1);
  pChaine += strlen(sItem);
  char s2[20];
  strncpy( s2, pChaine, nb);
  s2[nb] = 0;
  int iValeur;
  int cr = sscanf( s2, "%X", &iValeur);   // conversion Hexa
  if (cr == 1){
    return(iValeur);   // une valeur a été trouvée
  }
  // aucune valeur valide n'a été trouvée => on cherche plus loin    ##26 oct 2012
  char *pbuf2 = pChaine +1;
  pChaine = strstr( pbuf2, sItem);
  if (pChaine == NULL) return (-1);
  pChaine += strlen(sItem);
  strncpy( s2, pChaine, nb);
  s2[nb] = 0;
  cr = sscanf( s2, "%X", &iValeur);   // conversion Hexa
  if (cr == 1){
    return(iValeur);   // une valeur a été trouvée
  }
  return (-1);
}
//---------------------------------------------------------------------------
// chercheValApres2 : Detecte un chaine sItem ("A"...) et recupere le nombre qui suit
//---------------------------------------------------------------------------
int TForm1::chercheValApres2 (char *buf, char *sItem, int nb, int deb)
{
  char *pChaine = strstr( buf, sItem);
  if (pChaine == NULL) return (-1);
  pChaine += (strlen(sItem) + deb); //décale de deb caractères de début de la chaine à lire
  char s2[20];
  strncpy( s2, pChaine, nb);
  s2[nb] = 0;
  int iValeur;
  int cr = sscanf( s2, "%X", &iValeur);   // conversion
  if (cr == 1){
    return(iValeur);
  }
  return (-1);
}
//---------------------------------------------------------------------------
// chercheValApres2BCD : Detecte un chaine sItem ("A"...) et recupere le nombre BCD qui suit
//---------------------------------------------------------------------------
int TForm1::chercheValApres2BCD (char *buf, char *sItem, int nb, int deb)
{
  char *pChaine = strstr( buf, sItem);
  if (pChaine == NULL) return (-1);
  pChaine += ( strlen(sItem) + deb );
  char s2[20];
  strncpy( s2, pChaine, nb);
  s2[nb] = 0;
  int iValeur;
  int cr = sscanf( s2, "%d", &iValeur);   // conversion BCD
  if (cr == 1){
    return(iValeur);
  }
  return (-1);
}
//---------------------------------------------------------------------------
// chercheItem : Detecte un chaine sItem ("  1: "...) et indique si trouvé
//---------------------------------------------------------------------------
bool TForm1::chercheItem(char *schaine, char *sItem)
{
  char *ptS1 = strstr(schaine, sItem);  // recherche sItem dans schaine
  if (ptS1 == NULL) return (false);
  return (true);
}
//---------------------------------------------------------------------------
// chercheItem : Detecte un chaine sItem ("  1: "...) et recupere la chaine qui suit
//---------------------------------------------------------------------------
char *TForm1::chercheItem(char *schaine, char *sItem, char *dest)
{
  char *ptS1 = strstr(schaine, sItem);  // recherche sItem dans schaine
  if (ptS1 == NULL) return (NULL);
  char *ptSdeb = ptS1 + strlen(sItem);  // pointe apres la fin de chaine trouvee
  strcpy (dest, ptSdeb);
  return (dest);
}
//---------------------------------------------------------------------------
// chercheStrApres : Detecte un chaine sItem ("A"...) et recupere la chaine qui suit
//---------------------------------------------------------------------------
char *TForm1::chercheStrApres (char *buf, char *sItem, int nb, int deb, char *dest)
{
  int i,j;
  char *pChaine = strstr( buf, sItem);
  if (pChaine == NULL) return (NULL);
  pChaine += (strlen(sItem) + deb); //décale de deb caractères de début de la chaine à lire
  for (i=0, j=0; i<nb; i+=2, j++) {
    dest[j] = asciiToChar(&pChaine[i]);
  }
  dest[j] = 0;
  return (dest);
}
//---------------------------------------------------------------------------
// chercheStrApres2 : Detecte un chaine sItem ("A"...) et recupere la chaine qui suit
//                    sans decodage ASCII -> HEXA
//---------------------------------------------------------------------------
char *TForm1::chercheStrApres2 (char *buf, char *sItem, int nb, int deb, char *dest)
{
  int i;
  char *pChaine = strstr( buf, sItem);
  if (pChaine == NULL) return (NULL);
  pChaine += (strlen(sItem) + deb); //décale de deb caractères de début de la chaine à lire
  for (i=0; i<nb; i++) {   // BV 05/02/2014 : on renvoie finalement la chaine brute
    dest[i] = pChaine[i];
  }
  dest[i] = 0;
  return (dest);
}
//---------------------------------------------------------------------------
// chercheStrApres : Detecte une chaine sItem ("A"...) et recupere toute la chaine qui suit
//---------------------------------------------------------------------------
char *TForm1::chercheStrApres (char *buf, char *sItem, char *dest)
{
  int i,j;
  char *pChaine = strstr( buf, sItem);
  if (pChaine == NULL) return (NULL);
  pChaine += (strlen(sItem) ); //décale le début de la chaine à lire
  strcpy (dest, pChaine);
  return (dest);
}
//---------------------------------------------------------------------------
// asciiToChar()
//---------------------------------------------------------------------------
char TForm1::asciiToChar(char *schaine)
{
  if ( (schaine[0] < '0') || ( schaine[0] > '9' ) )   return (' ');
  if ( (schaine[1] < '0') || ( schaine[1] > 'F' )
        || ( (schaine[1] > '9') && (schaine[1] < 'A')  ) ) return (' ');
  uchar res = (schaine[0] & 15) << 4;
  uchar k = schaine[1] >> 4;
  if ( k == 3) {
    res += schaine[1] & 0x0F;
  }
  else {
    res += (schaine[1] & 0x0F) + 9;
  }
  if (res < ' ') res = ' ';
  return (res);
}
//---------------------------------------------------------------------------
// chercheTemp :  cherche la température PID 5 Mode 1
//---------------------------------------------------------------------------
int TForm1::chercheTemp(char *buf)
{
  char s2[40];
  chercheValApres(buf, "4105", s2, 2);  // on ne garde que les 2 octets qui suivent "4105"
  int iValeur;
  int cr = sscanf(s2,"%X", &iValeur);   // conversion
  if (cr == 1){
    iValeur -= 40;
    return(iValeur);
  }
  return (-256);
}
//---------------------------------------------------------------------------
char *TForm1::ToHexaAscii(int val, char *buf, int nbo)
{
  char str[10] = "        ";

  if ((nbo<0) || (nbo>8)) return (NULL); // nb octets significatifs dans chaine buf
  int ofset = 8 - nbo;
  str[0] = '0' | ((val >> 28) & 15) ;
  str[1] = '0' | ((val >> 24) & 15) ;
  str[2] = '0' | ((val >> 20) & 15) ;
  str[3] = '0' | ((val >> 16) & 15) ;
  str[4] = '0' | ((val >> 12) & 15) ;
  str[5] = '0' | ((val >> 8) & 15) ;
  str[6] = '0' | ((val >> 4) & 15) ;
  str[7] = '0' | (val & 15) ;
  strcpy (buf, &str[ofset]);
  return(buf);
}
//---------------------------------------------------------------------------
//  RetourTrameListPID(..) // traite la réponse à la demande de liste PID
//---------------------------------------------------------------------------
int TForm1::RetourTrameListPID(char *buf, int mode, int noPid, int groupe, int typeReq)
// mode (1 à 10)
// noPid: code du PID demandé n° 0, 32, 64,.. pour la liste des PID
// groupe 1 à 5. groupe 1 : PID 1 à 32; groupe 2 : 33 à 65; etc
// typereq : 1 : "4x";  2 : "4xx0"; 3 : "4x0000";  4 : "4x0001"; longueur de la chaine à trouver
{
  char szItem[20] = "4   ";
  ToHexaAscii(mode, &szItem[1], 1);  // "41" à "4F"
  ToHexaAscii(noPid, &szItem[2], 2);
  if (typeReq == 3) strcat(szItem, "00"); // 6 octets à trouver "4xx000"
  if (typeReq == 4) strcat(szItem, "01"); // 6 octets à trouver "4xx001"
  //if (typeReq == 2) ; // 6 octets à trouver "4000"
  //AnsiString As1 = szItem;
  //MemoAffi->Add("RetourTrame szItem: " + As1);


  AnsiString AsChaine;
  char szPID[] = "        ";
  if (chercheValApres(buf, szItem, szPID, 8) != NULL) {
      pid.set(mode, groupe, szPID);
      AfficheEtSauve("PID" + AffichePID(mode, AsChaine) );
      return(1);
  }
  else return (0);
}
//---------------------------------------------------------------------------
//  RetourTrameListPID(..)
//---------------------------------------------------------------------------
int TForm1::RetourTrameListPID(char *buf, int requete, int typeReq)
// requette: ex 0x0120 => mode 1 | noPid:0x20
// mode (1 à 10)
// noPid: code du PID demandé n° 0, 32, 64,.. pour la liste des PID
// groupe 1 à 5. groupe 1 : PID 1 à 32; groupe 2 : 33 à 65; etc
// typereq : 1 : "4x";  2 : "4xx0"; 3 : "4x0000";  4 : "4x0001"; longueur de la chaine à trouver
{
  int mode   = (requete >> 8) & 0xF;
  int noPid  = requete & 0xFF;
  int groupe = ( ( requete & 0xFF) >> 5 ) + 1;

  return ( RetourTrameListPID( buf, mode, noPid, groupe, typeReq ) );
}
//---------------------------------------------------------------------------
// decode1Trame: Tente de décoder une trame réponse (1er niveau de decodage)
//---------------------------------------------------------------------------
int TForm1::decode1Trame (char *buf, int nb)
{
  buf[nb] = 0;          // fin de chaine
  supresBlanc(buf);

  int cr = decode2Trame(buf);

  AfficheEtSauve(" cr=" + IntToStr(cr) + " " + buf);

  return(cr);
}
//---------------------------------------------------------------------------
// decode2Trame :  décode  les trames retour
// retourne (1:"NODATA" ou 2:"SEARCHING" ou 11:"OK")  + 256 si '>' détecté
//---------------------------------------------------------------------------

int TForm1::decode2Trame(char *schaine)
{
  // nettoyage: suppression des caracteres non affichables
  for (uint i=0; i<strlen(schaine); i++) {
    if ( (schaine[i] < ' ') || (schaine[i] > 'z') ) schaine[i] = '*';
    else switch( schaine[i] ) {
      case '\r':
      case '\n': schaine[i] = '*'; break;
      case ' ' : schaine[i] = '_'; break;
    }
  }

  int cr = 0;
  char *ptS1;

  ptS1 = strstr(schaine, ">");  // recherche ">" dans schaine
  if (ptS1 != NULL) cr = 256;

  ptS1 = strstr(schaine, "NODATA");  // recherche "NO_DATA"dans schaine
  if (ptS1 != NULL) return (cr + 1);

  ptS1 = strstr(schaine, "SEARCHING");  // recherche "SEARCHING" dans schaine
  if (ptS1 != NULL) return (cr + 2);

  ptS1 = strstr(schaine, "UNABLETOCONNECT");  // recherche "UNABLETOCONNECT" dans schaine
  if (ptS1 != NULL) return (cr + 3);

  ptS1 = strstr(schaine, "OK");  // recherche "OK" dans schaine
  if (ptS1 != NULL) return (cr + 11);

  //if( (schaine[0] =='>') && (strlen(schaine) < 3) )return (12);  // recherche ">" dans schaine

  return (cr);
}
//---------------------------------------------------------------------------
// decode3Trame: Tente de décoder une trame réponse (decodage aprofondi)
//---------------------------------------------------------------------------
int TForm1::decode3Trame (int noReq, char *bufRec, int nbr, int cr1, TREPONSE *pReponse)
{
  if (cr1 > 255) pReponse->repondu = true;

  //-------------------------  0902 : N° Identification du véhicule (VIN)
  if ( noReq == 0x902 ) {   
    int cr = pReponse->analyse17(noReq, bufRec, nbr, cr1);
    if (cr1 > 255) {
      StringGrid2->Cells[2][1] = pReponse->sz2;
      strcpy (sz2Vin, pReponse->sz2);
      AfficheEtSauve( "Mode 9 - info du véhicule (VIN): " + AnsiString(pReponse->sz2) ) ;
    }
    return(0);
  }
    //-------------------------  0904 : N° Identificateur de Calibration
  if ( noReq == 0x904 ) {
    int cr = pReponse->analyse17(noReq, bufRec, nbr, cr1);
    if (cr1 > 255) {
      StringGrid2->Cells[2][3] = pReponse->sz2;
      strcpy (sz2Cal, pReponse->sz2);
      AfficheEtSauve( "Mode 9 - info du véhicule (Id Cal): " + AnsiString(pReponse->sz2) ) ;
    }
    return(0);
  }
    //-------------------------  0906 : N° de Verification de Calibration (CVN)
  if ( noReq == 0x906 ) {
    int cr = pReponse->analyse17(noReq, bufRec, nbr, cr1);
    if (cr1 > 255) {
      StringGrid2->Cells[2][5] = pReponse->sz2;
      //StringGrid2->Cells[3][5] = pReponse->sz2;
      strcpy (sz2CVN, pReponse->sz2);
      AfficheEtSauve( "Mode 9 - info du véhicule (CVN): " + AnsiString(pReponse->sz2) ) ;
    }
    return(0);
  }

  int cr = pReponse->analyse1(noReq, bufRec, nbr, cr1, HeadersOn);

  return(0);
}
//---------------------------------------------------------------------------
//  TREPONSE : classe analysant les réponses à une requète
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  TREPONSE::analyse1() : analyse chaine contenant une valeur entière
//---------------------------------------------------------------------------
int TREPONSE::analyse1(int codeReq, char *bufRec, int lgbuf, int cr1, bool headers)
{
  if (lgbuf < 7) return (-1);    // valeur pas reçue
  char Str1[100], Str2[100], *pStr;
  char szItem[10] = "4";
  //int typeReq=0;

  typeRep = 1;
  strcpy (&szItem[1], IntToHex(codeReq, 3).c_str());  // exemple 0x902 -> "4902"
  strcpy(Str1, bufRec);

  for (int i= lgbuf-1; i > 0; i--) {       // raccourcir la chaine?
    if ((Str1[i] == '*') || (Str1[i] == '>')) {
      Str1[i] = 0;
    }
    else break;
  }
  pStr = Form1->chercheStrApres ( Str1, szItem , Str2);
  if (pStr == NULL) {
    strcpy(sz1, Str1);
    return (-1);
  }


  //if ( CheckSum(Str2) == hexaToInt( &Str2[lgbuf - 2] ) )  {
  if (headers)  { // checksum présent ?
    Str2[strlen(Str2) - 2] = 0; // on enlève le checksum
  }
  strcpy (sz1, Str2);

  if ( (codeReq & 0xFF) == 0x20) return (0);  // cas des scrutations de PID

  int ival = Form1->hexaToInt(sz1);
  if ((strlen(sz1) == 4) && (ival > 0x7FFF)) ival |= 0xFFFF0000; // passage en négatif
  int codeReq2 = codeReq;
  if  ( (codeReq2 & 0x0F00) == 0x200) codeReq2 -=0x100; // Mode = Mode 1

  switch (codeReq2) {
    // cas des temperatures:    // oct 2012 a verifier!!!!!
    case 0x105 : case 0x10F :
    case 0x13C : case 0x13D : case 0x13E : case 0x13F : case 0x146 :
    case 0x15C: case 0x167: case 0x168: case 0x16B:
    case 0x175: case 0x176: case 0x177: case 0x178: case 0x179: case 0x17C:
                 ival -= 40; break; //ival  * 100 / 180 ; break;

    case 0x10C : ival = ival / 4; break;  // compte tour rpm
    case 0x123 : ival = ival * 10; break;  // pression common rail
    case 0x121: case 0x131 : if (ival == 0xFFFF) ival=-1; break;  // nb km depuis MIL allmée
  }
  val = ival;
  return (ival);
}

//---------------------------------------------------------------------------
//  TREPONSE::analyse17() : analyse chaine réponse multiple
//---------------------------------------------------------------------------
int TREPONSE::analyse17(int noReq_, char *bufRec, int nbr, int cr1)
{
  int i=0, j=0, k=0, lg=0;

  /*  La chaine reçue peut contenir plusieurs sous chaines
      qu'il faut séparer pour remplir szVin[]
      exemple, réponse Sandero:
  1: 0902\r
  cr=0 87F17A4902010000005593*
  cr=0 87F17A490202553142535A*87F17A49020344454B5064*
  cr=0 87F17A4902043434313812*87F17A4902053434303610*
  */
  int id1 = 0;
  char str[100], *szStr;

  typeRep = 17;
  noReq = noReq_;
  AnsiString AsNoReq = IntToHex(noReq, 3);

  for (j=0; ; ){
  lg = strlen(&bufRec[j]);
    if ( lg < 13 ) {
      break;   // fin de trame
    }
    id1 = Form1->chercheValApres2(&bufRec[j], AsNoReq.c_str(), 2);  // recup des 2 octets qui suivent
    id1--;  // les identifiants vont de 1 à 8 ==> 0 à 7
    if ( (id1 >= 0) && (id1 < 10) ) {
      if (noReq_ == 0x906) { // cas particulier: chaine ASCI non decodee
        szStr = Form1->chercheStrApres2 (&bufRec[j], AsNoReq.c_str(), 8, 2, str); // recup des 8 octets qui suivent
      }
      else {
        szStr = Form1->chercheStrApres (&bufRec[j], AsNoReq.c_str(), 8, 2, str); // recup et decodage des 8 octets qui suivent
      }
      strcpy (szRep[id1], szStr);
      //bReponse = true;
    }
    for (k=0; k<lg; k++) {
      if (bufRec[j+k] == '*') {  // détection du séparateur (\r à l'origine)
        j += k+1;
        break;
      }
    }
    if (k==lg) break; // la chaine était terminée
  } // for (j

  if ( cr1 > 255 ) {  // detection '>'
    AnsiString AsRep ;
    for (i=0; i<10; i++) {
      AsRep += AnsiString(szRep[i]);
    }
    strcpy (sz2, AsRep.c_str());
    return (cr1);
  }
  return(0);
}
//---------------------------------------------------------------------------
//affiche_erreur_sys() : affiche le texte correspondand à la dernière erreur
//---------------------------------------------------------------------------
void __fastcall TForm1::affiche_erreur_sys(AnsiString AsMsg)
{
  LPVOID lpMsgBuf;      // pointeur sur une chaine qui sera alouée dynamiquement
  FormatMessage(        // fonction API WIN32
    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
    NULL,
    GetLastError(),     // Récupération de la dernière erreur détectée par Windows
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default langage
    (LPTSTR) &lpMsgBuf,
    0,
    NULL
  );
  AfficheEtSauve( AsMsg + ": " + (char*)lpMsgBuf);
}
//---------------------------------------------------------------------------
//  TthreadListeRequete:
//    Class permettant de mettre des listes de requètes à effectuer
//    en tache de fond
//    Le thread lance l'éxécution de fonctions appartenant à TForm1:
//    - LanceListeReqxxx()
//
//---------------------------------------------------------------------------
//  TthreadListeRequete
//    Constructeur du Thread de liste de requètes
//---------------------------------------------------------------------------
__fastcall TthreadListeRequete::TthreadListeRequete(bool CreateSuspended, int typeListe_)
    : TThread(CreateSuspended)
{
  typeListe = typeListe_;
}
//---------------------------------------------------------------------------
// Execute()
//---------------------------------------------------------------------------
void __fastcall TthreadListeRequete::Execute()    // Corps du Thread
{
  switch (typeListe) {
    case 1: Form1->LanceListeReqInit(); break;
    case 2: Form1->LanceListeReqPid(); break;   // lister les PID valides
    case 3: Form1->LanceListeReqDiag1(); break;
    case 4: Form1->LanceListeReqPid2(); break;  // exécuter les requètes PID
    case 9: Form1->LanceListeReqM9(); break;
  }
}
//---------------------------------------------------------------------------
//  LanceListeReqInit()
// Cette liste de requètes doit être lancé dès le démarrage de la liaison ELM
//---------------------------------------------------------------------------
void __fastcall TForm1::LanceListeReqInit()   // Exécution déportée du thread
{
  int nbr=0, i=0;
  int iVolt = 0;

  bool connectELM = false;
  bool UnableToConnectELM = false;
  char szAdMot[30];
  int essai = 0;
  char szVersionELM[50]="";

  BannuleRequete->Enabled = true;
  BannuleRequete->Tag = 0;
  ProgressBar1->Position = 0;

  Binit->Enabled = false;
  BscrutePID->Enabled = false;

  Write("\r");   // "\r"
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -3 ) {AfficheEtSauve("Time-out"); goto errCom;}
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  Write("ATWS\r");   // ATWS : Complete Reset
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -3 ) {AfficheEtSauve("Time-out"); goto errCom;}
  if ( nbr == -2 ) goto errCom; // Connexion rompue?

  ProgressBar1->Position += 2;

  Write(reqElm[0]);   // ATZ
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -3 ) {AfficheEtSauve("Time-out"); goto errCom;}
  if ( nbr == -2 ) goto errCom; // Connexion rompue?

  if (chercheStrApres (bufRec, "ELM327", szVersionELM) != NULL ) {
    for (int i=0; i< strlen(szVersionELM); i++) {
      if ((szVersionELM[i] == '\r')|| (szVersionELM[i] == '*')) {
        szVersionELM[i] = 0;
      }
    }
    Label7->Caption = "ELM327 " + AnsiString (szVersionELM);
  }

  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  Write(reqElm[1]);   // ATRV : Tension?
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  if ( ( iVolt = chercheVolt(bufRec)) > 0){
    AfficheEtSauve( "Tension " + IntToStr(iVolt/10) + "." + IntToStr(iVolt % 10) + "V");
  }
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  //---------------------------------------------
  Write(reqElm[2]);   // ATE0 Echo OFF
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  Write(reqElm[3]);   // ATL0 Line Feed OFF
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  //---------------------------------------------
  Write(reqElm[4]);   // ATS0 Space OFF
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  //---------------------------------------------
  Write(reqElm[5]);   // ATSP0 Set Protocol 0
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  //---------------------------------------------
  Write(reqElm[6]);   // ATH1 Set Headers ON
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  HeadersOn = true;
  if (BannuleRequete->Tag == 1) goto finInit;

  ProgressBar1->Position += 2;

  //---------------------------------------------  "0100\r"

  do {
    Write("0100\r");   //
    nbr = Read(bufRec, &reponse, timeOut + 4);
    if ( nbr == -3 ) continue;  // time-out
    if ( nbr == -2 ) goto errCom; // Connexion rompue?

    int lg = strlen(bufRec);
    if ( lg > 11 ){
      if (RetourTrameListPID(bufRec, 0x100, 2) > 0) {
        chercheValAvant(bufRec, "4100", szAdMot, 2);
        sscanf (szAdMot, "%X", &iAdECU);
        AfficheEtSauve("Un calculateur Moteur a été détecté à l'adresse 0x" + IntToHex(iAdECU,2));
      }
    }
    if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) {
      if ( ( (nbr & 0xFF) == 0) || ( (nbr & 0xFF) == 11) )   connectELM = true;
      if ( (nbr & 0xFF) == 3) {
        UnableToConnectELM = true;
        Sleep(100); // attente 1 sec
      }
      //break;  // detection '>'
    }
    //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
    if ( nbr == -2 ) AfficheEtSauve( "Erreur 0100 Réponse non reçue");
  } while ((!connectELM || UnableToConnectELM ) && ( essai++ < 3) );

  if ( UnableToConnectELM ) {
    AfficheEtSauve("Impossible de se connecter au Calculateur moteur");
    MemoAffi->Add("Le moteur est peut-être arrêté,");
    MemoAffi->Add("  ou sinon attendez quelques secondes et relancez l'Init Liaison ELM");
    goto finInit;
  }

  if (BannuleRequete->Tag == 1) goto finInit;
  if ( essai>= 3) AfficheEtSauve( "Erreur 0100\\r   '>' non détectée");

  ProgressBar1->Position += 2;

  //---------------------------------------------
  Write(reqElm[9]);   // ATH1 Set Headers OFF
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom; // Connexion rompue?
  //if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  HeadersOn = false;
  if (BannuleRequete->Tag == 1) goto finInit;
  if ( nbr < 0 ) AfficheEtSauve( "Erreur " + AnsiString(reqElm[9]) + "'>' non détectée");

  ProgressBar1->Position += 2;

  AfficheEtSauve( "Attente de l'initialisation de l'ELM avec le calculateur" );
  for (int i=0; i < 1; i++) {   // 2/11/10 baissé à 1 sec
    ProgressBar1->Position += 15;
    if (BannuleRequete->Tag == 1) goto finInit;
    Sleep(1000);
  }
  AfficheEtSauve( "Fin d'Attente - ELM initialisé" );

  Binit->Enabled = true;
  BscrutePID->Enabled = true;
  BLireDiag1->Enabled = true;
  BeffaceDiag1->Enabled = true;
  BannuleRequete->Enabled = false;
  BlireM9->Enabled = true;

  LanceListeReqPid(); // rajouté le 2/11/10

  return;

finInit:
  AfficheEtSauve( "Requete annulée");
fin:
  Binit->Enabled = true;
  BscrutePID->Enabled = true;
  BLireDiag1->Enabled = true;
  BeffaceDiag1->Enabled = true;
  BlireM9->Enabled = true;
  BannuleRequete->Enabled = false;
  BannuleRequete->Tag = 0;
  return;

errCom:
  AfficheEtSauve( "Erreur " + IntToStr(nbr) + " : perte de connexion avec l'ELM327 ?");
  goto fin;
}
//---------------------------------------------------------------------------
// LanceListeReqPid() : établit la liste des PID valides
//---------------------------------------------------------------------------
void __fastcall TForm1::LanceListeReqPid()   // Exécution déportée du thread
{
  int nbr, i, lg;
  char szAdMot[4]="  ";  // adresse du groupe Moteur

  bool connectELM = false;
  bool UnableToConnectELM;
  int essai = 0;

  BannuleRequete->Enabled = true;
  BannuleRequete->Tag = 0;
  ProgressBar1->Position = 0;

  Binit->Enabled = false;
  BscrutePID->Enabled = false;
  BannuleRequete->Enabled = true;
  //--------------------------------
  Write(reqElm[7]);   // ATDPN Describe the current protocol by nb
  int iProtocole_ = -1;
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 2) {
    iProtocole_ = chercheValApres2(bufRec, "A", 1);
  }
  if ( iProtocole_ < 0 ) AfficheEtSauve( "Erreur " + AnsiString(reqElm[7]) + "'>' non détectée");
  else  {
    iProtocoleOBD = iProtocole_;
    switch (iProtocole_){
      case 0 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " Automatique" ); break;
      case 1 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " SAE J1850 PWM" ); break;
      case 2 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " SAE J1850 VPW" ); break;
      case 3 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 9141-2" ); break;
      case 4 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 14230-4KWP(5 bauds init, 10,4kBauds)" ); break;
      case 5 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 14230-4KWP(fast init, 10,4kBauds)" ); break;
      case 6 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 15765-4CAN(11 bit ID, 500 Kbauds)" ); break;
      case 7 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 15765-4CAN(29 bit ID, 500 Kbauds)" ); break;
      case 8 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 15765-4CAN(11 bit ID, 250 Kbauds)" ); break;
      case 9 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " ISO 15765-4CAN(29 bit ID, 250 Kbauds)" ); break;
      case 10 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " SAE J1939 CAN(29 bit ID, 125 Kbauds)" ); break;
      case 11 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " USER1 CAN(11 bit ID, 125 Kbauds)" ); break;
      case 12 : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " USER2 CAN(11 bit ID, 50 Kbauds)" ); break;
      default : AfficheEtSauve("Protocole: " + IntToStr(iProtocole_) + " Non reconnu!!!");
    }
  }

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //-------------------------------- liste PID Mode 1 : 1 à 32

  do{
    Write("0100\r");
    UnableToConnectELM = false;
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) goto errCom;  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 11 ){
      // RetourTrameListPID() : mode (1 à 10)
      // noPid: code du PID demandé n° 0, 32, 64,.. pour la liste des PID
      // groupe 1 à 5. groupe 1 : PID 1 à 32; groupe 2 : 33 à 65; etc
      // typereq : 1 : "4x";  2 : "4xx0"; 3 : "4x0000";  4 : "4x0001"; longueur de la chaine à trouver
      RetourTrameListPID(bufRec, 0x100, 2);
    }
    if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) {
      if ( ( (nbr & 0xFF) == 0) || ( (nbr & 0xFF) == 11) )   connectELM = true;
      if ( (nbr & 0xFF) == 3) {
        UnableToConnectELM = true;
        Sleep(100); // attente 1 sec
      }
      break;  // detection '>'
    }
  } while ((!connectELM || UnableToConnectELM ) && ( essai++ < 3) );

  if ( UnableToConnectELM ) {
    AfficheEtSauve("Impossible de se connecter à l'ELM");
    MemoAffi->Add("Le moteur est peut-être arrêté,");
    MemoAffi->Add("  ou sinon attendez quelques secondes et relancez l'Init Liaison ELM");
    goto abortReq;
  }

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //--------------------------------
  char szRep011C[4];
  if ( pid.supporte(1,0x1C) ) {
    Write("011C\r");
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) goto errCom;  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 8){
      szRep011C[0] = bufRec[10]; szRep011C[1] = bufRec[11]; szRep011C[2] = 0;
      AfficheEtSauve("0x011C: Spécification OBD du Calculateur 0x" + AnsiString(szAdMot) + " : " + AnsiString(szRep011C));
    }
    //if ( i== 5) AfficheEtSauve( "Erreur 011C Réponse non reçue");
  }

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //-------------------------------- liste PID Mode 1 : 33 à 128
  int groupePid;
  for (groupePid = 0x20; groupePid <= 0x80; groupePid += 0x20) {
    if ( !pid.supporte(1, groupePid) ) {
      break;
    }
    char szReq[20] = "01 0\r";
    szReq[2] = (groupePid >> 4) + '0';
    Write(szReq);
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) goto errCom;  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 8){
      RetourTrameListPID(bufRec, 0x100 + groupePid, 2);
    }
    //if ( i== 5) AfficheEtSauve( "Erreur 01" + IntToHex(groupePid, 2) +"\r Réponse non reçue");

    ProgressBar1->Position += 2;
    if (BannuleRequete->Tag == 1) goto abortReq;
  }
  //-------------------------------- liste PID Mode 2 : 1 à 32
  Write("020000\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 8 ){
    RetourTrameListPID(bufRec, 0x200, 3);
  }
  //if ( i== 5) AfficheEtSauve( "Erreur 020000\r Réponse non reçue, Mode 2 non supporté");

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;
  //--------------------------------
  if ( pid.supporte(2,0x20) ) {
    Write("022000\r");
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) goto errCom;  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 8){
      RetourTrameListPID(bufRec, 0x220, 3);
    }
    //if ( i== 5) AfficheEtSauve( "Erreur 0220\r Réponse non reçue");
  }
  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;



  Write("03\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 8 ){
    RetourTrameListPID(bufRec, 0x300, 3);
  }
  //if ( i== 5) AfficheEtSauve( "Erreur 03\r Réponse non reçue, Mode 3 non supporté");

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //--------------------------------
  Write("0600\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 8 ){
    RetourTrameListPID(bufRec, 0x600, 1);
  }
  //if ( i== 5) AfficheEtSauve( "Erreur 0600\r Réponse non reçue, Mode 6 non supporté");

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //--------------------------------
  Write("07\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 8 ){
    RetourTrameListPID(bufRec, 0x700, 3);
  }
  if ( i== 5) AfficheEtSauve( "Erreur 07\r Réponse non reçue, Mode 7 non supporté");

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //--------------------------------
  Write("08000000000000\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 8 ){
    RetourTrameListPID(bufRec, 0x800, 3);
  }
  //if ( i== 5) AfficheEtSauve( "Erreur 08000000000000\r Réponse non reçue, Mode 8 non supporté");

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;

  //--------------------------------
  Write("0900\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  int cr;
  if ( lg > 8 ){
    if (!RetourTrameListPID(bufRec, 0x900, 4)) {  // normalement 490001
      cr = RetourTrameListPID(bufRec, 0x900, 2);       // sinon 4900    9/02/14
    }
  }
  if ( !cr) AfficheEtSauve( "Erreur 0900\r Réponse non reçue, Mode 9 non supporté!");

  ProgressBar1->Position += 10;
  if (BannuleRequete->Tag == 1) goto abortReq;


  //--------------------------------
  Write("0A00\r");
  nbr = Read(bufRec, &reponse, timeOut);
  if ( nbr == -2 ) goto errCom;  // Connexion rompue?
  lg = strlen(bufRec);
  if ( lg > 8 ){
    RetourTrameListPID(bufRec, 0xA00, 2);
  }
  //if ( i== 5) AfficheEtSauve( "Erreur 0A00 Réponse non reçue\r");

  ProgressBar1->Position += 10;

  BlirePID->Enabled = true;
  BlireM9->Enabled = true;
  BlistPID->Enabled = true;

finReq:       // fin normale
  BannuleRequete->Tag = 0;
  ProgressBar1->Position = 100;
  Binit->Enabled = true;
  BannuleRequete->Enabled = false;
  BscrutePID->Enabled = true;
  BlirePID->Enabled = true;
  return;

abortReq:     // aborté par opérateur
  AfficheEtSauve( "Scrutation des PID Annulée par opérateur");
  BannuleRequete->Tag = 0;
  goto finReq;

errCom:
  AfficheEtSauve( "Erreur " + IntToStr(nbr) + " : perte de connexion avec l'ELM327 ?");
  BannuleRequete->Tag = 0;
  goto finReq;
}
//---------------------------------------------------------------------------
// LanceListeReqPid2() : interroge tous les PID valides dans un mode donné
//---------------------------------------------------------------------------
void __fastcall TForm1::LanceListeReqPid2()   // Exécution déportée du thread
{
  int nbr, i, ligne, lg, res;
  int mode, noPid, codeReq;
  char req[20], str[100];

  BannuleRequete->Enabled = true;
  BannuleReq->Enabled = true;
  BannuleRequete->Tag = 0;
  BlirePID->Enabled = false;
  ProgressBar1->Position = 0;

  Binit->Enabled = false;
  BscrutePID->Enabled = false;
  BannuleRequete->Enabled = true;
  //--------------------------------

  mode = ComboBoxMode->ItemIndex +1;
  if (mode <1) return;

  for (ligne=1; ligne <= StringGrid3->RowCount; ligne++) {
    noPid = StringGrid3->Cells[0][ligne].ToIntDef(0);
    if (noPid < 1) break;
    codeReq = ((mode & 15) << 8) + noPid;
    if ( !pid.supporte(mode,noPid) ) continue;
    CodeReqToChar( codeReq, req );

  //-------------------------   appel de la requète sélectionnée
    char szItem[20];
    strcpy (szItem, szReqEnCours);
    szItem[0] = '4';
    szItem[strlen(szReqEnCours) -1] = 0;  // supression '\r'

    Write( req );

    char str1[100];
    // Analyse réponse
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) goto errCom;  // Connexion rompue?
    //if ( noReqEnCours == 0x902 ) {

    switch (noReqEnCours) {
      case 0x902 : StringGrid3->Cells[2][ligne] = sz2Vin; break;
      case 0x904 : StringGrid3->Cells[2][ligne] = sz2Cal; break;
      case 0x906 : StringGrid3->Cells[2][ligne] = sz2CVN; break;

      default:lg = strlen(bufRec);
      if (reponse.sz1[0] != 0) {
        StringGrid3->Cells[2][ligne] = AnsiString(reponse.sz1);
        if (noReqEnCours == 0x110) {  // valeur avec 2 decimales
          sprintf(str1, "%6.2f", ((float)reponse.val )/100.0 );
          StringGrid3->Cells[3][ligne] = str1;
        }
        else StringGrid3->Cells[3][ligne] = IntToStr(reponse.val);
        AfficheEtSauve("requète 0x" + AnsiString(szReqEnCours) + "  Valeur: " + IntToStr(reponse.val) );
        if (res > 0 ) {
          switch (mode) {
            case 1: if (noPid < NBPIDMOD1) AfficheEtSauve(AnsiString(szItemMode1[noPid])); break;
            case 5: if (noPid < NBPIDMOD5) AfficheEtSauve(AnsiString(szItemMode5[noPid])); break;
            case 6: if (noPid < NBPIDMOD6) AfficheEtSauve(AnsiString(szItemMode6[noPid])); break;
            case 9: if (noPid < NBPIDMOD9) AfficheEtSauve(AnsiString(szItemMode9[noPid])); break;
          }
        } // if (res)
      }
    }  // switch (noReqEnCours)

    //if ( i== 10) AfficheEtSauve( "Erreur " + AnsiString(req) +"\r Réponse non reçue");
  }  // for (ligne=



finReq:       // fin normale
  BannuleRequete->Tag = 0;
  ProgressBar1->Position = 100;
  Binit->Enabled = true;
  BannuleRequete->Enabled = false;
  BannuleReq->Enabled = false;
  BscrutePID->Enabled = true;
  BlirePID->Enabled = true;
  BlistPID->Enabled = true;
  BlireM9->Enabled = true;
  return;

abortReq:     // aborté par opérateur
  AfficheEtSauve( "Scrutation des PID Annulée par opérateur");
  BannuleRequete->Tag = 0;
  goto finReq;

errCom:
  AfficheEtSauve( "Erreur " + IntToStr(nbr) + " : perte de connexion avec l'ELM327 ?");
  BannuleRequete->Tag = 0;
  goto finReq;
}
//---------------------------------------------------------------------------
// LanceListeReqM9()  Requètes Mode 9
//---------------------------------------------------------------------------
void __fastcall TForm1::LanceListeReqM9()
{
  BannuleRequete->Enabled = true;
  BannuleRequete->Tag = 0;
  ProgressBar1->Position = 0;

  Binit->Enabled = false;
  BscrutePID->Enabled = false;
  BlireM9->Enabled = false;

  char str[100], *szStr;
  int i, j, k, nbr, lg, id1;
  int nbMsgCal=0, nbMsgVerif=0;
  bool bReponse = false;

  //-------------------------  0902 : N° Identification du véhicule (VIN)
  if ( pid.supporte(9,0x02) ) {
    Write("0902\r");

    // Analyse réponse
    nbr = Read(bufRec, &reponse, timeOut + 4);
    if ( nbr == -2 ) AfficheEtSauve("Erreur" + IntToStr(nbr) + " Pas de reponse");  // Connexion rompue?

    StringGrid2->Cells[2][1] = sz2Vin;
  }  // if ( pid.supporte(9,0x02) )

  if (BannuleRequete->Tag == 1) goto abortReq9;

  //-------------------------  0903 : Nb de messages pour les calibrations
  if ( pid.supporte(9,0x03) ) {

    Write("0903\r");
    // Analyse réponse
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) AfficheEtSauve("Erreur " + IntToStr(nbr) + " Pas de reponse");  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 6 ){
      nbMsgCal = chercheValApres2(bufRec, "903", 2);
      StringGrid2->Cells[2][2] = IntToStr(nbMsgCal);
      AfficheEtSauve( "Mode 9 - nb de Msg Calibration: " + IntToStr(nbMsgCal) ) ;
    }
  //if ( i== 5) AfficheEtSauve( "Erreur 0903\r Réponse non reçue");
  }  // if ( pid.supporte(9,0x03) )


  //-------------------------  0904 : Identificateur de calibrations
  if ( pid.supporte(9,0x04) ) {
    bReponse = false;

    Write("0904\r");
    // Analyse réponse
    nbr = Read(bufRec, &reponse, timeOut + 4);
    if ( nbr == -2 ) AfficheEtSauve("Erreur " + IntToStr(nbr) + " Pas de reponse");  // Connexion rompue?

  }
  if (BannuleRequete->Tag == 1) goto abortReq9;

  //-------------------------  0905 : Nb de messages pour les vérificateurs de calibrations
  if ( pid.supporte(9,0x05) ) {

    Write("0905\r");
    // Analyse réponse
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) AfficheEtSauve("Erreur " + IntToStr(nbr) + " Pas de reponse");  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 5 ){
      nbMsgVerif = chercheValApres2(bufRec, "905", 2);
      StringGrid2->Cells[2][4] = IntToStr(nbMsgVerif);
      AfficheEtSauve( "Mode 9 - nb de Msg vérificateurs de Calibration: " + IntToStr(nbMsgVerif) ) ;
    }
  //if ( i== 5) AfficheEtSauve( "Erreur 0905\r Réponse non reçue");
  }  // if ( pid.supporte(9,0x05) )
  if (BannuleRequete->Tag == 1) goto abortReq9;


  //-------------------------  0906 : Identificateur de vérificateurs de calibrations
  if ( pid.supporte(9,0x06) ) {
    bReponse = false;

    Write("0906\r");
    // Analyse réponse
    nbr = Read(bufRec, &reponse, timeOut + 4);
    if ( nbr == -2 ) AfficheEtSauve("Erreur " + IntToStr(nbr) + " Pas de reponse");  // Connexion rompue?
    //  La chaine reçue peut contenir plusieurs sous chaines
    for (j=0; ; ){
    lg = strlen(&bufRec[j]);
      if ( lg < 10 ) {
        break;   // fin de trame
      }
      id1 = chercheValApres2(&bufRec[j], "906", 2);  // recup des 2 octets qui suivent
      if ( (id1 > 0) && (id1 < 10) ) {
        char szItem2[] = "9060 ";
        szItem2[4] = '0' + id1; // generalement id1 = 1 ==> "90601"
        szStr = chercheStrApres2 (&bufRec[j], szItem2, 8, 2, str); // recup des 8 octets qui suivent
        strcpy (szIdVerif[id1], szStr);
        bReponse = true;
      }
      for (k=0; k<lg; k++) {
        if (bufRec[j+k] == '*') {  // détection du séparateur (\r à l'origine)
          j += k+1;
          break;
        }
      }
    } // for (j


    if ( !bReponse) {
      AfficheEtSauve( "Erreur 0906 Mode 9 (vérificateurs de calibration): Pas d'info\r");
      //Memo9->Lines->Add("Erreur 0906 Mode 9 (vérificateur de calibration): Pas d'info");
    }
    else {
      AnsiString AsVerif ;
      for (i=1; i<=nbMsgVerif; i++) {
        AsVerif += AnsiString(szIdVerif[i]);
      }
      StringGrid2->Cells[2][5] = AsVerif;
      AfficheEtSauve( "Mode 9 - Vérificateurs de calibration: " + AsVerif ) ;
    }
  }
  if (BannuleRequete->Tag == 1) goto abortReq9;




finReq9:       // fin normale
  BannuleRequete->Tag = 0;
  ProgressBar1->Position = 100;
  Binit->Enabled = true;
  BannuleRequete->Enabled = false;
  BscrutePID->Enabled = true;
  BlistPID->Enabled = true;
  BlireM9->Enabled = true;
  return;

abortReq9:     // aborté par opérateur
  AfficheEtSauve( "Scrutation Mode 9 Annulée par opérateur");
  BannuleRequete->Tag = 0;
  goto finReq9;

errCom:
  AfficheEtSauve( "Erreur " + IntToStr(nbr) + " : perte de connexion avec l'ELM327 ?");
  BannuleRequete->Tag = 0;
  goto finReq9;
}
//---------------------------------------------------------------------------
// LanceListeReqDiag1()  Diagnostique de base
//---------------------------------------------------------------------------
//
void __fastcall TForm1::LanceListeReqDiag1()
{
  int diag = 0;
  int i, j, nbr, lg;
  int valide, fini;
  int def1=-1, def2=-1, def3=-1; // défauts moteurs

  BannuleRequete->Tag = 0;
  BannuleRequete->Enabled = true;

  if (!simulation ) {   // 21/01/2012
    //--------- Liste
    Write("0101\r");
    nbr = Read(bufRec, &reponse, timeOut);
    if ( nbr == -2 ) AfficheEtSauve("Erreur " + IntToStr(nbr) + " Pas de reponse");  // Connexion rompue?
    lg = strlen(bufRec);
    if ( lg > 10 ){
      diag = chercheValApres2(bufRec, "4101", 8) ;
      if (diag != -1) {
        valide = ((diag >> 16) & 7) | ((diag  & 0xFF00) >> 5);
        fini =   ((diag >> 20) & 7) | ( (diag  & 0xFF) << 3);
      }
    }
    //if ( i== 5) AfficheEtSauve( "Erreur 0101 (Diagnostic de base) Réponse non reçue");
    if (BannuleRequete->Tag == 1) goto finDiag1;
    if ( nbr > 255 ) { // detection '>'
      for (i=1, j=1; j<=MAXDIAG1; i<<=1, j++) {
        if ( (valide & i) > 0) {
          StringGrid1->Cells[1][j] = "Oui";
          ligneGriseeGrid1[j] = false;
        }
        else  {
          StringGrid1->Cells[1][j] = "Non";
          ligneGriseeGrid1[j] = true;
        }
        if ( (fini & i) > 0)  StringGrid1->Cells[2][j] = "Non";
        else StringGrid1->Cells[2][j] = "Oui";
      }

      AfficheEtSauve( "Diagnostic de base, supporté: " + IntToHex(valide, 2) + " Etat: " + IntToHex(fini,2) );
    }

  }  // !simulation
  

  //-----------------  Y a t il des défauts enregistrés?

  for (int k=1; k < 4; k++) {     // Effacementde la table des défauts
    StringGrid4->Cells[0][k] = "";
    StringGrid4->Cells[1][k] = "";
    StringGrid4->Cells[2][k] = "";
  }

  Write("03\r");
  nbr = Read(bufRec, &reponse, timeOut);
  //lg = strlen(bufRec);
  lg = strlen(bufRec);
  if ( nbr < 0) AfficheEtSauve( "Erreur 03 Réponse non reçue");

  // Modif 23/01/2012:
  // Conversion de la chaine recue en considerant que c'est du BCD et non Hexa


  if ( ( lg > 10 ) || (lg ==7) ){
    if (lg == 7) {  // parfois l'ELM renvoie un message court si pas de défaut!
      if ( chercheItem(bufRec, "4300") ) {  // 4300**>
        def1 =0; def2 =0; def3 =0; // trouve donc pas de defaut
      }
    }
    else {
      //def1 = chercheValApres2(bufRec, "43", 4); // 23/01/2012  pas en Hexa mais en BCD!
      def1 = chercheValApres2BCD(bufRec, "43", 4, 0);
      def2 = chercheValApres2BCD(bufRec, "43", 4, 4);
      def3 = chercheValApres2BCD(bufRec, "43", 4, 8);
      if (def1 == -1) {
        def1 = chercheValApres2BCD(bufRec, "41", 4, 0);
        def2 = chercheValApres2BCD(bufRec, "41", 4, 4);
        def3 = chercheValApres2BCD(bufRec, "41", 4, 8);
      }
    }
    if ( (def1 > 0) || (def2 > 0) || (def3 > 0) ){
      AnsiString AsStr = "03 :Défauts: détectés:";
      AfficheEtSauve( AsStr);
      if (def1 > 0) {
        //StringGrid4->Cells[0][1] = IntToHex(def1,4);
        StringGrid4->Cells[1][1] = IntToStr(def1);
        if (def1 < 1000)  {
          //AfficheEtSauve("0x" + IntToHex(def1,4)+ " " + IntToStr(def1) + " : " + AnsiString(szItemDefault[def1]) );
          AfficheEtSauve( AnsiString(szItemDefault[def1]) +  AnsiString(szItemDefault[def1]) );
          StringGrid4->Cells[2][1] = AnsiString(szItemDefault[def1]);
        }
        else AfficheEtSauve("0x" + IntToHex(def1,4)+ " " + IntToStr(def1));
      }
      if (def2 > 0) {
        //StringGrid4->Cells[0][2] = IntToHex(def2,4);
        StringGrid4->Cells[1][2] = IntToStr(def2);
        if (def2 < 1000)  {
          //AfficheEtSauve("0x" + IntToHex(def2,4)+ " " + IntToStr(def2) + " : " + AnsiString(szItemDefault[def2]) );
          AfficheEtSauve( AnsiString(szItemDefault[def2]) +  AnsiString(szItemDefault[def2]) );
          StringGrid4->Cells[2][2] = AnsiString(szItemDefault[def2]);
        }
        else AfficheEtSauve("0x" + IntToHex(def2,4)+ " " + IntToStr(def2));
      }
      if (def3 > 0) {
        //StringGrid4->Cells[0][3] = IntToHex(def3,4);
        StringGrid4->Cells[1][3] = IntToStr(def3);
        if (def3 < 1000)  {
          //AfficheEtSauve("0x" + IntToHex(def3,4)+ " " + IntToStr(def3) + " : " + AnsiString(szItemDefault[def3]) );
          AfficheEtSauve( AnsiString(szItemDefault[def3]) +  AnsiString(szItemDefault[def3]) );
          StringGrid4->Cells[2][3] = AnsiString(szItemDefault[def3]);
        }
        else AfficheEtSauve("0x" + IntToHex(def3,4)+ " " + IntToStr(def3));
      }

      ImageMIL0->Visible = false;
      ImageMILok->Visible = false;
      ImageMIL1->Visible = true;
      Label11->Visible = true;
      Label10->Visible = false;
    }
    else if ( (def1 == 0) && (def2 == 0) && (def3 == 0) ) {
      AnsiString AsStr = "03 :Aucun Défaut détecté: ";
      AfficheEtSauve( AsStr);
      AfficheEtSauve( AsStr );
      ImageMIL0->Visible = false;
      ImageMILok->Visible = true;
      ImageMIL1->Visible = false;
      Label10->Visible = true;
      Label11->Visible = false;
    }
  }
  else {
  }

  if (BannuleRequete->Tag == 1) goto finDiag1;

  BeffaceDiag1->Enabled = true;
  BannuleRequete->Enabled = false;
  BlireM9->Enabled = true;
  return;

finDiag1:
  AfficheEtSauve( "Requete annulée");
  //MemoAffi->Add( "Requete annulée");
  BeffaceDiag1->Enabled = true;
  BannuleRequete->Enabled = false;
  BannuleRequete->Tag = 0;
  BlireM9->Enabled = true;
  return;

errCom:
  AfficheEtSauve( "Erreur " + IntToStr(nbr) + " : perte de connexion avec l'ELM327 ?");
  BannuleRequete->Tag = 0;
  goto finDiag1;
}
//---------------------------------------------------------------------------
// Write(..) Ecriture sur port série (ou USB)
//    ou recherche dans fichier log dans le cas de la Simulation
//---------------------------------------------------------------------------
int TForm1::Write(char *pReqElm)
{
  char str1[10];
  int i, j, noReq = 0, nbecrit = strlen(pReqElm);

  strcpy (szReqEnCours, pReqElm);
  for (i=0; i<nbecrit; i++) {
    if  (szReqEnCours[i] == '\r') szReqEnCours[i] = 0;  // suppression '\r'
  }
  strncpy (str1, szReqEnCours, 4); str1[4] = 0;
  sscanf(str1, "%X", &noReq);              // on tente de décoder les 4 premiers caractères
  noReqEnCours = noReq;

  pReqSimEnCours = NULL;
  noRepEnCours = 0;
  reponse.init();  // Raz de la précédente réponse

  if (simulation) {
    TREQ *pReq;
    if (noReq == 3 ) noReq <<= 8; // 23/01/12 le code PID est dans poids forts...

    MemoAffi->Add("PC: " + AnsiString(pReqElm));

    if ((noReq > 0) && (pReqElm[0] == '0')) {   // si ce n'est pas une commande AT
      for (i=0; i<nbReqSim; i++) { // recherche dans tableau req  sur le code PID
        pReq = &reqSim.at(i);
        if (pReq == NULL) return(-32);
        if (pReq->codePID == noReq) {
          if (pReq->HeadersOn == HeadersOn) {
            pReqSimEnCours = pReq;
            HeadersOn = pReq->HeadersOn;
            break;
          }
        }
      }
    }
    else {                                  // c'est sans doute une commande AT
      for (i=0; i<nbReqSim; i++) { // recherche dans tableau req sur la chaine question (requète)
        pReq = &reqSim.at(i);
        if (pReq == NULL) return(-32);
        if ( strcmp(pReqElm, pReq->question ) == 0  ) {
          pReqSimEnCours = pReq;
          if (strcmp(pReqElm, "ATH0\r")==0) {
            AfficheEtSauve("Headers OFF");
            HeadersOn = false;
          }
          else if (strcmp(pReqElm, "ATH1\r")==0) {
            AfficheEtSauve("Headers ON");
            HeadersOn = true;
          }
          break;
        }
      }
    }

    if ( pReqSimEnCours == NULL ) {
      MemoAffi->Add("Requète " + AnsiString (pReqElm) + "  Non trouvée dans fichier log");
      return (-1);
    }
  }  // if (simulation)

  else {

    if (RadioGroup1->ItemIndex == 0) {      // Wi-Fi
      //ClientSocket1->Socket->SendBuf(pReqElm, strlen(pReqElm));
      winSock1->Send_(pReqElm, strlen(pReqElm));
    }

    else {
      unsigned long nbecrit, i;
      if ((Hport == 0) || (Hport == INVALID_HANDLE_VALUE)) {
        AfficheEtSauve("Erreur: Port fermé ou invalide");
        return (-1);
      }

      WriteFile(
                Hport,
                pReqElm,
                strlen(pReqElm),
                &nbecrit,
                NULL);

    }
  } // si pas simulation
  
 // -- préparation de AsChaine contenant les caractères ascii à afficher dans Memo1
  AnsiString AsChaine = "  1: ";

  for (i=0; i < nbecrit; i++ ){     // chaque octet
    if ( (pReqElm[i] > 0x20) && (pReqElm[i] < 0x7F) ){
      AsChaine = AsChaine + pReqElm[i];  // ASCII
    }
    else {
      switch ( pReqElm[i] ) {
        case 0x20: AsChaine = AsChaine + "_";  break; // Space
        case 0x0D: AsChaine = AsChaine + "\\r";  break; // CR
        case 0x0A: AsChaine = AsChaine + "\\n";  break; // LF
        default:AsChaine = AsChaine +"\\"+ IntToHex((pReqElm[i]), 2) + " "; // Hexa
      }
    }
  }
//  if (nbecrit > 0)
    AfficheEtSauve(AsChaine); // réactualisation de l'affichage

  return (0);
}
//---------------------------------------------------------------------------
//   Read(..)
//    - attente réception sur port série ou Ethernet
//    - affichage des octets en Hexadécimal dans MemoAffi (Memo1 ou Memo2...)
//---------------------------------------------------------------------------
int TForm1::Read(char *pchaine, TREPONSE *pReponse, int time_out)
{
  Timer3->Tag =0; // Raz pour detection Time-out
  int nblu = 0;
  int cr=0, cr1=0, cr3=0;

  if (simulation) {   // ---- Lecture trame sur fichier log ...
    if (pReqSimEnCours == NULL) return(-30);
    if (noRepEnCours > 9) return (-31);
    strcpy (pchaine, pReqSimEnCours->reponse[noRepEnCours]);
    nblu = strlen ( pchaine);
  }

//
// ---- Attente trame sur port série ou TCP...
//
  else {   // si pas simulation
    if (BConnect->Enabled)   return(-1);   // la connexion est coupée!

    //
    // les trames arrivent souvent en morceaux,
    // aussi il faut detecter le '>' pour valider la trame complete
    
    ulong nb = 0;  // nb de bytes recus au dernier ReceiveBuf
    ulong nb2 = 0;  // index sur pchaine

    //
    // si Wi-Fi ---------------------------------------------
    //
    if (RadioGroup1->ItemIndex == 0) {
      for (int i=0; i<10; i++) {     // trame en 10 morceaux max

        Event1->ResetEvent();
        TWaitResult res = Event1->WaitFor(time_out * 1000);

        if (res == wrTimeout) {  // (wrTimeout, wrSignaled, wrAbandoned, wrError)
          AfficheEtSauve("Read : Erreur Time-out!");
          if ((nb2>=0) && (nb2<TAILLEBUF)) pchaine[nb2] = 0;   // fin de chaine
          nblu = -3;
          break;
        }
        if (res == wrSignaled) {
          bufTCP[nbRecu] = 0;   // juste pour affichage
          //MemoAffi->Add("Read: " + AnsiString(bufTCP));

          memcpy(&pchaine[nb2], bufTCP, nbRecu); // transfert dans pchaine
          nb2 += nbRecu;
          nbRecu = 0;  // pour la prochaine reception dans OnRecv()
          if ( pchaine[nb2-1] == '>' ) {  // la trame est complète?
            nblu = nb2;
            break;
          }
        }
        if ((res == wrAbandoned)|| (res == wrError)) {
          AfficheEtSauve("Read : erreur Event1");
          break;
        }
      }
    }

    //
    // si RS232  ---------------------------------------------------
    //
    else {
      // Modif 3/02/14 : boucle de réception jusqu'a '>'
      for (int i=0; i<10; i++) {  // trame en 10 morceaux max
        if (!ReadFile(        // lecture du port série
          Hport,            // Handle du port
          &pchaine[nb2],  // address of buffer that receives data
          Form1->ncara,	            // nombre max de bytes à lire
          &nb,	        // adresse du nombre de bytes lus
          NULL) 	        // LPOVERLAPPED:address of structure for data
        ) AfficheEtSauve("Erreur Read " + AsPort);

        nb2 += nb;
        if ( pchaine[nb2-1] == '>' ) {  // la trame est complète?
          nblu = nb2;
          break;
        }
        if (Timer3->Tag > time_out)  {
          AfficheEtSauve("Read : Erreur Time-out!");
          if ((nb2>=0) && (nb2<TAILLEBUF)) pchaine[nb2] = 0;   // fin de chaine
          nblu = -3;
          break;
        }
      }
      // 15 mars 2010 : détection d'erreurs de COM
      unsigned long EvtMask;
      GetCommMask(Hport, &EvtMask);
      Edit2->Text = IntToHex((__int64)EvtMask, 8);
    }
  }
  //
  // décodage de la trame recue:  ------------------------------------
  //
  if ( nblu == 0) cr =-2; // pas de car recus
  else if (nblu > 0) {
    cr1 = decode1Trame (pchaine, nblu);                   // decodage 1er niveau
    cr3 = decode3Trame(noReqEnCours, pchaine, nblu, cr1, pReponse); // decodage approfondi
    cr = cr1;   // Est ce nécessaire ???
  }
  else cr = nblu;

  noRepEnCours++;  // nb de read depuis le write

  return(cr);
}
//---------------------------------------------------------------------------
// nouveauRadioButton() : plus utilisé
//---------------------------------------------------------------------------
int TForm1::nouveauRadioButton(TWinControl* pere, int noReq)
{
  if (noReq >= MAXREQ) return(-noReq);

  char szReq[20];
  strcpy ( szReq, reqElm[noReq]);   // pour nettoyage chaine
  for (uint i=0; i < strlen(szReq); i++) if ( (szReq[i] > 'z') || (szReq[i] < ' ')) szReq[i] = ' ';

  RadioButton[noReq] = new TRadioButton( Form1);
  RadioButton[noReq]->Parent = pere;      // le composant doit appartenir à un objet
  RadioButton[noReq]->Top =  50 + 20*noReq;
  RadioButton[noReq]->Left = 120;
  AnsiString AsReq = szReq;
  RadioButton[noReq]->Caption = IntToStr(noReq) + ": " + AsReq;
  RadioButton[noReq]->Tag = noReq;  // pour savoir qui on est
  if ( !noReq ) RadioButton[noReq]->Checked = true;
  RadioButton[noReq]->OnClick = RadioButtonClick;

  return(++noReq);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButtonClick(TObject *Sender)
{
  for (int i=0; i<MAXREQ; i++){
    if (RadioButton[i] == NULL) return;
    if  (RadioButton[i]->Checked) {
      noReqElm = i;
      return;
    }
  }
}
//---------------------------------------------------------------------------
// AffichePID() Afficher la liste des PID valides dans 1 mode donné
//---------------------------------------------------------------------------
AnsiString TForm1::AffichePID(int mode, AnsiString AsChaine)
{
    AsChaine = " mode " + IntToStr(mode) + "  : ";
    for (int i=1; i < 65; i++) {
      bool etat = pid.supporte(mode, i);
      if (etat) AsChaine += "1" ;
      else  AsChaine += "0" ;
      if ( (i & 7 )== 0 ) AsChaine += "  ";
    }
    return (AsChaine);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BlistPIDClick(TObject *Sender)
{
  AfficheEtSauve("PID supportés: ");
  for (int mode =1; mode <11; mode++) {
    AnsiString AsChaine;
    AsChaine = AffichePID(mode, AsChaine);

    AfficheEtSauve(AsChaine);
  }
}
//---------------------------------------------------------------------------
//  SauveFicLog() : Ecrit une ligne dans le fichier Log
//---------------------------------------------------------------------------
int TForm1::SauveFicLog(AnsiString AsLigne)
{
  FILE *fic1 = fopen(AsNomFic.c_str(),"r+");
  if (!fic1){
    //Application->MessageBox(AsNomFic.c_str(), "Erreur Ouverture", MB_OK);
    return(-1);
  }
  fseek(fic1, 0L, SEEK_END);
  fwrite(AsLigne.c_str(), AsLigne.Length(), 1, fic1);

  fclose(fic1);
  return(0);
}
//---------------------------------------------------------------------------
// AfficheEtSauve()
//---------------------------------------------------------------------------
int TForm1::AfficheEtSauve(AnsiString AsLigne)
{
  TDateTime DateTime = Now();
  AnsiString AsTime = DateTime.TimeString();
  MemoAffi->Add(AsTime + " " + AsLigne);
  return (SauveFicLog(AsTime + " " + AsLigne + "\n"));
}
//---------------------------------------------------------------------------
// Timer1Timer()
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  ShapeReqEnCours->Visible = false;
  reqEnCours = false;

  int mode_ = (noReqEnCours >> 8) & 0xFF;
  int pid_ = noReqEnCours & 0xFF;

  if (mode_ > 0) {       // cas de l'interrogation directe MODE|PID ("0100" ...)
    if ( pid_ == 0 )  {   // 1ere d'une demande de Détermination des PIDs supportés dans ce mode
      Mode.set(mode_, 0);   // mode invalide
      ModeEnCours += 1;     // passer au suivant
      PidEncours = 0;
    }
    else {
      if ( (pid_ & 0x1F) == 0 ) { // autre demande de Détermination des PIDs supportés dans ce mode
        ModeEnCours += 1;     // passer au suivant
        PidEncours = 0;
      }
    }
  }
  AfficheEtSauve("Time-out détecté requète suivante: 0x" + IntToHex(ModeEnCours, 2) + IntToHex(PidEncours,2));
  Timer1->Enabled = false;
}
//---------------------------------------------------------------------------
// BlistPIDClick: Lance une demande auto de liste de PID valides
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
  if (reqEnCours) {
    return; // la précedente requète n'est pas finie
  }

  if ( (ModeEnCours <=0 ) || (ModeEnCours > 10) || (PidEncours > 255) ) {
    ModeEnCours = 0;
    PidEncours = 0;
    Timer2->Enabled = False;    // fin de la liste des requètes
    return;
  }

  ShapeReqEnCours->Visible = true;
  reqEnCours = true;

  noReqEnCours = ( ModeEnCours << 8 ) | PidEncours;
  LienElm327(noReqEnCours);
}
//---------------------------------------------------------------------------
// BlistPIDClick : tente de répertorier tous les PID valides par requètes successives
//---------------------------------------------------------------------------
void __fastcall TForm1::BscrutePIDClick(TObject *Sender)
{
  thListReq = new TthreadListeRequete(false, 2); // creation Thread scrutation PID
}
//---------------------------------------------------------------------------
// BannuleRequeteClick() demande l'arrêt de la liste des requètes
//---------------------------------------------------------------------------
void __fastcall TForm1::BannuleRequeteClick(TObject *Sender)
{
  BannuleRequete->Tag = 1;
}
//---------------------------------------------------------------------------
// BinitClick()
//---------------------------------------------------------------------------
void __fastcall TForm1::BinitClick(TObject *Sender)
{
  BannuleRequete->Enabled = true;
  thListReq = new TthreadListeRequete(false, 1); // creation Thread d'initialisation
}
//---------------------------------------------------------------------------
//  afficheTableauDiag()
//---------------------------------------------------------------------------
int TForm1::afficheTableauDiag()
{
  // Dimensionner le tableau d'affichage
  StringGrid1->RowCount = MAXDIAG1+1;
  StringGrid1->ColWidths[0] = 260;
  StringGrid1->ColWidths[1] = 100;
  StringGrid1->ColWidths[2] = 100;
  StringGrid1->Cells[0][0] = "Description Test";
  StringGrid1->Cells[1][0] = "Disponibilité";
  StringGrid1->Cells[2][0] = "Test Terminé";

  for (int i=0; i < MAXDIAG1; i++) {
    ligneGriseeGrid1[i+1] = false;
    StringGrid1->Cells[0][i+1] = szItemDiag1[i];
    StringGrid1->Cells[1][i+1] = "  ?";
  }
  return(0);
}
//---------------------------------------------------------------------------
//  afficheTableauDefauts()
//---------------------------------------------------------------------------
int TForm1::afficheTableauDefauts()
{
  // Dimensionner le tableau d'affichage
  StringGrid4->Cells[0][0] = "Hexa";
  StringGrid4->Cells[1][0] = "décimal";
  StringGrid4->Cells[2][0] = "Intitulé Défaut";

  for (int i=0; i < 3; i++) {
    StringGrid4->Cells[0][i+1] = "";
    StringGrid4->Cells[1][i+1] = "";
    StringGrid4->Cells[2][i+1] = "";
  }
  return(0);
}
//---------------------------------------------------------------------------
//  afficheTableauM9()
//---------------------------------------------------------------------------
int TForm1::afficheTableauM9()
{
  // Initialiser le tableau d'affichage
  StringGrid2->Cells[0][0] = "N°";
  StringGrid2->Cells[1][0] = "Intitulé";
  StringGrid2->Cells[2][0] = "Réponse";
  StringGrid2->Cells[3][0] = "Valeur";

  for (int i=2; i < 7; i++) {
    StringGrid2->Cells[0][i-1] = IntToStr(i);
    StringGrid2->Cells[1][i-1] = szItemMode9[i];
    StringGrid2->Cells[2][i-1] = "";
  }
  return(0);
}
//---------------------------------------------------------------------------
//  afficheTableauPid()
//---------------------------------------------------------------------------
int TForm1::afficheTableauPid(int mode)
{
  int  maxPid = 0, nbPid = 0, i, j;
  //INTITUL *ptIntitul[256];
  char *ptI = NULL;   // pointe sur le début d'un des tableaux d'intitulés

  // Raz des lignes précédentes
  int nb = StringGrid3->RowCount;
  for (int i=0; i< nb; i++) {
      StringGrid3->Cells[0][i] = "";
      StringGrid3->Cells[1][i] = "";
      StringGrid3->Cells[2][i] = "";
      StringGrid3->Cells[3][i] = "";
  }

  // Dans quel mode est on?
  switch (mode) {
    case 1:  ptI = szItemMode1[0]; maxPid = NBPIDMOD1; break;
    case 2:
    case 3:
    case 4:
    case 7:
    case 8:  maxPid = 0; break;
    case 5:  ptI = szItemMode5[0]; maxPid = NBPIDMOD5; break;
    case 6:  ptI = szItemMode6[0]; maxPid = NBPIDMOD6; break;
    case 9:  ptI = szItemMode9[0]; maxPid = NBPIDMOD9; break;
    default: return(-1);
  }
  nbPid = pid.nbPid(mode);

  StringGrid3->RowCount = nbPid + 1;
  StringGrid3->Cells[0][0] = "N° PID";
  StringGrid3->Cells[1][0] = "Intitulé PID";
  StringGrid3->Cells[2][0] = "ASCII";
  StringGrid3->Cells[3][0] = "Décimal";

  for (i=0, j=1; i < maxPid; i++) {
    if ( pid.supporte(mode, i) ) {
      StringGrid3->Cells[0][j] = IntToStr(i);
      if (i < maxPid) StringGrid3->Cells[1][j] = AnsiString(ptI+ i*100);
      StringGrid3->Cells[2][j] = "";
      StringGrid3->Cells[3][j] = "";
      j++;
    }
  }
  return(0);
}

//---------------------------------------------------------------------------
// BLireDiag1Click()
//---------------------------------------------------------------------------
void __fastcall TForm1::BLireDiag1Click(TObject *Sender)
{ // creation Thread scrutation Diagnostic de base
  BannuleRequete->Enabled = true;
  thListReq = new TthreadListeRequete(false, 3);
}
//---------------------------------------------------------------------------
// StringGrid1DrawCell() Evennement quand clic sur le StringGrid
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid1DrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
  String TheText;
  if (ligneGriseeGrid1[ARow]){
    TheText=StringGrid1->Cells[ACol][ARow];
    //StringGrid1->Canvas->Font->Color=clGray;
    StringGrid1->Canvas->Brush->Color=cl3DLight; // fond grisé
    StringGrid1->Canvas->TextRect(Rect,Rect.Left,Rect.Top,TheText);
  }
}
//---------------------------------------------------------------------------
// BeffaceDiag1Click() Effacement des défauts (mode 4)
//---------------------------------------------------------------------------
void __fastcall TForm1::BeffaceDiag1Click(TObject *Sender)
{
  char szRep[100];
  int i, nbr;

  BannuleRequete->Enabled = true;
  BannuleRequete->Tag = 0;

  int cr = Application->MessageBoxA("Opération dangereuse. Etes vous sûr?", "Effacement défauts", MB_YESNO);
  if (cr != 6) {
    AfficheEtSauve("Effacement défauts annulé");
    goto finEffaceDiag;
  }

  Write("04\r");
  for (i=0; i<3; i++) {
    nbr = Read(bufRec, &reponse, timeOut);
    int lg = strlen(bufRec);
    if ( lg > 3 ){
      if (chercheValApres(bufRec, "44",szRep, 10) ){
        AnsiString AsStr = "04 Efacement Défauts: " + AnsiString (szRep);
        AfficheEtSauve( AsStr);
      }
    }
    if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
  }
  if (BannuleRequete->Tag == 1) goto finEffaceDiag;
  if ( i== 3) {
    AfficheEtSauve( "Erreur 04 Efacement Défauts: Réponse non reçue");
  }
  return;
  
finEffaceDiag:
  AfficheEtSauve( "Requete Efacement Défauts annulée");
  BeffaceDiag1->Enabled = true;
  BannuleRequete->Tag = 0;
  return;
}
//---------------------------------------------------------------------------
// BlireM9Click()
//---------------------------------------------------------------------------
void __fastcall TForm1::BlireM9Click(TObject *Sender)
{
  BannuleRequete->Enabled = true;
  thListReq = new TthreadListeRequete(false, 9);
}
//---------------------------------------------------------------------------
// ComboBoxModeChange()
//---------------------------------------------------------------------------
void __fastcall TForm1::ComboBoxModeChange(TObject *Sender)
{
  if (ComboBoxMode->ItemIndex < 0) return;
  afficheTableauPid(ComboBoxMode->ItemIndex + 1);
}
//---------------------------------------------------------------------------
// StringGrid3DrawCell() Evennement quand clic sur le StringGrid
//---------------------------------------------------------------------------
void __fastcall TForm1::StringGrid3SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
  int i, nbr, lg, codeReq;
  char str[100], req[100];
  int res=0;

  if (ComboBoxMode->ItemIndex < 0) return;
  int noPid = StringGrid3->Cells[0][ARow].ToIntDef(0);
  if (!noPid)  return;
  
  int mode = ComboBoxMode->ItemIndex +1;
  if (!pid.supporte(mode, noPid)) {
    Memo3->Lines->Add("PID non supporté, mode: " + IntToStr(mode) +" PID: " + noPid);
    return;
  }

  MemoAffi->Add("Appel PID, mode: " + IntToStr(mode) +" PID: " + noPid);

  //-------------------------   appel de la requète sélectionnée
  codeReq = ((mode & 15) << 8) + noPid;
  char szItem[] ="4   ";
  if ( pid.supporte(mode,noPid) ) {
    codeReq = ((mode& 15) << 8) + noPid;
    CodeReqToChar( codeReq, req );
    szItem[1] = req[1]; szItem[2] = req[2]; szItem[3] = req[3];

    Write( req );
    // Analyse réponse
    for (i=0; i<10; i++) {
      nbr = Read(bufRec, &reponse, timeOut);
      lg = strlen(bufRec);
      if ( ( noReqEnCours != 0x902 )&&( noReqEnCours != 0x904 )) {
        if (lg > 8) {
          res = analyseReponse(str, bufRec, codeReq);
          StringGrid3->Cells[2][ARow] = AnsiString(str);
          if (res >= 0) {
            if (codeReq == 0x10C) res >>= 2; // spécifique vitesse moteur /4
          }
          StringGrid3->Cells[3][ARow] = IntToStr(res);
        }
      } // if ( noReqEnCours != 0x902
      // pas de traitement .......................
      if (( nbr > 255 ) || (BannuleRequete->Tag == 1)) break;  // detection '>'
    }
    if ( i== 10) AfficheEtSauve( "Erreur " + AnsiString(req) +"\r Réponse non reçue");
    else {
      if ( noReqEnCours == 0x902 ) {
        StringGrid3->Cells[2][ARow] = sz2Vin;
      }
      if ( noReqEnCours == 0x904 ) {
        StringGrid3->Cells[2][ARow] = sz2Cal;
      }
      if ( noReqEnCours == 0x906 ) {
        StringGrid3->Cells[2][ARow] = sz2CVN;
      }
    }
  }  // if ( pid.supporte(mode,noPid) )
}
//---------------------------------------------------------------------------
// PageControl1Change() : changement d'onglet
//---------------------------------------------------------------------------
void __fastcall TForm1::PageControl1Change(TObject *Sender)
{
  // Changement de Memo pour l'affichage en cours
  if (PageControl1->ActivePage == TabInfo) { MemoAffi = Memo9->Lines; }
  else if (PageControl1->ActivePage == TabPID) { MemoAffi = Memo3->Lines; }
  else if (PageControl1->ActivePage == TabDiag1) { MemoAffi = Memo2->Lines; }
  else  { MemoAffi = Memo1->Lines; }

  if (PageControl1->ActivePage == TabPID) {
    if (ComboBoxMode->ItemIndex < 0) ComboBoxMode->ItemIndex = 0;
    afficheTableauPid(ComboBoxMode->ItemIndex + 1);
  }
}
//---------------------------------------------------------------------------
// CheckSum()
//---------------------------------------------------------------------------
int TForm1::CheckSum(char *buf)
{
  int lg = strlen(buf);
  int somme = 0;
  for (int i=0; i< lg-2; i+=2) {
    somme += hexaToInt(&buf[i], 2);
  }
  return (somme & 0xFF);
}
//---------------------------------------------------------------------------
// hexaToInt() ascii -> int
//---------------------------------------------------------------------------
int TForm1::hexaToInt(char *schaine)
{
  return (hexaToInt(schaine, strlen(schaine)) );
}
//---------------------------------------------------------------------------
// hexaToInt() ascii -> int, pour nbDigit octets
//---------------------------------------------------------------------------
int TForm1::hexaToInt(char *schaine, uint nbDigit)
{
  // exemple  hexaToInt("0286", 4) renvoie 0x286 (646)
  //          hexaToInt("F1", 2) renvoie 0xF1 (241)
  int res=0, i, j;
  if ( (nbDigit > 8) || (nbDigit < 1) ) return (-9);
  if (nbDigit > strlen(schaine)) return (-10);
  
  for (i=0, j=(nbDigit-1)<<2; i< nbDigit; i++, j -= 4) {
    if ( (schaine[i] < '0') || ( schaine[i] > 'F' )
        || ( (schaine[i] > '9') && (schaine[i] < 'A')  ) ) return (-(i+1));

    int x = schaine[i] & 15;
    if ( schaine[i] > '9') x += 9;
    res += x << j;
  }
  return (res);
}//---------------------------------------------------------------------------
// analyseReponse()   analyse Reponse de l'ELM
//---------------------------------------------------------------------------
int TForm1::analyseReponse(char *dst, char *src, int codeReq)
{
  int lgbuf = strlen(src);
  char Str1[500], Str2[500], *pStr;
  char szItem[] = "4   ";

  strcpy (&szItem[1], IntToHex(codeReq, 3).c_str());  // exemple 0x902 -> "4902"
  strcpy(Str1, src);

  for (int i= lgbuf-1; i > 0; i--) {       // raccourcir la chaine?
    if ((Str1[i] == '*') || (Str1[i] == '>')) {
      Str1[i] = 0;
    }
    else break;
  }
  pStr = chercheStrApres ( Str1, szItem , Str2);
  if (pStr == NULL) {
    strcpy(dst, Str1);
    return (-1);
  }


  //if ( CheckSum(Str2) == hexaToInt( &Str2[lgbuf - 2] ) )  {
  if (HeadersOn)  { // checksum présent ?
    Str2[strlen(Str2) - 2] = 0; // on enlève le checksum
  }
  strcpy (dst, Str2);
  return (hexaToInt(dst));
}
//---------------------------------------------------------------------------
// BlirePIDClick()
//---------------------------------------------------------------------------
void __fastcall TForm1::BlirePIDClick(TObject *Sender)
{
  thListReq = new TthreadListeRequete(false, 4); // creation Thread scrutation PID
}
//---------------------------------------------------------------------------
// CodeReqToChar() conversion en ASCII
//---------------------------------------------------------------------------
char *TForm1::CodeReqToChar(int codeReq, char *req)
{
  char TabAscci[] = "0123456789ABCDEF";
  req[0] = TabAscci[(codeReq >> 12) & 15];
  req[1] = TabAscci[(codeReq >> 8 ) & 15];
  req[2] = TabAscci[(codeReq >> 4 ) & 15];
  req[3] = TabAscci[ codeReq  & 15];
  switch (codeReq & 0xF00) {
    case 0x200:  req[4] = '0'; req[5] = '0'; req[6] = '\r'; req[7] = 0; break;
    case 0x700:
    case 0x300:  req[2] = '\r'; req[3] = 0; break;
    case 0x800:  strcpy( &req[4], "0000000000\r"); break;
    default:     req[4] = '\r'; req[5] = 0; break;
  }
  return (req);
}

//---------------------------------------------------------------------------
// Quitter_Click()
//---------------------------------------------------------------------------
void __fastcall TForm1::Quitter_Click(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
char *TForm1::doubleSlach(char *dest, AnsiString AsChaine)
{     // génère des doubles '\\'
  int i, j;
  char src[512];
  strcpy(src, AsChaine.c_str() );

  int lg = strlen(src);
  for (i=0, j=0; (j<512) && (i<lg); i++, j++) {
    if (src[i]== '\\') dest[j++] = '\\';
    dest[j] = src[i];
  }
  dest[j] = 0;
  return(dest);
}
//---------------------------------------------------------------------------
// trouver() : trouver une chaine dans un fichier
//---------------------------------------------------------------------------
int TForm1::trouver(FILE *fic_, char *chaine)
{
  char ligne [512];
  int i, res;
  fseek(fic_, 0, SEEK_SET	);  // debut fichier

  while (fgets(ligne, 512, fic_) != NULL) {
    bool detect = false;
    for (i=0; i<strlen(chaine); i++) {
      if (ligne[i] == chaine[i]) detect = true;
      else {
        detect = false;
        break;
      }
    }
    if ( (i>0) && (detect)) {
      return(1);
    }
    //if (strcmp(chaine, ligne) >= 0) return(1);
  }
  return(0);
}
//---------------------------------------------------------------------------
// Lecture des fichier log
//  Les fonctions qui suivent permettent sans se connecter
//  - de lire les requètes issues d'un fichier log préalablement enregistré
//  - de les ordonner dans tableau dynamique (req)
//  - d'éliminer les doublons de ces requètes
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// SimulerClick()  Lit un fichier log au lieu de se connecter à l'ELM
//---------------------------------------------------------------------------
void __fastcall TForm1::SimulerClick(TObject *Sender)
{
  OpenDialog1->Options.Clear();
  //OpenDialog1->InitialDir = "d:\Builder_Prj\OBD2";
  OpenDialog1->Options << ofAllowMultiSelect;// << ofFileMustExist;
  OpenDialog1->Filter = "Fichiers txt (*.txt)|*.txt|Tous fichiers (*.*)|*.*";
  OpenDialog1->FilterIndex = 1; // démarre la boîte de dialogue montrant tous les fichiers
  AnsiString AsNomFic;
  //OpenDialog1->FileName = "GPXessai.gpx";
  if (OpenDialog1->Execute())
  {
    char nomFich[512];
    ficSimu = fopen(doubleSlach(nomFich, OpenDialog1->FileName),"r");
    if (!ficSimu){
      Application->MessageBox(OpenDialog1->FileName.c_str(), "Erreur Ouverture", MB_OK);
      return;
    }
    Form1->Caption = "OBD2bv - Diagnostic moteurs | Simulation: " + OpenDialog1->FileName;
    MemoAffi->Add("Simulation | Lecture fichier log: " + OpenDialog1->FileName);

    int nb = lireFicLog(ficSimu);
    MemoAffi->Add(IntToStr(nb) + " requètes ont été détectées");
    nb = filtrerLog();
    MemoAffi->Add("Filtrage:  " + IntToStr(nb) + " requètes ont été gardées");

    BConnect->Enabled = false;
    Bsimul->Enabled = false;
    Simuler->Enabled = false;
    simulation = true;

    LanceListeReqInit();
  }
}
//---------------------------------------------------------------------------
int TForm1::lireFicLog(FILE *fic1)
{
  char ligne [512], str[512];
  int i, res, noReq = 0, noRep=0, lgReq=0;
  TREQ *pReq = NULL;
  bool bQuestion = false;
  char *pStr;

  fseek(fic1, 0, SEEK_SET	);  // debut fichier

  while (fgets(ligne, 512, fic1) != NULL) {

    int lg= strlen(ligne);
    if (ligne[lg-1] == '\n') ligne[lg-1] = 0;    // suppression des \n
    lg= strlen(ligne);
    if ( (ligne[lg-1] == 'r') && (ligne[lg-2] == '\\') ) {
      ligne[lg-2] = '\r';         // remplacement des "\\r" par "\r"
      ligne[lg-1] = 0;
    }

    pStr = chercheItem(ligne, "  1: ", str);
    if (pStr != NULL) {
      if (bQuestion) pReq->nbR = noRep;
      reqSim.push_back ( TREQ(noReq, pStr) );  // nouveau reqSim
      pReq = &reqSim.at(noReq);
      if (pStr[0] != 'A') {
        int lg = strlen(pStr);
        //if (pStr[lg-2] == '\\') pStr[lg-2] = 0;
        char strReq[10];
        strncpy (strReq, pStr, 9); strReq[9] = 0; // seuls les 9 1er car sont gardés
        for (i=0; i< strlen(strReq); i++) {
          if (strReq[i] == '\r') strReq[i] = 0;          // suppression \r
        }
        lgReq = strlen(strReq);
        sscanf ( strReq, "%x", &pReq->codePID);
        switch (lgReq) {
          case 2: pReq->codePID <<=8; break;
          case 6: pReq->sousPID = pReq->codePID & 0xFF;
                  pReq->codePID >>=8;
                  break;
          case 8: pReq->sousPID = pReq->codePID & 0xFFFF;
                  pReq->codePID >>=16;
                  break;
        }

      }
      else {          // Détection requète Headers On / Off
        if (strcmp (pStr, "ATH1\r") == 0) {
          HeadersOn = true;
        }
        else if (strcmp (pStr, "ATH0\r") == 0) {
          HeadersOn = false;
        }
      }
      pReq->HeadersOn = HeadersOn ;
      bQuestion = true;
      ++noReq;
      noRep = 0;
    }
    else if (bQuestion) {
      //pStr = chercheItem(ligne, " cr=", str);
      int cr = chercheValApres3(ligne, " cr=", str);

      if (cr >=0) {
        pReq->cr [noRep] = cr;   // !!! 29 car sont insuffisants pour les requètes 0902...
        strncpy(pReq->reponse [noRep], str, 149);
        //Memo1->Lines->Add(" cr=" + AnsiString(cr) + " " + AnsiString(str));
        pReq->reponse [noRep][149]=0;
        if (noRep < 9) ++noRep;
      }
    }
  }
  nbReqSim = noReq;
  return(nbReqSim);
}
//---------------------------------------------------------------------------
//  BfiltreClick() suppression des doublons
//---------------------------------------------------------------------------
int TForm1::filtrerLog()
{
  TREQ *pReq1, *pReq2;

  if (reqSim.empty() ) return(0);

  for (int i=0 ; i < (reqSim.size()-1) ;  i++) {
    pReq1 = &reqSim.at(i);
    for (int j=i+1; j < reqSim.size(); j++) {
      pReq2 = &reqSim.at(j);
      if ( (!strcmp(pReq1->question, pReq2->question) )
          && (pReq1->HeadersOn == pReq2->HeadersOn)) {   // requètes égales ?
        // lequel garder ?
        int nbR1 = pReq1->nbR;                 // nombre de réponses
        int cr1 = pReq1->cr[nbR1-1];
        if ( (cr1 > 256) && (cr1 < 266)) {     // supprimer le 1er
          reqSim.erase(pReq1);
          --i;
          continue;
        }
        int nbR2 = pReq2->nbR;                 // nombre de réponses
        int cr2 = pReq2->cr[nbR2-1];
        if ( (cr2 > 256) && (cr2 < 266)) {     // supprimer 2eme
          reqSim.erase(pReq2);
          --j;
          continue;
        }
        if (nbR2 > nbR1) {
           reqSim.erase(pReq1);
           --i;
           continue;
        }else if (nbR2 < nbR1) {
           reqSim.erase(pReq2);
           --j;
           continue;
        }else {                                // détermination des réponses les plus longues
          int k, lg, lg1=0, lg2=0;
          for (k=0; k<nbR1; k++) if ( (lg=strlen (pReq1->reponse[k])) > lg1) lg1 = lg;
          for (k=0; k<nbR2; k++) if ( (lg=strlen (pReq2->reponse[k])) > lg1) lg2 = lg;
          if (lg1 > lg2) {
            reqSim.erase(pReq2);                 // on supprime la 2eme
            --j;
          }else {
            reqSim.erase(pReq1);                 // on supprime la 1ere
            --i;
          }
        }

      }
    }
  }
  nbReqSim = reqSim.size();
  return(nbReqSim);
}
//---------------------------------------------------------------------------
// Fin de la zone de Lecture des fichier log
//---------------------------------------------------------------------------

void __fastcall TForm1::AproposClick(TObject *Sender)
{
  Application->MessageBox(Form1->Caption.c_str() , "Diagnostic moteurs via inferface ELM 327", MB_OK);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::siteweb1Click(TObject *Sender)
{
  ShellExecute ( Application->Handle,"open","https://sites.google.com/site/obd2opensource/home",NULL,NULL,SW_NORMAL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
  if (RadioGroup1->ItemIndex == 0) {
    EditIP->Visible = true;
    EditPortTcp->Visible = true;
    ComboBox1->Visible = false;
    Edit2->Visible = false;
    CheckBox1->Visible = false;
    GroupBox1->Visible = false;
    Label3->Visible = true;
    Label1->Visible = false;
    Label2->Visible = false;
    Bactualiser->Visible = false;
  }
  else {
    EditIP->Visible = false;
    EditPortTcp->Visible = false;
    ComboBox1->Visible = true;
    Edit2->Visible = true;
    CheckBox1->Visible = true;
    GroupBox1->Visible = true;
    Label3->Visible = false;
    Label1->Visible = true;
    Label2->Visible = true;
    Bactualiser->Visible = true;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
  // gestion des Time-out en reception RS232 ou USB 
  Timer3->Tag += 1;
}
//---------------------------------------------------------------------------

