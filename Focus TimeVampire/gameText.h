#pragma once
void loadFont(sf::Font& font);
class GameText{
	private:
		sf::Text text;//used for display
		string textString = "";//not to be mutated
		int characterSize = 10;
		float fade = 0.25, alpha = 255;
		float moveX = 0, moveY = 0.075;
		sf::Color textColor;
		bool isFull = false;
		sf::Vector2f textPosition;
		friend class DiscussText;
	public:
		GameText(){};//used in gameScreen
		GameText(string string, sf::Font& font, int charSize, sf::Color& color, sf::Vector2f position);
		sf::Text& getText();
		string getTextString();
		void setTextString(sf::String string);
		void appendTextString(sf::String string);
		void centerTextOriginOnSprite(sf::Sprite sprite,float xOffset, float yOffset);
		bool getIsFull();
		void setIsFull(bool newBool);
		void deleteLastChar();
		void setTextToMoney(std::ostringstream& out);
		void setTextOrigin();
		void setTextPosition(sf::Vector2f newPosition);
		void setString_Origin_Position(string newString, sf::Vector2f newPosition);
		void setColor(sf::Color newColor);
		void fadeText();
		void moveText();
		void handleFallingText(sf::Vector2f mousePosition);
		sf::Vector2f getTextPosition();
};

class DiscussText: public GameText {
	private:
		int charToShow = 0;
		vector <float> charWidths;
		vector <string> discussQuestions;
	public:
		using GameText::GameText;
		vector <float> getCharWidthsVector();
		void setCharWidthsVector(string newString);
		void clearCharWidthsVector();
		vector <sf::RectangleShape> resetTextBlockers(vector <sf::RectangleShape> textBlockersVector);
		void drawTextBlockers(vector <sf::RectangleShape> textBlockersVector, sf::RenderWindow& window);
		void charToShowIncrementor(float *discussTimePtr, float timeRemaining, float *discussSpeedPtr, vector <sf::RectangleShape> textBlockersVector);
		sf::Color handleColor(sf::Color& color, int redInc, int blueInc, int greenInc);
		void updateNextQuestion(string nextQuestion);
		//void setDiscussQuestions();
};