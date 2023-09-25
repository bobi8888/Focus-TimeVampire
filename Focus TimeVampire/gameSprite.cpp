#include "utils.h"
#include "gameSprite.h"

GameSprite::GameSprite(string spritePNG, float x, float y) {
	sprite.setScale(x, y);
	texture.loadFromFile(spritePNG);
	sprite.setTexture(texture);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

void GameSprite::setNewTexture(string spritePNG) {
	texture.loadFromFile(spritePNG);
	sprite.setTexture(texture);
}
 sf::Sprite GameSprite::getSprite() {
	return sprite;
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

void GameSprite::setQuadrant(sf::CircleShape circle) {
	if (circle.getPosition().x > sprite.getPosition().x && circle.getPosition().y < sprite.getPosition().y) {
		quadrant = 1;
	}
	else if (circle.getPosition().x < sprite.getPosition().x && circle.getPosition().y < sprite.getPosition().y) {
		quadrant = 2;
	}
	else if (circle.getPosition().x < sprite.getPosition().x && circle.getPosition().y > sprite.getPosition().y) {
		quadrant = 3;
	}
	else {
		quadrant = 4;
	}
}
float GameSprite::returnQuadrantDirectionTowardsPlayerInDegrees(sf::CircleShape circle) {
	calc_Dir_y = circle.getPosition().y < sprite.getPosition().y ? sprite.getPosition().y - circle.getPosition().y : circle.getPosition().y - sprite.getPosition().y;
	calc_Dir_x = circle.getPosition().x < sprite.getPosition().x ? sprite.getPosition().x - circle.getPosition().x : circle.getPosition().x - sprite.getPosition().x;
	setQuadrant(circle);
	direction = atan(calc_Dir_y / calc_Dir_x) * 180 / std::_Pi;
	return direction;
}
void GameSprite::setForceOnPlayer(sf::CircleShape circle, float playerMass) {
	direction = returnQuadrantDirectionTowardsPlayerInDegrees(circle);
	distance = sqrt(calc_Dir_x * calc_Dir_x + calc_Dir_y * calc_Dir_y);
	gravitationalForce = (gravConst * mass * playerMass) / distance;
	float y = sin(direction * std::_Pi / 180) * gravitationalForce;
	float x = sqrt(pow(gravitationalForce, 2) - pow(y, 2));

	//swap the - & + for x & y to change from gravity pulling, to gravity pushing
	switch (quadrant) {
	case 1:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x - x, circle.getPosition().y + y);
		break;
	case 2:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x + x, circle.getPosition().y + y);
		break;
	case 3:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x + x, circle.getPosition().y - y);
		break;
	case 4:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x - x, circle.getPosition().y - y);
		break;
	}
}

sf::Vector2f GameSprite::getForceOnPlayer() {
	return forceOnPlayer;
}
