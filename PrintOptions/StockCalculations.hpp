#ifndef STOCKCALCULATION_HPP
#define STOCKCALCULATION_HPP

#include <vector>

#include "Stock.hpp"
#include "Tick.h"


double rateOfReturn(Stock &stock, int timePeriod) {
	
	double ror = 0;

	int dayInc = 0;
	int days = 0;

	vector<Tick> vTicks = stock.m_TimeSeries.Ticks();

	while ((dayInc + timePeriod) < vTicks.size()) {

		ror = ror*days + (vTicks[dayInc].close() - vTicks[dayInc + timePeriod].close()) / (vTicks[dayInc + timePeriod].close());
		ror = ror / (days + 1);

		days++;
		dayInc += timePeriod;
	}

	return ror;

};

double constantVolatility(Stock &stock, int timePeriod) {
	double constVol = 0;

	int dayInc = 0;
	double periodCounter = 0;
	double changeCounter = 0;

	bool lastMonthGain = true;

	vector<Tick> vTicks = stock.m_TimeSeries.Ticks();

	while ((dayInc + timePeriod) < vTicks.size()) {

		if (vTicks[dayInc].close() < vTicks[dayInc + timePeriod].close()) {
			if (!lastMonthGain) {
				changeCounter++;
			}

			lastMonthGain = true;
		}
		else if (vTicks[dayInc].close() > vTicks[dayInc + timePeriod].close()) {
			if (lastMonthGain) {
				changeCounter++;
			}

			lastMonthGain = false;
		}

		periodCounter++;
		dayInc += timePeriod;
	}

	constVol = changeCounter / periodCounter;

	return constVol;
}

#endif
