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
	float ZHomingSpeed;
	float ZHomingXPos, ZHomingYPos;
	int InteractiveHome;

	int DigXDec;
	int DigXInc;
	int DigYDec;
	int DigYInc;
	int DigZDec;
	int DigZInc;
	int DigLDec;
	int DigLInc;
	int DigToggleAutoManual;
	int DigSpeedChange;
	int AxXAxis;
	int AxYAxis;
	int AxZAxis;
	int AxLAxis;
	};


#define REFPOSNAMELEN 31

struct RefPos
{
	char Name[REFPOSNAMELEN + 1];
	bool IsZ;
	union
	{
		struct t_XY
		{
			float X;
			float Y;
		} XY;
		float Z;
	} Pos;
};

#endif