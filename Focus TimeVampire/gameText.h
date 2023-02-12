#pragma once

void loadFont(sf::Font& font);

class GameText{
	private:
		sf::Text text;//used for display
		string textString = "";//not to be mutated
		int charSize = 10;
		bool isFull = false;
	public:
		GameText(){};//used in gameScreen
		GameText(sf::Font &font, int characterSize, string string, float spaceFromTop, sf::RenderWindow &window);
		sf::Text& getText();
		string getTextString();
		void setTextString(sf::String string);
		void appendTextString(sf::String string);
		void centerTextOriginOnSprite(sf::Sprite sprite,float xOffset, float yOffset);
		bool getIsFull();
		void setIsFull(bool newBool);
		void deleteLastChar();
		void setTextToMoney(std::ostringstream& out);
};