#pragma once

class GameScreen{
	private:
		vector <sf::Sprite> vectorOfSprites;
		GameText screenText;
	public:
		GameScreen(string string, sf::Font &font, int charSize, float titleSpaceFromTop, sf::RenderWindow& window);
		void addSprite(const sf::Sprite &newSprite);
		vector <sf::Sprite> getScreenSprites();
		sf::Sprite getSpriteFromVector(int vectorPositon);
		sf::Text setAndCenterTitle(string newTitle);
		void drawScreen(sf::RenderWindow& window, const sf::Text& timerTextText);
		friend class GameText;
};
