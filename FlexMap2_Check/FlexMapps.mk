
FlexMapps.dll: dlldata.obj FlexMap_p.obj FlexMap_i.obj
	link /dll /out:FlexMapps.dll /def:FlexMapps.def /entry:DllMain dlldata.obj FlexMap_p.obj FlexMap_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FlexMapps.dll
	@del FlexMapps.lib
	@del FlexMapps.exp
	@del dlldata.obj
	@del FlexMap_p.obj
	@del FlexMap_i.obj
