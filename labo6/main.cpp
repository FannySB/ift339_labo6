#include <iostream>
#include <string>
#include "map.h"
#include <string>


using namespace std;

int main() {
	map<int, int> testMap = map<int, int>();
	for (size_t i = 0; i < 100; i++) {
		std::cout << "ASC -- 1 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	map<int, int>::iterator lower_bound = testMap.lower_bound(0);
	lower_bound = testMap.lower_bound(50);
	lower_bound = testMap.lower_bound(100);


	testMap = map<int, int>();
	for (size_t i = 100; i > 0; i--) {
		std::cout << "DESC -- 1 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	lower_bound = testMap.lower_bound(0);
	lower_bound = testMap.lower_bound(50);
	lower_bound = testMap.lower_bound(100);

	testMap = map<int, int>();
	for (size_t i = 0; i < 50; i++) {
		std::cout << "ASC -- 2 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	for (size_t i = 100; i > 50; i--) {
		std::cout << "DESC -- 2 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	lower_bound = testMap.lower_bound(0);
	lower_bound = testMap.lower_bound(50);
	lower_bound = testMap.lower_bound(100);



	lower_bound = testMap.lower_bound(5);

	lower_bound = testMap.lower_bound(5);
	//std::cout << lower_bound->first << std::endl;
}