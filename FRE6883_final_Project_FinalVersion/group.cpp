//group.cpp
//
//Wen Teng

#include "group.h"

group::group(string GroupType_, int StockAmount_, const vector<stock>& Stocks1000_)
{
	GroupType = GroupType_;
	StockAmount = StockAmount_;
	StockSet = sampling(GroupType_, StockAmount_, Stocks1000_);
	AAR = calAAR();
	CAAR = calCAAR();
}

vector<double> group::calAAR()
{
	vector<double> aar; //Vector is vector<double>
	aar.resize(StockSet[0].Date_trimmed.size());
	for (int j = 0; j < StockAmount; j++)
	{
		//aar = (j / (j + 1.0)) * aar + StockSet[j].AbnomalRet / (j + 1.0);
		aar = aar + StockSet[j].AbnomalRet_trimmed / StockAmount;
	}
	return aar;
};

vector<double> group::calCAAR()
{
	vector<double> caar;
	caar.resize(AAR.size());
	caar[0] = AAR[0];
	for (int i = 1; i < AAR.size(); i++)
	{
		caar[i] = caar[i - 1] + AAR[i];
	}
	return caar;
}

