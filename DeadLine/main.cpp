#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iterator>

#define INPUT_FILE_NAME "INPUT.txt"
#define OUTPUT_FILE_NAME "OUTPUT.txt"
#define THERE_IS_NO_WAY "No"
#define LAND_CHAR '@'
#define WATER_CHAR '.'

enum MAP_LOCATION_MARKER { WATER = 0, LAND = -1, VISITED = -2 };

/*
/	I'm using a self-written "Node" structure to store
/ coordinates instead of standard std::pair because
/ i’m too lazy to write ".first" and ".second",
/ it’s too cumbersome.
*/
struct Node
{
	int x;
	int y;

	Node(int x, int y) : x(x), y(y) {}

	bool operator ==(Node& otherNode) { return x == otherNode.x && y == otherNode.y; }
};

struct READING_RESULT
{
	const std::string OK = "ok";
	const std::string INVALID_INPUT_DATA = "invalid input data";
	const std::string CANNOT_OPEN_FILE = std::string("can't open file \"") + INPUT_FILE_NAME + "\"";
};

std::string readInput(std::vector<std::string>& lines, int& mapSize, int& raftSize);

bool inRange(const int mapSize, const int raftSize, const int x, const int y) { return (x >= 0 && x + (raftSize - 1) < mapSize) && (y >= 0 && y + (raftSize - 1) < mapSize); }
bool collision(int* const map, const int mapSize, const int raftSize, const int raftX, const int raftY);



int main(int argc, char const *argv[])
{
	std::vector<std::string> lines;

	int mapSize;
	int raftSize;

	const std::string readingResult = readInput(lines, mapSize, raftSize);
	if (readingResult != READING_RESULT().OK)
	{
		std::cerr << "[error]: " << readingResult << std::endl;
		return 1;
	}

	int* map = new int[mapSize * mapSize]{};
	for (int y = 0; y < mapSize; ++y)
		for (int x = 0; x < mapSize; ++x)
			if (lines[y][x] == LAND_CHAR)
				map[mapSize * y + x] = MAP_LOCATION_MARKER::LAND;

	Node nodeStart(0, 0);
	Node nodeEnd(mapSize - raftSize, mapSize - raftSize);

	map[mapSize * nodeStart.y + nodeStart.x] = MAP_LOCATION_MARKER::VISITED;

	std::vector<Node> wave;
	std::vector<Node> nextWave;

	wave.push_back(nodeStart);

	int result = -1;
	while (result == -1)
	{
		if (!wave.size())
		{
			if (!nextWave.size())
				break;
			wave = nextWave;
			nextWave.clear();
		}

		Node node = wave.back();
		wave.pop_back();

		if (node == nodeEnd)
		{
			/*
			/ In the next line of code, i'm doing +2 because
			/ nodeStart is marked on map as MAP_LOCATION_MARKER::VISITED (-2)
			/ and we need to add 2 to the result to compensate for that.
			/ So if you remove this, the result is 2 less than expected.
			*/
			result = map[mapSize * node.y + node.x] + 2;
			break;
		}

		if (inRange(mapSize, raftSize, node.x, node.y - 1) && map[mapSize * (node.y - 1) + node.x] == MAP_LOCATION_MARKER::WATER && !collision(map, mapSize, raftSize, node.x, node.y - 1))
		{
			map[mapSize * (node.y - 1) + node.x] = map[mapSize * node.y + node.x] + 1;
			nextWave.push_back(Node(node.x, node.y - 1));
		}

		if (inRange(mapSize, raftSize, node.x, node.y + 1) && map[mapSize * (node.y + 1) + node.x] == MAP_LOCATION_MARKER::WATER && !collision(map, mapSize, raftSize, node.x, node.y + 1))
		{
			map[mapSize * (node.y + 1) + node.x] = map[mapSize * node.y + node.x] + 1;
			nextWave.push_back(Node(node.x, node.y + 1));
		}

		if (inRange(mapSize, raftSize, node.x - 1, node.y) && map[mapSize * node.y + (node.x - 1)] == MAP_LOCATION_MARKER::WATER && !collision(map, mapSize, raftSize, node.x - 1, node.y))
		{
			map[mapSize * node.y + (node.x - 1)] = map[mapSize * node.y + node.x] + 1;
			nextWave.push_back(Node(node.x - 1, node.y));
		}

		if (inRange(mapSize, raftSize, node.x + 1, node.y) && map[mapSize * node.y + (node.x + 1)] == MAP_LOCATION_MARKER::WATER && !collision(map, mapSize, raftSize, node.x + 1, node.y))
		{
			map[mapSize * node.y + (node.x + 1)] = map[mapSize * node.y + node.x] + 1;
			nextWave.push_back(Node(node.x + 1, node.y));
		}
	}

	std::ofstream ofs(OUTPUT_FILE_NAME);
	ofs << (result != -1 ? std::to_string(result) : THERE_IS_NO_WAY);

	delete[] map;
	return 0;
}



bool collision(int* const map, const int mapSize, const int raftSize, const int raftX, const int raftY)
{
	for (int y = 0; y < raftSize; ++y)
		for (int x = 0; x < raftSize; ++x)
			if (map[mapSize * (raftY + y) + (raftX + x)] == MAP_LOCATION_MARKER::LAND)
				return true;
	return false;
}

bool isNumber(const std::string& value)
{
	std::string::const_iterator it = value.begin();
	while (it != value.end() && std::isdigit(*it))
		++it;
	return !value.empty() && it == value.end();
}

bool isValidArgs(const std::vector<std::string>& args)
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

bool isValidMap(const std::vector<std::string>& map, const int mapSize)
{
	if (map.size() != mapSize)
		return false;

	for (int y = 0; y < mapSize; ++y)
		for (int x = 0; x < mapSize; ++x)
			if (!(map[y][x] == WATER_CHAR || map[y][x] == LAND_CHAR))
				return false;

	return true;
}

std::string readInput(std::vector<std::string>& lines, int& mapSize, int& raftSize)
{
	std::string line;

	std::ifstream ifs(INPUT_FILE_NAME);
	if (!ifs.is_open())
		return READING_RESULT().CANNOT_OPEN_FILE;
	
	while (std::getline(ifs, line))
		lines.push_back(line);
	ifs.close();

	if (lines.size() < 2)
		return READING_RESULT().INVALID_INPUT_DATA;

	std::istringstream iss(lines[0]);
	std::vector<std::string> args((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

	if (!isValidArgs(args))
		return READING_RESULT().INVALID_INPUT_DATA;

	mapSize = std::stoi(args[0]);
	raftSize = std::stoi(args[1]);

	lines.erase(lines.begin());

	if (!isValidMap(lines, mapSize))
		return READING_RESULT().INVALID_INPUT_DATA;

	return READING_RESULT().OK;
}