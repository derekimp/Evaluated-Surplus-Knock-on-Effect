#include "repeat.h"


repeat::repeat(int times_, const vector<stock>& Stocks1000_)
{
	cout << "Bear With Me. (O_O!) Calculating......" << endl;
	times = times_;
	AveAAR.resize(3);
	StdAAR.resize(3);
	AveCAAR.resize(3);
	StdCAAR.resize(3);
	for (int i = 0; i < times; i++)
	{
		group beat("beat", 40, Stocks1000_); //Initialize beat group
		BeatAAR.push_back(beat.AAR);
		BeatCAAR.push_back(beat.CAAR);
		group meet("meet", 40, Stocks1000_); //Initialize meet group
		MeetAAR.push_back(meet.AAR);
		MeetCAAR.push_back(meet.CAAR);
		group miss("miss", 40, Stocks1000_); //Initialize miss group
		MissAAR.push_back(miss.AAR);
		MissCAAR.push_back(miss.CAAR);
		if (i == 0)
		{
			int n = BeatAAR[i].size();
			for (int i = 0; i < 3; i++)
			{
				AveAAR[i].resize(n);
				AveCAAR[i].resize(n);
				StdAAR[i].resize(n);
				StdCAAR[i].resize(n);
			}
		}
		AveAAR[0] = AveAAR[0] + beat.AAR / times;
		AveAAR[1] = AveAAR[1] + meet.AAR / times;
		AveAAR[2] = AveAAR[2] + miss.AAR / times;
		AveCAAR[0] = AveCAAR[0] + beat.CAAR / times;
		AveCAAR[1] = AveCAAR[1] + meet.CAAR / times;
		AveCAAR[2] = AveCAAR[2] + miss.CAAR / times;
	}
	for (int i = 0; i < times; i++)
	{
		StdAAR[0] = StdAAR[0] + (1.0 / times) * (BeatAAR[i] - AveAAR[0]) * (BeatAAR[i] - AveAAR[0]);
		StdAAR[1] = StdAAR[1] + (1.0 / times) * (MeetAAR[i] - AveAAR[1]) * (MeetAAR[i] - AveAAR[1]);
		StdAAR[2] = StdAAR[2] + (1.0 / times) * (MissAAR[i] - AveAAR[2]) * (MissAAR[i] - AveAAR[2]);
		StdCAAR[0] = StdCAAR[0] + (1.0 / times) * (BeatCAAR[i] - AveCAAR[0]) * (BeatCAAR[i] - AveCAAR[0]);
		StdCAAR[1] = StdCAAR[1] + (1.0 / times) * (MeetCAAR[i] - AveCAAR[1]) * (MeetCAAR[i] - AveCAAR[1]);
		StdCAAR[2] = StdCAAR[2] + (1.0 / times) * (MissCAAR[i] - AveCAAR[2]) * (MissCAAR[i] - AveCAAR[2]);
	}
	for (int i = 0; i < 3; i++)
	{
		StdAAR[i] = sqrt(StdAAR[i]);
		StdCAAR[i] = sqrt(StdCAAR[i]);
	}
	MatrixAveStd.resize(3);
	for (int i = 0; i < 3; i++)
	{
		MatrixAveStd[i].resize(4);
		MatrixAveStd[i][0] = AveAAR[i];
		MatrixAveStd[i][1] = StdAAR[i];
		MatrixAveStd[i][2] = AveCAAR[i];
		MatrixAveStd[i][3] = StdCAAR[i];
	}
}

vector<vector<double>> repeat::GetAveAAR()
{
	return AveAAR;
}
vector<vector<double>> repeat::GetAveCAAR()
{
	return AveCAAR;
}
vector<vector<double>> repeat::GetStdAAR()
{
	return StdAAR;
}
vector<vector<double>> repeat::GetStdCAAR()
{
	return StdCAAR;
}

void repeat::showInfo() {
	
	string arr[3] = {"Beat","Meet","Miss"};
	cout << "AveARR: " << endl;
	for (int i = 0; i < AveAAR.size(); i++) {
		cout  << arr[i] << " ";
		for (int j = 0; j < AveAAR[i].size()-1; j++) {
			cout << AveAAR[i][j] << " ";
		}
		cout << endl;
	}

	cout << "AveCARR: " << endl;
	for (int i = 0; i < AveCAAR.size(); i++) {
		cout << arr[i] << " ";
		for (int j = 0; j < AveCAAR[i].size() - 1; j++) {
			cout << AveCAAR[i][j] << " ";
		}
		cout << endl;
	}

	cout << "StdARR: " << endl;
	for (int i = 0; i < StdAAR.size(); i++) {
		cout << arr[i] << " ";
		for (int j = 0; j < StdAAR[i].size() - 1; j++) {
			cout << StdAAR[i][j] << " ";
		}
		cout << endl;
	}

	cout << "StdCARR: " << endl;
	for (int i = 0; i < StdCAAR.size(); i++) {
		cout << arr[i] << " ";
		for (int j = 0; j < StdCAAR[i].size() - 1; j++) {
			cout << StdCAAR[i][j] << " ";
		}
		cout << endl;
	}
	
	system("pause");
	system("cls");
}