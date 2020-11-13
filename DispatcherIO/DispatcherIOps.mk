
DispatcherIOps.dll: dlldata.obj DispatcherIO_p.obj DispatcherIO_i.obj
	link /dll /out:DispatcherIOps.dll /def:DispatcherIOps.def /entry:DllMain dlldata.obj DispatcherIO_p.obj DispatcherIO_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DispatcherIOps.dll
	@del DispatcherIOps.lib
	@del DispatcherIOps.exp
	@del dlldata.obj
	@del DispatcherIO_p.obj
	@del DispatcherIO_i.obj
