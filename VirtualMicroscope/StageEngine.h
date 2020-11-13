#ifndef _SYSAL_VIRTUALMICROSCOPE_STAGE_ENGINE_
#define _SYSAL_VIRTUALMICROSCOPE_STAGE_ENGINE_

class StageEngine
{
	public:

		struct AxisInfo
		{
			struct t_Current
			{
				float Pos;
				unsigned Time;
				} Current;
			struct t_Target
			{
				float Pos, Speed, Acc;
				unsigned StartTime;
				float StartPos;
				unsigned EndTime;
				bool IsValid;
				bool IsSpeed;
				} Target;
			};

	protected:

		AxisInfo Axes[3];

		unsigned short Light;

		void Evolve(unsigned axis);

	public:

		StageEngine();

		bool PosMove(unsigned axis, float pos, float speed, float acc);
		bool SpeedMove(unsigned axis, float speed, float acc);
		bool Stop(unsigned axis);
		bool Reset(unsigned axis);
		bool GetPos(unsigned axis, float &pos);
		bool GetTarget(unsigned axis, AxisInfo::t_Target &t);
		void SetLight(unsigned short light);
		void GetLight(unsigned short &light);

	};

#endif