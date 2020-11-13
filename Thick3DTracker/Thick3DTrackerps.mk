
Thick3DTrackerps.dll: dlldata.obj Thick3DTracker_p.obj Thick3DTracker_i.obj
	link /dll /out:Thick3DTrackerps.dll /def:Thick3DTrackerps.def /entry:DllMain dlldata.obj Thick3DTracker_p.obj Thick3DTracker_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Thick3DTrackerps.dll
	@del Thick3DTrackerps.lib
	@del Thick3DTrackerps.exp
	@del dlldata.obj
	@del Thick3DTracker_p.obj
	@del Thick3DTracker_i.obj
