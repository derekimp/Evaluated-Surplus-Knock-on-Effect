// FRE6883_final_Project.cpp : main is here
#include <iostream>
#include <thread>
using namespace std;

#include"stockManager.h"
#include "repeat.h"
#include "visualization.h"
//Xinhao Zhu

//Teng wen

//Lewei Peng

int test1()
{
    cout << "For Convenience, the author defaulted N = 3, SamplingTimes = 30." << endl
        << "The user can change the setting by menu later."<<endl
        << "***********  Please Press Any Key to Continue: **********" << endl;
    system("pause");

    int choice = 0;//Used to store user options

    stockManager sm;

    bool OneClicked = false;
    vector<vector<double>> plotmatrix;
    string plotchoice;
    while (true) {
        sm.showMenu();
        cout << "Please enter your options: " << endl;
        cin >> choice; 
        switch (choice) {
        case 1: 
            OneClicked = true;
            cout << "Please enter N: " << endl;
            int N; cin >> N;
            sm.slice_N(N);
            sm.GetData();
            sm.updateStocksReturn();
            sm.calculate_abret();
            sm.enter_N_retrieve_data();
            break;
        case 2: 
            if (OneClicked == false) {
                cout << "You must enter \"1\" first to kick off the sampling process!!! ";
                system("pause");
                system("cls");
                break;
            }
            sm.pull_one_stock_data();
            break;
        case 3: 
            if (OneClicked == false) {
                cout << "You must enter \"1\" first to kick off the sampling process!!! ";
                system("pause");
                system("cls");
                break;
            }
            sm.r.showInfo();
            break;
        case 4:
            if (OneClicked == false) {
                cout << "You must enter \"1\" first to kick off the sampling process!!! ";
                system("pause");
                system("cls");
                break;
            }

            cout << "Choose AveAAR, AveCAAR, StdAAR or StdCAAR" << endl;
            cin >> plotchoice;
            if (plotchoice == "AveAAR") plotmatrix = sm.r.GetAveAAR();
            else if (plotchoice == "AveCAAR") plotmatrix = sm.r.GetAveCAAR();
            else if (plotchoice == "StdAAR") plotmatrix = sm.r.GetStdAAR();
            else if (plotchoice == "StdCAAR") plotmatrix = sm.r.GetStdCAAR();
            else {
                cout << "wrong input!" << endl;
                break;
            }
            plotResults(plotmatrix, sm.GetN());
            
            break;
        case 0:
            sm.exitSystem();
            break;
        default:
            system("cls"); //clean the screen
            break;
        }
    }
    
    return 0;
}

int main() {
    test1();
}