#include "BitcoinExchange.hpp"

int parse_key_file(std::string const &tmp) {
    std::string year = tmp.substr(0, 4);
    std::string month = tmp.substr(5, 2);
    std::string day = tmp.substr(8, 2);

    for (size_t i = 0; i < year.length(); ++i)
        if (!isdigit(year[i]))
            return 1;
    for (size_t i = 0; i < month.length(); ++i)
        if (!isdigit(month[i]))
            return 1;
    for (size_t i = 0; i < day.length(); ++i)
        if (!isdigit(day[i]))
            return 1;

    int year_int = atoi(year.c_str());
    int month_int = atoi(month.c_str());
    int day_int = atoi(day.c_str());

    if (month_int > 12 || month_int < 1)
        return 1;
    if (day_int > 31 || day_int < 1)
        return 1;
    if (tmp[10] != ' ' || tmp[11] != '|' || tmp[4] != '-' || tmp[7] != '-')
        return 1;
    if ((month_int == 4 || month_int == 6 || month_int == 9 || month_int == 11) && day_int > 30)
        return 1;
    if (month_int == 2) 
	{
        if (year_int % 4 == 0) 
		{
            if (day_int > 29)
                return 1;
        } else 
		{
            if (day_int > 28)
                return 1;
        }
    }

    return 0;
}

float parse_value_file(std::string const &tmp) {
	if (!tmp[13])
		return -1;
	if (tmp[12] != ' ')
		return -1;
	if (tmp[13] == '-')
		return -2;
	for (int i = 13; tmp[i]; i++)
		if (!isdigit(tmp[i]) && tmp[i] != '.')
			return -1;
	int j = 0;
	int i = 13;
	while (tmp[i++])
		j++;
	if (atol(tmp.substr(13, j).c_str()) > 2147483647)
		return -3;
	return atof(tmp.substr(13, j).c_str());
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
	if (atoi(month.c_str()) > 12)
		return 1;
	if (atoi(day.c_str()) > 31)
		return 1;

	int year_int = atoi(year.c_str());
    int month_int = atoi(month.c_str());
    int day_int = atoi(day.c_str());
	
	if ((month_int == 4 || month_int == 6 || month_int == 9 || month_int == 11) && day_int > 30)
        return 1;
    if (month_int == 2) 
	{
        if (year_int % 4 == 0) 
		{
            if (day_int > 29)
                return 1;
        } else 
		{
            if (day_int > 28)
                return 1;
        }
    }
	if (tmp[10] != ',')
		return 1;
	return 0;
}

int parse_value_data(std::string const &tmp) {
	if (!tmp[11])
		return 1;
	for (int i = 11; tmp[i]; i++) {
		if (!isdigit(tmp[i]) && tmp[i] != '.')
			return 1;
	}
	int j = 0;
	int i = 11;
	while (tmp[i++])
		j++;
	if (atol(tmp.substr(11, j).c_str()) > 2147483647)
		return 1;
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

void calcul(std::string const &tmp, float value, std::map<std::string, float> &map) {
	std::string date = tmp.substr(0, 10);
	std::map<std::string, float>::iterator it;
	bool found = false;
	for (it = map.begin(); it != map.end(); ++it)
	{
		if ((*it).first == date)
		{
			std::cout << date << " => " << value * (*it).second << std::endl;
			found = true;
			break ;
		}
	}
	if (!found) {
        std::map<std::string, float>::reverse_iterator rit;
        for (rit = map.rbegin(); rit != map.rend(); ++rit) {
            if ((*rit).first < date) {
                std::cout << (*rit).first << " => " << value * (*rit).second << std::endl;
                break;
            }
        }
    }

}

int check_infile(std::ifstream &infile, std::map<std::string, float> &map) {
	std::string tmp;
	int i = 0;
	while(getline(infile, tmp))
	{
		if (i == 0)
			i++;
		else if (parse_key_file(tmp))
			std::cout << tmp << " => Bad input" << std::endl;
		else if (parse_value_file(tmp) == -1)
			std::cout << tmp << " => Invalid format" << std::endl;
		else if (parse_value_file(tmp) == -2)
			std::cout << tmp << " => Not a positive number" << std::endl;
		else if (parse_value_file(tmp) == -3)
			std::cout << tmp << " => Too large number" << std::endl;
		else
			calcul(tmp, parse_value_file(tmp), map);
	}

	return 0;
}

bool is_openable(const char *filename) {
    if (access(filename, F_OK) == -1)
        return false;
    if (access(filename, R_OK) == -1)
        return false;
    return true;
}

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
		return std::cout << "Invalid format in .csv file" << std::endl, 1;
	check_infile(infile, map);
	/*------------------------------------------------------------*/
    
	/*----------------------Affichage de map----------------------*/
	// std::map<std::string, float>::iterator it;
	// for (it = map.begin(); it != map.end(); ++it)
	// {
    //     std::cout << (*it).first << "," <<(*it).second << std::endl;
	// }
	/*------------------------------------------------------------*/

	data_file.close();
	infile.close();
	return 0;
}