
EGTotalScanReaderps.dll: dlldata.obj EGTotalScanReader_p.obj EGTotalScanReader_i.obj
	link /dll /out:EGTotalScanReaderps.dll /def:EGTotalScanReaderps.def /entry:DllMain dlldata.obj EGTotalScanReader_p.obj EGTotalScanReader_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EGTotalScanReaderps.dll
	@del EGTotalScanReaderps.lib
	@del EGTotalScanReaderps.exp
	@del dlldata.obj
	@del EGTotalScanReader_p.obj
	@del EGTotalScanReader_i.obj
