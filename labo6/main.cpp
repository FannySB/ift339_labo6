#include <iostream>
#include <string>
#include "map.h"
#include <string>


using namespace std;

int main() {
	map<int, int> testMap = map<int, int>();

/*
	std::cout << "ASC -- 1 -- Insertion de " << 3 << std::endl;
	testMap[5] = 5;
	testMap.afficher();


	std::cout << "ASC -- 1 -- Insertion de " << 3 << std::endl;
	testMap[4] = 4;
	testMap.afficher();

	std::cout << "ASC -- 1 -- Insertion de " << 2 << std::endl;
	testMap[3] = 3;
	testMap.afficher();


	std::cout << "ASC -- 1 -- Insertion de " << 10 << std::endl;
	testMap[10] = 10;
	testMap.afficher();

	std::cout << "ASC -- 1 -- Insertion de " << 1 << std::endl;
	testMap[2] = 2;
	testMap.afficher();

	std::cout << "ASC -- 1 -- Insertion de " << 4 << std::endl;
	testMap[1] = 1;
	testMap.afficher();

*/

	for (size_t i = 0; i < 10; i++) {
		std::cout << "ASC -- 1 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	map<int, int>::iterator lower_bound = testMap.lower_bound(-1);
	lower_bound = testMap.lower_bound(0);
	lower_bound = testMap.lower_bound(50);
	lower_bound = testMap.lower_bound(100);
	lower_bound = testMap.lower_bound(200);
	lower_bound = testMap.lower_bound(1000);


	testMap = map<int, int>();
	for (size_t i = 100; i > 0; i--) {
		std::cout << "DESC -- 1 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	lower_bound = testMap.lower_bound(-1);
	lower_bound = testMap.lower_bound(0);
	lower_bound = testMap.lower_bound(50);
	lower_bound = testMap.lower_bound(100);
	lower_bound = testMap.lower_bound(200);
	lower_bound = testMap.lower_bound(1000);

	testMap = map<int, int>();
	for (size_t i = 0; i < 50; i++) {
		std::cout << "ASC -- 2 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	for (size_t i = 100; i > 94; i--) {
		std::cout << "DESC -- 2 -- Insertion de " << i << std::endl;
		testMap[i] = i;
		testMap.afficher();
	}
	lower_bound = testMap.lower_bound(-1);
	lower_bound = testMap.lower_bound(0);
	lower_bound = testMap.lower_bound(50);
	lower_bound = testMap.lower_bound(100);
	lower_bound = testMap.lower_bound(200);
	lower_bound = testMap.lower_bound(1000);
}