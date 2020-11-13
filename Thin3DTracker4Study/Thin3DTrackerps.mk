
Thin3DTrackerps.dll: dlldata.obj Thin3DTracker_p.obj Thin3DTracker_i.obj
	link /dll /out:Thin3DTrackerps.dll /def:Thin3DTrackerps.def /entry:DllMain dlldata.obj Thin3DTracker_p.obj Thin3DTracker_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Thin3DTrackerps.dll
	@del Thin3DTrackerps.lib
	@del Thin3DTrackerps.exp
	@del dlldata.obj
	@del Thin3DTracker_p.obj
	@del Thin3DTracker_i.obj
