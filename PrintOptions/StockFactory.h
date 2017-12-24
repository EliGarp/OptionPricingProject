#ifndef STOCKFACTORY_H
#define STOCKFACTORY_H

#include <string>
#include <vector>
#include <tuple>
#include <ctime>
#include <time.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "MetaData.h"
#include "TimeSeries.h"
#include "Tick.h"
#include "Stock.hpp"

using namespace std;

int secsInDay = 60 * 60 * 24;

Stock stockFactoryFromJsonString(string);
MetaData metaDataFactoryFromJsonString(string);
TimeSeries timeSeriesFactoryFromJsonString(string);
Tick tickFactoryFromJsonString(string);

string returnSectionString(string sectionName, string jsonString) {

	int counterOpenBrackets = 0;
	int counterClosedBrackets = 0;
	int sectionHeaderStart = jsonString.find(sectionName);

	//Find first char in section and using first open bracket
	int sectionBegin = jsonString.find("{", sectionHeaderStart) + 1;
	counterOpenBrackets++;

	int i = sectionBegin;
	while (i < jsonString.length() && counterOpenBrackets > counterClosedBrackets) {

		char c = jsonString[i];

		if (c == '{') {
			counterOpenBrackets++;
		}
		else if (c == '}') {
			counterClosedBrackets++;
		}

		i++;
	}

	int sectionEnd = i - 1;

	string sectionString = jsonString.substr(sectionBegin, sectionEnd - sectionBegin);

	boost::trim(sectionString);

	return sectionString;
}


template <class T>
T returnProperty(string propertyName, string sectionString) {

	int sectionStart = sectionString.find(propertyName);
	int propertyNameCloseQuote = sectionString.find("\"", sectionStart);
	int propertyBegin = sectionString.find("\"", propertyNameCloseQuote + 1) + 1;
	int propertyEnd = sectionString.find("\"", propertyBegin);

	T prop = sectionString.substr(propertyBegin, propertyEnd - propertyBegin);

	return prop;
}

int tickCounter(string timeSeriesSection) {

	return count(timeSeriesSection.begin(), timeSeriesSection.end(), '{');

}

vector<string> returnDays(string timeSeriesSection) {

	vector<string> vDays;

	int tickCount = tickCounter(timeSeriesSection);
	int increment = 0;
	
	while (vDays.size() < tickCount){

		int firstQuote = timeSeriesSection.find("\"", increment);
		int secondQuote = timeSeriesSection.find("\"", firstQuote + 1);

		string day = timeSeriesSection.substr(firstQuote + 1, secondQuote - firstQuote - 1);
		
		vDays.push_back(day);

		increment = timeSeriesSection.find("}", increment) + 1;

	}

	return vDays;
}

vector<Tick> tickVectorFactory(vector<string> vDays, string jsonString, int noDays, int startDay) {
	vector<Tick> vTick;
	string tickDate;
	string tickSection;

	for (int i = 0; i < vDays.size() && vTick.size() < noDays; i++) {

		if (i >= startDay) {

			tickDate = vDays[i];

			tickSection = returnSectionString(tickDate, jsonString);

			Tick tick = Tick();

			tick.date(tickDate);
			tick.close(atof(returnProperty<string>("close", tickSection).c_str()));
			tick.open(atof(returnProperty<string>("open", tickSection).c_str()));
			tick.high(atof(returnProperty<string>("high", tickSection).c_str()));
			tick.low(atof(returnProperty<string>("low", tickSection).c_str()));
			tick.volume(atof(returnProperty<string>("volume", tickSection).c_str()));

			vTick.push_back(tick);
		}

	}

	return vTick;
}


Stock stockFactoryFromJsonString(string jsonString, int noDays, int startDay) {

	//Meta Data
	string metaDataSection = returnSectionString("Meta Data", jsonString);

	MetaData metaData = MetaData();

	metaData.Information(returnProperty<string>("Information", metaDataSection));
	metaData.LastRefreshed(returnProperty<string>("Last Refreshed", metaDataSection));
	metaData.Symbol(returnProperty<string>("Symbol", metaDataSection));
	metaData.OutputSize(returnProperty<string>("Output Size", metaDataSection));
	metaData.TimeZone(returnProperty<string>("Time Zone", metaDataSection));

	// Time Series
	string timeSeriesSection = returnSectionString("Time Series (Daily)", jsonString);

	vector<string> vDays = returnDays(timeSeriesSection);
	
	//Ticks
	vector<Tick> vTick = tickVectorFactory(vDays, jsonString, noDays, startDay);

	//Assemble Time Series:
	TimeSeries timeSeries = TimeSeries();

	timeSeries.Ticks(vTick);

	//Assemble Stock
	Stock stock = Stock();

	stock.m_MetaData = metaData;
	stock.m_TimeSeries = timeSeries;
	
	return stock;
};

#endif