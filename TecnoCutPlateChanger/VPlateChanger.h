#ifndef __VPLATECHANGERCLASS_H_
#define __VPLATECHANGERCLASS_H_

#include "id.h"
#include "PlateChangerStatus.h"
#include "ConfigData.h"

class VPlateChanger
{
public:

   virtual HRESULT _stdcall LoadPlate(Identifier id, BYTE *pppp) = 0;
   virtual HRESULT _stdcall UnloadPlate() = 0;
   virtual HRESULT _stdcall DispenseOil(float AreaMinX, float AreaMinY, float AreaMaxX, float AreaMaxY) = 0 ;
   /*
      Only methods used also by the COM object should be declared HRESULT _stdcall.
      Other methods need not use this modifier.
      Example:
      virtual int get_Brick() = 0;
   */
   virtual ConfigData  GetConfig      () const = 0 ;
   virtual TPCStatus   GetTPCStatus   () const = 0 ;
   virtual TDigIO*     GetIO          () = 0 ;
   virtual void        SetConfig ( ConfigData newC ) = 0 ;

   virtual bool OpGoToLoadPosition  () = 0 ; 
   virtual bool OpStart             () = 0 ;
   virtual bool OpLockPlate         () = 0 ;
   virtual bool OpUnlockPlate       () = 0 ;
   virtual bool OpCheckLoadPosition () = 0 ;

   virtual bool OpDispenseOil       ( int wait_time_ms ) = 0 ;

   virtual int  MC_GetPos(float* x, float* y, float* z)= 0 ;
   virtual int  MC_PosMoveAndWait ( float target_x, float target_y, float target_z ) =0; 

   // qui vanno le versioni virtuali di tutte le funzioni che rispondono ai bottoni del Monitor
};

#endif
