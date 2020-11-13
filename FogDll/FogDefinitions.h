
//#if !defined(_FOG_DEFINITIONS_DEFINED_)
//#define _FOG_DEFINITIONS_DEFINED_



#define FOG_OPT_DIFFERENTIAL		1
#define FOG_OPT_SHOWPICTURE			2
#define FOG_OPT_SHOWGRAINS			4
#define FOG_OPT_REDGRAINS			8
#define FOG_OPT_GREENGRAINS			16
#define FOG_OPT_REALSIZE			32
#define FOG_OPT_SAVEGRAINS			64
#define FOG_OPT_FILEDIRECTORY		128
#define FOG_OPT_SELECTFRAMES		256
#define FOG_OPT_TRACK				512
#define FOG_OPT_SHOWTRACKS			1024
#define FOG_OPT_SHOWGRID			2048
#define FOG_OPT_PARENTPARAM			4096
#define FOG_OPT_THREEFRAMES			8192
#define FOG_OPT_STATISTICS			16384
#define FOG_OPT_SAVETXT				32768
#define FOG_OPT_COMPUTEPHS			65536
#define FOG_OPT_SAVETABLES			131072
#define FOG_OPT_INVERTXY			262144
#define FOG_OPT_FOG2000				524288
#define FOG_OPT_SAVEIMAGES			1048576
#define FOG_OPT_FINDGRAINS			2097152
#define FOG_OPT_GLOBALBYTES			4194304
#define FOG_OPT_SINGLEFRAME			8388608
#define FOG_OPT_SAVETRACKTABLE		16777216
#define FOG_OPT_SAVEGRAINSTABLE		33554432
#define FOG_OPT_CORRECTDIST			67108864
#define FOG_OPT_ENABLEOVERSAMPLING	134217728
#define FOG_OPT_MANUALCOMPUTE		268435456
#define FOG_OPT_CIANGRAINS			536870912


#define FOG_OPT_INVALIDOPTIONS		4294967296
#define FOG_OPT_BLUEGRAINS			24
#define FOG_OPT_BLACKGRAINS			0





#define GF_INVALID_FRAME		-1
#define GF_NOT_USED_DEPTH		100000.f







#define FOG_BLACK				(COLORREF)0x00
#define FOG_RED					(COLORREF)0x0000ff
#define FOG_GREEN				(COLORREF)0x00ff00
#define FOG_BLUE				(COLORREF)0xff0000
#define FOG_CIAN				(COLORREF)0xffff00
#define FOG_SPOTS_COLOR			(COLORREF)0x282828
#define FOG_SPOTS_RED			(COLORREF)0x1010c0

#define PI_QUARTI				0.78539816f
#define PI_FOG					3.14159265f
#define PI_MEZZI				1.57079632f

#define MAX_NUMBER_OF_IMAGES	120
#define MAX_MICROSCOPE_LIGHT	32767
#define FOG_WAITTIME_AUTOMATIC	0x70000000
#define FOG_MAXSIGNED_NUMBER	0x7fffffff
#define FOG_DONTWAIT			false
#define FOG_WAIT				true
#define FOG_DEF_SPEED			0
#define FOG_SET					true
#define FOG_GET					false

#define FOG_GOOD_VIEWS			10//Number of views used to measure Emulsion Width used in scanning

#define FOG_DOT_NODOT			1
#define FOG_DOT_IRREGULARDOT	2
#define FOG_DOT_ELLIPTICALDOT	4
#define FOG_DOT_GOODDOT			8
#define FOG_DOT_BADDOT			16



#define WM_USER_COMMANDLINE		0x0401
#define WM_USER_UPDATETRACKS	0x0402
#define WM_USER_SHOWSINGLEMIP	0x0403
#define WM_USER_SHOWTIP			0x0404
#define WM_USER_POPTIP			0x0405
#define WM_USER_CLOSEINFODLG	0x0406
#define WM_USER_UPDATEFOG		0x0407

#define FOG_UPDATE_FILE			0x0001
#define FOG_UPDATE_TRACKS		0x0002


#define FOG_CHECK_SHOW			0x0001
#define FOG_TRACKS_DLG			0x0002







//#endif