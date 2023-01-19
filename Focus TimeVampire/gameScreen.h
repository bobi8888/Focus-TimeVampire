#pragma once

#ifndef gameScreen_H
#define gameScreen_H

class GameScreen{
	private:
		vector <sf::Sprite> vectorOfSprites;
		GameText screenText;
	public:
		GameScreen(string string, sf::Font &font, int charSize, float titleSpaceFromTop);
		void addSprite(const sf::Sprite &newSprite);
		vector <sf::Sprite> getScreenSprites();
		sf::Sprite getSpriteFromVector(int vectorPositon);
		sf::Text setAndCenterTitle(string newTitle);
		void drawScreen(sf::RenderWindow& window, const sf::Text& timerTextText);
		friend class GameText;
};

GameScreen::GameScreen(string string, sf::Font &font, int charSize, float titleSpaceFromTop) {
	screenText.setFont(font);
	screenText.getText().setFont(font);
	screenText.setCharSize(charSize);//pass titleCHarSize as arg
	screenText.setString(string);
	screenText.setOrigin(sf::Vector2f(screenText.getText().getGlobalBounds().width / 2, screenText.getText().getCharacterSize() / 2
		+ ((screenText.getText().getCharacterSize() - screenText.getText().getGlobalBounds().height) / 2)));
	screenText.setPosition(sf::Vector2f(window.getSize().x / 2, titleSpaceFromTop));
}
void GameScreen::addSprite(const sf::Sprite& newSprite) {
	vectorOfSprites.push_back(newSprite);
}
vector <sf::Sprite> GameScreen::getScreenSprites() {
	return vectorOfSprites;
}
sf::Sprite GameScreen::getSpriteFromVector(int vectorPosition) {
	return getScreenSprites().at(vectorPosition);
}
sf::Text GameScreen::setAndCenterTitle(string newTitle) {
	screenText.setStringAndCenterOrigin(newTitle, 0, 0);
	return screenText.getText();
}
void GameScreen::drawScreen(sf::RenderWindow& window, const sf::Text& timerTextText) {
	window.draw(timerTextText);
	window.draw(screenText.getText());
	for (int i = 0; i < vectorOfSprites.size(); i++) {
		window.draw(vectorOfSprites[i]);
	}
}
#endif