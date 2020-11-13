#ifndef __PLATECHANGERSTATUSCLASS_H_
#define __PLATECHANGERSTATUSCLASS_H_

#include "DigitalIO.h"
#include "id.h"

#include <vector>
#include <cmath>

// the flag definitions      

// OUTPUT
																	// -- NI 7344 ---  conn.    cable  lev.ad 
                                                   // Digital Ground  pin 50				
#define PC_START             0x01  // 0000 0001    // Port 1 : bit 0  pin 10    14
#define PC_UNLOCK            0x02  // 0000 0010    // Port 1 : bit 1  pin 44    16
#define PC_LOCK              0x04  // 0000 0100    // Port 1 : bit 2  pin 45    18   
#define PC_VACUUM            0x08  // 0000 1000    // Port 1 : bit 3  pin 12    20 
#define PC_AIR1              0x10  // 0001 0000    // Port 1 : bit 4  pin 13    22   
#define PC_OIL               0x20  // 0010 0000    // Port 1 : bit 5  pin 47    24		   
#define PC_AIR2              0x40  // 0100 0000    // Port 1 : bit 6  pin 48    25		 
#define PC_CLOSE             0x80  // 1000 0000    // Port 1 : bit 7  pin 15      

#define PC_ALL               0xFF  

// INPUT
                                                   // Digital Ground  pin 50
#define PC_ALARM_ON          0x01  // 0000 0001    // Port 2 : bit 0  pin 16
#define PC_READY_TO_UNLOCK   0x02  // 0000 0010    // Port 2 : bit 1  pin 17
#define PC_READY_TO_LOCK     0x04  // 0000 0100    // Port 2 : bit 2  pin 51
#define PC_OUT_OF_MICROSCOPE 0x08  // 0000 1000    // Port 2 : bit 3  pin 52
#define PC_VACUUM_HIGH       0x10  // 0001 0000    // Port 2 : bit 4  pin 53
#define PC_VACUUM_LOW        0x20  // 0010 0000    // Port 2 : bit 5  pin 54

//-*************************************************************************-//

// Port1, Port2 classes are used by the monitor to minimize the data throughput to the board.
// Ex:
//   TDigIO io ;
//   TPort1 port1 = io->ReadPort1() ;
//   TPort2 port2 = io->ReadPort2() ;
//   DrawSemaphoreGreen( IDC_MN_LED_ALARM             , port2.Is_AlarmON()      );
//


const int kPC_UNKNOWN     = -1 ;
const int kPC_MANUALSTART =  0 ;
const int kPC_LOAD        =  1 ;
const int kPC_UNLOAD      =  2 ;
const int kPC_NOTACTIVE   =  3 ;


//___________________________________________________________________________//
class TPort1   // port 1 OUTPUT
{
public:
   TPort1() { };
   TPort1(unsigned char port) { fPort = port ; };
   virtual ~TPort1(void) {};

   bool Is_Start()           const  { return ( fPort & PC_START             )!=0 ; };
   bool Is_Unlock()          const  { return ( fPort & PC_UNLOCK            )!=0 ; };
   bool Is_Lock()            const  { return ( fPort & PC_LOCK              )!=0 ; };
   bool Is_Vacuum()          const  { return ( fPort & PC_VACUUM            )!=0 ; };
   bool Is_Air()             const  { return ( fPort & PC_AIR1              )!=0 ; };
   bool Is_Oil()             const  { return ( fPort & PC_OIL               )!=0 ; };
   bool Is_Air2()            const  { return ( fPort & PC_AIR2              )!=0 ; };
   bool Is_CloseCycle()      const  { return ( fPort & PC_CLOSE             )!=0 ; };
   operator unsigned int()   const  { return fPort ; } ;

protected:
   unsigned char fPort ;	
};

//___________________________________________________________________________//
class TPort2  // port 2 INPUT
{
public:
   TPort2() { };
   TPort2(unsigned char port) { fPort = port ; };
   virtual ~TPort2(void) {};

   bool Is_AlarmON()         const  { return ( fPort & PC_ALARM_ON          )!=0 ; };
   bool Is_ReadyToUnlock()   const  { return ( fPort & PC_READY_TO_UNLOCK   )!=0 ; };
   bool Is_ReadyToLock()     const  { return ( fPort & PC_READY_TO_LOCK     )!=0 ; };
   bool Is_OutOfMicroscope() const  { return ( fPort & PC_OUT_OF_MICROSCOPE )!=0 ; };
   bool Is_VacuumHigh()      const  { return ( fPort & PC_VACUUM_HIGH       )!=0 ; };
   bool Is_VacuumLow()       const  { return ( fPort & PC_VACUUM_LOW        )!=0 ; };
   operator unsigned int()   const  { return   fPort ; } ;

protected:
   unsigned char fPort ;	
};

//___________________________________________________________________________//
class TDigIO
{
   // Function Members (Methods)
public:
   TDigIO() { iDigIO = 0 ; };
   virtual ~TDigIO(void) {};

	//new functions
	int GetLastJob() ;
  
  //
   void SetInterface ( IDigitalIO* idigio )   { iDigIO = idigio ;  };
   IDigitalIO*   GetInterface()               { return iDigIO; } ;

   // read port
   unsigned char ReadPort( int nport)  ;

   TPort1 ReadPort1()		  { return TPort1( ReadPort(1) ) ; }
	TPort2 ReadPort2()		  { return TPort2( ReadPort(2) ) ; }

   bool Is_Start()           { return ReadPort1().Is_Start()           ; };
   bool Is_Unlock()          { return ReadPort1().Is_Unlock()          ; };
   bool Is_Lock()            { return ReadPort1().Is_Lock()            ; };
   bool Is_Vacuum()          { return ReadPort1().Is_Vacuum()          ; };
   bool Is_Air()             { return ReadPort1().Is_Air()             ; };
   bool Is_Oil()             { return ReadPort1().Is_Oil()             ; };
   bool Is_Air2()            { return ReadPort1().Is_Air2()            ; };
   bool Is_CloseCycle()      { return ReadPort1().Is_CloseCycle()      ; };
   
   bool Is_AlarmON()	        { return ReadPort2().Is_AlarmON()	        ; };
   bool Is_ReadyToUnlock()	  { return ReadPort2().Is_ReadyToUnlock()   ; };
   bool Is_ReadyToLock()     { return ReadPort2().Is_ReadyToLock()     ; };
   bool Is_OutOfMicroscope() { return ReadPort2().Is_OutOfMicroscope() ; };
   bool Is_VacuumHigh()      { return ReadPort2().Is_VacuumHigh()      ; };
   bool Is_VacuumLow()       { return ReadPort2().Is_VacuumLow()       ; };

   // set | unset | toggle bits
public:
   void Reset()              { Set_Unset_Bits( 1, 0, PC_ALL ) ; } ;
   void ResetExceptVacuum()  { Set_Unset_Bits( 1, 0, PC_ALL & ! PC_VACUUM) ; } ;
                            
   void Set_Start()          {                              Set_Bits  (1, PC_START   ) ; };
   void Set_Unlock()         {                              Set_Bits  (1, PC_UNLOCK  ) ; };
   void Set_Lock()           {                              Set_Bits  (1, PC_LOCK    ) ; };
   void Set_Vacuum()         { UnSet_Bits(1, PC_AIR1    ) ; Set_Bits  (1, PC_VACUUM  ) ; };
   void Set_Air()            { UnSet_Bits(1, PC_VACUUM  ) ; Set_Bits  (1, PC_AIR1    ) ; };
   void Set_Oil()            {                              Set_Bits  (1, PC_OIL     ) ; }; 
   void Set_Air2()           {                              Set_Bits  (1, PC_AIR2    ) ; }; 
   void Set_CloseCycle()     {                              Set_Bits  (1, PC_CLOSE   ) ; }; 
                            
   void UnSet_Start()        { UnSet_Bits(1, PC_START   ) ; };
   void UnSet_Unlock()       { UnSet_Bits(1, PC_UNLOCK  ) ; };
   void UnSet_Lock()         { UnSet_Bits(1, PC_LOCK    ) ; };
   void UnSet_Vacuum()       { UnSet_Bits(1, PC_VACUUM  ) ; };
   void UnSet_Air()          { UnSet_Bits(1, PC_AIR1    ) ; };
   void UnSet_Oil()          { UnSet_Bits(1, PC_OIL     ) ; };
   void UnSet_Air2()         { UnSet_Bits(1, PC_AIR2    ) ; };
   void UnSet_CloseCycle()   { UnSet_Bits(1, PC_CLOSE   ) ; };
                            
   void Toggle_Start()       { Is_Start()  ? UnSet_Start()  : Set_Start()  ; }
   void Toggle_Unlock()      { Is_Unlock() ? UnSet_Unlock() : Set_Unlock() ; }
   void Toggle_Lock()        { Is_Lock()   ? UnSet_Lock()   : Set_Lock()   ; }
   void Toggle_Vacuum()      { Is_Vacuum() ? UnSet_Vacuum() : Set_Vacuum() ; }  
   void Toggle_Air()         { Is_Air()    ? UnSet_Air()    : Set_Air()    ; }  
   void Toggle_Oil()         { Is_Oil()    ? UnSet_Oil()    : Set_Oil()    ; }  
   void Toggle_Air2()        { Is_Air2()   ? UnSet_Air2()   : Set_Air2()   ; }  
   void Toggle_CloseCycle()  { Is_CloseCycle()   ? UnSet_CloseCycle()   : Set_CloseCycle()   ; }  

protected:
   int Set_Unset_Bits   ( int port, int bitmask_tobeset, int bitmask_tobeunset ) ;
   inline int Set_Bits  ( int port, int bitmask_tobeset   ) ;
   inline int UnSet_Bits( int port, int bitmask_tobeunset ) ;

   // Data Members          
protected:
	IDigitalIO* iDigIO   ;
};

inline int TDigIO::Set_Bits  ( int port, int bitmask_tobeset   ) { return Set_Unset_Bits ( port, bitmask_tobeset , 0  ) ; } ;
inline int TDigIO::UnSet_Bits( int port, int bitmask_tobeunset ) { return Set_Unset_Bits ( port, 0, bitmask_tobeunset ) ; } ;

//___________________________________________________________________________//

struct t_OilZone
{
   int ndrops  ;
   float X     ;
   float Y     ;
   DWORD time  ; 
};

inline double dist( t_OilZone z0, t_OilZone z1 )
{
   return sqrt( pow(z0.X-z1.X,2)+pow(z0.Y-z1.Y,2) ) ;
}

const int kIDUNKNOWN         = INT_MAX        ;  // INT_MAX = 2147483647
const int kIDTOBEUNLOAD      = kIDUNKNOWN - 1 ;
const int kIDNOTLOADED       = kIDUNKNOWN - 2 ;

const Identifier kIDPLATETOBEUNLOADED = {kIDTOBEUNLOAD ,kIDTOBEUNLOAD ,kIDTOBEUNLOAD ,kIDTOBEUNLOAD } ;


class TPCStatus
{
   // Function Members (Methods)
public:
	TPCStatus()  ;
   virtual ~TPCStatus(void) {} ;

   // loaded plate
	bool Is_AnyPlateAlreadyLoaded() ;
	bool Is_PlateAlreadyLoaded(Identifier id) ;
	void Set_LoadedPlate(Identifier id) ;
   void UnSet_PlateLoaded()            ;
	Identifier GetLoadedPlateID()             { return fPlateID ; } ; 
   bool Is_LoadedPlateKnown( ) ;

   // oil
   void ResetOilZones()                      { fOilZones.clear()          ; } ;
   void AddOilDrop( t_OilZone zone )         { fOilZones.push_back( zone ) ; } ;
   bool Is_OilAlreadyDispensed( t_OilZone zone , float htol ) ; 

   // Data Members          
protected:
   Identifier fPlateID ;
   std::vector<t_OilZone> fOilZones ;

};

//___________________________________________________________________________//
#endif

