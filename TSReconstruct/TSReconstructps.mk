
TSReconstructps.dll: dlldata.obj TSReconstruct_p.obj TSReconstruct_i.obj
	link /dll /out:TSReconstructps.dll /def:TSReconstructps.def /entry:DllMain dlldata.obj TSReconstruct_p.obj TSReconstruct_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TSReconstructps.dll
	@del TSReconstructps.lib
	@del TSReconstructps.exp
	@del dlldata.obj
	@del TSReconstruct_p.obj
	@del TSReconstruct_i.obj
