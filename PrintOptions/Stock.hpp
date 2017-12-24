#ifndef STOCK_HPP
#define STOCK_HPP

#include <string>
#include <vector>
#include <tuple>

#include <algorithm>
#include <boost/algorithm/string.hpp>

#include <iostream>

#include "MetaData.h"
#include "TimeSeries.h"



using namespace std;


class Stock {

private:
	
	//
public:
	MetaData m_MetaData;
	TimeSeries m_TimeSeries;
	//
	Stock() {};
	
	string to_string() {
		stringstream ss;

		ss << "Meta Data: " << endl;
		ss << "Information: " << m_MetaData.Information() << endl;
		ss << "Symbol: " << m_MetaData.Symbol() << endl;
		ss << "Last Refreshed: " << m_MetaData.LastRefreshed() << endl;
		ss << "Output Size: " << m_MetaData.OutputSize() << endl;
		ss << "Time Zone: " << m_MetaData.TimeZone() << endl << endl;
		ss << "There are " << m_TimeSeries.Ticks().size() << " days of data" << endl << endl;
		ss << m_TimeSeries.Ticks()[0].to_string() << endl;
		ss << m_TimeSeries.Ticks()[m_TimeSeries.Ticks().size()-1].to_string() << endl;

		return ss.str();
	}
};







#endif
