#pragma once
#ifndef repeat_h
#define repeat_h
//repeat.h
//
//by Wen Teng
#include "group.h"
#include "operator2.h"
#include<iostream>
using namespace std;

class repeat 
	//Sampling: 40 stocks for each of the three groups; pass sampling times during initialization;
{
private:
	int times;
	//Repeat sampling for a certain times and record the AAR and CAAR of each time
	//Size: times * (2N+1)
	vector<vector<double>> BeatAAR; 
	vector<vector<double>> MeetAAR;
	vector<vector<double>> MissAAR;
	vector<vector<double>> BeatCAAR; 
	vector<vector<double>> MeetCAAR;
	vector<vector<double>> MissCAAR;

	//Calculate average of AAR for each group. Ave[0] is for beat. Ave[1] is for meet. Ave[2] is for miss. 
	//Size: 3*(2N+1)
	vector<vector<double>> AveAAR;
	vector<vector<double>> AveCAAR;
	vector<vector<double>> StdAAR;
	vector<vector<double>> StdCAAR;
	vector<vector<vector<double>>> MatrixAveStd;

public:
	repeat() : times(30) //Default constructor with default sampling times 30
	{};
	repeat(int times_, const vector<stock>& Stocks1000_);
	vector<vector<double>> GetAveAAR();
	vector<vector<double>> GetAveCAAR();
	vector<vector<double>> GetStdAAR();
	vector<vector<double>> GetStdCAAR();
	void showInfo(); //Print mean and variance information.
};

#endif // !repeat_h