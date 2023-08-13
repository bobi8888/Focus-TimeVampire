#include "utils.h"

#include "gameSprite.h"

GameSprite::GameSprite(string spritePNG, float x, float y) {
	sprite.setScale(x, y);
	texture.loadFromFile(spritePNG);
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}
const sf::Texture GameSprite::getTexture() {
	return texture;
}
void GameSprite::setNewTexture(string spritePNG) {
	texture.loadFromFile(spritePNG);
	sprite.setTexture(texture);
}
 sf::Sprite GameSprite::getSprite() {
	return sprite;
}
void GameSprite::setSprite(sf::Sprite& newSprite) {
	sprite = newSprite;
}
void GameSprite::setRotation(float angle) {
	sprite.setRotation(angle);
}
void GameSprite::setPosition(sf::Vector2f newPosition) {
	sprite.setPosition(newPosition);
}
bool GameSprite::getIsVisible() {
	return isVisible;
}
void GameSprite::setVisibilty(bool visibility) {
	isVisible = visibility;
}
bool GameSprite::getIsComplete() {
	return isComplete;
}
void GameSprite::setToComplete() {
	isComplete = true;
}
bool GameSprite::getCanMove(){
	return canMove;
}
void GameSprite::handleCanMove(sf::Event event, sf::Vector2f translatedMousePosition) {
	if (event.type == sf::Event::EventType::MouseButtonPressed) {
		if (getSprite().getGlobalBounds().contains(translatedMousePosition) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			canMove = true;
		}
	} else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		canMove = false;
	}
}

int GameSprite::getBoundry() {
	return boundry;
}