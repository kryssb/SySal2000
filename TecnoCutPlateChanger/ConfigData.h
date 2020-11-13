#ifndef _CONFIGDATA_H_
#define _CONFIGDATA_H_

struct ConfigData
{
   //----config
//   int   CHANGEME               ;
//   float CHANGEME2              ;

   //----machine defaults
   int   Firmware2             ;  //       
   int   UsePlateChanger       ;  //       
   float TimeOut_s             ;  //       
   float UnloadAirTime_s       ;  //       
   float LoadVacuumTime_s      ;  //       
   float DelayTimeAfterLoad_s  ;  //      
   int   OilObjective          ;  //       
   float OilDeltaPosX          ;  //       
   float OilDeltaPosY          ;  //       
   float OilWaitTime_s         ;  //       
   int   OilNPulses            ;  //       
   float OilStep               ;  //       
   float OilTol                ;  //       
};


#endif