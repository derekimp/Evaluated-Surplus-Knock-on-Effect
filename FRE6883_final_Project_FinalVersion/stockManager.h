#pragma once
#ifndef stockManager_h
#define stockManager_h
#include <iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include"stock.h"
#include"group.h"
#include"repeat.h"
#include"YahooData.h"


#include <sstream>


#include <stdlib.h>
#include <ctype.h>  
#include"operator2.h"
#include <stdio.h>
#include <thread>

using namespace std;

//Xinhao Zhu

//Lewei Peng

class stockManager {
public:
	map<string, stock> stocks;
	
	int N;

	map<string, stock> beat;
	map<string, stock> meet;
	map<string, stock> miss;

	vector<string> datelist;

	map<string, double> IWB;

	void enter_N_retrieve_data();

	void pull_one_stock_data();

	stockManager(); // constructor

	~stockManager(); //destructor

	vector<stock> Stocks;

	void showMenu();	

	void exitSystem(); 

	vector<string> TickerList; //unused


	void slice_N(int N_);

	void GetData();

	void load_eps_csv();

	void load_IWB();

	void calculate_abret();

	void PrintARet();

	void updateStocksReturn();

	void PrintDates();

	void SetStocks(vector<stock> & Stocks1000);

	repeat r;

	void updateRepeat();

	void updateStocks();

	double GetN() {
		return N;
	}
};



#endif