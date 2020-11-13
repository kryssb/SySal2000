
IdentityMapps.dll: dlldata.obj IdentityMap_p.obj IdentityMap_i.obj
	link /dll /out:IdentityMapps.dll /def:IdentityMapps.def /entry:DllMain dlldata.obj IdentityMap_p.obj IdentityMap_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del IdentityMapps.dll
	@del IdentityMapps.lib
	@del IdentityMapps.exp
	@del dlldata.obj
	@del IdentityMap_p.obj
	@del IdentityMap_i.obj
