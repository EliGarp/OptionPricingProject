#ifndef TICK_HPP
#define TICK_HPP

#include <string>
#include <sstream>

using namespace std;

class Tick {
private:
	string m_date;
	double m_open;
	double m_high;
	double m_low;
	double m_close;
	double m_volume;

public:

	Tick() {};

	void date(string date) { m_date = date; };
	string date() { return m_date; };
	void open(double open) { m_open = open; };
	double open() { return m_open; };
	void high(double high) { m_high = high; };
	double high() { return m_high; };
	void low(double low) { m_low = low; };
	double low() { return m_low; };
	void close(double close) { m_close = close; };
	double close() { return m_close; };
	void volume(double volume) { m_volume = volume; };
	double volume() { return m_volume; };

	string to_string() {
		stringstream ss;

		ss << "Tick Data: " << endl;
		ss << "Date: " << m_date << endl;
		ss << "Open: " << m_open << endl;
		ss << "Close: " << m_close << endl;
		ss << "Low: " << m_low << endl;
		ss << "High: " << m_high << endl;
		ss << "Volume: " << m_volume << endl;

		return ss.str();
	}

};


#endif
