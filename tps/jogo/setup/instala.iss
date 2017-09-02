#define MyAppName "Ameaça Terrorista"
#define MyAppVersion "1.0"
#define MyAppPublisher "Douglas R. Almeida"
#define MyAppURL "mailto://douglasralmeida@live.com"
#define MyAppExeName "aterror.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{6CF0BF32-837B-45F0-9D0C-81B7FFAB7064}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\Ameaca Terrorista
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputBaseFilename=ainstala
SetupIconFile=..\res\setupicone.ico
Compression=lzma
SolidCompression=yes
ShowLanguageDialog=no
UninstallDisplayName=Ameaça Terrorista
UninstallDisplaySize=44040192
UninstallDisplayIcon={app}\aterror.exe
VersionInfoVersion=1.0
VersionInfoProductName=Ameaça Terrorista
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64
MinVersion=0,6.1
WizardSmallImageFile=..\res\setup_img_pequena.bmp
WizardImageFile=..\res\setup_img_grande.bmp
OutputDir=..\ 
DefaultDialogFontName=Segoe UI

[Languages]
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\bin\aterror.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\recursos\*"; DestDir: "{app}\recursos"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "..\bin\mp4demux.dll"; DestDir: "{app}"; Flags: ignoreversion regserver sharedfile uninsnosharedfileprompt
Source: "..\bin\openal32.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro_acodec-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro_audio-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro_font-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro_image-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro_primitives-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro_ttf-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\allegro-5.1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libbz2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libfreetype-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libglib-2.0-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libharfbuzz-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libiconv-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libintl-8.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libjpeg-8.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libogg-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libpng16-16.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libvorbis-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libvorbisfile-3.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\bin\libs\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; IconFilename: "{app}\aterror.exe"; IconIndex: 0; Comment: "Executa o jogo Ameaça Terrorista."
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; Comment: "Remove o jogo Ameaça Terrorista do seu computador."
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; IconFilename: "{app}\aterror.exe"; IconIndex: 0; Comment: "Executa o jogo Ameaça Terrorista."; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; Flags: nowait postinstall skipifsilent; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"

