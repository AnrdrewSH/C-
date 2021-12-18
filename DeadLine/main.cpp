#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

bool isWayOut(std::vector<std::string> map, int x, int y)
{
	map[y][x] = '!';

	if (x - 1 < 0 || x + 1 >= map[0].size() || y - 1 < 0 || y + 1 >= map.size())
		return true;

	if (map[y][x - 1] == '0')
		return isWayOut(map, x - 1, y);

	if (map[y][x + 1] == '0')
		return isWayOut(map, x + 1, y);

	if (map[y - 1][x] == '0')
		return isWayOut(map, x, y - 1);

	if (map[y + 1][x] == '0')
		return isWayOut(map, x, y + 1);

	return false;
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

	std::istringstream iss(lines[0]);
	std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	int h = std::stoi(results[0]);
	int w = std::stoi(results[1]);

	lines.erase(lines.begin());

	int result = 0;

	for (int y = 0; y < h; ++y)
		for (int x = 0; x < w; ++x)
			if (lines[y][x] == '1')
			{
				if (x - 1 < 0 || (lines[y][x - 1] == '0' && isWayOut(lines, x - 1, y)))
					result += 1;
				if (x + 1 >= w || (lines[y][x + 1] == '0' && isWayOut(lines, x + 1, y)))
					result += 1;
				if (y - 1 < 0 || (lines[y - 1][x] == '0' && isWayOut(lines, x, y - 1)))
					result += 1;
				if (y + 1 >= h || (lines[y + 1][x] == '0' && isWayOut(lines, x, y + 1)))
					result += 1;
			}

	std::ofstream ofs("OUTPUT.txt");
	ofs << std::to_string(result);

	return 0;
}