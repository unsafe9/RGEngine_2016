#ifndef _RGTIME_H_
#define _RGTIME_H_

#pragma warning(disable:4244)

namespace RGEngine
{
	class Time
	{
	private:
		bool m_highperf;
		double m_timeScale;
		__int64 m_frequency;

		__int64 m_timeCurrent;
		__int64 m_timeLast;
		unsigned int m_fps;
		unsigned int m_fpsCount;
		double m_fpsElapsed;

		double m_timeElapsed;
		double m_time;

	public:
		Time(void);

		void Tick(void); // callback by framework

		void Reset(void); // reset

		double GetTimeScale(void) const;
		unsigned int GetFrameRate(void) const;
		double GetElapsedTime(void) const; // delta time
		double GetTime(void) const;

	};
}

#endif // _RGTIME_H_