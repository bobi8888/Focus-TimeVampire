#include "utils.h"
#include "wall.h"

Wall::Wall(float centerX, float centerY, float len, float hi, float ang) {
	centerPosition = sf::Vector2f(centerX, centerY);
	length = len;
	height = hi;
	scaleFactor = height / 2 / length;
	angle = ang;
	radians = angle * 0.01745329252;
	oppo = sin(radians) * length;
	adj = cos(radians) * length;
	bisectOrigin = sf::Vector2f(centerX - length /2, centerY);
	bisectEnd = sf::Vector2f(bisectOrigin.x + adj, centerY - oppo);

	zeroPosition = sf::Vector2f(bisectOrigin.x - sin(radians) * height / 2, bisectOrigin.y - cos(radians) * height / 2);
	firstPosition = sf::Vector2f(bisectEnd.x - oppo * scaleFactor, bisectEnd.y - adj * scaleFactor);
	secondPosition = sf::Vector2f(bisectEnd.x + oppo * scaleFactor, bisectEnd.y + adj * scaleFactor);
	thirdPosition = sf::Vector2f(bisectOrigin.x + sin(radians) * height / 2, bisectOrigin.y + cos(radians) * height / 2);

	sf::VertexArray newVertexArray(sf::Quads, 5);
	newVertexArray[0].position = zeroPosition;
	newVertexArray[1].position = firstPosition;
	newVertexArray[2].position = secondPosition;
	newVertexArray[3].position = thirdPosition;
	newVertexArray[4].position = zeroPosition;
	
	newVertexArray[0].color = sf::Color::Green;
	newVertexArray[1].color = sf::Color::Magenta;
	newVertexArray[2].color = sf::Color::Cyan;
	newVertexArray[3].color = sf::Color::Blue;

	vertexArray = newVertexArray;
}

sf::Vector2f Wall::getBisectOrigin() {
	return bisectOrigin;
}
float Wall::getAngle() {
	return angle;
}
float Wall::getHeight() {
	return height;
}

sf::VertexArray Wall::getVertexArray() {
	return vertexArray;
}
void Wall::setFourCorners(sf::Vector2f zero, sf::Vector2f one, sf::Vector2f two, sf::Vector2f three) {
	zeroPosition = zero;
	firstPosition = one;
	secondPosition = two;
	thirdPosition = three;
	forthPosition = zero;

	vertexArray[0].position = zero;
	vertexArray[1].position = one;
	vertexArray[2].position = two;
	vertexArray[3].position = three;
	vertexArray[4].position = zero;
}