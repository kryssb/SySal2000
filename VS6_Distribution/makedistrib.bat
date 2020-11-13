rd Exe /s /q
rd Src /s /q
md Exe
md Exe\Client
md Exe\Server
md Src
copy ..\VertigoScan6.0\ReleaseMinSize\*.dll Exe\Client\ 
copy ..\SmartTracker8.5\ReleaseMinSize\*.dll Exe\Client\
copy ..\SmartFitter2.3\ReleaseMinSize\*.dll Exe\Client\
copy ..\VertigoScan6.0\ReleaseMinSize\*.dll Exe\Server\
copy ..\SmartTracker8.5\ReleaseMinSize\*.dll Exe\Server\
copy ..\SmartFitter2.3\ReleaseMinSize\*.dll Exe\Server\
copy ..\VertigoScan6Server_Win\bin\Release\VertigoScan6Server_Win.exe Exe\Server\
md Src\DLLs
copy ..\DLLs\* Src\DLLs\
md Src\VertigoScan6.0
copy ..\VertigoScan6.0\* Src\VertigoScan6.0\
md Src\SmartTracker8.5
copy ..\SmartTracker8.5\* Src\SmartTracker8.5\
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