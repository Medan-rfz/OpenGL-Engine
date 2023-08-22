#pragma once
#include <chrono>

class Timer
{
public:
	void Start();
	float GetTimeUs(float* lastDuration);

private:
	std::chrono::steady_clock::time_point _timeStart;
	std::chrono::steady_clock::time_point _prevTimeStamp;
};


