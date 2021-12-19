#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

int countSteps(std::vector<std::string>& map, int mapSize);

bool isNumber(const std::string& s);
bool isValidArgs(std::vector<std::string>& args);
bool isValidMap(std::vector<std::string>& map, int size);
bool inRange(int mapSize, int raftSize, int x, int y) { return (x >= 0 && x + raftSize < mapSize) && (y >= 0 && y + raftSize < mapSize); }
bool collision(std::vector<std::string>& map, int raftSize, int raftX, int raftY);

void findPath(std::vector<std::string> map, int mapSize, int raftSize, int& steps, int x = 0, int y = 0)
{
	if (steps != -1)
		return;

	map[y][x] = '!';

	if (x == mapSize - (raftSize + 1) && y == mapSize - (raftSize + 1))
		steps = countSteps(map, mapSize) - 1;

	if (inRange(mapSize, raftSize, x + 1, y) && !collision(map, raftSize, x + 1, y))
		findPath(map, mapSize, raftSize, steps, x + 1, y);

	if (inRange(mapSize, raftSize, x, y + 1) && !collision(map, raftSize, x, y + 1))
		findPath(map, mapSize, raftSize, steps, x, y + 1);

	if (inRange(mapSize, raftSize, x - 1, y) && !collision(map, raftSize, x - 1, y))
		findPath(map, mapSize, raftSize, steps, x - 1, y);

	if (inRange(mapSize, raftSize, x, y - 1) && !collision(map, raftSize, x, y - 1))
		findPath(map, mapSize, raftSize, steps, x, y - 1);
}

int main(int argc, char const *argv[])
{
	std::vector<std::string> lines;
	std::string line;

	std::ifstream ifs("INPUT.txt");
	if (!ifs.is_open())
	{
		std::cerr << "[error]: can't open file \"INPUT.txt\"" << std::endl;
		return 1;
	}
	
	while (std::getline(ifs, line))
		lines.push_back(line);
	ifs.close();

	if (lines.size() < 2)
	{
		std::cerr << "[error]: invalid input data" << std::endl;
		return 1;
	}

	std::istringstream iss(lines[0]);
	std::vector<std::string> args((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	if (!isValidArgs(args))
	{
		std::cerr << "[error]: invalid input data" << std::endl;
		return 1;
	}

	int mapSize = std::stoi(args[0]);
	int raftSize = std::stoi(args[1]) - 1;

	lines.erase(lines.begin());

		if (!isValidMap(lines, mapSize))
	{
		std::cerr << "[error]: invalid input data" << std::endl;
		return 1;
	}

	int result = -1;

	findPath(lines, mapSize, raftSize, result);

	std::ofstream ofs("OUTPUT.txt");
	ofs << (result != -1 ? std::to_string(result) : "No");

	return 0;
}

int countSteps(std::vector<std::string>& map, int mapSize)
{
	int steps = 0;
	
	for (int y = 0; y < mapSize; ++y)
		for (int x = 0; x < mapSize; ++x)
			if (map[y][x] == '!')
				steps++;

	return steps;
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

bool isValidArgs(std::vector<std::string>& args)
{
	if (args.size() < 2)
		return false;

	if (!isNumber(args[0]) || !isNumber(args[1]))
		return false;

	int N = std::stoi(args[0]);
	int M = std::stoi(args[1]);

	if (!(1 <= N && N <= 300) || !(1 <= M && M <= N))
		return false;

	return true;
}

bool isValidMap(std::vector<std::string>& map, int size)
{
	if (map.size() != size)
		return false;

	for (int y = 0; y < size; ++y)
		for (int x = 0; x < size; ++x)
			if (!(map[y][x] == '.' || map[y][x] == '@'))
				return false;

	return true;
}

bool collision(std::vector<std::string>& map, int raftSize, int raftX, int raftY)
{
	for (int y = 0; y <= raftSize; ++y)
		for (int x = 0; x <= raftSize; ++x)
			if (map[raftY + y][raftX + x] != '.')
				return true;
	return false;
}