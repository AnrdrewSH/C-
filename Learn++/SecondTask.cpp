#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	int rows = 0;
	int cols = 0;
	int result = 0;

	bool boolParam = true;

	ifstream file;
	file.open("file.txt");
	string params;
	string dataString;
	char tempSharp = '#';
		
	cout << "BedIsNotBad" << endl;

	if (file.is_open())
	{
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
		{
			for (int j = 0; j < rows; j++)
			{
				if (field[i][j] == '#')
				{
					if (field[i + 1][j] == '#' || field[i][j + 1] == '#' || field[i - 1][j] == '#' || field[i][j - 1] == '#') field[i][j] = '.';
				}
			}
		}

		system("cls");

		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				cout << field[i][j];
			}
			cout << endl;
		}

		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (field[i][j] == '#')
				{
					result++;
				}
			}
		}

		cout << result;
	}
	else cout << "File is not opened!";

	file.close();

	system("pause > nul");
	return 0;
}


	
	