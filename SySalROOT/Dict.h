/********************************************************************
* Dict.h
********************************************************************/
#ifdef __CINT__
#error Dict.h/C is only for compilation. Abort cint.
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define G__ANSIHEADER
#define G__DICTIONARY
#include "G__ci.h"
extern "C" {
extern void G__cpp_setup_tagtableDict();
extern void G__cpp_setup_inheritanceDict();
extern void G__cpp_setup_typetableDict();
extern void G__cpp_setup_memvarDict();
extern void G__cpp_setup_globalDict();
extern void G__cpp_setup_memfuncDict();
extern void G__cpp_setup_funcDict();
extern void G__set_cpp_environmentDict();
}


#include "TROOT.h"
#include "TMemberInspector.h"
#include "SySalROOT.h"

#ifndef G__MEMFUNCBODY
#endif

extern G__linked_taginfo G__DictLN_TClass;
extern G__linked_taginfo G__DictLN_TBuffer;
extern G__linked_taginfo G__DictLN_TMemberInspector;
extern G__linked_taginfo G__DictLN_TObject;
extern G__linked_taginfo G__DictLN_TFile;
extern G__linked_taginfo G__DictLN_TROOT;
extern G__linked_taginfo G__DictLN_TTree;
extern G__linked_taginfo G__DictLN_TSRHeader;
extern G__linked_taginfo G__DictLN_TSRLayer;
extern G__linked_taginfo G__DictLN_TSRAlignment;
extern G__linked_taginfo G__DictLN_TSRSegment;
extern G__linked_taginfo G__DictLN_TSRTrack;
extern G__linked_taginfo G__DictLN_TSRTrackSegment;
extern G__linked_taginfo G__DictLN_TSRVertexTrack;
extern G__linked_taginfo G__DictLN_TSRVertex;
extern G__linked_taginfo G__DictLN_TSySalTLG;
extern G__linked_taginfo G__DictLN_TSySalTLGcLcLTLGFormat;
extern G__linked_taginfo G__DictLN_TSySalRWD;
extern G__linked_taginfo G__DictLN_TSySalRWDcLcLRWDFormat;
extern G__linked_taginfo G__DictLN_TSySalRWDcLcLRWDGrainCompression;
extern G__linked_taginfo G__DictLN_TSySalTSR;
extern G__linked_taginfo G__DictLN_TSySalTSRcLcLTSRFormat;

/* STUB derived class for protected member access */
