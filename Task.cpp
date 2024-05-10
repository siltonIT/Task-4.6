#include "Task.h"
#include <climits>

int main() {
	BigInt num = 1;
	for(size_t i = 2; i <= 100; ++i)
		num *= i;
	
	std::cout << num << std::endl;
}	
