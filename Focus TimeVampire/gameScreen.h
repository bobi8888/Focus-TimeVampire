#pragma once

class GameScreen{
	private:
		vector <sf::Sprite> vectorOfSprites;
		GameText screenText;
		sf::Music gameScreenMusic;
		//bool isActive = false;
	public:
		GameScreen(string string, sf::Font& font, int charSize, sf::Vector2f titlePosition);
		void addSprite(const sf::Sprite &newSprite);
		vector <sf::Sprite> getScreenSprites();
		sf::Sprite getSpriteFromVector(int vectorPositon);
		sf::Text setAndCenterTitle(string newTitle);
		void drawScreen(sf::RenderWindow& window, const sf::Text& timerTextText);
};
