#pragma once
#ifndef operator_h
#define operator_h

//operator.h
//
//Wen Teng

//Xinhao Zhu
#include<iostream>
using namespace std;

inline vector<double> operator+(const vector<double>& a, const vector<double>& b)
{
	vector<double> add;
	for (int i = 0; i < a.size(); i++) add.push_back(a[i] + b[i]);
	return add;
}

inline vector<double> operator-(const vector<double>& a, const vector<double>& b)
{
	vector<double> min;
	for (int i = 0; i < a.size(); i++) min.push_back(a[i] - b[i]);
	return min;
}

inline vector<double> operator/(const vector<double>& a, const double& b)
{
	vector<double> div;
	for (int i = 0; i < a.size(); i++) div.push_back(a[i] / b);
	return div;
}

inline vector<double> operator/(const vector<double>& a, const int& b)
{
	vector<double> div;
	for (int i = 0; i < a.size(); i++) div.push_back(a[i] / b);
	return div;
}

inline vector<double> operator*(const double& a, const vector<double>& b)
{
	vector<double> mul;
	for (int i = 0; i < b.size(); i++) mul.push_back(a * b[i]);
	return mul;
}

inline vector<double> operator*(const int& a, const vector<double>& b)
{
	vector<double> mul;
	for (int i = 0; i < b.size(); i++) mul.push_back(a * b[i]);
	return mul;
}

inline vector<double> operator*(const vector<double>& a, const vector<double>& b)
{
	vector<double> mul;
	for (int i = 0; i < b.size(); i++) mul.push_back(a[i] * b[i]);
	return mul;
}

inline vector<double> sqrt(const vector<double>& a)
{
	vector<double> sqrt_;
	for (int i = 0; i < a.size(); i++) sqrt_.push_back(sqrt(a[i]));
	return sqrt_;
}

#endif // !operator_h