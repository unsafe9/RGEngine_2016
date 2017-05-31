#include "RGTime.h"

#include <chrono>
#include <ctime>

#include <Windows.h>
#pragma comment(lib, "winmm.lib")

namespace RGEngine
{
	Time::Time(void)
	{
		Reset();
		m_fpsElapsed = 0.0;
	}

	void Time::Tick(void)
	{
		if (m_highperf)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_timeCurrent);
		}
		else
		{
			m_timeCurrent = (__int64)timeGetTime();
		}
		m_timeElapsed = (double)(m_timeCurrent - m_timeLast) * m_timeScale;
		m_timeLast = m_timeCurrent;

		++m_fpsCount;
		m_fpsElapsed += m_timeElapsed;

		m_time += m_timeElapsed;

		if (m_fpsElapsed > 1.0)
		{
			m_fps = m_fpsCount;
			m_fpsCount = 0;
			m_fpsElapsed = 0.0;
		}
	}

	void Time::Reset(void)
	{
		m_highperf = QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency) ? true : false;
		if (m_highperf)
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&m_timeLast);
			m_timeScale = 1.0 / (double)m_frequency;
		}
		else
		{
			m_timeLast = (__int64)timeGetTime();
			m_timeScale = 0.001;
		}
		m_fps = 0;
		m_fpsCount = 0;
		m_time = 0.0;
	}


	unsigned int Time::GetFrameRate(void) const
	{
		return m_fps;
	}

	double Time::GetElapsedTime(void) const
	{
		return m_timeElapsed;
	}

	double Time::GetTimeScale(void) const
	{
		return m_timeScale;
	}
	double Time::GetTime(void) const
	{
		return m_time;
	}

}