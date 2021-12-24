#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>

#define INPUT_FILE_NAME "INPUT.txt"
#define OUTPUT_FILE_NAME "OUTPUT.txt"

struct READING_RESULT
{
	const std::string OK = "ok";
	const std::string WRONG_NUMBER_OF_LINES = "wrong number of lines (must be 3)";
	const std::string INVALID_INPUT_DATA = "invalid input data (contains non-integer value)";
	const std::string WRONG_PARAMS = "wrong parameters (must be 2 integers)";
	const std::string CANNOT_OPEN_FILE = std::string("can't open file \"") + INPUT_FILE_NAME + "\"";
	const std::string BAD_AMOUNT_OF_DATA = "amount of data does not match the one specified in the parameters";
	const std::string PARAMS_VALUE_OUT_OF_RANGE = "value in the parameters are out of range (1 <= value <= 100000)";
	const std::string DATA_VALUE_OUT_OF_RANGE = "data contains value out of range (1 <= value <= 100000000)";
};

std::string readInput(std::vector<std::vector<int>>& lines);

int countReadyToSell(std::vector<int>& sellers, int price);
int countReadyToBuy(std::vector<int>& buyers, int price);



int main(int argc, char const *argv[])
{
	std::vector<std::vector<int>> lines;

	const std::string readingResult = readInput(lines);
	if (readingResult != READING_RESULT().OK)
	{
		std::cerr << "[error]: " << readingResult << std::endl;
		return 1;
	}

	std::vector<int> prices = lines[0];
	std::sort(prices.begin(), prices.end());
	prices.erase(unique(prices.begin(), prices.end()), prices.end());

	std::vector<int>& sellers = lines[0];
	std::sort(sellers.begin(), sellers.end());

	std::vector<int>& buyers = lines[1];
	std::sort(buyers.begin(), buyers.end());
	std::reverse(buyers.begin(), buyers.end());

	int uniformPrice = 0;
	int maxProfit = 0;

	for (int i = 0; i < prices.size(); ++i)
	{
		int readyToBuy = countReadyToBuy(buyers, prices[i]);
		int readyToSell = countReadyToSell(sellers, prices[i]);

		int profit = (readyToBuy > readyToSell ? readyToSell : readyToBuy) * prices[i];
		if (profit > maxProfit)
		{
			maxProfit = profit;
			uniformPrice = prices[i];
		}
	}

	std::ofstream ofs(OUTPUT_FILE_NAME);
	ofs << std::to_string(uniformPrice) + " " + std::to_string(maxProfit);

	return 0;
}



int countReadyToSell(std::vector<int>& sellers, int price)
{
	for (int i = 0; i < sellers.size(); ++i)
		if (sellers[i] > price)
			return i - 1;
	return sellers.size();
}

int countReadyToBuy(std::vector<int>& buyers, int price)
{
	for (int i = 0; i < buyers.size(); ++i)
		if (buyers[i] < price)
			return i - 1;
	return buyers.size();
}

bool isNumber(const std::string& value)
{
	std::string::const_iterator it = value.begin();
	while (it != value.end() && std::isdigit(*it))
		++it;
	return !value.empty() && it == value.end();
}

std::string readInput(std::vector<std::vector<int>>& lines)
{
	std::string line;

	std::ifstream ifs(INPUT_FILE_NAME);
	if (!ifs.is_open())
		return READING_RESULT().CANNOT_OPEN_FILE;
	
	int lineIndex = 0;
	while (std::getline(ifs, line))
	{
		std::istringstream iss(line);
		std::vector<std::string> vec((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
		std::vector<int> res(vec.size());
		for (int i = 0; i < vec.size(); ++i)
		{
			if (!isNumber(vec[i]))
				return READING_RESULT().INVALID_INPUT_DATA;
			
			int value = std::stoi(vec[i]);

			if (lineIndex == 0)
				if (!(value >= 1 && value <= 100000))
					return READING_RESULT().PARAMS_VALUE_OUT_OF_RANGE;

			if (lineIndex > 0)
				if (!(value >= 1 && value <= 1000000000))
					return READING_RESULT().DATA_VALUE_OUT_OF_RANGE;

			res[i] = value;
		}
		lines.push_back(res);
		lineIndex++;
	}
	ifs.close();

	if (lines.size() != 3)
		return READING_RESULT().WRONG_NUMBER_OF_LINES;

	if (lines[0].size() != 2)
		return READING_RESULT().WRONG_PARAMS;

	int sellersLength = lines[0][0];
	int buyersLength = lines[0][1];

	lines.erase(lines.begin());

	if (lines[0].size() != sellersLength || lines[1].size() != buyersLength)
		return READING_RESULT().BAD_AMOUNT_OF_DATA;

	return READING_RESULT().OK;
}