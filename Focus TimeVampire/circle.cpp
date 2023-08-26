#include "utils.h"
#include "circle.h"
#include "acceptUtils.h"

Circle::Circle(string newTexture, float movement, float rotation, float scale) {
	texture.loadFromFile(newTexture);
	circle.setRadius(texture.getSize().x * scale / 2);
	circle.setTexture(&texture);
	circle.setOrigin(texture.getSize().x / 2 * scale, texture.getSize().y / 2 * scale);
	movementSpeed = movement;
	rotationSpeed = rotation;
}
sf::CircleShape Circle::getCircle() {
	return circle;
}
void Circle::setPosition(sf::Vector2f newPosition) {
	circle.setPosition(newPosition);
}
void Circle::setMovementSpeed(float movement) {
	movementSpeed = movement;
}
int Circle::getSpriteContactIndex() {
	return spriteContactIndex;
}
void Circle::setSpriteContactIndex(int index){
	spriteContactIndex = index;
}

bool Circle::isAnyArrowKeyDown() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
		return true;
}
void Circle::handlePlayerInput(sf::RenderWindow& window) {
	previousPosition = circle.getPosition();
	if (isAnyArrowKeyDown()) {
		//rotation
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circle.setRotation(circle.getRotation() + rotationSpeed);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circle.setRotation(circle.getRotation() - rotationSpeed);

		//movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) circle.setPosition(circle.getPosition().x - movementSpeed, circle.getPosition().y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) circle.setPosition(circle.getPosition().x + movementSpeed, circle.getPosition().y);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) circle.setPosition(circle.getPosition().x, circle.getPosition().y - movementSpeed);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) circle.setPosition(circle.getPosition().x, circle.getPosition().y + movementSpeed);
	}
}

bool Circle::hasVertexArrayCollision(sf::VertexArray vertexArray) {
	float closestX = (circle.getPosition().x < vertexArray.getBounds().left ? vertexArray.getBounds().left : (circle.getPosition().x
	> vertexArray.getBounds().left + vertexArray.getBounds().width ? vertexArray.getBounds().left + vertexArray.getBounds().width : circle.getPosition().x));

	float closestY = (circle.getPosition().y < vertexArray.getBounds().top ? vertexArray.getBounds().top : (circle.getPosition().y
	> vertexArray.getBounds().top + vertexArray.getBounds().height ? vertexArray.getBounds().top + vertexArray.getBounds().height : circle.getPosition().y));

	float dx = closestX - circle.getPosition().x;
	float dy = closestY - circle.getPosition().y;
	return (dx * dx + dy * dy) <= circle.getRadius() * circle.getRadius();
}
bool Circle::hasSpriteCollision(sf::Sprite sprite) {
	float closestX = (circle.getPosition().x < sprite.getGlobalBounds().left ? sprite.getGlobalBounds().left : (circle.getPosition().x
	> sprite.getGlobalBounds().left + sprite.getGlobalBounds().width ? sprite.getGlobalBounds().left + sprite.getGlobalBounds().width : circle.getPosition().x));

	float closestY = (circle.getPosition().y < sprite.getGlobalBounds().top ? sprite.getGlobalBounds().top : (circle.getPosition().y
	> sprite.getGlobalBounds().top + sprite.getGlobalBounds().height ? sprite.getGlobalBounds().top + sprite.getGlobalBounds().height : circle.getPosition().y));

	float dx = closestX - circle.getPosition().x;
	float dy = closestY - circle.getPosition().y;
	return (dx * dx + dy * dy) <= circle.getRadius() * circle.getRadius();
}
void Circle::handleScreenBoundsCollision(sf::RenderWindow& window) {
	if (circle.getPosition().x - circle.getRadius() < 0) circle.setPosition(circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().x + circle.getRadius() > window.getSize().x) circle.setPosition(window.getSize().x - circle.getRadius(), circle.getPosition().y);
	if (circle.getPosition().y - circle.getRadius() < 0) circle.setPosition(circle.getPosition().x, circle.getRadius());
	if (circle.getPosition().y + circle.getRadius() > window.getSize().y) circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius());
}
void Circle::handleVertexArrayCollision(sf::VertexArray vertexArray) {
	if (hasVertexArrayCollision(vertexArray)) {
		circle.setPosition(previousPosition);
	}
}

sf::Vector2f Circle::handleRepulsion(const sf::Sprite& acceptSprite) {
	float x = circle.getPosition().x < acceptSprite.getPosition().x ? xq_chargeOfParticle = xq_chargeOfParticle * -1 : xq_chargeOfParticle;
	float y = circle.getPosition().y < acceptSprite.getPosition().y ? yq_chargeOfParticle = yq_chargeOfParticle * -1 : yq_chargeOfParticle;

	sf::Vector2f forceVector(circle.getPosition().x, circle.getPosition().y);
	forceVector = sf::Vector2f(circle.getPosition().x + xq_chargeOfParticle, circle.getPosition().y + yq_chargeOfParticle);
	return forceVector;
}
void Circle::handlePlayerMovement(sf::RenderWindow& window, const sf::Sprite& acceptSprite) {
	handlePlayerInput(window);
	setPosition(handleRepulsion(acceptSprite));
	handleScreenBoundsCollision(window);
}

//bool PlayerSprite::hasCircleContactWithSprite(const sf::Sprite& sprite, int boundry) {
//	float a, b, c, minDist;
//
//	minDist = getRadius() + boundry + sprite.getGlobalBounds().height / 2;
//	a = getSprite().getPosition().y - sprite.getPosition().y;
//	if (a < 0) { a = a * -1; }
//	b = getSprite().getPosition().x - sprite.getPosition().x;
//	if (b < 0) { b = b * -1; }
//	c = sqrt(a * a + b * b);
//	if (c < minDist) {
//		return hasContact = true;
//	}
//	else {
//		return hasContact = false;
//	}
//}