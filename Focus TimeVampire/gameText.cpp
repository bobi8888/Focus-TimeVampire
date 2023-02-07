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
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2)));
	text.setPosition(sf::Vector2f(window.getSize().x / 2, spaceFromTop));
}
sf::Text& GameText::getText() {
	return text;
}
sf::Text& GameText::setStringAndPosition(sf::String string, float x_offset, float y_offset) {
	text.setString(string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2 + x_offset
		, (text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2)) + y_offset));
	return text;
}
bool GameText::getIsFull() {
	return isFull;
}
void GameText::setIsFull(bool newBool) {
	isFull = newBool;
}
void GameText::deleteLastChar(sf::String &playerInput, std::ostringstream &out){//need to split this in 2, delete character & set new string
	if (playerInput.getSize() > 0) {
		playerInput.erase(playerInput.getSize() - 1, 1);

		out.imbue(std::locale(""));
		out << std::put_money(playerInput);
		string outString = '$' + out.str();
		//setStringAndPosition(outString, 0, -55);
		text.setString(outString);
		out.str("");
	}
}
