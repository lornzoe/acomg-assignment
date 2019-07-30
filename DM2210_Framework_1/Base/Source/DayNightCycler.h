#pragma once
#include "MyMath.h"
#include "Vector3.h"

class DayNightCycler
{
public:
	// in a complete oscillation (from 1 to pi)
	float f_cyclePoint;

	// radius
	float f_amplitude;

	// for simplicity, sun and moon positions are at complete opposites.
	Vector3 v_sunPos;
	Vector3 v_moonPos;

	DayNightCycler();
	~DayNightCycler();

	void Update(double dt);
};