
BetaBrainps.dll: dlldata.obj BetaBrain_p.obj BetaBrain_i.obj
	link /dll /out:BetaBrainps.dll /def:BetaBrainps.def /entry:DllMain dlldata.obj BetaBrain_p.obj BetaBrain_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del BetaBrainps.dll
	@del BetaBrainps.lib
	@del BetaBrainps.exp
	@del dlldata.obj
	@del BetaBrain_p.obj
	@del BetaBrain_i.obj
