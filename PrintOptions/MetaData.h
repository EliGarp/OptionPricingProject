#ifndef METADATA_HPP
#define METADATA_HPP

#include <string>
#include <sstream>

using namespace std;

class MetaData {

private:
	string m_Information;
	string m_Symbol;
	string m_LastRefreshed;
	string m_OutputSize;
	string m_TimeZone;

public:

	MetaData() {};

	void Information(string information) { m_Information = information; };
	string Information() { return m_Information; };
	void Symbol(string symbol) { m_Symbol = symbol; };
	string Symbol() { return m_Symbol; };
	void LastRefreshed(string lastRefreshed) { m_LastRefreshed = lastRefreshed; };
	string LastRefreshed() { return m_LastRefreshed; };
	void OutputSize(string outputSize) { m_OutputSize = outputSize; };
	string OutputSize() { return m_OutputSize; };
	void TimeZone(string timeZone) { m_TimeZone = timeZone; };
	string TimeZone() { return m_TimeZone; };

	string to_string() {
		stringstream ss;

		ss << "Meta Data: " << endl;
		ss << "Information: " << m_Information << endl;
		ss << "Symbol: " << m_Symbol << endl;
		ss << "Last Refreshed: " << m_LastRefreshed << endl;
		ss << "Output Size: " << m_OutputSize << endl;
		ss << "Time Zone: " << m_TimeZone << endl;

		return ss.str();
	}
};

#endif
