#ifndef ListePortsH
#define ListePortsH
//---------------------------------------------------------------------------
// Classe et Fonction CALLBACK de lecture de la Registry  (listport.h)
//---------------------------------------------------------------------------

#include <Classes.hpp>

#define PORT_NAME_BUF_SIZE    8

typedef struct
{
  LPCTSTR lpPortName;     /* "COM1", etc. */
  LPCTSTR lpFriendlyName; /* Suitable to describe the port, as for  */
                          /* instance "Infrared serial port (COM4)" */
  LPCTSTR lpTechnology;   /* "BIOS","INFRARED","USB", etc.          */
}LISTPORTS_PORTINFO;

typedef BOOL (CALLBACK* LISTPORTS_CALLBACK)(LPVOID              lpCallbackValue,
                                            LISTPORTS_PORTINFO* lpPortInfo);
/* User provided callback funtion that receives the information on each
 * serial port available.
 * The strings provided on the LISTPORTS_INFO are not to be referenced after
 * the callback returns; instead make copies of them for later use.
 * If the callback returns FALSE, port enumeration is aborted.
 */
BOOL CALLBACK listport_callback(LPVOID lpCallbackValue, LISTPORTS_PORTINFO* lpPortInfo);
int ports_cmp(const void* port1, const void* port2);

//--------------------------------------------------------
class REG
{
  public:
    int get_port_names(char** list, int* list_size);

    char* ports_list;
    int ports_list_index;
    int ports_list_size;

  private:
    //BOOL CALLBACK listport_callback(LPVOID lpCallbackValue, LISTPORTS_PORTINFO* lpPortInfo);
    BOOL ListPorts(LISTPORTS_CALLBACK lpCallback,LPVOID lpCallbackValue);
/* Lists serial ports available on the system, passing the information on
 * each port on succesive calls to lpCallback.
 * lpCallbackValue, treated opaquely by ListPorts(), is intended to carry
 * information internal to the callback routine.
 * Returns TRUE if succesful, otherwise error code can be retrieved via
 * GetLastError().
 */
    BOOL WinNT40ListPorts(LISTPORTS_CALLBACK lpCbk,LPVOID lpCbkValue);

};

extern REG Reg; // la fonction CALLBACK listport_callback a accès à certaines variables...
#endif
