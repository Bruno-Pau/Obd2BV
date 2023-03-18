#include "ListePorts.h"
//---------------------------------------------------------------------------
// Fonctions CALLBACK de lecture de la Registry (listport.c)
// Permet de recuperer la liste des Ports COM du systeme
//---------------------------------------------------------------------------
static BOOL CALLBACK listport_callback(LPVOID lpCallbackValue, LISTPORTS_PORTINFO* lpPortInfo)
{
   char* new_list;
   int new_size;

   //if (strlen(lpPortInfo->lpPortName) < PORT_NAME_BUF_SIZE && strnicmp(lpPortInfo->lpPortName, "COM", 3) == 0)
   if (strlen(lpPortInfo->lpPortName) < PORT_NAME_BUF_SIZE )
   {
      if (Reg.ports_list_index == Reg.ports_list_size)
      {
         new_size = Reg.ports_list_size + 8;
         new_list = (char*)realloc(Reg.ports_list, new_size * PORT_NAME_BUF_SIZE);
         if (new_list == NULL)
            return FALSE;
         Reg.ports_list = new_list;
         Reg.ports_list_size = new_size;
      }

      strncpy(Reg.ports_list + Reg.ports_list_index * PORT_NAME_BUF_SIZE, lpPortInfo->lpPortName, 7);
      Reg.ports_list_index++;
   }

   return TRUE;
}

//-----------------------------------------------
static int ports_cmp(const void* port1, const void* port2)
{
   int len1 = strlen((char *)port1);
   int len2 = strlen((char *)port2);

   if (len1 > len2)
      return 1;
   else if (len1 < len2)
      return -1;
   else
      return stricmp((char *)port1, (char *)port2);
}
//---------------------------------------------------------------------------
// Classe de lecture de la Registry (listport.c)
//---------------------------------------------------------------------------

BOOL REG::ListPorts(LISTPORTS_CALLBACK lpCbk,LPVOID lpCbkValue)
{
  OSVERSIONINFO osvinfo;

  /* check parameters */

  if(!lpCbk){
    SetLastError((unsigned long)ERROR_INVALID_PARAMETER);
    return FALSE;
  }

  /* determine which platform we're running on and forward
   * to the appropriate routine
   */

  ZeroMemory(&osvinfo,sizeof(osvinfo));
  osvinfo.dwOSVersionInfoSize=sizeof(osvinfo);

  GetVersionEx(&osvinfo);

  switch(osvinfo.dwPlatformId){
    //case VER_PLATFORM_WIN32_WINDOWS:
    //  return Win9xListPorts(lpCbk,lpCbkValue);
    //  break;
    case VER_PLATFORM_WIN32_NT:
      return WinNT40ListPorts(lpCbk,lpCbkValue);
      //break;
    default:
      SetLastError((unsigned long)ERROR_OLD_WIN_VERSION);
      return FALSE;
      //break;
  }
  return (false);
}
//------------------------------------------------------------------------------
// Lecture dans la base de registres HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM
//  de l'énumération des ports séries
//------------------------------------------------------------------------------
BOOL REG::WinNT40ListPorts(LISTPORTS_CALLBACK lpCbk,LPVOID lpCbkValue)
{
  DWORD  dwError=0;
  HKEY   hKey=NULL;
  DWORD  dwIndex;
  LPTSTR lpValueName=NULL;
  LPTSTR lpPortName=NULL;

  if((dwError=RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"),
                          0,KEY_READ,&hKey)) != 0){
    // it is really strange that this key does not exist, but could happen in theory
    if(dwError==ERROR_FILE_NOT_FOUND)dwError=0;
    goto end;
  }

  for(dwIndex=0;;++dwIndex){
    DWORD              cbValueName=32*sizeof(TCHAR);
    DWORD              cbPortName=32*sizeof(TCHAR);
    LISTPORTS_PORTINFO portinfo;

    // loop asking for the value data til we allocated enough memory

    for(;;){
      free(lpValueName);
      if(!(lpValueName=(LPTSTR)malloc(cbValueName))){
        dwError=ERROR_NOT_ENOUGH_MEMORY;
        goto end;
      }
      free(lpPortName);
      if(!(lpPortName=(LPTSTR)malloc(cbPortName))){
        dwError=ERROR_NOT_ENOUGH_MEMORY;
        goto end;
      }
      if(!(dwError=RegEnumValue(hKey,dwIndex,lpValueName,&cbValueName,
                                NULL,NULL,(LPBYTE)lpPortName,&cbPortName))){
        break; // we did it
      }
      else if(dwError==ERROR_MORE_DATA){ // not enough space
        dwError=0;
        // no indication of space required, we try doubling
        cbValueName=(cbValueName+sizeof(TCHAR))*2;
      }
      else goto end;
    }

    portinfo.lpPortName=lpPortName;
    portinfo.lpFriendlyName=lpPortName; // no friendly name in NT 4.0
    portinfo.lpTechnology=TEXT(""); // this information is not available
    if(!lpCbk(lpCbkValue,&portinfo)){
      goto end; // listing aborted by callback
    }
  } 

end:
  free(lpValueName);
  free(lpPortName);
  if(hKey!=NULL)RegCloseKey(hKey);
  if(dwError!=0){
    SetLastError(dwError);
    return FALSE;
  }
  else return TRUE;
}

//-----------------------------------------------
int REG::get_port_names(char** list, int* list_size)
{
   int i, j;
   char* new_list;
   int new_list_size = 0;

   if(list == NULL)return(-1);
   if(list_size == NULL)return(-1);
   
   *list = NULL;
   *list_size = 0;
   
   ports_list = NULL;
   ports_list_size = 0;
   ports_list_index = 0;
   
   ListPorts(listport_callback, NULL);
   
   if (ports_list_index == 0)
      return 0;
   
   // Remove duplicates
   for (i = 0; i < ports_list_index; i++)
   {
      for (j = 0; j < new_list_size; j++)
         if (strcmp(ports_list + i * PORT_NAME_BUF_SIZE, ports_list + j * PORT_NAME_BUF_SIZE) == 0)
            break;
      if (j == new_list_size)
      {
         if (new_list_size != i)
            strncpy(ports_list + new_list_size * PORT_NAME_BUF_SIZE, ports_list + i * PORT_NAME_BUF_SIZE, PORT_NAME_BUF_SIZE - 1);
         new_list_size++;
      }
   }
   
   // Shrink
   if (new_list_size < ports_list_size)
   {
      new_list = (char*)realloc(ports_list, new_list_size * PORT_NAME_BUF_SIZE);
      if (new_list != NULL)
         ports_list = new_list;
   }

   // Sort
   qsort(ports_list, new_list_size, PORT_NAME_BUF_SIZE, ports_cmp);

   *list = ports_list;
   *list_size = new_list_size;
   return 0;
}
//---------------------------------------------------------------------------

