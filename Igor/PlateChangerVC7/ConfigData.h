#ifndef _CONFIGDATA_H_
#define _CONFIGDATA_H_



struct ConfigData
{
	int NumberOfAttempt; //number of attempt to take emulsion from the stage
	int PositionTimeout; //timeout in steps of 100ms for H and V movements
	int VacuumTimeout; //same for vacuum
	int BubbleTimeout; //timeout before emulsion will stick to the table and all air under it is out
	int NumberOfBanks; //number of banks to use
	int WithSeparators; //default value for presence of separators
    int SeparationAttempts; //number of ascillations at the bank brushes to separate emulsions
    float LimOffsetX; //Stage limiter offset on X
    float LimOffsetY; //Stage limiter offset on Y
    float FMOffsetX; //FM offset on X
    float FMOffsetY; //FM offset on Y
    float FMOffsetZ; //FM offset on Z wrt top of the base
    float LimOffsetZ; //Stage limiter offset on Y
    float SpeedX;
    float SpeedY;
    float SpeedZ;
    float AccX;
    float AccY;
    float AccZ;
    int LightLevel;
	int LiftCorners; //to start from lifting plate corners when taling from the stage
	int ComPort;
	};


#endif