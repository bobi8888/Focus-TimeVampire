#include <SFML/Graphics.hpp>
#include "gameSprite.h"
#include "dataSprite.h"
using std::string;

string DataSprite::getLetter() {
	return letter;
}
void DataSprite::setLetter(string newLetter) {
	letter = newLetter;
}

long DataSprite::getLongValue() {
	return value;
}
void DataSprite::setLongValue(long currentLong) {
	value = currentLong;
}

string DataSprite::getStringValue() {
	return valueAsString;
}
void DataSprite::setStringValue(string string) {
	valueAsString = string;
}

string DataSprite::getFullDataString() {
	return fullDataString;
}
void DataSprite::setFullDataString(string string) {
	fullDataString = string;
}

bool DataSprite::getIsComplete(){
	return isComplete;
}
void DataSprite::setIsComplete(bool complete){
	isComplete = complete;
}