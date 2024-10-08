#pragma once
#include"utils.h"
#include"gameText.h"

#include"gameScreen.h"

GameScreen::GameScreen(string string, sf::Font& font, int charSize, sf::Vector2f titlePosition) {
	screenText.getText().setFont(font);
	screenText.getText().setCharacterSize(charSize);
	screenText.getText().setString(string);
	screenText.getText().setOrigin(sf::Vector2f(screenText.getText().getGlobalBounds().width / 2, screenText.getText().getCharacterSize() / 2
		+ ((screenText.getText().getCharacterSize() - screenText.getText().getGlobalBounds().height) / 2)));
	screenText.getText().setPosition(titlePosition);
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
	screenText.setTextString(newTitle);
	return screenText.getText();
}
void GameScreen::drawScreen(sf::RenderWindow& window, const sf::Text& timerTextText) {
	window.draw(timerTextText);
	window.draw(screenText.getText());
	for (int i = 0; i < vectorOfSprites.size(); i++) {
		window.draw(vectorOfSprites[i]);
	}
}
