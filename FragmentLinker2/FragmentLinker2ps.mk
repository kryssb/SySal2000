
FragmentLinker2ps.dll: dlldata.obj FragmentLinker2_p.obj FragmentLinker2_i.obj
	link /dll /out:FragmentLinker2ps.dll /def:FragmentLinker2ps.def /entry:DllMain dlldata.obj FragmentLinker2_p.obj FragmentLinker2_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del FragmentLinker2ps.dll
	@del FragmentLinker2ps.lib
	@del FragmentLinker2ps.exp
	@del dlldata.obj
	@del FragmentLinker2_p.obj
	@del FragmentLinker2_i.obj
