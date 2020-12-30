#include"stockManager.h"


//Xinhao Zhu

//Lewei Peng

//default constructor
stockManager::stockManager() {


	this->load_IWB();

	//Load "eps1.csv" file and load eps, surprise and ticker information.
	this->load_eps_csv();


}



stockManager::~stockManager() {}

//show menu
void stockManager::showMenu() {
	cout << "************************************************************************" << endl;
	cout << "****               Welcome to Earning Impact Labotory             ******" << endl;
	cout << "****   1.Enter N to retrieve historical price data for all stocks.******" << endl;
	cout << "****   2.Pull information for one stock from one group.           ******" << endl;
	cout << "****   3.Show AAR, AAR-SD, CAAR and CAAR-STD for one group.       ******" << endl;
	cout << "****   4.Show the Excel or gnuplot graph with CAAR for all 3 groups ****" << endl;
	cout << "****                    0.Exit your program                       ******" << endl;
	cout << "************************************************************************" << endl;
}

void stockManager::exitSystem() {
	cout << "Welcome back again! (O_O)! " << endl;
	system("pause");
	exit(0);
}

void string2num(string str, double& num)
{
	stringstream ss;
	ss << str;
	ss >> num;
}

void trim(string& s){   
	if (!s.empty()){
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
}

string transform_Format(string& annDate) {
	int firstDash = annDate.find('-');
	int secondDash = annDate.find('-', firstDash);
	string annDate2 = "2020-";

	if (annDate.substr(3, 3) == "APR") {
		annDate2 += "04-";
	}
	else if (annDate.substr(3, 3) == "MAY") {
		annDate2 += "05-";

	}
	else if (annDate.substr(3, 3) == "MAR") {
		annDate2 += "03-";
	}
	else if (annDate.substr(3, 3) == "JUN") {
		annDate2 += "06-";
	}
	else if (annDate.substr(3, 3) == "JUL") {
		annDate2 += "07-";
	}
	annDate2 += annDate.substr(0, 2);
	return annDate2;
}


void stockManager::updateStocks() {
	for (map<string, stock>::iterator itr = this->stocks.begin(); itr != this->stocks.end(); itr++)
	{
		Stocks.push_back(itr->second);
	}
}



void stockManager::load_eps_csv() {
	ifstream ifs("eps.csv", ios::in);//Input stream object, read file
	//File exists
	string _line;
	while (getline(ifs, _line))
	{
		//Parse each row of data
		stringstream ss(_line);
		string _sub;
		vector<string> subArray;

		//Separated by comma
		while (getline(ss, _sub, ',')) {
			subArray.push_back(_sub); //adding to subarray
		}
		double surprise_ = 0;
		string2num(subArray[5],surprise_);
		string group;

		//Determine which group it is
		if (surprise_ >= 15) {
			group = "beat";
		}else if(surprise_ >= 0 && surprise_ < 15) {
			group = "meet";
		}
		else {
			group = "miss";
		}

		//Instantiate stock, and put <ticker, stock> into map stocks
		string ticker = subArray[6];
		stock s = stock(ticker, subArray[0], surprise_, group);
		stocks.insert(make_pair(ticker, s));

		if (group == "beat") {
			beat.insert(make_pair(ticker, s));
		}
		if (group == "meet") {
			meet.insert(make_pair(ticker, s));
		}
		if (group == "miss") {
			miss.insert(make_pair(ticker, s));
		}
	}
	cout << endl;
	//¹Ø±ÕÊäÈëÁ÷¡£
	ifs.close();
}


void stockManager::slice_N(int N_) {
	N = N_;

	for (map<string, stock>::iterator itr = this->stocks.begin(); itr != this->stocks.end(); itr++) {
		string str = itr->second.announcementDate;
		itr->second.annTransform = transform_Format(str);
		for (int i = 0; i < datelist.size();i++) {
			
			if (datelist[i] == itr->second.annTransform) {
				itr->second.startDate = datelist[i - N];
				itr->second.endDate = datelist[i + N];
				continue;
			}
		}
	}
	for (map<string, stock>::iterator itr = this->beat.begin(); itr != this->beat.end(); itr++) {
		string str = itr->second.announcementDate;
		itr->second.annTransform = transform_Format(str);
		for (int i = 0; i < datelist.size();i++) {

			if (datelist[i] == itr->second.annTransform) {
				itr->second.startDate = datelist[i - N];
				itr->second.endDate = datelist[i + N];
				continue;
			}
		}
	}
	for (map<string, stock>::iterator itr = this->meet.begin(); itr != this->meet.end(); itr++) {
		string str = itr->second.announcementDate;
		itr->second.annTransform = transform_Format(str);
		for (int i = 0; i < datelist.size();i++) {

			if (datelist[i] == itr->second.annTransform) {
				itr->second.startDate = datelist[i - N];
				itr->second.endDate = datelist[i + N];
				continue;
			}
		}
	}
	for (map<string, stock>::iterator itr = this->miss.begin(); itr != this->miss.end(); itr++) {
		string str = itr->second.announcementDate;
		itr->second.annTransform = transform_Format(str);
		for (int i = 0; i < datelist.size();i++) {

			if (datelist[i] == itr->second.annTransform) {
				itr->second.startDate = datelist[i - N];
				itr->second.endDate = datelist[i + N];
				continue;
			}
		}
	}
}

void stockManager::GetData() {
	
	thread t1(ref(RetrieveMulti), ref(beat));
	thread t2(ref(RetrieveMulti), ref(meet));
	thread t3(ref(RetrieveMulti), ref(miss));
	t1.join();
	t2.join();
	t3.join();
	
	stocks.swap(beat);
	stocks.insert(meet.begin(), meet.end());
	stocks.insert(miss.begin(), miss.end());
	

	//RetrieveAll(stocks);
}

//Calculating Stocks return
void stockManager::updateStocksReturn() {
	for (map<string, stock>::iterator it = this->stocks.begin(); it != this->stocks.end(); it++) {
		it->second.calculateReturn();
	}
}

void stockManager::load_IWB() {

	RetrieveIWB(IWB, datelist);

}

void stockManager::calculate_abret() {
	map<string, double> IWB_return;
	vector<double> IWB_price;
	for (map<string, double> ::iterator itr = IWB.begin(); itr != IWB.end(); itr++) {
		if (IWB_price.size() == 0) {
			IWB_price.push_back(itr->second);
			IWB_return[itr->first] = 0.0;
			continue;
		}
		else {
			double price = itr->second;
			double ret = (price - IWB_price.back()) / IWB_price.back();
			IWB_return[itr->first] = ret;
			IWB_price.push_back(price);
		}
	}

	for (map<string, stock> ::iterator it = stocks.begin();it != stocks.end();it++) {
		if (it->second.Return.empty()) {
			cout << it->first << " " << it->second.PriceIsEmpty << endl;
			continue;
		}
		else {

			if (it->second.Price.size() != 2*N+1) {
				it->second.PriceIsEmpty = true;
				cout << it->second.PriceIsEmpty << endl;
				continue;
			}
			else {
				cout << it->first << it->second.PriceIsEmpty << endl;
				string startdate = it->second.startDate;
				string enddate = it->second.endDate;
				double i = 0;
				for (auto itr = IWB_return.find(startdate); itr != IWB_return.find(enddate); itr++) {
					double IWB1 = itr->second * 100;
					it->second.AbnomalRet_trimmed.push_back(it->second.Return[i] - IWB1);
					it->second.Date_trimmed.push_back(itr->first);

					i++;
				}
				
			
			}
		}
	}

}


//print out vector<double> AbnormalRet;
void stockManager::PrintARet() {
	for (map<string, stock>::iterator it = stocks.begin(); it != stocks.end(); it++) {
		cout << it->second.AbnomalRet << endl;
	}
}

//print out vector<string>Date;
void stockManager::PrintDates() {
	for (map<string, stock>::iterator it = stocks.begin(); it != stocks.end(); it++) {
		cout << it->second.Date << endl;
	}
}

void stockManager::SetStocks(vector<stock> & Stocks1000_) //must be empty
{
	int i(0);
	for (map<string, stock>::iterator itr = stocks.begin(); itr != stocks.end(); itr++)
	{
		Stocks1000_.push_back(itr->second);
		i++;
	}
}

void stockManager::enter_N_retrieve_data() {
	
	this->updateStocks();
	this->updateRepeat();
	system("pause");
	system("cls");
	
}

void stockManager::pull_one_stock_data() {
	cout << "Please Enter one stock ticker: " << endl;
	string target; cin >> target;
	map<string, stock>::iterator it= this->stocks.find(target);
	if (it != stocks.end()) {
		(*it).second.showInfo();//stock
	}
	else {
		cout << "This stock's info is missing in our database" << endl << "Please retry another stock::" << endl;
	}
	system("pause");
	system("cls");

}


void stockManager::updateRepeat() {
	repeat repeat_30 = repeat(30, this->Stocks);
	this->r = repeat_30;
}


