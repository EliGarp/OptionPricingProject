#ifndef OPTIONHELPERMETHODS_HPP
#define OPTIONHELPERMETHODS_HPP

#include "OneFactorPlainOption.hpp"
#include "PerpetualOption.hpp"

#include <iostream>
#include <vector>

using namespace std;

namespace Options {
	namespace OneFactor {
		vector<double> CalculateOptionPriceForAVector(vector<double>, vector<double>,
			vector<double>, vector<double>, vector<double>, string, string);
		vector<double> CalculateDeltaForAVector(vector<double>, vector<double>,
			vector<double>, vector<double>, vector<double>, string, string);
		vector<double> CalculateGammaForAVector(vector<double>, vector<double>,
			vector<double>, vector<double>, vector<double>, string);
	}
	namespace Perpetual {
		vector<double> CalculateOptionPriceForAVector(vector<double>, vector<double>,
			vector<double>, vector<double>, vector<double>, string);
	}
}

//Calculate for a vector of option prices
vector<double> Options::OneFactor::CalculateOptionPriceForAVector(vector<double> vS, vector<double> vK,
	vector<double> vR, vector<double> vO, vector<double> vT, string modelType, string priceType) {

	//Throw error if input vectors are of different sizes
	if (vS.size() != vK.size() || vS.size() != vR.size() || vS.size() != vO.size() || vS.size() != vT.size()) {
		throw "All input vectors must be of the same size.";
	}

	//Create a vector of call prices based on the ith values of each of the input vectors
	OneFactorPlainOption option;
	vector<double> vPrices = vector<double>();

	//Set model type once
	option.modeltype(modelType);
	
	for (int i = 0; i < vS.size(); i++) {
		option.S(vS[i]);
		option.K(vK[i]);
		option.r(vR[i]); 
		option.o(vO[i]); 
		option.T(vT[i]); 
		
		if (priceType == "Put") {
			vPrices.push_back(option.PutPrice());
		}
		else {
			vPrices.push_back(option.CallPrice());
		}
	}

	return vPrices;

}

//Calculate for a vector of option prices
vector<double> Options::OneFactor::CalculateDeltaForAVector(vector<double> vS, vector<double> vK,
	vector<double> vR, vector<double> vO, vector<double> vT, string modelType, string optionType) {

	//Throw error if input vectors are of different sizes
	if (vS.size() != vK.size() || vS.size() != vR.size() || vS.size() != vO.size() || vS.size() != vT.size()) {
		throw "All input vectors must be of the same size.";
	}

	//Create a vector of call prices based on the ith values of each of the input vectors
	OneFactorPlainOption option;
	vector<double> vGreeks = vector<double>();

	//Set model type once
	option.modeltype(modelType);

	for (int i = 0; i < vS.size(); i++) {
		option.S(vS[i]);
		option.K(vK[i]);
		option.r(vR[i]);
		option.o(vO[i]);
		option.T(vT[i]);

		if (optionType == "Call") {
			vGreeks.push_back(option.CallDelta());
		}
		else {
			vGreeks.push_back(option.PutDelta());
		}

	}

	return vGreeks;
}

//Calculate for a vector of option prices
vector<double> Options::OneFactor::CalculateGammaForAVector(vector<double> vS, vector<double> vK,
	vector<double> vR, vector<double> vO, vector<double> vT, string modelType) {

	//Throw error if input vectors are of different sizes
	if (vS.size() != vK.size() || vS.size() != vR.size() || vS.size() != vO.size() || vS.size() != vT.size()) {
		throw "All input vectors must be of the same size.";
	}

	//Create a vector of call prices based on the ith values of each of the input vectors
	OneFactorPlainOption option;
	vector<double> vGreeks = vector<double>();

	//Set model type once
	option.modeltype(modelType);

	for (int i = 0; i < vS.size(); i++) {
		option.S(vS[i]);
		option.K(vK[i]);
		option.r(vR[i]);
		option.o(vO[i]);
		option.T(vT[i]);

		vGreeks.push_back(option.PutDelta());
	}

	return vGreeks;
}

//Calculate for a vector of option prices
vector<double> Options::Perpetual::CalculateOptionPriceForAVector(vector<double> vS, vector<double> vK,
	vector<double> vR, vector<double> vO, vector<double> vB, string priceType) {

	//Throw error if input vectors are of different sizes
	if (vS.size() != vK.size() || vS.size() != vR.size() || vS.size() != vO.size() || vS.size() != vB.size()) {
		throw "All input vectors must be of the same size.";
	}

	//Create a vector of call prices based on the ith values of each of the input vectors
	PerpetualOption option;
	vector<double> vCallPrices = vector<double>();


	for (int i = 0; i < vS.size(); i++) {
		option.S(vS[i]);
		option.K(vK[i]);
		option.r(vR[i]);
		option.o(vO[i]);
		option.b(vB[i]);

		if (priceType == "Put"){
			vCallPrices.push_back(option.PutPrice());
		}
		else{
			vCallPrices.push_back(option.CallPrice());
		}
	}

	return vCallPrices;

}





#endif
