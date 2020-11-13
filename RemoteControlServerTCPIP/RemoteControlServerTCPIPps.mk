
RemoteControlServerTCPIPps.dll: dlldata.obj RemoteControlServerTCPIP_p.obj RemoteControlServerTCPIP_i.obj
	link /dll /out:RemoteControlServerTCPIPps.dll /def:RemoteControlServerTCPIPps.def /entry:DllMain dlldata.obj RemoteControlServerTCPIP_p.obj RemoteControlServerTCPIP_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del RemoteControlServerTCPIPps.dll
	@del RemoteControlServerTCPIPps.lib
	@del RemoteControlServerTCPIPps.exp
	@del dlldata.obj
	@del RemoteControlServerTCPIP_p.obj
	@del RemoteControlServerTCPIP_i.obj
