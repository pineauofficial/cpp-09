#include "BitcoinExchange.hpp"

#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>

int parse_key_file(std::string const &tmp) {
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

int parse_value_file(std::string const &tmp) {
	if (!tmp[13])
		return 1;
	if (tmp[12] != ' ')
		return std::cout << "Invalid format" << std::endl, 1;
	for (int i = 12; tmp[i]; i++)
		if (!isdigit(tmp[i]))
			return std::cout << "Invalid format" << std::endl, 1;
	int j = 0;
	int i = 13;
	while (tmp[i++])
		j++;
	if (atol(tmp.substr(13, j).c_str()) > 2147483647)
		return std::cout << "Too large number" << std::endl, 1;
	return 0;
}

int parse_key_data(std::string const &tmp) {
	std::string year = tmp.substr(0, 4);
	std::string month = tmp.substr(5, 2);
	std::string day = tmp.substr(8, 2);

	for (int i = 0; year[i]; i++)
		if (!isdigit(year[i]))
			return 1;
	for (int i = 0; month[i]; i++)
		if (!isdigit(month[i]))
			return 1;
	for (int i = 0; day[i]; i++)
		if (!isdigit(day[i]))
			return 1;

	if (tmp[10] != ',')
		return 1;
	return 0;
}

int parse_value_data(std::string const &tmp) {
	if (!tmp[11])
		return 1;
	for (int i = 11; tmp[i]; i++) {
		if (!isdigit(tmp[i]) && tmp[i] != '.')
			return std::cout << "Invalid format" << std::endl, 1;
	}
	int j = 0;
	int i = 11;
	while (tmp[i++])
		j++;
	if (atol(tmp.substr(11, j).c_str()) > 2147483647)
		return std::cout << "Too large number" << std::endl, 1;
	return 0;
}

std::string key(std::string const &tmp) {
	std::string key = tmp.substr(0, 10);
	return key;
}

float value(std::string const  &tmp) {
	int i = 11;
	int j = 0;
	while (tmp[i++])
		j++;
	// std::string value = tmp.substr(11, j);
	// // std::cout << "value "<< value << std::endl;
	// // std::cout << "value atof "<< atof(value.c_str()) << std::endl;
	// return atof(value.c_str());
	float value;
	value = static_cast<float>(std::atof(tmp.substr(11, j).c_str()));
	return value;
}

int fill_map(std::map<std::string, float> &map, std::ifstream &data_file) {
	std::string tmp;
	int i = 0;
	while(getline(data_file, tmp))
	{
		if (parse_key_data(tmp) || parse_value_data(tmp))
		{
			if (i != 0)
			{
				return 1;
			}
		}
		else
			if (i != 0)
				map.insert(std::make_pair(key(tmp), value(tmp)));
		i++;
	}
	return 0;
}

//enfait je dois faire le calcul la dedans et checker en meme temps
int check_infile(std::ifstream &infile) {
	std::string tmp;
	int i = 0;
	while(getline(data_file, tmp))
	{
		if (parse_key_data(tmp))
			return std::cout << "Bad input" << std::endl;
		if 
	}
}

bool is_openable(const char *filename) {
    if (access(filename, F_OK) == -1)
        return false;
    if (access(filename, R_OK) == -1)
        return false;
    return true;
}

//gerer format des dates genre 42/42/2012
int main(int argc, char **argv) {
	if (argc != 2)
		return (std::cout << "Need one file .txt as argument", 1);
	std::map<std::string, float> map;

	/*--------------------Gestion du file.txt--------------------*/
	std::ifstream infile;
	std::string name_infile;
	name_infile = argv[1];
	infile.open(name_infile.c_str(), std::fstream::in);
	if (!is_openable(argv[1]))
		return std::cout << "Can't open this file" << std::endl, 1;

	/*------------------------------------------------------------*/

	/*--------------------Gestion du data.csv--------------------*/
	std::ifstream data_file;
	std::string name_data_file;
	name_data_file = "data.csv"; 
	data_file.open(name_data_file.c_str(), std::fstream::in);
	if (!is_openable(argv[1]))
		return std::cout << "Can't open this file" << std::endl, 1;
	/*------------------------------------------------------------*/

	/*---------------------Coeur du programme---------------------*/
	if (fill_map(map, data_file))
		return std::cout << "Invalid format" << std::endl, 1;
	/*------------------------------------------------------------*/
    
	/*----------------------Affichage de map----------------------*/
	std::map<std::string, float>::iterator it;
	for (it = map.begin(); it != map.end(); ++it)
	{
        std::cout << (*it).first << "," <<(*it).second << std::endl;
	}
	/*------------------------------------------------------------*/

	data_file.close();
	infile.close();
	return 0;
}