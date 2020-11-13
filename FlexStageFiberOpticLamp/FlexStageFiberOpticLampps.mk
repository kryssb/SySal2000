
FlexStageps.dll: dlldata.obj FlexStage_p.obj FlexStage_i.obj
	link /dll /out:FlexStageps.dll /def:FlexStageps.def /entry:DllMain dlldata.obj FlexStage_p.obj FlexStage_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FlexStageps.dll
	@del FlexStageps.lib
	@del FlexStageps.exp
	@del dlldata.obj
	@del FlexStage_p.obj
	@del FlexStage_i.obj
