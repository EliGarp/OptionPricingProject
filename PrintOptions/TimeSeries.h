#ifndef TIMESERIES_HPP
#define TIMESERIES_HPP

#include <vector>
#include <string>

#include "Tick.h"

using namespace std;

class TimeSeries {
private:
	int m_nTicks;
	vector<Tick> m_Ticks;

public:

	TimeSeries() : m_nTicks(100) {};

	TimeSeries(int nTicks) : m_nTicks(nTicks) {};

	void Ticks(vector<Tick> ticks) { m_Ticks = ticks; };
	vector<Tick> Ticks() { return m_Ticks; };
	void nTicks(int nTicks) { m_nTicks = nTicks; };
	int nTicks() { return m_nTicks; };
};


#endif