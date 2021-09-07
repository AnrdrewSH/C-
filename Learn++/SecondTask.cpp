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
	int neighborCounter = 0;

	ifstream file;
	file.open("file.txt");
	string params;
	string dataString;
		
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
					if (i + 1 != cols)
					{
						if (field[i + 1][j] == '#') neighborCounter++, field[i][j] = '.';
					}
					if (j + 1 != rows)
					{
						if (field[i][j + 1] == '#') neighborCounter++, field[i][j] = '.';
					}
					if (i - 1 >= 0)
					{
						if (field[i - 1][j] == '#') neighborCounter++, field[i][j] = '.';
					}
					if (j - 1 >= 0)
					{
						if (field[i][j - 1] == '#') neighborCounter++, field[i][j] = '.';
					}
					if (neighborCounter > 1) result--;
				}
				neighborCounter = 0;
			}
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

		cout << endl << result;
	}
	else cout << "File is not opened!";

	file.close();

	system("pause > nul");
	return 0;
}


	
	