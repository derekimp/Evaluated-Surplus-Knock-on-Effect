#pragma once

#ifndef operator2_h
#define operator2_h


#include<iostream>
#include <vector>
using namespace std;
//Xinhao Zhu


inline ostream& operator<< (ostream& out, vector<string>& _vec) {
    for (vector<string>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
        out << *it << " "<<endl;
    return out;
}

inline ostream& operator<< (ostream& out, vector<double>& _vec) {
    for (vector<double>::const_iterator it = _vec.begin(); it != _vec.end(); ++it)
        out << *it << " " << endl;
    return out;
}


inline ostream& operator<< (ostream& out, vector<vector<double>>& _vec) {
    for (vector<vector<double>>::const_iterator it = _vec.begin(); it != _vec.end(); ++it) {
        //out << (*it) << " " << endl;
        for (vector<double>::const_iterator itr = it->begin(); itr != it->end(); ++it) {
            out << *itr << " ";
        }
        cout << endl;
    }
    return out;
}


#endif