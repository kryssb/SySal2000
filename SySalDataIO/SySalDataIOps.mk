
SySalDataIOps.dll: dlldata.obj SySalDataIO_p.obj SySalDataIO_i.obj
	link /dll /out:SySalDataIOps.dll /def:SySalDataIOps.def /entry:DllMain dlldata.obj SySalDataIO_p.obj SySalDataIO_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del SySalDataIOps.dll
	@del SySalDataIOps.lib
	@del SySalDataIOps.exp
	@del dlldata.obj
	@del SySalDataIO_p.obj
	@del SySalDataIO_i.obj
