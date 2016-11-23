#include <iostream>
#include <string>
#include "map.h"
#include <string>


using namespace std;

int main() {
	map<int, int> testMap = map<int, int>();
	std::cout << "Insertion de 10" << std::endl;
	testMap[10] = 10;
		testMap.afficher();

	std::cout << "Insertion de 9" << std::endl;
	testMap[9] = 9;
		testMap.afficher();

	std::cout << "Insertion de 8" << std::endl;
	testMap[8] = 8;
		testMap.afficher();

	std::cout << "Insertion de 7" << std::endl;
	testMap[7] = 7;
		testMap.afficher();

	std::cout << "Insertion de 6" << std::endl;
	testMap[6] = 6;
		testMap.afficher();

	std::cout << "Insertion de 5" << std::endl;
	testMap[5] = 5;
		testMap.afficher();

	std::cout << "Insertion de 4" << std::endl;
	testMap[4] = 4;
		testMap.afficher();

	std::cout << "Insertion de 3" << std::endl;
	testMap[3] = 3;
		testMap.afficher();

	std::cout << "Insertion de 3" << std::endl;
	testMap[2] = 2;
		testMap.afficher();


	map<int, int>::iterator lower_bound = testMap.lower_bound(5);

	testMap = map<int, int>();
	std::cout << "Insertion de 1" << std::endl;
	testMap[1] = 1;
	std::cout << "Insertion de 2" << std::endl;
	testMap[2] = 2;
	std::cout << "Insertion de 3" << std::endl;
	testMap[3] = 3;
	std::cout << "Insertion de 4" << std::endl;
	testMap[4] = 4;
	std::cout << "Insertion de 5" << std::endl;
	testMap[6] = 6;
	testMap.afficher();


	lower_bound = testMap.lower_bound(5);
	//std::cout << lower_bound->first << std::endl;
}