#ifndef TIMER_H
#define TIMER_H
#include <time.h>

namespace Kaotic_Alpha
{
	class Timer
	{
	public:
		Timer();
		~Timer();
		void Start();
		void Pause();
		void Reset();
		void Update();
		float GetElapsedTime();

	private:
		bool m_Paused;
		clock_t m_StartTime;
	};
}

#endif