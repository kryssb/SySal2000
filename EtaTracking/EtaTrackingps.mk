
EtaTrackingps.dll: dlldata.obj EtaTracking_p.obj EtaTracking_i.obj
	link /dll /out:EtaTrackingps.dll /def:EtaTrackingps.def /entry:DllMain dlldata.obj EtaTracking_p.obj EtaTracking_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del EtaTrackingps.dll
	@del EtaTrackingps.lib
	@del EtaTrackingps.exp
	@del dlldata.obj
	@del EtaTracking_p.obj
	@del EtaTracking_i.obj
