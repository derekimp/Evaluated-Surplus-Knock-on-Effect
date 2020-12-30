#pragma once
#ifndef group_h
#define group_h
//group.h
//
//Wen Teng
#include<time.h>
#include <stdlib.h>
#include<string>
#include<vector>
#include"stock.h"
#include"operator.h"
#include <iostream>
using namespace std;

inline vector<stock> sampling(string GroupType_, int StockAmount_, const vector<stock> Stocks1000_)
{
	vector<stock> sample;
	size_t n = Stocks1000_.size();
	for (int i = 0; i < StockAmount_; i++)
	{
		srand(time(NULL));
		int s = rand() % n;
		while (Stocks1000_[s].group != GroupType_ || Stocks1000_[s].PriceIsEmpty == 1)
		{
			if (s >= n - 1)	s = rand() % (n - 1);
			s += 1;
		}
		sample.push_back(Stocks1000_[s]);
	}
	return sample;
};

class group
{
private:
	string GroupType;
	int StockAmount;
	vector<stock> StockSet;
	vector<double> AAR; //1*60
	vector<double> CAAR; //1*60
public:
	group() :GroupType("beat"), StockAmount(40)
	{};
	group(string GroupType_, int StockAmount_, const vector<stock>& Stocks1000_);
	vector<double> calAAR();
	vector<double> calCAAR();
	friend class repeat;
};

#endif