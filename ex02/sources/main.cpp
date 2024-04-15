#include "PmergeMe.hpp"

void printDeque(const std::deque<int> &vec, std::string const &name) {
    std::cout << "Contenu du vecteur " << name << ": ";
    for (size_t i = 0; i < vec.size(); ++i)
	{
        std::cout << vec[i];
        if (i != vec.size() - 1)
		{
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void fill_deque(std::deque<int> &vec, char **argv) {
	for (int i = 1; argv[i]; i++)
		vec.push_back(atoi(argv[i]));
}

void insert_element_at_deque(std::deque<int> &vec, int element, size_t position) {
	vec.insert(vec.begin() + position, element);
}

size_t binary_search_deque(std::deque<int> &vec, int target, size_t pos) {
    size_t left = 0;
	size_t right = pos;
	size_t mid;

    while (left < right)
	{
        mid = left + (right - left) / 2;
        if (vec[mid] < target)
		{
			left = mid + 1;
		}
		else
            right = mid;
    }

    return left;	
}

size_t find_deque(std::deque<int> &vec, int target) {
	size_t i = 0;
	while (vec[i] != target)	
		i++;
	return i;
}

void merge_sequences_deque(std::deque<int> &sequence, std::deque<int> &tmp, std::deque<int> &save) {
	size_t i = 0;

	while (i < tmp.size() && tmp[i] && save[i])
	{
		insert_element_at_deque(sequence, tmp[i], binary_search_deque(sequence, tmp[i], find_deque(sequence, save[i])));
		i++;
	}
}

void rearrange_tmp_deque(std::deque<int> &tmp) {
	size_t group = 6;
	size_t group_m = 2;
	size_t group_m_m = 2;

	if (tmp.size() >= 2 && tmp[0] && tmp[1])
        std::swap(tmp[0], tmp[1]);
    if (tmp.size() >= 4 && tmp[2] && tmp[3])
	{
        std::swap(tmp[2], tmp[3]);
	}
	size_t i = 4;
	size_t j;
	if (tmp.size() >= 10)
		j = 9;
	else
		j = tmp.size()-1;
	size_t groups = 10;
	int mode;
	while (i < tmp.size())
	{
		if (i < j)
		{
			std::swap(tmp[i], tmp[j]);
			mode = 0;
		}
		else
		{
			int gtmp = group_m;
			group_m = group;
			group_m_m = gtmp;
			group = group_m + (group_m_m * 2);

			if (groups < tmp.size() && tmp[groups])
				i = groups;
			else
				break;
			groups = groups + group;
			if (tmp.size() >= groups)
				j = groups -1;
			else
				j = tmp.size()-1;
			mode = 1;
		}
		if (mode == 0)
		{
			i++;
			j--;
		}
	}

}

void merge_deque(std::deque<int> &sequence, const std::deque<int> &p1, const std::deque<int> &p2) {
    unsigned int i = 0, j = 0, k = 0;
    while (i < p1.size() && j < p2.size())
	{
        if (p1[i] < p2[j])
            sequence[k++] = p1[i++];
        else
            sequence[k++] = p2[j++];
    }
    while (i < p1.size())
        sequence[k++] = p1[i++];
    while (j < p2.size())
        sequence[k++] = p2[j++];
}

void merge_sort_deque(std::deque<int> &sequence) {
    if (sequence.size() <= 1)
        return;

    std::deque<int> p1(sequence.begin(), sequence.begin() + sequence.size() / 2);
    std::deque<int> p2(sequence.begin() + sequence.size() / 2, sequence.end());

    merge_sort_deque(p1);
    merge_sort_deque(p2);

    merge_deque(sequence, p1, p2);
}

void get_sequence_deque(std::deque<int> &vec, std::deque<int> &sequence, std::deque<int> &tmp) {
	size_t i = 0;
	while (i < vec.size())
	{
		if (vec[i] && !vec[i + 1])
			sequence.push_back(vec[i]);
		else if (vec[i] > vec[i + 1])
		{
			sequence.push_back(vec[i]);
			tmp.push_back(vec[i + 1]);
		}
		else
		{
			sequence.push_back(vec[i + 1]);
			tmp.push_back(vec[i]);
		}
		i = i + 2;
	}
}

void sort_deque(std::deque<int> &vec) {
	size_t i = 0;
	size_t j = 0;
	while (i < vec.size())
	{
		if (vec[i] < vec[i + 1] && vec[i + 1])
			std::swap(vec[i], vec[i + 1]);
		i = i + 2;
	}
	i = 0;
	while (i < vec.size())
	{
		j = i + 2;
		while(j < vec.size())
		{
			if (vec[i] > vec[j] && vec[j] && vec[j + 1])
			{
				std::swap(vec[i], vec[j]);
				std::swap(vec[i + 1], vec[j + 1]);
			}
			j = j + 2;
		}
		i = i + 2;
	}
}

int check_doublon_deque(std::deque<int> &vec) {
	size_t i = 0;
	size_t j = 0;
	while (i < vec.size())
	{
		j = i + 1;
		while (j < vec.size())
		{
			if (vec[i] == vec[j])
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}


/******************************************************************************************/
/******************************************************************************************/
/******************************************************************************************/



void printVector(const std::vector<int> &vec, std::string const &name) {
    std::cout << "Contenu du vecteur " << name << ": ";
    for (size_t i = 0; i < vec.size(); ++i)
	{
        std::cout << vec[i];
        if (i != vec.size() - 1)
		{
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int parse(char **argv) {
	for (int i = 1; argv[i]; i++)
	{
		if (atol(argv[i]) > 2147483647 || atol(argv[i]) < 0)
			return 1;
		for (int j = 0; argv[i][j]; j++)
		{
			if (argv[i][0] == '-' && argv[i][1] && isdigit(argv[i][1]))
				continue;
			else if (isdigit(argv[i][j]))
				continue;
			else
				return 1;
		}
	}
	return 0;
}

void fill_vector(std::vector<int> &vec, char **argv) {
	for (int i = 1; argv[i]; i++)
		vec.push_back(atoi(argv[i]));
}

void insert_element_at(std::vector<int> &vec, int element, size_t position) {
	vec.insert(vec.begin() + position, element);
}

size_t binary_search(std::vector<int> &vec, int target, size_t pos) {
    size_t left = 0;
	size_t right = pos;
	size_t mid;

    while (left < right)
	{
        mid = left + (right - left) / 2;
        if (vec[mid] < target)
		{
			left = mid + 1;
		}
		else
            right = mid;
    }

    return left;	
}

size_t find(std::vector<int> &vec, int target) {
	size_t i = 0;
	while (vec[i] != target)	
		i++;
	return i;
}

void merge_sequences(std::vector<int> &sequence, std::vector<int> &tmp, std::vector<int> &save) {
	size_t i = 0;

	while (i < tmp.size() && tmp[i] && save[i])
	{
		insert_element_at(sequence, tmp[i], binary_search(sequence, tmp[i], find(sequence, save[i])));
		i++;
	}
}

void rearrange_tmp(std::vector<int> &tmp) {
	size_t group = 6;
	size_t group_m = 2;
	size_t group_m_m = 2;

	if (tmp.size() >= 2 && tmp[0] && tmp[1])
        std::swap(tmp[0], tmp[1]);
    if (tmp.size() >= 4 && tmp[2] && tmp[3])
	{
        std::swap(tmp[2], tmp[3]);
	}
	size_t i = 4;
	size_t j;
	if (tmp.size() >= 10)
		j = 9;
	else
		j = tmp.size()-1;
	size_t groups = 10;
	int mode;
	while (i < tmp.size())
	{
		if (i < j)
		{
			std::swap(tmp[i], tmp[j]);
			mode = 0;
		}
		else
		{
			int gtmp = group_m;
			group_m = group;
			group_m_m = gtmp;
			group = group_m + (group_m_m * 2);

			if (groups < tmp.size() && tmp[groups])
				i = groups;
			else
				break;
			groups = groups + group;
			if (tmp.size() >= groups)
				j = groups -1;
			else
				j = tmp.size()-1;
			mode = 1;
		}
		if (mode == 0)
		{
			i++;
			j--;
		}
	}

}

void merge(std::vector<int> &sequence, const std::vector<int> &p1, const std::vector<int> &p2) {
    unsigned int i = 0, j = 0, k = 0;
    while (i < p1.size() && j < p2.size())
	{
        if (p1[i] < p2[j])
            sequence[k++] = p1[i++];
        else
            sequence[k++] = p2[j++];
    }
    while (i < p1.size())
        sequence[k++] = p1[i++];
    while (j < p2.size())
        sequence[k++] = p2[j++];
}

void merge_sort(std::vector<int> &sequence) {
    if (sequence.size() <= 1)
        return;

    std::vector<int> p1(sequence.begin(), sequence.begin() + sequence.size() / 2);
    std::vector<int> p2(sequence.begin() + sequence.size() / 2, sequence.end());

    merge_sort(p1);
    merge_sort(p2);

    merge(sequence, p1, p2);
}

void get_sequence(std::vector<int> &vec, std::vector<int> &sequence, std::vector<int> &tmp) {
	size_t i = 0;
	while (i < vec.size())
	{
		if (vec[i] && !vec[i + 1])
			sequence.push_back(vec[i]);
		else if (vec[i] > vec[i + 1])
		{
			sequence.push_back(vec[i]);
			tmp.push_back(vec[i + 1]);
		}
		else
		{
			sequence.push_back(vec[i + 1]);
			tmp.push_back(vec[i]);
		}
		i = i + 2;
	}
}

void sort_vector(std::vector<int> &vec) {
	size_t i = 0;
	size_t j = 0;
	while (i < vec.size())
	{
		if (vec[i] < vec[i + 1] && vec[i + 1])
			std::swap(vec[i], vec[i + 1]);
		i = i + 2;
	}
	i = 0;
	while (i < vec.size())
	{
		j = i + 2;
		while(j < vec.size())
		{
			if (vec[i] > vec[j] && vec[j] && vec[j + 1])
			{
				std::swap(vec[i], vec[j]);
				std::swap(vec[i + 1], vec[j + 1]);
			}
			j = j + 2;
		}
		i = i + 2;
	}
}

int check_doublon(std::vector<int> &vec) {
	size_t i = 0;
	size_t j = 0;
	while (i < vec.size())
	{
		j = i + 1;
		while (j < vec.size())
		{
			if (vec[i] == vec[j])
				return 1;
			j++;
		}
		i++;
	}
	return 0;
}

//clear && make && ./PmergeMe $(shuf -i 1-1000 -n 1000) && make fclean 
int main(int argc, char **argv) {
	clock_t start = clock();

	if (argc < 2 || parse(argv))
		return std::cout << "A positive number sequence from 0 to 2147483647 is required" << std::endl, 1;

	std::vector<int> vec;
	std::vector<int> sequence;
	std::vector<int> tmp;
	std::vector<int> save;
	int last_number = -1;

	fill_vector(vec, argv);
	if (check_doublon(vec))
		return std::cout << "The sequence must not contain duplicates" << std::endl, 1;
	if (vec.size() % 2 != 0)
	{
		last_number = vec[vec.size() - 1];
		vec.pop_back();
	}

	sort_vector(vec);
	get_sequence(vec, sequence, tmp);
	merge_sort(sequence);
	save.insert(save.end(), sequence.begin(), sequence.end());
	rearrange_tmp(tmp);
	rearrange_tmp(save);
	merge_sequences(sequence, tmp, save);

	if (last_number > 0)
		insert_element_at(sequence, last_number, binary_search(sequence, last_number, sequence.size()));
	
	printVector(sequence, "S post merge");

	clock_t end = clock();
	double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;

	/******************************************************************************************/
	/****************************************DEQUE PART****************************************/
	/******************************************************************************************/

	clock_t start_deque = clock();

	if (argc < 2 || parse(argv))
		return std::cout << "A positive number sequence from 0 to 2147483647 is required" << std::endl, 1;

	std::deque<int> deque;
	std::deque<int> sequence_deque;
	std::deque<int> tmp_deque;
	std::deque<int> save_deque;
	int last_number_deque = -1;

	fill_deque(deque, argv);
	if (check_doublon_deque(deque))
		return std::cout << "The sequence must not contain duplicates" << std::endl, 1;
	if (deque.size() % 2 != 0)
	{
		last_number_deque = deque[deque.size() - 1];
		deque.pop_back();
	}

	sort_deque(deque);
	get_sequence_deque(deque, sequence_deque, tmp_deque);
	merge_sort_deque(sequence_deque);
	save_deque.insert(save_deque.end(), sequence_deque.begin(), sequence_deque.end());
	rearrange_tmp_deque(tmp_deque);
	rearrange_tmp_deque(save_deque);
	merge_sequences_deque(sequence_deque, tmp_deque, save_deque);

	if (last_number_deque > 0)
		insert_element_at_deque(sequence_deque, last_number_deque, binary_search_deque(sequence_deque, last_number_deque, sequence_deque.size()));
	
	printDeque(sequence_deque, "S post merge");

	clock_t end_deque = clock();
	double elapsed_secs_deque = double(end_deque - start_deque) / CLOCKS_PER_SEC;
	std::cout << "Le programme a pris avec le container vector " << elapsed_secs << " secondes pour s'exécuter." << std::endl;
	std::cout << "Le programme a pris avec le container deque  " << elapsed_secs_deque << " secondes pour s'exécuter." << std::endl;

	return 0;
}