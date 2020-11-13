
EGTotalScanWriterps.dll: dlldata.obj EGTotalScanWriter_p.obj EGTotalScanWriter_i.obj
	link /dll /out:EGTotalScanWriterps.dll /def:EGTotalScanWriterps.def /entry:DllMain dlldata.obj EGTotalScanWriter_p.obj EGTotalScanWriter_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EGTotalScanWriterps.dll
	@del EGTotalScanWriterps.lib
	@del EGTotalScanWriterps.exp
	@del dlldata.obj
	@del EGTotalScanWriter_p.obj
	@del EGTotalScanWriter_i.obj
