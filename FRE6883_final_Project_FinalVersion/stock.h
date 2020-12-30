#pragma once
#ifndef stock_h
#define stock_h
#include <iostream>
#include<string>
#include<vector>
#include<iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include"operator2.h"
using namespace std;
//Xinhao Zhu

class stock {
public:
	string ticker;
	vector<string> Date;
	vector<double> Price;
	string announcementDate;
	string annTransform;
	double surprise;
	bool PriceIsEmpty; //mark useless data

	string group;
	vector<double> Return;
	vector<double> AbnomalRet;
	vector<double> AbnomalRet_trimmed;
	vector<double> Price_trimmed;
	vector<string> Date_trimmed;

	vector<double> AdjClose;

	string startDate;
	string endDate;


	void calculateReturn();
	void showInfo();

	//constructor with parameters	
	stock(string ticker_, string announcementDate_, double surprise_, string group_) {
		ticker = ticker_;
		announcementDate = announcementDate_;
		surprise = surprise_;
		group = group_;
		PriceIsEmpty = false;
	}
};

#endif // !stock


