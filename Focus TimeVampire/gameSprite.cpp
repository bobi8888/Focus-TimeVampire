#include "utils.h"
#include "gameSprite.h"

GameSprite::GameSprite(string spritePNG, float xScale, float yScale, sf::Vector2f spritePos, float hbSize) {
	texture.loadFromFile(spritePNG);
	sprite.setTexture(texture);
	sprite.setScale(xScale, yScale);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	hitbox.setSize(sf::Vector2f(hbSize, hbSize));
	hitbox.setOrigin(sf::Vector2f(hbSize / 2, hbSize / 2));
	sprite.setPosition(spritePos);
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
	hitbox.setPosition(newPosition);
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
void GameSprite::setGravitationalPull(bool pull) {
	if (!pull) gravitationalPull = false;
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
	if (!canMovePlayer) {
		forceX = 0;
		forceY = 0;
	}
	else {
		direction = returnQuadrantDirectionTowardsPlayerInDegrees(circle);
		distance = sqrt(calc_Dir_x * calc_Dir_x + calc_Dir_y * calc_Dir_y);
		gravitationalForce = (gravConst * mass * playerMass) / distance;
		forceY = sin(direction * std::_Pi / 180) * gravitationalForce;
		forceX = sqrt(pow(gravitationalForce, 2) - pow(forceY, 2));
		if (!gravitationalPull) {
			forceX *= -1;
			forceY *= -1;
		}
	}
	switch (quadrant) {
	case 1:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x + forceX, circle.getPosition().y - forceY);
		break;
	case 2:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x - forceX, circle.getPosition().y - forceY);
		break;
	case 3:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x - forceX, circle.getPosition().y + forceY);
		break;
	case 4:
		forceOnPlayer = sf::Vector2f(circle.getPosition().x + forceX, circle.getPosition().y + forceY);
		break;
	}
}

sf::Vector2f GameSprite::getForceOnPlayer() {
	return forceOnPlayer;
}

sf::RectangleShape GameSprite::getHitbox() {
	return hitbox;
}
void GameSprite::setCanMovePlayer(bool movePlayer) {
	canMovePlayer = movePlayer;
}
void GameSprite::setMass(double nuMass) {
	mass = nuMass;
}