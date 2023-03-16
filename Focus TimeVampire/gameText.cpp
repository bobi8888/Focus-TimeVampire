#include "utils.h"
#include "gameSprite.h"
#include "gameText.h"

void loadFont(sf::Font& font) {
	if (!font.loadFromFile("RobotoCondensed-Regular.ttf")) {
		std::cout << "Error: Font not loaded." << printf("\n");
	}
}

GameText::GameText(sf::Font &font, int characterSize, string string, float spaceFromTop, sf::RenderWindow& window) {
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setString(string);
	textString = string;
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2)));
	text.setPosition(sf::Vector2f(window.getSize().x / 2, spaceFromTop));
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
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2
	, (text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2))));
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
		textString.erase(textString.size() - 1, 1);
		text.setString(textString);
	}
}
void GameText::setTextToMoney(std::ostringstream& out) {
	out.imbue(std::locale(""));
	out << std::put_money(textString);
	string outString = '$' + out.str();
	text.setString(outString);
	out.str("");
}