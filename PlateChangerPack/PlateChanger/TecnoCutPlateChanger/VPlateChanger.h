#ifndef __VPLATECHANGERCLASS_H_
#define __VPLATECHANGERCLASS_H_

#include "id.h"
#include "PlateChangerStatus.h"

const bool kUsePlateChanger = true   ;
const int  kTimeOut         = 90000  ;  //ms
const int  kUnloadAirTime1  =  1000  ;  //ms   // compressed air time for ScanAndAir
const int  kUnloadAirTime2  =   500  ;  //ms   // compressed air time before Unlock
const int  kLoadVacuumTime  =  5000  ;  //ms
const int  kWaitTimeBeforeUnload = 0 ;  //ms

const bool kDryObjective    = false   ;
//LNGS const int  kOilDeltaPosX    =  -6000 ;  // micron  //LNGS 
//LNGS const int  kOilDeltaPosY    = -16500 ;  // micron  //LNGS 
const int  kOilDeltaPosX    = -17000 ;  // micron //BOLOGNA
const int  kOilDeltaPosY    =      0 ;  // micron //BOLOGNA
const int  kOilWaitTime     =   2000 ;  //  ms
const int  kOilNPulses      =      2 ;  //  number of pulses
const int  kOilStep = 7000 ; // micron
const int  kOilTol  = 3000 ; // micron

/*
struct PCConfiguration
{
	bool fUsePlateChanger =  true  ;
	int  fTimeOut         = 90000  ;  //ms
	int  fUnloadAirTime1  =  1000  ;  //ms   // compressed air time for ScanAndAir
	int  fUnloadAirTime2  =  1000  ;  //ms   // compressed air time before Unlock
	int  fLoadVacuumTime  =  4000  ;  //ms
	int  fWaitTimeBeforeUnload = 0 ;  //ms

	bool fDryObjective    =  true  ;
	int  fOilDeltaPosX    =  -6000 ;  // micron
	int  fOilDeltaPosY    = -16500 ;  // micron
	int  fOilWaitTime     =   3000 ;  //  ms
	int  fOilNPulses      =      2 ;  //  number of pulses
};
*/
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
      virtual TDigIO* GetIO() = 0 ;
		virtual TPCStatus GetTPCStatus() = 0 ;

		virtual bool OpGoToLoadPosition()                   = 0 ; 
		virtual bool OpStart(int timeout_ms=kTimeOut)       = 0 ;
		virtual bool OpStartAndAir(int timeout_ms=kTimeOut) = 0 ;
      virtual bool OpLockPlate(int timeout_ms=kTimeOut)   = 0 ;
      virtual bool OpUnlockPlate(int timeout_ms=kTimeOut) = 0 ;
      virtual bool OpCheckLoadPosition()                  = 0 ;

      virtual bool OpDispenseOil(int wait_time_ms=kOilWaitTime ) = 0 ;

      virtual int  MC_GetPos(float* x, float* y, float* z)= 0 ;
      virtual int  MC_PosMoveAndWait ( float target_x, float target_y, float target_z ) =0; 

		/* qui vanno le versioni virtuali di tutte le funzioni che rispondono ai bottoni del Monitor */
};

#endif
