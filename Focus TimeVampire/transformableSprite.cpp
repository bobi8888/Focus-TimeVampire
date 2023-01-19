#include "utils.h"

#include "gameSprite.h"
#include "dataSprite.h"
#include "dataSpriteVector.h"
#include "transformableSprite.h"

TransformableSprite::TransformableSprite(float buildSpeed, float buildRadius) {
	movementSpeed = buildSpeed;
	radius = buildRadius;
}
float TransformableSprite::getMovementSpeed() {
	return movementSpeed;
}
void TransformableSprite::setMovementSpeed(float speed) {
	movementSpeed = speed;
}
float TransformableSprite::getRadius() {
	return radius;
}
void TransformableSprite::setRadius(float newRadius) {
	radius = newRadius;
}
sf::Sprite TransformableSprite::setMovement(sf::RenderWindow &window) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		setRotation(getSprite().getRotation() - getMovementSpeed());

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x - getMovementSpeed(), getSprite().getPosition().y));
			if (getSprite().getPosition().x - getRadius() < 0) {
				setSpritePosition(sf::Vector2f(getRadius(), getSprite().getPosition().y));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x + getMovementSpeed(), getSprite().getPosition().y));
			if (getSprite().getPosition().x + getRadius() > window.getSize().x) {
				setSpritePosition(sf::Vector2f(window.getSize().x - getRadius(), getSprite().getPosition().y));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y - getMovementSpeed()));
			if (getSprite().getPosition().y - getRadius() < 0) {
				setSpritePosition(sf::Vector2f(getSprite().getPosition().x, getRadius()));
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y + getMovementSpeed()));
			if (getSprite().getPosition().y + getRadius() > window.getSize().y) {
				setSpritePosition(sf::Vector2f(getSprite().getPosition().x, window.getSize().y - getRadius()));
			}
		}
		return getSprite();
	}
}
bool TransformableSprite::hasCircleContact(sf::Sprite sprite) {
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

int TransformableSprite::getSpriteContactIndex(){
	return spriteContactIndex;
}
void TransformableSprite::setSpriteContactIndex(int itr) {
	spriteContactIndex = itr;
}

void TransformableSprite::handleSpriteContactIndex(DataSpriteVector dataSpriteVector) {
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