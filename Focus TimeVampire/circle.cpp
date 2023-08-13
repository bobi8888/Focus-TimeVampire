#include "utils.h"
#include "circle.h"

Circle::Circle(string newTexture, float movement, float rotation, float xScale, float yScale) {
	texture.loadFromFile(newTexture);
	circle.setTexture(&texture);
	circle.setScale(xScale, yScale);
	circle.setOrigin(texture.getSize().x / 2 * xScale, texture.getSize().y / 2 * yScale);
	circle.setRadius(texture.getSize().x / 2 * xScale);
	movementSpeed = movement;
	rotationSpeed = rotation;
	circle.setOutlineColor(sf::Color::Yellow);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineThickness(-4);
}
sf::CircleShape Circle::getCircle() {
	return circle;
}
void Circle::setPosition(sf::Vector2f newPosition) {
	circle.setPosition(newPosition);
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


void Circle::handlePlayerInput(sf::RenderWindow& window) {
	previousPosition = circle.getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			circle.setRotation(circle.getRotation() + rotationSpeed);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			circle.setRotation(circle.getRotation() - rotationSpeed);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			circle.setPosition(circle.getPosition().x - movementSpeed, circle.getPosition().y);
			if (circle.getPosition().x - circle.getRadius() < 0) {
				circle.setPosition(circle.getRadius(), circle.getPosition().y);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			circle.setPosition(circle.getPosition().x + movementSpeed, circle.getPosition().y);
			if (circle.getPosition().x + circle.getRadius() > window.getSize().x) {
				circle.setPosition(window.getSize().x - circle.getRadius(), circle.getPosition().y);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			circle.setPosition(circle.getPosition().x, circle.getPosition().y - movementSpeed);
			if (circle.getPosition().y - circle.getRadius() < 0) {
				circle.setPosition(circle.getPosition().x, circle.getRadius());
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			circle.setPosition(circle.getPosition().x, circle.getPosition().y + movementSpeed);
			if (circle.getPosition().y + circle.getRadius() > window.getSize().y) {
				circle.setPosition(circle.getPosition().x, window.getSize().y - circle.getRadius());
			}
		}
	}
}
void Circle::handlePlayerCollision(sf::VertexArray vertexArray) {
	if (getCircle().getGlobalBounds().intersects(vertexArray.getBounds())) {
		circle.setPosition(previousPosition);
	}
}
//void Circle::load_and_setTexture(string newTexture) {
//	texture.loadFromFile(newTexture);
//	circle.setTexture(&texture);
//}
//void Circle::setOrigin() {
//	circle.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
//}
//void Circle::setRadius() {
//	circle.setRadius(texture.getSize().x / 2);
//}