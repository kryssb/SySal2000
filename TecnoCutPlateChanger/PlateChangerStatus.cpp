#include "PlateChangerStatus.h"


//new functions
int TDigIO::GetLastJob()
{

	if( ! Is_ReadyToLock() && ! Is_ReadyToUnlock() && Is_AlarmON() )
		return kPC_NOTACTIVE  ;

	if( ! Is_ReadyToLock() && !Is_ReadyToUnlock() &&  ! Is_AlarmON() )
		return kPC_MANUALSTART ;

	if(   Is_ReadyToLock() && !Is_ReadyToUnlock() )
		return kPC_LOAD ;

	if( ! Is_ReadyToLock() &&  Is_ReadyToUnlock() )
		return kPC_UNLOAD  ;

	return kPC_UNKNOWN ;
};

unsigned char TDigIO::ReadPort( int nport )  
{
   if (iDigIO == 0) 
      return 0;

	// read 
   int value ;
	  iDigIO->DigitalIn( nport, & value );

   return (unsigned char) value ;
};

int TDigIO::Set_Unset_Bits  (int port, int bitmask_tobeset, int bitmask_tobeunset )
{
	if (iDigIO == 0) 
	   return 0;

	// write
	iDigIO->DigitalOut( port, bitmask_tobeset, bitmask_tobeunset );

	/*
	When executing this function in a program, there may be a delay of up to 
	0.5 ms before the output lines are physically updated.  The program flow 
	will continue, even though the output may not have been updated yet. This 
	behavior could become an issue when you are using digital I/O in conjunction 
	with other devices, such as a DAQ board.

	To ensure your program continues only after a written value has filtered down 
	to the physical lines, use the Read I/O Port function immediately after 
	calling this function. The Read I/O Port function will block program flow 
	until it completely executes, thus ensuring the previous Set I/O Port MOMO 
	function has completed.
	*/
	ReadPort( port ) ;

   return 1;
} ;

//___________________________________________________________________________//

TPCStatus::TPCStatus() 
{ 
	fPlateID.Part[0] = kIDUNKNOWN ;
	fPlateID.Part[1] = kIDUNKNOWN ;
	fPlateID.Part[2] = kIDUNKNOWN ;
	fPlateID.Part[3] = kIDUNKNOWN ; 
} ;

bool  TPCStatus::Is_PlateAlreadyLoaded( Identifier id ) 
{ 
	return (    fPlateID.Part[0] == id.Part[0] 
		      && fPlateID.Part[1] == id.Part[1]
			   && fPlateID.Part[2] == id.Part[2]
				&& fPlateID.Part[3] == id.Part[3] ) ; 
} ;

bool  TPCStatus::Is_LoadedPlateKnown( ) 
{ 
	if (  fPlateID.Part[0] == kIDUNKNOWN 
      && fPlateID.Part[1] == kIDUNKNOWN 
	   && fPlateID.Part[2] == kIDUNKNOWN 
		&& fPlateID.Part[3] == kIDUNKNOWN )
      return false ;
   else
      return true ;
} ;

bool  TPCStatus::Is_AnyPlateAlreadyLoaded() 
{ 
	if (  fPlateID.Part[0] == kIDNOTLOADED 
      && fPlateID.Part[1] == kIDNOTLOADED 
	   && fPlateID.Part[2] == kIDNOTLOADED 
		&& fPlateID.Part[3] == kIDNOTLOADED )
      return false ;
   else
      return true ;
} ;

void TPCStatus::UnSet_PlateLoaded()     
{ 
	fPlateID.Part[0] = kIDNOTLOADED ;
	fPlateID.Part[1] = kIDNOTLOADED ;
	fPlateID.Part[2] = kIDNOTLOADED ;
	fPlateID.Part[3] = kIDNOTLOADED ; 

   ResetOilZones() ;
} ;

void TPCStatus::Set_LoadedPlate(Identifier id) 
{ 
	fPlateID.Part[0] = id.Part[0] ;
	fPlateID.Part[1] = id.Part[1] ;
	fPlateID.Part[2] = id.Part[2] ;
	fPlateID.Part[3] = id.Part[3] ; 
} ;

bool TPCStatus::Is_OilAlreadyDispensed( t_OilZone zone , float htol ) 
{
   int nzones = fOilZones.size() ;
   for ( int i=0; i< nzones ; i++)    {
      if ( dist(zone, fOilZones[i]) < htol )
         return true ;
   }
   return false ;
} ;



