#pragma once

void loadFont(sf::Font& font);

class GameText{
	private:
		sf::Text text;
		int charSize = 10;
		bool isFull = false;
	public:
		GameText(){};//used in gameScreen
		GameText(sf::Font &font, int characterSize, string string, float spaceFromTop, sf::RenderWindow &window);
		sf::Text& getText();
		sf::Text& setStringAndPosition(sf::String string, float x_offset, float y_offset);
		bool getIsFull();
		void setIsFull(bool newBool);
		void deleteLastChar(sf::String &playerInput, std::ostringstream &out);
};