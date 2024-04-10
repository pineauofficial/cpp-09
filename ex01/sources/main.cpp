#include "RPN.hpp"

int parse(char *argv) {
	int i = 0;
	int digit = 0;
	int ope = 0;
	int mode = 0;

	while (argv[i])
	{
		if ((argv[i] == '+' || argv[i] == '-' || argv[i] == '*' || argv[i] == '/') && mode != 1)
		{
			ope++;
			mode = 1;
		}
		else if (isdigit(argv[i]) && mode != 1)
		{
			digit++;
			mode = 1;
		}	
		else if (argv[i] == ' ')
			mode = 2;
		else
			return 1;
		i++;
	}
	int check = 0;
	for (int i = 0; check != 2; i++)
	{
		if (isdigit(argv[i]))
			check ++;
		else if (argv[i] != ' ')
			return 1;
	}
	if (digit - 1 != ope)
		return 1;
	return 0;
}

int calcul(std::stack<long long int> &stack, char *argv) {
	long long int result = 0;
	for (int i = 0; argv[i]; i++)
	{
		if (isdigit(argv[i]))
			stack.push(argv[i] - '0');
		else if (argv[i] == '+')
		{
			result = stack.top();
			stack.pop();
			result = result + stack.top();
			stack.pop();
			stack.push(result);
		}
		else if (argv[i] == '-')
		{
			result = stack.top();
			stack.pop();
			result = stack.top() - result;
			stack.pop();
			stack.push(result);
		}
		else if (argv[i] == '*')
		{
			result = stack.top();
			stack.pop();
			result = stack.top() * result;
			stack.pop();
			stack.push(result);
		}
		else if (argv[i] == '/')
		{
			result = stack.top();
			stack.pop();
			if (result == 0)
				return 1;
			result = stack.top() / result;
			stack.pop();
			stack.push(result);
		}
		if (argv[i] != ' ' && stack.top() > 2147483647)
			return 1;
	}
	std::cout << stack.top() << std::endl;
	return 0;
}

//gerer div 0
int main(int argc, char **argv) {
	if (argc != 2)
		return 1;
	if (parse(argv[1]))
		return std::cout << "Error" << std::endl, 1;
	
	std::stack<long long int> stack;
	if (calcul(stack, argv[1]))
		return std::cout << "Error" << std::endl, 1;
	return 0;
}