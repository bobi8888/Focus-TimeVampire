#include "utils.h"

#include "gameSprite.h"

GameSprite::GameSprite(){};
GameSprite::GameSprite(string spritePNG, float x, float y) {
	texture.loadFromFile(spritePNG);
	xScale = x;
	yScale = y;
	sprite.setTexture(texture);
	sprite.setScale(xScale, yScale);
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
void GameSprite::setSpritePosition(sf::Vector2f newPosition) {
	sprite.setPosition(newPosition);
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
float GameSprite::getProgress() {
	return progression;
}
void GameSprite::setProgress(float progress) {
	progression = progress;
}