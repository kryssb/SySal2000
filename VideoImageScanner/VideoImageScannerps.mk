
VideoImageScannerps.dll: dlldata.obj VideoImageScanner_p.obj VideoImageScanner_i.obj
	link /dll /out:VideoImageScannerps.dll /def:VideoImageScannerps.def /entry:DllMain dlldata.obj VideoImageScanner_p.obj VideoImageScanner_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del VideoImageScannerps.dll
	@del VideoImageScannerps.lib
	@del VideoImageScannerps.exp
	@del dlldata.obj
	@del VideoImageScanner_p.obj
	@del VideoImageScanner_i.obj
