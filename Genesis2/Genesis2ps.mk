
Genesis2ps.dll: dlldata.obj Genesis2_p.obj Genesis2_i.obj
	link /dll /out:Genesis2ps.dll /def:Genesis2ps.def /entry:DllMain dlldata.obj Genesis2_p.obj Genesis2_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Genesis2ps.dll
	@del Genesis2ps.lib
	@del Genesis2ps.exp
	@del dlldata.obj
	@del Genesis2_p.obj
	@del Genesis2_i.obj
