#include "PmergeMe.hpp"

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

void compare_and_swap(std::vector<int> &vec) {
	if (vec.front() < vec.back())
		std::swap(vec.front(), vec.back());
}

std::vector<int> get_sequence(std::vector<int> &vec) {
    std::vector<int> sequence;

	if (vec.size() <= 2)
	{
		compare_and_swap(vec);
		sequence.push_back(vec.front());
        return sequence;
	}

    std::vector<int> p1(vec.begin(), vec.begin() + vec.size() / 2);
    std::vector<int> p2(vec.begin() + vec.size() / 2, vec.end());

	printVector(p1, "p1");
	printVector(p2, "p2");
   	
	p1 = get_sequence(p1);
    p2 = get_sequence(p2);

    sequence.insert(sequence.end(), p1.begin(), p1.end());
    sequence.insert(sequence.end(), p2.begin(), p2.end());

	printVector(sequence, "sequence");

    return sequence;
}

int main(int argc, char **argv) {
	if (argc < 2 || parse(argv))
		return std::cout << "A number sequence is required" << std::endl, 1;
	std::vector<int> vec;
	fill_vector(vec, argv);
	vec = get_sequence(vec);

	return std::cout << "All good" << std::endl, 0;
}