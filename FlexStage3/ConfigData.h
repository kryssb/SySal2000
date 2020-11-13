#ifndef _CONFIGDATA_H_
#define _CONFIGDATA_H_

struct ConfigData
{
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
	int TurnOffLightTime;
	int InvertX, InvertY, InvertZ;
	float ZParkDisplacement;
	float ZBaseThickness;
	};

#endif