#include "utils.h"
#include "gameSprite.h"
#include "wall.h"

Player::Player(string newTexture, float movement, float rotation, float scale) {
	texture.loadFromFile(newTexture);
	circle.setRadius(texture.getSize().x * scale / 2);
	circle.setTexture(&texture);
	circle.setOrigin(texture.getSize().x / 2 * scale, texture.getSize().y / 2 * scale);
	//speed = movement;
	rotationSpeed = rotation;
}
sf::CircleShape Player::getCircle() {
	return circle;
}
void Player::setPlayerPosition(sf::Vector2f newPosition) {
	circle.setPosition(newPosition);
}
void Player::setPreviousPosition() {
	previousPosition = circle.getPosition();
}
sf::Vector2f Player::getPreviousPosition() {
	return previousPosition;
}
void Player::setPlayerSpeed(float newSpeed) {
	playerSpeed = newSpeed;
}

int Player::getSpriteContactIndex() {
	return spriteContactIndex;
}
void Player::setSpriteContactIndex(int index) {
	spriteContactIndex = index;
}
sf::Vector2f Player::getNormalAxisMinCoords() {
	return normalAxisMinCoords;
}
sf::Vector2f Player::getNormalAxisMaxCoords() {
	return normalAxisMaxCoords;
}
void Player::handlePlayerMotion() {
	if (xSpeed < speedUnit && xSpeed > - speedUnit) { xSpeed = 0; }
	if (xSpeed != 0) xSpeed = xSpeed > 0 ? xSpeed -= speedUnit : xSpeed += speedUnit;
	if (ySpeed < speedUnit && ySpeed > - speedUnit) { ySpeed = 0; }
	if (ySpeed != 0) ySpeed = ySpeed > 0 ? ySpeed -= speedUnit : ySpeed += speedUnit;
	float currentX = circle.getPosition().x + xSpeed;
	float currentY = circle.getPosition().y + ySpeed;
	circle.setPosition(currentX, currentY);
	normalAxisMinCoords = sf::Vector2f(currentX - circle.getRadius(), currentY - circle.getRadius());
	normalAxisMaxCoords = sf::Vector2f(currentX + circle.getRadius(), currentY + circle.getRadius());
}

//Player movement and screen bounds
bool Player::isAnyArrowKeyDown() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		return true;
	}
	else return false;
}
void Player::handleArrowKeyInput() {
	if (isAnyArrowKeyDown()) {
		//rotation
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circle.setRotation(circle.getRotation() + rotationSpeed);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circle.setRotation(circle.getRotation() - rotationSpeed);
		//movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) xSpeed -= playerSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  xSpeed += playerSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ySpeed -= playerSpeed;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  ySpeed += playerSpeed;
	}
	xSpeed = std::clamp(xSpeed, -4.f, 4.f);
	ySpeed = std::clamp(ySpeed, -4.f, 4.f);
}
void Player::handleScreenBoundsCollision(sf::RenderWindow& window) {
	if (circle.getPosition().x - circle.getRadius() < 0) circle.setPosition(circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().x + circle.getRadius() > window.getSize().x) circle.setPosition(window.getSize().x - circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().y - circle.getRadius() < 0) circle.setPosition(circle.getPosition().x, circle.getRadius());
	if (circle.getPosition().y + circle.getRadius() > window.getSize().y) circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius());
}
bool Player::handleWallCollision(bool isColliding) {
	if (isColliding) {
		circle.setPosition(resetPosition.x, resetPosition.y);
		xSpeed = 0;
		ySpeed = 0;
		return true;
	}
	else {
		setPreviousPosition();
		return false;
	}
}
void Player::handlePlayerMovementWithinScreen(sf::RenderWindow& window, float deltaTime, bool isColliding) {
	handleArrowKeyInput();
	handlePlayerMotion();
	handleWallCollision(isColliding);
	handleScreenBoundsCollision(window);	
	//This was used for applying force?
	//setDirectionInDegrees();
}

//Sprite Collisions
bool Player::hasSpriteCollision(sf::Sprite sprite) {
	float closestX = (circle.getPosition().x < sprite.getGlobalBounds().left ? sprite.getGlobalBounds().left : (circle.getPosition().x
	> sprite.getGlobalBounds().left + sprite.getGlobalBounds().width ? sprite.getGlobalBounds().left + sprite.getGlobalBounds().width : circle.getPosition().x));

	float closestY = (circle.getPosition().y < sprite.getGlobalBounds().top ? sprite.getGlobalBounds().top : (circle.getPosition().y
	> sprite.getGlobalBounds().top + sprite.getGlobalBounds().height ? sprite.getGlobalBounds().top + sprite.getGlobalBounds().height : circle.getPosition().y));

	float dx = closestX - circle.getPosition().x;
	float dy = closestY - circle.getPosition().y;
	return (dx * dx + dy * dy) <= circle.getRadius() * circle.getRadius();
}

//Velocity

float Player::getMass() {
	return mass;
}

//Direction
void Player::setQuadrant() {
	if (circle.getPosition().x > previousPosition.x && circle.getPosition().y < previousPosition.y
		|| circle.getPosition().x > previousPosition.x && circle.getPosition().y == previousPosition.y) {
		quadrant = 1;
	}
	else if (circle.getPosition().x < previousPosition.x && circle.getPosition().y < previousPosition.y
		|| circle.getPosition().x == previousPosition.x && circle.getPosition().y < previousPosition.y) {
		quadrant = 2;
	}
	else if (circle.getPosition().x <  previousPosition.x && circle.getPosition().y >  previousPosition.y
		|| circle.getPosition().x < previousPosition.x && circle.getPosition().y == previousPosition.y) {
		quadrant = 3;
	}
	else {
		quadrant = 4;
	}
}
//void Player::setDirectionInDegrees() {
//	calc_Dir_y = circle.getPosition().y < previousPosition.y ? previousPosition.y - circle.getPosition().y : circle.getPosition().y - previousPosition.y;
//	calc_Dir_x = circle.getPosition().x < previousPosition.x ? previousPosition.x - circle.getPosition().x : circle.getPosition().x - previousPosition.x;
//	setQuadrant();
//	direction = atan(calc_Dir_y / calc_Dir_x) * 180 / std::_Pi;
//	switch (quadrant) {
//	case 2:
//		direction = 180 - direction;
//		break;
//	case 3:
//		direction += 180;
//		break;
//	case 4:
//		direction = 360 - direction;
//		break;
//	}
//}