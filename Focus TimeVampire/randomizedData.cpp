//#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <random>

#include "randomizedData.h"

int randomInt(float floor, int range) {
	int randomNum = floor + (rand() % range);
	return randomNum;
}

string randomizeStart_Alpha(int num) {
	//auto rd = std::random_device{}; used to randomize multiple calls?
	auto rng = std::default_random_engine{};
	int charCount = 65;
	char newChar;
	vector <int>numbers = {charCount};
	string letters = (1,"");

	for(int i = 1; i < num; i++) {
		charCount++;
		numbers.push_back(charCount);
	}	
	std::shuffle(std::begin(numbers), std::end(numbers), rng);

	for(int i = 0; i < num; i++) {
		newChar = numbers[i];
		letters += newChar;
	}
	return letters;
}

//vector <string> setBubbleValues(std::ostringstream& out, vector <string> bubvec) {
//	string letters, value;
//	letters = randomABC();
//
//	for (int i = 0; i < bubvec.size(); i++) {
//		long randomNum = rand() * (RAND_MAX * 0.001);//more decimals, more smaller
//		out.imbue(std::locale(""));
//		out << letters[i] << ":   " << std::put_money(randomNum);
//		value = out.str();
//		bubvec.at(i) = value;
//		out.str("");
//	}
//	return bubvec;
//}