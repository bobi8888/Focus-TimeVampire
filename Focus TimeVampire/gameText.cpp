#include "utils.h"
//#include "gameSprite.h"
#include "gameText.h"
#include "window.h"
#include "ignoreUtils.h"

void loadFont(sf::Font& font) {
	if (!font.loadFromFile("RobotoCondensed-Regular.ttf")) {
		std::cout << "Error: Font not loaded." << printf("\n");
	}
}

GameText::GameText(string string, sf::Font &f, int charSize, sf::Color &color, sf::Vector2f position) {
	text.setString(string);
	textString = string;
	font = f;
	text.setFont(font);
	characterSize = charSize;
	text.setCharacterSize(characterSize);
	textColor = color;
	text.setFillColor(textColor);
	text.setOutlineColor(textColor);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2)));
	textPosition = position;
	text.setPosition(textPosition);
}
sf::Text& GameText::getText() {
	return text;
}
string GameText::getTextString(){
	return textString;
}
void GameText::setTextString(sf::String newString) {
	textString = newString;
	text.setString(textString);
}
void GameText::appendTextString(sf::String newString){
	textString += newString;
	text.setString(textString);
}
void GameText::centerTextOriginOnSprite(sf::Sprite sprite, float xOffset, float yOffset) {
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, (characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2))));
	text.setPosition(sf::Vector2f(sprite.getPosition().x + xOffset, sprite.getPosition().y + yOffset));
}
bool GameText::getIsFull() {
	return isFull;
}
void GameText::setIsFull(bool newBool) {
	isFull = newBool;
}
void GameText::deleteLastChar(){	
	if (textString.size() > 0) {
		text.setString(textString.erase(textString.size() - 1, 1));
	}
}
void GameText::setTextToMoney(std::ostringstream& out) {
	out.imbue(std::locale(""));
	out << std::put_money(textString);
	string outString = '$' + out.str();
	text.setString(outString);
	out.str("");
}
void GameText::setTextOrigin(){
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2)));
}
void GameText::setTextPosition(sf::Vector2f newPosition){
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2
		, (text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2))));
	text.setPosition(newPosition);
}
void GameText::setString_Origin_Position(string newString, sf::Vector2f newPosition){
	setTextString(newString);
	setTextOrigin();
	setTextPosition(newPosition);
}
void GameText::setColor(sf::Color newColor) {
	text.setFillColor(newColor);
}
void GameText::fadeText() {
	if (text.getFillColor().a != 0) {
		textColor.a = alpha -= fade;
		text.setFillColor(textColor);
	}
}
void GameText::moveText() {
	text.setPosition(sf::Vector2f(text.getPosition().x + moveX, text.getPosition().y + moveY));
}
void GameText::handleFallingText(sf::Vector2f mousePosition) {
	if (!text.getGlobalBounds().contains(mousePosition)) {
		fadeText();
		moveText();
	}
}
sf::Vector2f GameText::getTextPosition() {
	return textPosition;
}
void GameText::loadPrompts(int currentPrompt) {
	//i believe this is used for adding a random int to a prompt
	// this is very hard coded and inflexible...
	//, const std::optional<std::string>& randomInt_String = std::nullopt
	//if (ignorePrompt.size() > 1)
	//	ignorePrompt[1][0].insert(0, *randomInt_String + " ");
	sf::Text tempText("", font);
	tempText.setPosition(getText().getPosition());
	float postAppend = getText().getPosition().x;
	float preAppend = 0;
	float stringLength = postAppend;
	float displayLength = 0;

	//for (int i = 0; i < testStruct().ignorePromptVectors.size(); i++) {
	//	for (int j = 0; j < testStruct().ignorePromptVectors[i].size(); j++) {
	//		preAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
	//		tempText.setString(tempText.getString() + testStruct().ignorePromptVectors[i][j][0]);
	//		postAppend = tempText.getGlobalBounds().width + tempText.getPosition().x;
	//		stringLength = postAppend - preAppend;
	//		displayLength += stringLength;
	//		if (displayLength < (screenWidth - tempText.getPosition().x * 1.3)) {
	//			appendTextString(testStruct().ignorePromptVectors[currentPrompt][i][j]);
	//		}
	//		else {
	//			appendTextString("\n" + testStruct().ignorePromptVectors[currentPrompt][i][j]);
	//			displayLength = stringLength;
	//		}
	//	}
	//}
}