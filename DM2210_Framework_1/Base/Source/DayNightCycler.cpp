#include "DayNightCycler.h"

DayNightCycler::DayNightCycler()
	:
	v_sunPos(0, 0, 0),
	v_moonPos(0, 0, 0),
	f_cyclePoint(0.f),
	f_amplitude(0.f)
{
}

DayNightCycler::~DayNightCycler()
{
}

void DayNightCycler::Update(double dt)
{
	f_cyclePoint += (float)dt;
	if (f_cyclePoint > Math::PI)
	{
		f_cyclePoint -= Math::PI;
	}

	v_sunPos.Set(sin(f_cyclePoint), cos(f_cyclePoint), 0);
	v_sunPos * f_amplitude;
	v_moonPos = -v_sunPos;
}
