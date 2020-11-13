
EGClusterDumpReaderps.dll: dlldata.obj EGClusterDumpReader_p.obj EGClusterDumpReader_i.obj
	link /dll /out:EGClusterDumpReaderps.dll /def:EGClusterDumpReaderps.def /entry:DllMain dlldata.obj EGClusterDumpReader_p.obj EGClusterDumpReader_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EGClusterDumpReaderps.dll
	@del EGClusterDumpReaderps.lib
	@del EGClusterDumpReaderps.exp
	@del dlldata.obj
	@del EGClusterDumpReader_p.obj
	@del EGClusterDumpReader_i.obj
