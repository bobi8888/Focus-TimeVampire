#include <iostream>
#include <sstream>
#include <iomanip>

#include "dataSpriteVector.h"
#include "transformableSprite.h"
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
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2)));
	text.setPosition(sf::Vector2f(window.getSize().x / 2, spaceFromTop));
}
sf::String GameText::getString() {
	return text.getString();
}
void GameText::setString(string string) {
	text.setString(string);
}
sf::Text& GameText::setStringAndCenterOrigin(sf::String string, float x_offset, float y_offset) {
	text.setString(string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2 + x_offset
		, (text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2)) + y_offset));
	return text;
}

int GameText::getCharSize() {
	return text.getCharacterSize();
}
void GameText::setCharSize(int charSize) {
	text.setCharacterSize(charSize);
}

sf::Vector2f GameText::getOrigin() {
	return text.getOrigin();
}
void GameText::setOrigin(sf::Vector2f origin) {
	text.setOrigin(origin);
}
void GameText::centerOrigin() {
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2)));
}

sf::Vector2f GameText::getPosition() {
	return text.getPosition();
}
void GameText::setPosition(sf::Vector2f position) {
	text.setPosition(position);
}

void GameText::setFont(sf::Font& newFont) {
	gameTextFont = newFont;
}
sf::Text& GameText::getText() {
	return text;
}
void GameText::setFillColor(sf::Color color) {
	text.setFillColor(color);
}
bool GameText::getIsFull() {
	return isFull;
}
void GameText::setIsFull(bool newBool) {
	isFull = newBool;
}

void GameText::deleteLastChar(sf::String &playerInput, std::ostringstream &out){
	if (playerInput.getSize() > 0) {
		playerInput.erase(playerInput.getSize() - 1);
		out.imbue(std::locale(""));
		out << std::put_money(playerInput);
		string outString = '$' + out.str();
		setStringAndCenterOrigin(outString, 0, -55);
		out.str("");
	}
}

void GameText::enterLetterPrompt(int charSize, DataSpriteVector dataSpriteVector, TransformableSprite player){
	setCharSize(23);
	//letter = dataSpriteVector.getLetter(0, player.getSpriteContactIndex());
	setStringAndCenterOrigin("Enter " + dataSpriteVector.getLetter(0, player.getSpriteContactIndex()), 0, 0);
}