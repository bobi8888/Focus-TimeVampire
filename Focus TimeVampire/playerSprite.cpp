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
bool PlayerSprite::hasCircleContact(const sf::Sprite& sprite) {
	float a, b, c, minDist;

	minDist = getRadius() + sprite.getGlobalBounds().height / 2;
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
int PlayerSprite::getSpriteContactIndex(){
	return spriteContactIndex;
}
void PlayerSprite::setSpriteContactIndex(int itr) {
	spriteContactIndex = itr;
}
void PlayerSprite::handleSpriteContactIndex(DataSpriteVector dataSpriteVector) {
	if (getSpriteContactIndex() == -1) {
		for (int i = 0; i < dataSpriteVector.getDataSpriteVector().size(); i++) {
			if (hasCircleContact(dataSpriteVector.getDataSpriteVector()[i].getSprite())) {
				setSpriteContactIndex(i);
			}
		}
	} else if (!hasCircleContact(dataSpriteVector.getDataSpriteVector()[getSpriteContactIndex()].getSprite())) {
		setSpriteContactIndex(-1);
	}
}