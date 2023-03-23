#pragma once

void loadFont(sf::Font& font);

class GameText{
	private:
		sf::Text text;//used for display
		string textString = "";//not to be mutated
		int charSize = 10; 
		bool isFull = false;
		friend class DiscussText;
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
		void setTextPosition(sf::Vector2f newPosition);
};

class DiscussText: public GameText {
	private:
		int charToShow = 0;
		vector <float> charWidths;
	public:
		using GameText::GameText;
		vector <float> getCharWidthsVector();
		void setCharWidthsVector(string newString);
		void clearCharWidthsVector();
		vector <sf::RectangleShape> setTextBlockers(vector <sf::RectangleShape> textBlockersVector);
		void drawTextBlockers(vector <sf::RectangleShape> textBlockersVector, sf::RenderWindow& window);
		void charToShowIncrementor(float discussTime, float timeRemaining, float discussSpeed, vector <sf::RectangleShape> textBlockersVector);
		sf::Color handleColor(sf::Color& color, int red, int blue, int green);
};