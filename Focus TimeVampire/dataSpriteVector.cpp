#include "utils.h";

#include "gameSprite.h"
#include "dataSprite.h"
#include "transformableSprite.h"
#include "randomizedData.h"
#include "dataSpriteVector.h"

vector <DataSprite> DataSpriteVector::getDataSpriteVector() {
	return dataSpriteVector;
}
void DataSpriteVector::addSprite(DataSprite dataSprite, int qty) {
	for (int i = 0; i < qty; i++) {
		dataSpriteVector.push_back(dataSprite);
	}
}
void DataSpriteVector::setSpritePositions(int rows, int columns, float xSpriteSpacing, float ySpriteSpacing, float initialX, float initialY) {
	auto xIncrement = xSpriteSpacing + dataSpriteVector[0].getSprite().getGlobalBounds().width;
	auto yIncrement = ySpriteSpacing + dataSpriteVector[0].getSprite().getGlobalBounds().height;
	sf::Vector2f newPosition;
	for (int i = 0; i < rows; i++) {
		if (i > 0) {
			initialY += yIncrement;
		}
		for (int j = 1; j <= columns; j++) {
			if (j > 1) {
				initialX += xIncrement;
			}
			newPosition.x = initialX;
			newPosition.y = initialY;
			dataSpriteVector.at(i).setPosition(newPosition);
		}
	}
}
void DataSpriteVector::setAndCenterSpritePositions(int index, int rows, int columns, float xSpriteSpacing, float ySpriteSpacing, sf::RenderWindow &window) {
	auto xIncrement = xSpriteSpacing + dataSpriteVector[0].getSprite().getGlobalBounds().width;
	auto yIncrement = ySpriteSpacing + dataSpriteVector[0].getSprite().getGlobalBounds().height;
	float xPosition = window.getSize().x / 2 - xIncrement * (rows - 1) / 2;
	float yPosition = window.getSize().y / 2 - yIncrement * (columns - 1) / 2;
	sf::Vector2f newPosition;
	int num = 0;

	for (int i = 0; i < rows; i++) {
		if (i > 0) {
			yPosition += yIncrement;
			xPosition = window.getSize().x / 2 - xIncrement * (rows - 1) / 2;
		}
		for (int j = 1; j <= columns; j++) {
			if (j > 1) {
				xPosition += xIncrement;
			}
			newPosition.x = xPosition;
			newPosition.y = yPosition;
			dataSpriteVector.at(num).setPosition(newPosition);
			num++;
		}
	}
}
void DataSpriteVector::drawSprites(sf::RenderWindow &window) {
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		window.draw(dataSpriteVector[i].getSprite());	
	}
}
void DataSpriteVector::updateIndividualTexture(int index, string newTexture){
	dataSpriteVector[index].setNewTexture(newTexture);
}
void DataSpriteVector::updateVectorComplete(){
vectorComplete = true;
}
bool DataSpriteVector::getVectorComplete(){
	return vectorComplete;
}

void DataSpriteVector::setSpriteToComplete(int index){
	dataSpriteVector[index].setIsComplete(true);
}

bool DataSpriteVector::isSpriteComplete(TransformableSprite player){
	if (player.getSpriteContactIndex() < 0){
		return false;
	}else{
		return dataSpriteVector[player.getSpriteContactIndex()].getIsComplete();
	}
}

string DataSpriteVector::getLetter(int index, int itr) {
	return dataSpriteVector.at(itr).getLetter();
}
void DataSpriteVector::setLetter(int index) {
	string letters = randomizeStart_Alpha(dataSpriteVector.size());

	for (int i = 0; i < dataSpriteVector.size(); i++) {
		string tempString = (1, "");
		tempString = letters[i];
		dataSpriteVector.at(i).setLetter(tempString);
	}
}

long DataSpriteVector::getLongValues(int index, int itr) {
	return dataSpriteVector.at(itr).getLongValue();
}
void DataSpriteVector::setLongValues(int index) {
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		long randomNum = rand() * (RAND_MAX * 0.001);//more decimals, more smaller
		dataSpriteVector.at(i).setLongValue(randomNum);
	}
}

void DataSpriteVector::setStringValues(std::stringstream& stream) {//this is adding a comma to the string value from the long int 
	string outString;
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		//out.imbue(std::locale(""));
		stream << dataSpriteVector[i].getLongValue();
		outString = stream.str();
		dataSpriteVector[i].setStringValue(outString);
		stream.str("");
	}
}

string DataSpriteVector::getFullDataStrings(int index, int itr) {
	return dataSpriteVector.at(itr).getFullDataString();
}
void DataSpriteVector::setFullDataStrings(std::ostringstream& out) { 
	string outString;
	for (int i = 0; i < dataSpriteVector.size(); i++) {
		out.imbue(std::locale(""));
		out << std::put_money(dataSpriteVector[i].getLongValue());
		outString = out.str();
		dataSpriteVector[i].setFullDataString(dataSpriteVector[i].getLetter() + ":  $" + outString);
		out.str("");
	}
}