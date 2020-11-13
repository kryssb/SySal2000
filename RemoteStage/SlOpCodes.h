#ifndef _SYSAL_SLAVE_OPCODES_
#define _SYSAL_SLAVE_OPCODES_

#pragma pack(push)
#pragma pack(1)

#define SLOP_GENERAL						0x00
#define SLOP_GEN_IDENTIFY 					(SLOP_GENERAL + 0x01)
#define SLOP_GEN_RESET	  					(SLOP_GENERAL + 0x02)

#define SLOP_SWITCH							0xA0
#define SLOP_SWITCH_TO_SOFTWARE				(SLOP_SWITCH + 0x01)
#define SLOP_SWITCH_TO_MANUAL				(SLOP_SWITCH + 0x02)

#define SLOP_SW_SET							0xC0
#define SLOP_SW_STOP						(SLOP_SW_SET + 0x01)
#define SLOP_SW_MOVEABS						(SLOP_SW_SET + 0x02)
#define SLOP_SW_MOVEREL						(SLOP_SW_SET + 0x03)
#define SLOP_SW_CONSTSPEED					(SLOP_SW_SET + 0x04)
#define SLOP_SW_RESET						(SLOP_SW_SET + 0x05)
#define SLOP_SW_LIGHT						(SLOP_SW_SET + 0x0C)

#define SLOP_MAN_SET						0xD0
#define SLOP_MAN_STOPXY						(SLOP_MAN_SET + 0x01)
#define SLOP_MAN_STOPZ						(SLOP_MAN_SET + 0x02)
#define SLOP_MAN_MOVEXY						(SLOP_MAN_SET + 0x03)
#define SLOP_MAN_MOVEZ						(SLOP_MAN_SET + 0x04)
#define SLOP_MAN_LIGHT						(SLOP_MAN_SET + 0x0C)

#define SLOP_GET							0xB0
#define SLOP_GET_POS						(SLOP_GET + 0x01)
#define SLOP_GET_LIM						(SLOP_GET + 0x02)
#define SLOP_GET_LIGHT						(SLOP_GET + 0x0C)

#define MASTERIDSTRING "IMTHEMASTER"
#define SLAVEIDSTRING "GREETINGSSIR"

namespace SlaveOperation
{

	struct Op
	{
		BYTE OpCode;

		Op(BYTE opcode) : OpCode(opcode) {};
		};

   struct OpSWStop
   {
   		BYTE OpCode;
		BYTE Axis;

	    OpSWStop(BYTE axis) : OpCode(SLOP_SW_STOP), Axis(axis) {};
   		};

   struct OpSWReset
   {
   		BYTE OpCode;
		BYTE Axis;

		OpSWReset(BYTE axis) : OpCode(SLOP_SW_RESET), Axis(axis) {};
   		};

   struct OpSWMoveAbs
   {
   		BYTE OpCode;
		BYTE Axis;
		float Speed;
		float Pos;
		float Acc;

		OpSWMoveAbs(BYTE axis, float speed, float pos, float acc)
      		: OpCode(SLOP_SW_MOVEABS), Axis(axis), Speed(speed), Pos(pos), Acc(acc) {};
   		};

   struct OpSWMoveRel
   {
   		BYTE OpCode;
		BYTE Axis;
		float Speed;
		float Disp;
		float Acc;

		OpSWMoveRel(BYTE axis, float speed, float disp, float acc)
      		: OpCode(SLOP_SW_MOVEREL), Axis(axis), Speed(speed), Disp(disp), Acc(acc) {};
   		};

   struct OpSWConstSpeed
   {
   		BYTE OpCode;
		BYTE Axis;
		float Speed;

		OpSWConstSpeed(BYTE axis, float speed) : OpCode(SLOP_SW_CONSTSPEED), Axis(axis), Speed(speed) {};
   		};

   struct OpSWLight
   {
   		BYTE OpCode;
		WORD Light;

		OpSWLight(WORD light) : OpCode(SLOP_SW_LIGHT), Light(light) {};
   		};

   struct OpManMoveXY
   {
   		BYTE OpCode;
		float SpeedX, SpeedY;

		OpManMoveXY(float speedx, float speedy) : OpCode(SLOP_MAN_MOVEXY),
      		SpeedX(speedx), SpeedY(speedy) {};
   		};

   struct OpManMoveZ
   {
   		BYTE OpCode;
		float Speed;

		OpManMoveZ(float speed) : OpCode(SLOP_MAN_MOVEZ), Speed(speed) {};
   		};

   struct OpManLight
   {
   		BYTE OpCode;
		WORD Light;

		OpManLight(WORD light) : OpCode(SLOP_MAN_LIGHT), Light(light) {};
   		};

   struct OpGetPos
   {
		BYTE OpCode;
		BYTE Axis;

		OpGetPos(BYTE axis) : OpCode(SLOP_GET_POS), Axis(axis) {};
   		};

   struct OpGetLim
   {
		BYTE OpCode;
		BYTE Axis;

		OpGetLim(BYTE axis) : OpCode(SLOP_GET_LIM), Axis(axis) {};
   		};

   };

#pragma pack(pop)

#endif
