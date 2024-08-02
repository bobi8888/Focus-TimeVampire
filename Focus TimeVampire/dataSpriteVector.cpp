#include"utils.h"

#include "gameSprite.h"
#include "randomizedData.h"

DataSpriteVector::DataSpriteVector(){};
DataSpriteVector::DataSpriteVector(int qty, DataSprite dataSprite){
	for (int i = 1; i <= qty; i++) {
		dataSpriteVector.push_back(dataSprite);
	}
}
void DataSpriteVector::setPositions(sf::Vector2f center, int rows, int columns, float rowSpacing, float colSpacing) {
	auto xC2C = colSpacing + dataSpriteVector[0].getSprite().getGlobalBounds().width;
	auto yC2C = rowSpacing + dataSpriteVector[0].getSprite().getGlobalBounds().height;

	auto overallX = (dataSpriteVector[0].getSprite().getGlobalBounds().width * columns) + colSpacing * (columns - 1);
	auto overallY = (dataSpriteVector[0].getSprite().getGlobalBounds().height * rows) + rowSpacing * (rows - 1);

	float baseX = center.x - (overallX / 2) + (dataSpriteVector[0].getSprite().getGlobalBounds().width / 2);
	float baseY = center.y - overallY / 2 + dataSpriteVector[0].getSprite().getGlobalBounds().height / 2;
	sf::Vector2f newPosition(baseX, baseY);
	int qty = 0;
	while (qty < rows * columns) {
		for (int i = 0; i < rows; i++) {//y
			if (i > 0) {
				newPosition.y += yC2C;//creates next row
				newPosition.x = baseX;//restarts x
			}
			for (int j = 0; j < columns; j++) {//x
				if (j > 0) {
					newPosition.x += xC2C;//increment x
				}
				dataSpriteVector[qty].setPosition(newPosition);
				qty++;
			}
		}
	}
}

vector <DataSprite> DataSpriteVector::getDataSpriteVector() {
	return dataSpriteVector;
}
DataSprite DataSpriteVector::getSingleSprite(int index){
	return dataSpriteVector.at(index);
}
//what it the int qty really doing?
void DataSpriteVector::addSprite(DataSprite dataSpritePtr, int qty) {
	for (int i = 1; i <= qty; i++) {
		dataSpriteVector.push_back(dataSpritePtr);
	}
}

void DataSpriteVector::setCanMove(int index, sf::Event event, sf::Vector2f translatedMousePosition) {
	dataSpriteVector[index].handleCanMove(event, translatedMousePosition);
}
void DataSpriteVector::setSpritePosition(int index, sf::Vector2f newPosition){
	dataSpriteVector[index].setPosition(newPosition);
}

void DataSpriteVector::drawSprites(sf::RenderWindow &window, int skipIndex) {//skipIndex is needed for the assemble
	if (skipIndex > 0) window.draw(dataSpriteVector[skipIndex].getSprite());

	for (int i = 0; i < dataSpriteVector.size(); i++) {
		if (i != skipIndex) window.draw(dataSpriteVector[i].getSprite());	
	}
}
void DataSpriteVector::updateIndividualTexture(int index, string newTexture){
	dataSpriteVector[index].setNewTexture(newTexture);
}

void DataSpriteVector::checkForCompletion() {
	int numComplete = 0;
	for (int i = 0; i < dataSpriteVector.size(); i++) if (dataSpriteVector[i].getIsComplete()) numComplete++;
	if (numComplete == dataSpriteVector.size()) vectorComplete = true;
}
bool DataSpriteVector::getVectorComplete(){
	return vectorComplete;
}
void DataSpriteVector::setSpriteToComplete(int index) {
	dataSpriteVector[index].setToComplete();
}

string DataSpriteVector::getLetter(int index) {
	return dataSpriteVector.at(index).getLetter();
}
void DataSpriteVector::setLetters() {
	string letters = randomizeStart_Alpha(dataSpriteVector.size());
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		string tempString = (1, "");
		tempString = letters[i];
		dataSpriteVector.at(i).setLetter(tempString);
	}
}

long DataSpriteVector::getLongValues(int index) {
	return dataSpriteVector.at(index).getLongValue();
}
void DataSpriteVector::setLongValues() {
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		long randomNum = rand() * (RAND_MAX * 0.001);//more decimals, more smaller
		dataSpriteVector.at(i).setLongValue(randomNum);
	}
}

string DataSpriteVector::getFullDataStrings(int index) {
	return dataSpriteVector.at(index).getFullDataString();
}
void DataSpriteVector::setFullDataStrings(std::ostringstream& out) { 
	string outString;
	for (int i = 0; i <= dataSpriteVector.size() - 1; i++) {
		out.imbue(std::locale(""));
		out << std::put_money(dataSpriteVector[i].getLongValue());
		outString = out.str();
		dataSpriteVector[i].setFullDataString(dataSpriteVector[i].getLetter() + ":  $" + outString);
		out.str("");
	}
}

void DataSpriteVector::setStringValues(std::stringstream& stream) {//this is adding a comma to the string value from the long int 
	string outString;
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		stream << dataSpriteVector[i].getLongValue();
		outString = stream.str();
		dataSpriteVector[i].setStringValue(outString);
		stream.str("");
	}
}