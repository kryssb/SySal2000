
DBSySalIOps.dll: dlldata.obj DBSySalIO_p.obj DBSySalIO_i.obj
	link /dll /out:DBSySalIOps.dll /def:DBSySalIOps.def /entry:DllMain dlldata.obj DBSySalIO_p.obj DBSySalIO_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del DBSySalIOps.dll
	@del DBSySalIOps.lib
	@del DBSySalIOps.exp
	@del dlldata.obj
	@del DBSySalIO_p.obj
	@del DBSySalIO_i.obj
