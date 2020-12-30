#pragma once
#include <stdio.h>
#include <string> 
#include <iostream>
#include <sstream>  
#include <vector>
#include <locale>
#include <iomanip>
#include <mutex>

#pragma comment(lib, "wldap32.lib" )
#pragma comment(lib, "crypt32.lib" )
#pragma comment(lib, "Ws2_32.lib")

#define CURL_STATICLIB 
#include <curl/curl.h>

#include "curl_easy.h"
#include "curl_form.h"
#include "curl_ios.h"
#include "curl_exception.h"

#include "stockManager.h"

using namespace std;

//Lewei Peng

inline int write_data(void* ptr, int size, int nmemb, FILE* stream)
{
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return (int)written;
}

struct MemoryStruct {
	char* memory;
	size_t size;
};

inline void* myrealloc(void* ptr, size_t size)
{
	if (ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

inline int write_data2(void* ptr, size_t size, size_t nmemb, void* data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct* mem = (struct MemoryStruct*)data;
	mem->memory = (char*)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return (int)realsize;
}

inline string getTimeinSeconds(string Time)
{
	std::tm t = { 0 };
	std::istringstream ssTime(Time);
	char time[100];
	memset(time, 0, 100);
	if (ssTime >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S"))
	{
		cout << std::put_time(&t, "%c %Z") << "\n"
			<< std::mktime(&t) << "\n";
		sprintf(time, "%lld", mktime(&t));
		return string(time);
	}
	else
	{
		cout << "Parse failed\n";
		return "";
	}
}

inline int RetrieveIWB(map<string, double>& IWB, vector<string>& datelist) {
	
	string startTime = getTimeinSeconds("2020-01-01T16:00:00");
	string endTime = getTimeinSeconds("2020-11-30T16:00:00");
	//vector<string> symbolList;
	//populateSymbolVector(symbolList);
	//vector<string>::iterator itr = symbolList.begin();

	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	// declaration of an object CURL 
	CURL* handle;

	CURLcode result;

	// file pointers to create file that store the data  
	//FILE* fp1, * fp2;

	// name of files  
	//const char outfilename[FILENAME_MAX] = "Output.txt";
	//const char resultfilename[FILENAME_MAX] = "Results.txt";

	

	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();

	FILE* fp;

	// if everything's all right with the easy handle... 
	if (handle)
	{
		string sCookies, sCrumb;

			if (sCookies.length() == 0 || sCrumb.length() == 0)
			{
				curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");

				curl_easy_setopt(handle, CURLOPT_ENCODING, "");
				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &data);
				result = curl_easy_perform(handle);

				if (result != CURLE_OK)
				{
					// if errors have occurred, tell us what is wrong with result
					fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				char cKey[] = "CrumbStore\":{\"crumb\":\"";
				char* ptr1 = strstr(data.memory, cKey);
				char* ptr2 = ptr1 + strlen(cKey);
				char* ptr3 = strstr(ptr2, "\"}");
				if (ptr3 != NULL)
					*ptr3 = NULL;

				sCrumb = ptr2;

				fp = fopen("cookies.txt", "r");
				char cCookies[100];
				if (fp) {
					while (fscanf(fp, "%s", cCookies) != EOF);
					fclose(fp);
				}
				else
					cerr << "cookies.txt does not exists" << endl;

				sCookies = cCookies;
				free(data.memory);
				data.memory = NULL;
				data.size = 0;
			}

			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string symbol = "IWB";
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";
			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char* cURL = url.c_str();
			const char* cookies = sCookies.c_str();
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);
			curl_easy_setopt(handle, CURLOPT_URL, cURL);

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *) &data);
			result = curl_easy_perform(handle);

			// Check for errors */
			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with 'result'
				fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			stringstream sData;
			sData.str(data.memory);
			string sValue, sDate;
			double dValue = 0;
			string line;
			getline(sData, line);
			while (getline(sData, line)) {
				sDate = line.substr(0, line.find_first_of(','));
				line.erase(line.find_last_of(','));
				sValue = line.substr(line.find_last_of(',') + 1);
				dValue = strtod(sValue.c_str(), NULL);
				//cout << sDate << " " << std::fixed << ::setprecision(6) << dValue << endl;
				datelist.push_back(sDate);
				IWB[sDate] = dValue;
			}

			
		
		
		free(data.memory);
		data.size = 0;
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	// cleanup since you've used curl_easy_init  
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init() 
	curl_global_cleanup();

	return 0;
}




inline int RetrieveAll(map<string, stock>& Group) {
	auto itr = Group.begin();

	

	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	

	// declaration of an object CURL 
	CURL* handle;

	CURLcode result;

	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();

	FILE * fp;


	// if everything's all right with the easy handle... 
	if (handle)
	{
			string sCookies, sCrumb;
		
		
			if (sCookies.length() == 0 || sCrumb.length() == 0)
			{
				
				curl_easy_setopt(handle, CURLOPT_URL, "https://finance.yahoo.com/quote/AMZN/history");
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYPEER, 0);
				curl_easy_setopt(handle, CURLOPT_SSL_VERIFYHOST, 0);
				curl_easy_setopt(handle, CURLOPT_COOKIEJAR, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_COOKIEFILE, "cookies.txt");
				curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1);

				curl_easy_setopt(handle, CURLOPT_ENCODING, "");

				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);

				// perform, then store the expected code in result
				result = curl_easy_perform(handle);

				if (result != CURLE_OK)
				{
					// if errors have occured, tell us what is wrong with result
					fprintf(stderr, "1 curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				
				char cKey[] = "CrumbStore\":{\"crumb\":\"";
				char* ptr1 = strstr(data.memory, cKey);
				char* ptr2 = ptr1 + strlen(cKey);
				char* ptr3 = strstr(ptr2, "\"}");
				if (ptr3 != NULL)
					*ptr3 = NULL;

				sCrumb = ptr2;

				fp = fopen("cookies.txt", "r");
				char cCookies[100];
				if (fp) {
					while (fscanf(fp, "%s", cCookies) != EOF);
					fclose(fp);
				}
				else
					cerr << "cookies.txt does not exists" << endl;

				sCookies = cCookies;
			}
			while (true) {
				if (itr == Group.end())
					break;

				free(data.memory);
				data.memory = NULL;
				data.size = 0;

				string startTime = getTimeinSeconds(itr->second.startDate+"T16:00:00");
				string endTime = getTimeinSeconds(itr->second.endDate + "T16:00:00");

				string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
				string symbol = itr->first;
				string urlB = "?period1=";
				string urlC = "&period2=";
				string urlD = "&interval=1d&events=history&crumb=";
				string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
				const char* cURL = url.c_str();
				const char* cookies = sCookies.c_str();
				curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);
				curl_easy_setopt(handle, CURLOPT_URL, cURL);

				curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
				curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
				result = curl_easy_perform(handle);

				if (result != CURLE_OK)
				{
					// if errors have occurred, tell us what is wrong with result
					fprintf(stderr, "2 curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
					return 1;
				}

				stringstream sData;
				sData.str(data.memory);

				string sValue;
				double dValue = 0;
				vector<double> adj;
				string line;
				getline(sData, line);
				while (getline(sData, line)) {
					line.erase(line.find_last_of(','));
					sValue = line.substr(line.find_last_of(',') + 1);
					dValue = strtod(sValue.c_str(), NULL);
					adj.push_back(dValue);
				}

				itr->second.Price = adj;
				itr++;
			}
		
		free(data.memory);
		data.size = 0;
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}

	// cleanup since you've used curl_easy_init  
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init() 
	curl_global_cleanup();

	return 0;
}


inline int RetrieveMulti(map<string, stock>& Group) {
	auto itr = Group.begin();



	struct MemoryStruct data;
	data.memory = NULL;
	data.size = 0;

	

	// declaration of an object CURL 
	CURL* handle;

	CURLcode result;

	// set up the program environment that libcurl needs 
	curl_global_init(CURL_GLOBAL_ALL);

	// curl_easy_init() returns a CURL easy handle 
	handle = curl_easy_init();

	FILE* fp;

	// if everything's all right with the easy handle... 
	if (handle)
	{
		

		while (true) {

			string sCookies, sCrumb;

			if (itr == Group.end())
				break;

			free(data.memory);
			data.memory = NULL;
			data.size = 0;
			
			string startTime = getTimeinSeconds(itr->second.startDate + "T16:00:00");
			string endTime = getTimeinSeconds(itr->second.endDate + "T16:00:00");
			

			string urlA = "https://query1.finance.yahoo.com/v7/finance/download/";
			string symbol = itr->first;
			string urlB = "?period1=";
			string urlC = "&period2=";
			string urlD = "&interval=1d&events=history&crumb=";
			string url = urlA + symbol + urlB + startTime + urlC + endTime + urlD + sCrumb;
			const char* cURL = url.c_str();
			const char* cookies = sCookies.c_str();
			curl_easy_setopt(handle, CURLOPT_COOKIE, cookies);
			curl_easy_setopt(handle, CURLOPT_URL, cURL);

			curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data2);
			curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void*)&data);
			result = curl_easy_perform(handle);

			if (result != CURLE_OK)
			{
				// if errors have occurred, tell us what is wrong with result
				fprintf(stderr, "2 curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
				return 1;
			}

			cout << itr->first;

			stringstream sData;
			sData.str(data.memory);

			string sValue;
			double dValue = 1;
			vector<double> adj;
			string line;
			getline(sData, line);
			while (getline(sData, line)) {
				size_t found = line.find("-");
				if (found != std::string::npos) {
					line.erase(line.find_last_of(','));
					sValue = line.substr(line.find_last_of(',') + 1);
					dValue = strtod(sValue.c_str(), NULL);
					adj.push_back(dValue);
					
				}
			}
			cout <<"  " << dValue << endl;
			itr->second.Price = adj;
			itr++;
		}

		free(data.memory);
		data.size = 0;
	}
	else
	{
		fprintf(stderr, "Curl init failed!\n");
		return 1;
	}


	// cleanup since you've used curl_easy_init  
	curl_easy_cleanup(handle);

	// release resources acquired by curl_global_init() 
	curl_global_cleanup();

	return 0;
}