
EGVertigoScanReaderps.dll: dlldata.obj EGVertigoScanReader_p.obj EGVertigoScanReader_i.obj
	link /dll /out:EGVertigoScanReaderps.dll /def:EGVertigoScanReaderps.def /entry:DllMain dlldata.obj EGVertigoScanReader_p.obj EGVertigoScanReader_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EGVertigoScanReaderps.dll
	@del EGVertigoScanReaderps.lib
	@del EGVertigoScanReaderps.exp
	@del dlldata.obj
	@del EGVertigoScanReader_p.obj
	@del EGVertigoScanReader_i.obj
