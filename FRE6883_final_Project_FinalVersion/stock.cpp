#pragma once
#include<iostream>
using namespace std;
#include"stock.h"
#include<vector>

//Xinhao Zhu

void stock::calculateReturn() {
	if (this->Price.empty()) {
		this->PriceIsEmpty = true;
		return;
	}
	else {
		for (vector<double>::iterator it = Price.begin(); it != Price.end() - 1; it++)
		{
			Return.push_back((*(it + 1) - *it) / (*it) * 100);
		}
	}
}

void stock::showInfo() {
	if (PriceIsEmpty == false) {
		cout << "Ticker:" << this->ticker
			<< "\tAnnouncement Date: " << this->announcementDate
			<< "\tSurprise: " << this->surprise
			<< "\t Group: " << this->group
			<< "\tPriceIsEmpty: " << this->PriceIsEmpty << endl
			<< "Dates: " << endl << this->Date_trimmed
			<< "Prices: " << endl << this->Price;
	}
	else {
		cout << "This stock's date is missing:: Invalid." << endl;
	}

}
