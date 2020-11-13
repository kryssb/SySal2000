
ScanServerps.dll: dlldata.obj ScanServer_p.obj ScanServer_i.obj
	link /dll /out:ScanServerps.dll /def:ScanServerps.def /entry:DllMain dlldata.obj ScanServer_p.obj ScanServer_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \
.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ScanServerps.dll
	@del ScanServerps.lib
	@del ScanServerps.exp
	@del dlldata.obj
	@del ScanServer_p.obj
	@del ScanServer_i.obj
