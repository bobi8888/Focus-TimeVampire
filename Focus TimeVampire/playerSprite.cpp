#include "utils.h"
#include "gameSprite.h"

float PlayerSprite::getMovementSpeed() {
	return movementSpeed;
}
void PlayerSprite::setMovementSpeed(float speed) {
	movementSpeed = speed;
}
float PlayerSprite::getRadius() {
	return radius;
}
void PlayerSprite::setRadius(float newRadius) {
	radius = newRadius;
}
sf::Sprite PlayerSprite::setMovement(sf::RenderWindow &window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		setRotation(getSprite().getRotation() - getMovementSpeed());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x - getMovementSpeed(), getSprite().getPosition().y));
			if (getSprite().getPosition().x - getRadius() < 0) {
				setPosition(sf::Vector2f(getRadius(), getSprite().getPosition().y));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x + getMovementSpeed(), getSprite().getPosition().y));
			if (getSprite().getPosition().x + getRadius() > window.getSize().x) {
				setPosition(sf::Vector2f(window.getSize().x - getRadius(), getSprite().getPosition().y));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y - getMovementSpeed()));
			if (getSprite().getPosition().y - getRadius() < 0) {
				setPosition(sf::Vector2f(getSprite().getPosition().x, getRadius()));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y + getMovementSpeed()));
			if (getSprite().getPosition().y + getRadius() > window.getSize().y) {
				setPosition(sf::Vector2f(getSprite().getPosition().x, window.getSize().y - getRadius()));
			}
		}
		return getSprite();
	}
}

bool PlayerSprite::hasCircleContactWithSprite(const sf::Sprite& sprite, int boundry) {
	float a, b, c, minDist;

	minDist = getRadius() + boundry + sprite.getGlobalBounds().height / 2;
	a = getSprite().getPosition().y - sprite.getPosition().y;
	if (a < 0) { a = a * -1; }
	b = getSprite().getPosition().x - sprite.getPosition().x;
	if (b < 0) { b = b * -1; }
	c = sqrt(a * a + b * b);
	if (c < minDist) {
		return hasContact = true;
	}
	else {
		return hasContact = false;
	}
}

bool PlayerSprite::intersects(PlayerSprite &player, GameSprite &wall){
	float circleDistance_x = abs(player.getSprite().getPosition().x - wall.getSprite().getPosition().x);
	float circleDistance_y = abs(player.getSprite().getPosition().y - wall.getSprite().getPosition().y);

	//left or right of wall
	if (circleDistance_x > (wall.getSprite().getGlobalBounds().width / 2 + player.getRadius())) { 
		std::cout << "1\n";
		return false; }
	//under or above wall
	if (circleDistance_y > (wall.getSprite().getGlobalBounds().height / 2 + player.getRadius())) { 
		std::cout << "2\n";
		return false; }

	if (circleDistance_x <= wall.getSprite().getGlobalBounds().width / 2) { 
		std::cout << "3\n";
		return true; }
	if (circleDistance_y <= wall.getSprite().getGlobalBounds().height / 2) { 
		std::cout << "4\n";
		return true; }
	std::cout << "test\n";
	int temp_x = circleDistance_x - wall.getSprite().getGlobalBounds().width / 2;
	int temp_y = circleDistance_y - wall.getSprite().getGlobalBounds().height / 2;
	float cornerDistance_sq = pow(temp_x,2) + pow(temp_y,2);
	std::cout << "5\n";
	return (cornerDistance_sq <= pow(player.getRadius(),2));
}

int PlayerSprite::getSpriteContactIndex(){
	return spriteContactIndex;
}
void PlayerSprite::setSpriteContactIndex(int itr) {
	spriteContactIndex = itr;
}
void PlayerSprite::handleSpriteContactIndex(DataSpriteVector dataSpriteVector, int boundry) {
	if (getSpriteContactIndex() == -1) {
		for (int i = 0; i < dataSpriteVector.getDataSpriteVector().size(); i++) {
			if (hasCircleContactWithSprite(dataSpriteVector.getDataSpriteVector()[i].getSprite(), boundry)) {
				setSpriteContactIndex(i);
			}
		}
	} else if (!hasCircleContactWithSprite(dataSpriteVector.getDataSpriteVector()[getSpriteContactIndex()].getSprite(), boundry)) {
		setSpriteContactIndex(-1);
	}
}
float PlayerSprite::getVectorSpeed() {
	return 0;
}
sf::Vector2f PlayerSprite::getVectorDirection(const sf::Sprite& acceptSprite) {
	float xForce = 0.01, yForce = 0.01;

	sf::Vector2f test ((getSprite().getPosition().x - acceptSprite.getPosition().x) * xForce + getSprite().getPosition().x
		, (getSprite().getPosition().y - acceptSprite.getPosition().y) * yForce + getSprite().getPosition().y);
	//std::cout << "x is " << test.x << " & y is " << test.y << "\n";
	return test;
}

float PlayerSprite::tangentTest(GameSprite wall) {
	float tangent, degrees;
	float abs_x = abs(getSprite().getPosition().x - wall.getSprite().getPosition().x);
	float abs_y = abs(getSprite().getPosition().y - wall.getSprite().getPosition().y);
	tangent = tan(abs_y / abs_x);
	degrees = tangent*(180/3.14);
	std::cout << degrees << "\n";
	return tangent;
}