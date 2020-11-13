@echo off
pushd

cd %1

:ASK
echo Choose MIL version for your Odyssey board:
echo 1: MIL 8.00.1318.03
echo 2: Old version (ONL build 650c)
set /p MILVER=Choose number:
 
IF %MILVER%==1 GOTO REG1
IF %MILVER%==2 GOTO REG2
GOTO ASK

:REG1
regsvr32 %1\Odyssey3_MIL_8.00.1318.03.dll /s
goto ENDLINE

:REG2
regsvr32 %1\Odyssey3_OldMIL.dll /s
goto ENDLINE

:ENDLINE

popd

exit