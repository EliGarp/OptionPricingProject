// TestMatrixExcel.cpp
//
// Test output of a matrix in Excel. Here we 
// use the Excel Driver object directly.
//
// The output is in cell/numeric format.
//
// (C) Datasim Education BV 2006-2017
//


#include "UtilitiesDJD/ExcelDriver/ExcelDriverLite.hpp"
#include "UtilitiesDJD/ExcelDriver/Utilities.hpp"

#include <boost/numeric/ublas/matrix.hpp>
#include "UtilitiesDJD/VectorsAndMatrices/NestedMatrix.hpp"

#include <string>
#include <vector>
#include <list>
#include <map>

#include "OneFactorPlainOption.hpp"
#include "OptionHelperMethods.hpp"

#include "HTTPRequest.h"
#include "Stock.hpp"
#include "StockFactory.h"
#include "StockCalculations.hpp"



//
#include <iostream>
#include <sstream>

vector<double> MeshArray(double startValue, double endSize, double h = 0) {
	vector<double> mesh;

	//Increments startValue by h * i
	//endSize = the total size of the vector to be returned
	double value = startValue;
	for (double i = 0; i < endSize; i++) {
		mesh.push_back(value + h*i);
	}

	return mesh;
}

string createURL(string const &url, vector<string> const &vParams, map<string, string> const &mParams) {

	stringstream ss;

	ss << url;

	vector<string>::const_iterator iterParams = vParams.begin();

	ss << *iterParams << "=" << mParams.at(*iterParams) ;

	iterParams++;

	while (iterParams != vParams.end()) {

		ss << "&" << *iterParams << "=" << mParams.at(*iterParams);

		iterParams++;
	}

	return ss.str();
}


int main()
{
	
	// C++11 syntax
	typedef NestedMatrix<double> NumericMatrix;
	typedef NestedMatrix<string> CharMatrix;
	typedef std::vector<double> Vector;
	

	//Define Parameters
	string urlBase = "https://www.alphavantage.co/query?";

	vector<string> vParams;
	vParams.push_back("function");
	vParams.push_back("symbol");
	vParams.push_back("outputsize");
	vParams.push_back("apikey");

	map<string, string> mParams;
	mParams["function"] = "TIME_SERIES_DAILY";
	mParams["symbol"] = "AAPL";
	mParams["outputsize"] = "full";
	mParams["apikey"] = "ALPHADAVANTAGEAPIKEY";

	//Build URL
	string url = createURL(urlBase, vParams, mParams);
	cout << url << endl << endl;

	//Get Response
	string response = returnResponseAsString(url);

	//Extract stock
	int predicDays = 90;
	Stock stockPredic = stockFactoryFromJsonString(response,predicDays*20, predicDays);
	cout << stockPredic.to_string() << endl;

	//Get rate of return
	double ror = rateOfReturn(stockPredic, predicDays);
	cout << "ror: " << ror << endl;

	//Get Constant Volatility
	double constVol = constantVolatility(stockPredic, predicDays);
	cout << "constVol: " << constVol << endl << endl;

	//Assemble Mesh Arrays
	vector<double> vAsset = MeshArray(stockPredic.m_TimeSeries.Ticks()[0].close(), 50);
	vector<double> vStrike = MeshArray(stockPredic.m_TimeSeries.Ticks()[0].close()-25, 50, 1);
	vector<double> vInterest = MeshArray(ror, 50);
	vector<double> vConstVol = MeshArray(constVol, 50);
	vector<double> vTime = MeshArray(predicDays, 50);

	//Create Arrays of Calls and Puts;
	vector<double> vCalls = Options::OneFactor::CalculateOptionPriceForAVector(vAsset, vStrike, vInterest, vConstVol, vTime, "Black_Scholes_Stock", "Call");
	vector<double> vPuts = Options::OneFactor::CalculateOptionPriceForAVector(vAsset, vStrike, vInterest, vConstVol, vTime, "Black_Scholes_Stock", "Put");

	//Get Analysis Period
	Stock stockOption = stockFactoryFromJsonString(response, predicDays, 0);
	cout << "Analysis stock: " << endl << stockOption.to_string() << endl << endl;

	//Place into matrix
	std::size_t N = 50; std::size_t M = 3 + predicDays; // rows and columns
	NumericMatrix matrix(N, M);
	for (std::size_t i = 0; i < matrix.size1(); ++i)
	{
		matrix(i, 0) = static_cast<double>(vStrike[i]);
		matrix(i, 1) = static_cast<double>(vCalls[i]);
		matrix(i, 2) = static_cast<double>(vPuts[i]);

		for (int k = 3; k < matrix.size2(); k++) {
			matrix(i, k) = static_cast<double>(stockOption.m_TimeSeries.Ticks()[k - 3].close());
		}
	}

	//Start Excel
	ExcelDriver& excel = ExcelDriver::Instance();
	excel.MakeVisible(true);		// Default is INVISIBLE!

	//Call Excel print function
	std::string sheetName("Prices");
	long row = 1; long col = 1;

	//Print Headers
	//excel.printStringInExcel("Strike Price", sheetName, row, col);
	//col++;
	//excel.printStringInExcel("Call Price", sheetName, row, col);
	//col++;
	//excel.printStringInExcel("Put Price", sheetName, row, col);
	//col++;

	//for (std::size_t col = 3; col < 3 + predicDays; col++) {
	//	stringstream hs;
	//	hs << "Day: ";
	//	hs << predicDays - col - 3;
	//	excel.printStringInExcel(hs.str(), sheetName, row, col);
	//}

	//Set col and row
	col = 1;
	row++;
	excel.AddMatrix<NumericMatrix>(matrix, sheetName, row, col);



	return 0;
}
