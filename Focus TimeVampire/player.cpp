#include "utils.h"
#include "gameSprite.h"

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

int Player::getSpriteContactIndex() {
	return spriteContactIndex;
}
void Player::setSpriteContactIndex(int index) {
	spriteContactIndex = index;
}
void Player::handlePlayerMotion() {
	if (xSpeed < 0.05 && xSpeed > -0.05) { xSpeed = 0; }
	if (xSpeed != 0) xSpeed = xSpeed > 0 ? xSpeed -= 0.05 : xSpeed += 0.05;
	if (ySpeed < 0.05 && ySpeed > -0.05) { ySpeed = 0; }
	if (ySpeed != 0) ySpeed = ySpeed > 0 ? ySpeed -= 0.05 : ySpeed += 0.05;
	circle.setPosition(circle.getPosition().x + xSpeed, circle.getPosition().y + ySpeed);
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
	xSpeed = std::clamp(xSpeed, -3.f, 3.f);
	ySpeed = std::clamp(ySpeed, -3.f, 3.f);
}
void Player::handleScreenBoundsCollision(sf::RenderWindow& window) {
	if (circle.getPosition().x - circle.getRadius() < 0) circle.setPosition(circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().x + circle.getRadius() > window.getSize().x) circle.setPosition(window.getSize().x - circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().y - circle.getRadius() < 0) circle.setPosition(circle.getPosition().x, circle.getRadius());
	if (circle.getPosition().y + circle.getRadius() > window.getSize().y) circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius());
}
void Player::handlePlayerMovementWithinScreen(sf::RenderWindow& window, float deltaTime) {
	handleScreenBoundsCollision(window);
	setPreviousPosition();
	handlePlayerMotion();
	handleArrowKeyInput();
	setDirectionInDegrees();
}

//Vertex Array Collisions
bool Player::hasVertexArrayCollision(sf::VertexArray vertexArray) {
	float closestX = (circle.getPosition().x < vertexArray.getBounds().left ? vertexArray.getBounds().left : (circle.getPosition().x
	> vertexArray.getBounds().left + vertexArray.getBounds().width ? vertexArray.getBounds().left + vertexArray.getBounds().width : circle.getPosition().x));

	float closestY = (circle.getPosition().y < vertexArray.getBounds().top ? vertexArray.getBounds().top : (circle.getPosition().y
	> vertexArray.getBounds().top + vertexArray.getBounds().height ? vertexArray.getBounds().top + vertexArray.getBounds().height : circle.getPosition().y));

	float dx = closestX - circle.getPosition().x;
	float dy = closestY - circle.getPosition().y;
	return (dx * dx + dy * dy) <= circle.getRadius() * circle.getRadius();
}
void Player::handleVertexArrayCollision(sf::VertexArray vertexArray) {
	if (hasVertexArrayCollision(vertexArray)) {
		circle.setPosition(previousPosition);
	}
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
void Player::printVeloVector(sf::Sprite sprite) {
	//this isn't printing out the motion that sprites are enacting on the player
	if (clock.getElapsedTime().asSeconds() > 1) {
		clock.restart();
		cout << "Direction is " << direction << "\n";
		velocity = sqrt(calc_Dir_x * calc_Dir_x + calc_Dir_y * calc_Dir_y);
		cout << "Velocity is " << velocity << " \n";
	}
}

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
void Player::setDirectionInDegrees() {
	calc_Dir_y = circle.getPosition().y < previousPosition.y ? previousPosition.y - circle.getPosition().y : circle.getPosition().y - previousPosition.y;
	calc_Dir_x = circle.getPosition().x < previousPosition.x ? previousPosition.x - circle.getPosition().x : circle.getPosition().x - previousPosition.x;
	
	
	setQuadrant();
	direction = atan(calc_Dir_y / calc_Dir_x) * 180 / std::_Pi;
	switch (quadrant) {
	case 2:
		direction = 180 - direction;
		break;
	case 3:
		direction += 180;
		break;
	case 4:
		direction = 360 - direction;
		break;
	}
}