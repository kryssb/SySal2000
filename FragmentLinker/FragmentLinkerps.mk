
FragmentLinkerps.dll: dlldata.obj FragmentLinker_p.obj FragmentLinker_i.obj
	link /dll /out:FragmentLinkerps.dll /def:FragmentLinkerps.def /entry:DllMain dlldata.obj FragmentLinker_p.obj FragmentLinker_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FragmentLinkerps.dll
	@del FragmentLinkerps.lib
	@del FragmentLinkerps.exp
	@del dlldata.obj
	@del FragmentLinker_p.obj
	@del FragmentLinker_i.obj
