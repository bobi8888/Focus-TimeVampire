#pragma once

using std::string;
void loadFont(sf::Font& font);

class DataSpriteVector;
class TransformableSprite;

class GameText{
	private:
		sf::Font gameTextFont;
		sf::Text text;
		int charSize = 10;
		bool isFull = false;

	public:
		GameText(){};
		GameText(sf::Font &font, int characterSize, string string, float spaceFromTop, sf::RenderWindow &window);
		void setString(string string);
		sf::Text& setStringAndCenterOrigin(sf::String string, float x_offset, float y_offset);
		sf::String getString();
		int getCharSize();
		void setCharSize(int charSize);
		sf::Vector2f getOrigin();
		void setOrigin(sf::Vector2f origin);
		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);
		void centerOrigin();
		void setFont(sf::Font &font);
		sf::Text& getText();
		void setFillColor(sf::Color color);
		bool getIsFull();
		void setIsFull(bool newBool);
		void deleteLastChar(sf::String &playerInput, std::ostringstream &out);
		void enterLetterPrompt(int charSize, DataSpriteVector dataSpriteVector, TransformableSprite player);	
};