;NSIS Modern User Interface
;sOPC-Install Script

;--------------------------------
;Include Modern UI

  !include "MUI2.nsh"

;--------------------------------
;General

  ;Nom du programme et du fichier
  Name "Obd2bv"
  OutFile "Obd2bv_install_2_0.exe"

  ;Dossier d'installation par défaut
  InstallDir "$PROGRAMFILES\Obd2bv"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKLM "Software\Obd2bv" "Homepath"

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin
  
;--------------------------------
;Variables

  Var StartMenuFolder
  
;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  ;1er partie
  !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Docs\Modern UI\License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  
  ;Configuration du menu Démarrer/Programmes
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKLM" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\Obd2bv" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"
  !insertmacro MUI_PAGE_STARTMENU Application $StartMenuFolder
  
  ;2e partie
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages

  !insertmacro MUI_LANGUAGE "French"

;--------------------------------
;Installer Sections

;Section "sOpc" SecOPC
Section "Obd2bv" SecOBD
  
  ; Installation des fichiers du programme
  SetOutPath "$INSTDIR"
  File Obd2bv.exe
  
  ;Store installation folder
  WriteRegStr HKLM "Software\Obd2bv" "Homepath" "$INSTDIR\"
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall_Obd2bv.exe"
  
  ;StartMenuFolder
  !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
  
  ;Create Folder
    CreateDirectory "$SMPROGRAMS\$StartMenuFolder"
	
  ;Create shortcuts
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Obd2bv.lnk" "$INSTDIR\Obd2bv.exe"
    CreateShortCut "$SMPROGRAMS\$StartMenuFolder\Uninstall.lnk" "$INSTDIR\Uninstall_Obd2bv.exe"
  !insertmacro MUI_STARTMENU_WRITE_END

SectionEnd


Section /o "Sources" SecSrc

  ; Création des dossiers
  CreateDirectory "$INSTDIR\src"
  
  ; Sources du logiciel
  SetOutPath "$INSTDIR\src"
  File src\*.*      
  
  ;Autre fichiers
  SetOutPath "$INSTDIR\src"
  File Obd2bv_install_2_0.nsi

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SecOBD ${LANG_FRENCH} "Obd2bv 2.0."
  LangString DESC_SecSrc ${LANG_FRENCH} "Sources du programme." 
  
  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
   !insertmacro MUI_DESCRIPTION_TEXT ${SecOBD} $(DESC_SecOBD)
   !insertmacro MUI_DESCRIPTION_TEXT ${SecSrc} $(DESC_SecSrc)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;Supprime les sources
  Delete "$INSTDIR\src\*.*"
  Delete "$INSTDIR\src\*.*"
  RmDir "$INSTDIR\src"
  
  
  ;Supprime les fichiers du programme
  Delete "$INSTDIR\Obd2bv.exe"
  Delete "$INSTDIR\Uninstall_Obd2bv.exe"
  
  ; Supprime le dossier d'installation
  RMDir "$INSTDIR"
  
  ; Supprime les raccourcis et le dossier, du menu Démarrer/Programmes
  !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuFolder
  Delete "$SMPROGRAMS\$StartMenuFolder\*.lnk"
  RMDir "$SMPROGRAMS\$StartMenuFolder"
  
  ; Supprime la clé de programme de la base de registre
  DeleteRegKey /ifempty HKLM "Software\Obd2bv"

SectionEnd