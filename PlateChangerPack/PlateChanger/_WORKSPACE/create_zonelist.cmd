
 
FOR /L %%I IN (57,-1,1) DO (
     echo %1,%%I,>>list.txt
     s:GetDBMarks.exe %1 %%I nominal L>>list.txt
     echo 0 , 80000, 80100 , 90000 , 90100,R:\temp\DUMMY_%%I_>>zonelist.txt
)
