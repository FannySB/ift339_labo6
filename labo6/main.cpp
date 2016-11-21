#include <iostream>
#include <string>
#include "map.h"
#include <string>


using namespace std;

int main() {
	map<int, int> testMap = map<int, int>();
	testMap[1] = 1;
	testMap[2] = 2;
	testMap[3] = 3;
	testMap[4] = 4;
	testMap[5] = 5;

	map<int, int>::PAIR testPair = map<int, int>::PAIR(1, 1);

	testMap.afficher();
}