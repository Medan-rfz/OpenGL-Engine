#include "Timer.hpp"

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
void Timer::Start()
{
	_timeStart = std::chrono::high_resolution_clock::now();
	_prevTimeStamp = _timeStart;
}

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
float Timer::GetTimeUs(float* lastDuration)
{
	auto timeStamp = std::chrono::high_resolution_clock::now();
	auto res = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStamp - _timeStart);

	if (lastDuration)
		*lastDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(timeStamp - _prevTimeStamp).count();

	_prevTimeStamp = timeStamp;

	return res.count();
}


