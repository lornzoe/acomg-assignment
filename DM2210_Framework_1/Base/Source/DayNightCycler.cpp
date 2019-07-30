#include "DayNightCycler.h"

DayNightCycler::DayNightCycler()
	:
	v_sunPos(0, 0, 0),
	v_moonPos(0, 0, 0),
	f_cyclePoint(0.f),
	f_amplitude(0.f),
	f_cycleSpeed(1.f)
{
}

DayNightCycler::~DayNightCycler()
{
}

void DayNightCycler::Update(double dt)
{
	f_cyclePoint += (float)dt * 0.05 * f_cycleSpeed;
	if (f_cyclePoint > Math::TWO_PI)
	{
		f_cyclePoint -= Math::TWO_PI;
	}

	v_sunPos.Set(sin(f_cyclePoint) * f_amplitude, cos(f_cyclePoint) * f_amplitude, 0);
	v_moonPos = -v_sunPos;

	f_hour = (int)((f_cyclePoint / Math::TWO_PI) * 24);
	
	//cout << v_sunPos << '\n';
}
