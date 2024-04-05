#include "BitcoinExchange.hpp"

int parse_key(std::string const &tmp) {
	std::string year = tmp.substr(0, 4);
	std::string month = tmp.substr(5, 2);
	std::string day = tmp.substr(8, 2);

	for (int i = 0; year[i]; i++)
		if (!isdigit(year[i]))
			return std::cout << "Invalid format" << std::endl, 1;
	for (int i = 0; month[i]; i++)
		if (!isdigit(month[i]))
			return std::cout << "Invalid format" << std::endl, 1;
	for (int i = 0; day[i]; i++)
		if (!isdigit(day[i]))
			return std::cout << "Invalid format" << std::endl, 1;

	if (tmp[10] != ' ' || tmp[11] != '|' || tmp[4] != '-' || tmp[7] != '-')
		return std::cout << "Invalid format" << std::endl, 1;
	return 0;
}

int parse_value(std::string const &tmp) {
	if (tmp[12] != ' ')
		return std::cout << "Invalid format" << std::endl, 1;
	for (int i = 12; tmp[i]; i++)
		if (!isdigit(tmp[i]))
			return std::cout << "Invalid format" << std::endl, 1;
	if (atol(tmp) > 2147483647 || atol(tmp) < -2147483648)
		return std::cout << "Too large number"
	return 0;
}

std::string key(std::string const &tmp) {
	return std::string key = tmp.substr(0, 10);
}

std::string value(std::string const  &tmp) {
	int i = 12;
	int j = 0;
	while (tmp[i++])
		j++;
	return std::string value = tmp.substr(12, j);
}

void fill_map(std::map &map, ) {
	std::string tmp;
	while(getline(infile, tmp))
		map.insert(key(tmp), value(tmp));
}

int	is_openable() {

}

int main(int argc, char **argv) {
	if (argc != 2)
		return (std::cout << "Need one file .txt as argument", 1);
	std::ifstream infile;
	std::string nameinfile;

	nameinfile = argv[1];
	infile.open(nameinfile.c_str(), std::fstream::in);
	std::string tmp;
	while(getline(infile, tmp))
		std::cout << tmp << std::endl;

	std::map<std::string, int> map;
	fill_map(map);

}