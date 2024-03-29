!macro MediaInfo_Extensions_Install_I Extension
  ; Old InfoTip
  DeleteRegKey HKCR "${Extension}\shellex\{00021500-0000-0000-C000-000000000046}"
  DeleteRegKey /ifempty HKCR "${Extension}\shellex"
  ; Old Extension
  ReadRegStr $1 HKCR "${Extension}" ""
  DeleteRegKey HKCR "$1\Shell\Media Info"
  DeleteRegKey HKCR "$1\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "$1\Shell"
  DeleteRegKey /ifempty HKCR "$1"
  ; Old Extension (folder...)
  DeleteRegKey HKCR "${Extension}\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "${Extension}\Shell"
  ; Old Extension (in 1 version)
  DeleteRegKey HKCR "SystemFileAssociations\${Extension}\Shell\MediaInfo"
  DeleteRegKey /ifempty HKCR "SystemFileAssociations\${Extension}\Shell"
!macroend

!macro MediaInfo_Extensions_Uninstall_I Extension
  ; InfoTip
  DeleteRegKey HKCU "Software\Classes\${Extension}\shellex\{00021500-0000-0000-C000-000000000046}"
  DeleteRegKey /ifempty HKCU "Software\Classes\${Extension}\shellex"
  ; Extension
  DeleteRegKey HKCU "Software\Classes\SystemFileAssociations\${Extension}\shell\MediaInfo"
  DeleteRegKey /ifempty HKCU "Software\Classes\SystemFileAssociations\${Extension}\shell"
!macroend

!macro MediaInfo_Extensions_Install
  ; Per item
  !insertmacro MediaInfo_Extensions_Install_I ".3gp"
  !insertmacro MediaInfo_Extensions_Install_I ".3gpp"
  !insertmacro MediaInfo_Extensions_Install_I ".aac"
  !insertmacro MediaInfo_Extensions_Install_I ".ac3"
  !insertmacro MediaInfo_Extensions_Install_I ".ape"
  !insertmacro MediaInfo_Extensions_Install_I ".asf"
  !insertmacro MediaInfo_Extensions_Install_I ".avi"
  !insertmacro MediaInfo_Extensions_Install_I ".bdmv"
  !insertmacro MediaInfo_Extensions_Install_I ".clpi"
  !insertmacro MediaInfo_Extensions_Install_I ".dat"
  !insertmacro MediaInfo_Extensions_Install_I ".divx"
  !insertmacro MediaInfo_Extensions_Install_I ".dpg"
  !insertmacro MediaInfo_Extensions_Install_I ".dts"
  !insertmacro MediaInfo_Extensions_Install_I ".dv"
  !insertmacro MediaInfo_Extensions_Install_I ".dvr"
  !insertmacro MediaInfo_Extensions_Install_I ".dvr-ms"
  !insertmacro MediaInfo_Extensions_Install_I ".eac3"
  !insertmacro MediaInfo_Extensions_Install_I ".evo"
  !insertmacro MediaInfo_Extensions_Install_I ".flac"
  !insertmacro MediaInfo_Extensions_Install_I ".f4v"
  !insertmacro MediaInfo_Extensions_Install_I ".flv"
  !insertmacro MediaInfo_Extensions_Install_I ".gvi"
  !insertmacro MediaInfo_Extensions_Install_I ".h264"
  !insertmacro MediaInfo_Extensions_Install_I ".ifo"
  !insertmacro MediaInfo_Extensions_Install_I ".isma"
  !insertmacro MediaInfo_Extensions_Install_I ".ismv"
  !insertmacro MediaInfo_Extensions_Install_I ".j2k"
  !insertmacro MediaInfo_Extensions_Install_I ".jp2"
  !insertmacro MediaInfo_Extensions_Install_I ".m1s"
  !insertmacro MediaInfo_Extensions_Install_I ".m1t"
  !insertmacro MediaInfo_Extensions_Install_I ".m1v"
  !insertmacro MediaInfo_Extensions_Install_I ".m2p"
  !insertmacro MediaInfo_Extensions_Install_I ".m2s"
  !insertmacro MediaInfo_Extensions_Install_I ".m2t"
  !insertmacro MediaInfo_Extensions_Install_I ".m2ts"
  !insertmacro MediaInfo_Extensions_Install_I ".m2v"
  !insertmacro MediaInfo_Extensions_Install_I ".m4a"
  !insertmacro MediaInfo_Extensions_Install_I ".m4v"
  !insertmacro MediaInfo_Extensions_Install_I ".mac"
  !insertmacro MediaInfo_Extensions_Install_I ".mka"
  !insertmacro MediaInfo_Extensions_Install_I ".mks"
  !insertmacro MediaInfo_Extensions_Install_I ".mkv"
  !insertmacro MediaInfo_Extensions_Install_I ".mod"
  !insertmacro MediaInfo_Extensions_Install_I ".mov"
  !insertmacro MediaInfo_Extensions_Install_I ".mp+"
  !insertmacro MediaInfo_Extensions_Install_I ".mp2"
  !insertmacro MediaInfo_Extensions_Install_I ".mp3"
  !insertmacro MediaInfo_Extensions_Install_I ".mp4"
  !insertmacro MediaInfo_Extensions_Install_I ".mpc"
  !insertmacro MediaInfo_Extensions_Install_I ".mpe"
  !insertmacro MediaInfo_Extensions_Install_I ".mpeg"
  !insertmacro MediaInfo_Extensions_Install_I ".mpg"
  !insertmacro MediaInfo_Extensions_Install_I ".mpgv"
  !insertmacro MediaInfo_Extensions_Install_I ".mpgx"
  !insertmacro MediaInfo_Extensions_Install_I ".mpls"
  !insertmacro MediaInfo_Extensions_Install_I ".mpm"
  !insertmacro MediaInfo_Extensions_Install_I ".mpv"
  !insertmacro MediaInfo_Extensions_Install_I ".mts"
  !insertmacro MediaInfo_Extensions_Install_I ".mxf"
  !insertmacro MediaInfo_Extensions_Install_I ".oga"
  !insertmacro MediaInfo_Extensions_Install_I ".ogg"
  !insertmacro MediaInfo_Extensions_Install_I ".ogm"
  !insertmacro MediaInfo_Extensions_Install_I ".ogv"
  !insertmacro MediaInfo_Extensions_Install_I ".qt"
  !insertmacro MediaInfo_Extensions_Install_I ".ra"
  !insertmacro MediaInfo_Extensions_Install_I ".rm"
  !insertmacro MediaInfo_Extensions_Install_I ".rmvb"
  !insertmacro MediaInfo_Extensions_Install_I ".smv"
  !insertmacro MediaInfo_Extensions_Install_I ".swf"
  !insertmacro MediaInfo_Extensions_Install_I ".tp"
  !insertmacro MediaInfo_Extensions_Install_I ".trp"
  !insertmacro MediaInfo_Extensions_Install_I ".ts"
  !insertmacro MediaInfo_Extensions_Install_I ".tta"
  !insertmacro MediaInfo_Extensions_Install_I ".vob"
  !insertmacro MediaInfo_Extensions_Install_I ".w64"
  !insertmacro MediaInfo_Extensions_Install_I ".wav"
  !insertmacro MediaInfo_Extensions_Install_I ".wma"
  !insertmacro MediaInfo_Extensions_Install_I ".wmv"
  !insertmacro MediaInfo_Extensions_Install_I ".wv"
  !insertmacro MediaInfo_Extensions_Install_I ".wvc"
  !insertmacro MediaInfo_Extensions_Install_I "Folder"
  !insertmacro MediaInfo_Extensions_Install_I "audio"
  !insertmacro MediaInfo_Extensions_Install_I "Directory.Audio"
  !insertmacro MediaInfo_Extensions_Install_I "Directory.Video"
  !insertmacro MediaInfo_Extensions_Install_I "video"
!macroend

!macro MediaInfo_Extensions_Uninstall
  ;Old stuff
  !insertmacro MediaInfo_Extensions_Install

  ; Global
  DeleteRegKey HKCU "Software\Classes\CLSID\{869C14C8-1830-491F-B575-5F9AB40D2B42}"
  DeleteRegKey HKCU "Software\Classes\MediaInfoShellExt.MediaInfoShellExt_"
  DeleteRegKey HKCU "Software\Classes\MediaInfoShellExt.MediaInfoShellExt_.1"

  !insertmacro MediaInfo_Extensions_Uninstall_I ".3gp"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".3gpp"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".aac"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ac3"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ape"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".asf"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".avi"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".bdmv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".clpi"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".dat"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".divx"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".dpg"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".dts"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".dv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".dvr"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".dvr-ms"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".eac3"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".evo"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".f4v"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".flac"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".flv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".gvi"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".h264"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ifo"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".isma"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ismv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".j2k"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".jp2"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m1s"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m1t"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m1v"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m2p"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m2s"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m2t"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m2ts"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m2v"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m4a"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".m4v"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mac"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mka"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mks"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mkv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mod"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mov"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mp+"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mp2"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mp3"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mp4"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpc"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpe"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpeg"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpg"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpgv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpgx"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpls"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpm"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mpv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mts"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".mxf"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".oga"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ogg"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ogm"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ogv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".qt"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ra"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".rm"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".rmvb"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".smv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".swf"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".tp"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".trp"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".ts"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".tta"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".vob"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".w64"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".wav"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".wma"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".wmv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".wv"
  !insertmacro MediaInfo_Extensions_Uninstall_I ".wvc"
  !insertmacro MediaInfo_Extensions_Uninstall_I "Folder"
  !insertmacro MediaInfo_Extensions_Uninstall_I "audio"
  !insertmacro MediaInfo_Extensions_Uninstall_I "Directory.Audio"
  !insertmacro MediaInfo_Extensions_Uninstall_I "Directory.Video"
  !insertmacro MediaInfo_Extensions_Uninstall_I "video"
!macroend


