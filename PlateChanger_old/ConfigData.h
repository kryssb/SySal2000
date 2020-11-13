#ifndef _CONFIGDATA_H_
#define _CONFIGDATA_H_

struct ArmPos
{
	int Theta;
	int Z;
	};

struct ArmSpeed
{
	int Theta;
	int Z;
	};

struct ArmAcc
{
	int Theta;
	int Z;
	};

struct ArmMotionCtl
{
	ArmSpeed Speed;
	ArmAcc Acc;
	};

struct ConfigData
{
	int COMPort;
	ArmPos Waiting, Pickup, Release, ScanningStage, Safe;
	ArmMotionCtl ToSafe, ToWait, ToPickup, ToStage, ToRelease;

/*
	int BoardId;
	int XYStepsRev, ZStepsRev;
	int XYLinesRev, ZLinesRev;
	float XYEncoderToMicrons, ZEncoderToMicrons;
	float XYMicronsToSteps, ZMicronsToSteps;
	float XYManSpeedMultiplier, ZManSpeedMultiplier;
	float XYSpeedChangeLimit, ZSpeedChangeLimit;
	float XYAccel, ZAccel;
	float XYMaxSpeed, ZMaxSpeed;
	float XYManMaxSpeed, ZManMaxSpeed;
	float ConstSpeedAccel;
	int AccelFactor;
	int LimPol;
	int CtlModeIsCWCCW;
	int LightLimit;
	int InvertX, InvertY, InvertZ;
*/
	};

#endif