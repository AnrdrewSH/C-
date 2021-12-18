#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void search(std::vector<std::string>& map, int x, int y)
{
	map[y][x] = '!';

	if (x - 1 >= 0 && map[y][x - 1] == '.')
		search(map, x - 1, y);

	if (x + 1 < map.size() && map[y][x + 1] == '.')
		search(map, x + 1, y);
	
	if (y - 1 >= 0 && map[y - 1][x] == '.')
		search(map, x, y - 1);

	if (y + 1 < map.size() && map[y + 1][x] == '.')
		search(map, x, y + 1);
}

int main(int argc, char const *argv[])
{
	std::vector<std::string> lines;
	std::string line;

	std::ifstream ifs("INPUT.txt");
	if (ifs.is_open())
	{
		while (std::getline(ifs, line))
			lines.push_back(line);
		ifs.close();
	}
	else
	{
		std::cerr << "[error]: can't open file" << std::endl;
		return 1;
	}

	int n = std::stoi(lines[0]);
	lines.erase(lines.begin());

	search(lines, 0, 0);

	int result = 0;
	for (int y = 0; y < n; ++y)
		for (int x = 0; x < n; ++x)
			if (lines[y][x] == '!')
			{
				if (x - 1 < 0 || lines[y][x - 1] == '#')
					result += 9;
				if (x + 1 >= n || lines[y][x + 1] == '#')
					result += 9;
				if (y - 1 < 0 || lines[y - 1][x] == '#')
					result += 9;
				if (y + 1 >= n || lines[y + 1][x] == '#')
					result += 9;
			}

	result -= 9 * 4;

	std::ofstream ofs("OUTPUT.txt");
	ofs << result;

	return 0;
}