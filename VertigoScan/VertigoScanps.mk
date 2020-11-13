
VertigoScanps.dll: dlldata.obj VertigoScan_p.obj VertigoScan_i.obj
	link /dll /out:VertigoScanps.dll /def:VertigoScanps.def /entry:DllMain dlldata.obj VertigoScan_p.obj VertigoScan_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VertigoScanps.dll
	@del VertigoScanps.lib
	@del VertigoScanps.exp
	@del dlldata.obj
	@del VertigoScan_p.obj
	@del VertigoScan_i.obj
