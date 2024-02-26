#pragma once

#include "EntityManager.h"
#include "Entity.h"

#include <chrono>

class Countdown : public Entity
{
private:

public:
	std::chrono::steady_clock::time_point m_startTime, m_endTime;
	std::chrono::duration<double> m_elapsedTime;

	int m_frame = 3;

	Countdown(int, float, float, float, int, EntityManager*);
	~Countdown();

	void animateCountdown() override;
	int getCountdownFrame() const override;
};