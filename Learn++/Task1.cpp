#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int numberOfSellers = 0;
	int numberOfCustomers = 0;
	int parsValue = 0;
	int maxCountOfSales = 0;
	int numberOfPrice = 0;
	int sellerCounter = 0;
	int customerCounter = 0;
	int tempParam = 0;

	std::vector<int> PricesToSell;
	std::vector<int> PricesToBuy;
	std::vector<int> ResultArray;

	ifstream file;
	file.open("Task1.txt");
	string paramsInString;
	string stringSellers;
	string stringCustomers;

	if (!file.is_open())
	{
		cout << "File is not opened!";
		system("pause > nul");
		return 1;
	}

	getline(file, paramsInString, ' ');
	numberOfSellers = stoi(paramsInString);

	getline(file, paramsInString);
	numberOfCustomers = stoi(paramsInString);

	for (int i = 0; i < numberOfSellers; i++)
	{
		char separator = '\n';
		if (i < numberOfSellers - 1) separator = ' ';

		getline(file, stringSellers, separator);
		parsValue = stoi(stringSellers);
		PricesToSell.push_back(parsValue);
	}

	for (int i = 0; i < numberOfCustomers; i++)
	{
		getline(file, stringCustomers, ' ');
		parsValue = stoi(stringCustomers);
		PricesToBuy.push_back(parsValue);
	}

	file.close();

	for (int i = 0; i < PricesToBuy.size(); i++)
	{
		for (int j = 0; j < PricesToSell.size(); j++)
			if (PricesToSell[j] <= PricesToBuy[i]) sellerCounter++;

		for (int j = 0; j < PricesToBuy.size(); j++)
			if (PricesToBuy[i] <= PricesToBuy[j]) customerCounter++;

		if (sellerCounter >= customerCounter)
			maxCountOfSales = PricesToBuy[i] * customerCounter;
		else if (customerCounter > sellerCounter)
			maxCountOfSales = PricesToBuy[i] * sellerCounter;

		if (maxCountOfSales > tempParam)
		{
			tempParam = maxCountOfSales;
			numberOfPrice = PricesToBuy[i];
		}

		sellerCounter = 0;
		customerCounter = 0;
	}

	ResultArray.push_back(tempParam);
	ResultArray.push_back(numberOfPrice);

	cout << ResultArray[1] << ' ' << ResultArray[0];

	system("pause > nul");
	return 0;
}