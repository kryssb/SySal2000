
ThetaTSReconstructps.dll: dlldata.obj ThetaTSReconstruct_p.obj ThetaTSReconstruct_i.obj
	link /dll /out:ThetaTSReconstructps.dll /def:ThetaTSReconstructps.def /entry:DllMain dlldata.obj ThetaTSReconstruct_p.obj ThetaTSReconstruct_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del ThetaTSReconstructps.dll
	@del ThetaTSReconstructps.lib
	@del ThetaTSReconstructps.exp
	@del dlldata.obj
	@del ThetaTSReconstruct_p.obj
	@del ThetaTSReconstruct_i.obj
