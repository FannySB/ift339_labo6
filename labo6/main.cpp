#include <iostream>
#include <string>
#include "mapG.h"
#include "map2.h"
#include <string>



int main() {


	map<int, std::string> test;
	test.afficher();

	test[5] = "a";
	test[2] = "b";
	test[3] = "c";
	test[4] = "d";
	test[5] = "e";
	test[10] = "a1";
	test[20] = "b1";
	test[30] = "c1";
	test[40] = "d1";
/*
	test[50] = "e1";
	test[9] = "e1";
	test[8] = "e1";

	test["15"] = "a5";
	test["25"] = "b5";
	test["35"] = "c5";
	test["45"] = "d5";
	test["55"] = "e5"; 

	test.afficher();

	test.erase("1");
	test.erase("10");
	test.erase("15");
	*/


	test.afficher();
}