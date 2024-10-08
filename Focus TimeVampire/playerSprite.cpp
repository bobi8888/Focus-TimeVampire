//#include "utils.h"
//#include "gameSprite.h"
//
//float PlayerSprite::getMovementSpeed() {
//	return movementSpeed;
//}
//void PlayerSprite::setMovementSpeed(float speed) {
//	movementSpeed = speed;
//}
//sf::Vector2f PlayerSprite::getPreviousPosition() {
//	return previousPosition;
//}
//void PlayerSprite::setPreviousPosition(sf::Vector2f currentPosition) {
//	previousPosition = currentPosition;
//}
//float PlayerSprite::getRadius() {
//	return radius;
//}
//void PlayerSprite::setRadius(float newRadius) {
//	radius = newRadius;
//}
//
//sf::CircleShape PlayerSprite::getSpriteRadiusCircle() {
//	return spriteRadiusCircle;
//}
//void PlayerSprite::initializeSpriteRadiusCircle(size_t pointcount) {
//	spriteRadiusCircle.setRadius(getRadius());
//	spriteRadiusCircle.setPointCount(pointcount);
//	spriteRadiusCircle.setOrigin(getSprite().getPosition().x, getSprite().getPosition().y);
//	spriteRadiusCircle.setPosition(getSprite().getPosition());
//	spriteRadiusCircle.setFillColor(sf::Color::Red);
//}
//
//void PlayerSprite::setSpriteRadiusCirclePosition() {
//	spriteRadiusCircle.setOrigin(getSprite().getOrigin());
//	spriteRadiusCircle.setPosition(getSprite().getPosition());
//}
//
//bool PlayerSprite::getCollision() {
//	return collision;
//}
//
//void PlayerSprite::setCollision(sf::VertexArray vertexArray) {
//	if (getSpriteRadiusCircle().getGlobalBounds().intersects(vertexArray.getBounds())) {
//		collision = true;
//	}
//	else {
//		collision = false;
//	}
//}
//
//sf::Sprite PlayerSprite::setMovement(sf::RenderWindow &window) {
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
//		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//			setRotation(getSprite().getRotation() - getMovementSpeed());
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//			setRotation(getSprite().getRotation() + getMovementSpeed());
//		}
//
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//			setPosition(sf::Vector2f(getSprite().getPosition().x - getMovementSpeed(), getSprite().getPosition().y));
//			if (getSprite().getPosition().x - getRadius() < 0) {
//				setPosition(sf::Vector2f(getRadius(), getSprite().getPosition().y));
//			}
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//			setPosition(sf::Vector2f(getSprite().getPosition().x + getMovementSpeed(), getSprite().getPosition().y));
//			if (getSprite().getPosition().x + getRadius() > window.getSize().x) {
//				setPosition(sf::Vector2f(window.getSize().x - getRadius(), getSprite().getPosition().y));
//			}
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y - getMovementSpeed()));
//			if (getSprite().getPosition().y - getRadius() < 0) {
//				setPosition(sf::Vector2f(getSprite().getPosition().x, getRadius()));
//			}
//		}
//		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//			setPosition(sf::Vector2f(getSprite().getPosition().x, getSprite().getPosition().y + getMovementSpeed()));
//			if (getSprite().getPosition().y + getRadius() > window.getSize().y) {
//				setPosition(sf::Vector2f(getSprite().getPosition().x, window.getSize().y - getRadius()));
//			}
//		}
//		return getSprite();
//	}
//}
//
//void PlayerSprite::handleCollision(sf::VertexArray vertexArray) {
//	if (!getCollision()) {
//		previousPosition = getSpriteRadiusCircle().getPosition();
//	}
//	else {
//		setPosition(getPreviousPosition());
//
//	}
//}
//
//
//int PlayerSprite::getSpriteContactIndex(){
//	return spriteContactIndex;
//}
//void PlayerSprite::setSpriteContactIndex(int itr) {
//	spriteContactIndex = itr;
//}
//void PlayerSprite::handleSpriteContactIndex(DataSpriteVector dataSpriteVector, int boundry) {
//	if (getSpriteContactIndex() == -1) {
//		for (int i = 0; i < dataSpriteVector.getDataSpriteVector().size(); i++) {
//			if (hasCircleContactWithSprite(dataSpriteVector.getDataSpriteVector()[i].getSprite(), boundry)) {
//				setSpriteContactIndex(i);
//			}
//		}
//	} else if (!hasCircleContactWithSprite(dataSpriteVector.getDataSpriteVector()[getSpriteContactIndex()].getSprite(), boundry)) {
//		setSpriteContactIndex(-1);
//	}
//}