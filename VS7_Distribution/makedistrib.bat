rd Exe /s /q
rd Src /s /q
md Exe
md Exe\Client
md Exe\Server
md Src
copy ..\VertigoScan7.1\ReleaseMinSize\*.dll Exe\Client\ 
copy ..\SmartTracker8.5\ReleaseMinSize\*.dll Exe\Client\
copy ..\SmartTracker8.6\ReleaseMinSize\*.dll Exe\Client\
copy ..\SmartFitter2.3\ReleaseMinSize\*.dll Exe\Client\
copy ..\VertigoScan7.1\ReleaseMinSize\*.dll Exe\Server\
copy ..\SmartTracker8.5\ReleaseMinSize\*.dll Exe\Server\
copy ..\SmartTracker8.6\ReleaseMinSize\*.dll Exe\Server\
copy ..\SmartFitter2.3\ReleaseMinSize\*.dll Exe\Server\
copy ..\VertigoScan6Server_Win\bin\Release\VertigoScan6Server_Win.exe Exe\Server\
md Src\DLLs
copy ..\DLLs\* Src\DLLs\
md Src\VertigoScan7.1
copy ..\VertigoScan7.1\* Src\VertigoScan7.1\
md Src\SmartTracker8.5
copy ..\SmartTracker8.5\* Src\SmartTracker8.5\
md Src\SmartTracker8.6
copy ..\SmartTracker8.6\* Src\SmartTracker8.6\
md Src\SmartFitter2.3
copy ..\SmartFitter2.3\* Src\SmartFitter2.3\
md Src\VertigoScan6Server_Win
copy ..\VertigoScan6Server_Win\* Src\VertigoScan6Server_Win\
md Src\VertigoScan6Server_Win\Properties\
copy ..\VertigoScan6Server_Win\Properties\* Src\VertigoScan6Server_Win\Properties\
del Src\*.ncb /s
del Src\*.opt /s
del Src\*.aps /s
del Src\*.plg /s
del Src\*.obj /s
del Src\*.pdb /s
del Src\*.ilk /s