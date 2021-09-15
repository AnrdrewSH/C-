#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void recursionSearch(int i, int j, vector <string> field(), int cols, int rows)
{
	if ()
}

int main()
{
	int rows = 0;
	int cols = 0;
	int result = 0;
	int neighborCounter = 0;
	int defaultFanceNumber = 4;

	ifstream file;
	file.open("Laba1Task1.txt");
	string params;
	string dataString;

	if (!file.is_open())
	{
		cout << "File is not opened!";
		system("pause > nul");
		return 1;
	}
	
	getline(file, params, ' ');
	cols = stoi(params);

	getline(file, params);
	rows = stoi(params);

	vector <string> field(cols);

	for (int i = 0; i < cols; i++)
	{
		getline(file, dataString);
		field[i] = dataString;
	}

	for (int i = 0; i < cols; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			cout << field[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < cols; i++)
		for (int j = 0; j < rows; j++)
		{
			if (i + 1 != cols)
				if (field[i + 1][j] == '1') neighborCounter++;

			if (j + 1 != rows)
				if (field[i][j + 1] == '1') neighborCounter++;

			if (i - 1 >= 0)
				if (field[i - 1][j] == '1') neighborCounter++;

			if (j - 1 >= 0)
				if (field[i][j - 1] == '1') neighborCounter++;

			if (field[i][j] == '1')
				result += defaultFanceNumber - neighborCounter;

			else if (field[i][j] != '1')
				if (neighborCounter == 4) result -= 4;

			neighborCounter = 0;
		}

	cout << endl << result;

	file.close();

	system("pause > nul");
	return 0;
}



